# Task

A task, along with the scheduler, forms the basis of the Mynewt OS. A task 
consists of two basic elements: a task stack and a task function. The task 
function is basically a forever loop, waiting for some "event" to wake it up. 
There are two methods used to signal a task that it has work to do: event queues 
and semaphores (see the appropriate manual sections for descriptions of these 
features).
 
The Mynewt OS is a multi-tasking, preemptive OS. Every task is assigned a task 
priority (from 0 to 255), with 0 being the highest priority task. If a higher 
priority task than the current task wants to run, the scheduler preempts the 
currently running task and switches context to the higher priority task. This is 
just a fancy way of saying that the processor stack pointer now points to the 
stack of the higher priority task and the task resumes execution where it left 
off.

Tasks run to completion unless they are preempted by a higher priority task. The 
developer must insure that tasks eventually "sleep"; otherwise lower priority 
tasks will never get a chance to run (actually, any task lower in priority than 
the task that never sleeps). A task will be put to sleep in the following cases: 
it puts itself to sleep using `os_time_delay()`, it waits on an event queue 
which is empty or attempts to obtain a mutex or a semaphore that is currently 
owned by another task.
 
Note that other sections of the manual describe these OS features in more 
detail.

## Description

In order to create a task two data structures need to be defined: the task 
object (struct os_task) and its associated stack. Determining the stack size can 
be a bit tricky; generally developers should not declare large local variables 
on the stack so that task stacks can be of limited size. However, all 
applications are different and the developer must choose the stack size 
accordingly. NOTE: be careful when declaring your stack! The stack is in units 
of `os_stack_t` sized elements (generally 32-bits). Looking at the example given 
below and assuming `os_stack_t` is defined to be a 32-bit unsigned value, 
"my_task_stack" will use 256 bytes. 
 
A task must also have an associated "task function". This is the function that 
will be called when the task is first run. This task function should never 
return!
 
In order to inform the Mynewt OS of the new task and to have it added to the 
scheduler, the `os_task_init()` function is called. Once `os_task_init()` is 
called, the task is made ready to run and is added to the active task list. Note 
that a task can be initialized (started) before or after the os has started 
(i.e. before `os_start()` is called) but must be initialized after the os has 
been initialized (i.e. 'os_init' has been called). In most of the examples and 
current Mynewt projects, the os is initialized, tasks are initialized, and the 
the os is started. Once the os has started, the highest priority task will be 
the first task set to run.
 
Information about a task can be obtained using the `os_task_info_get_next()` 
API. Developers can walk the list of tasks to obtain information on all created 
tasks. This information is of type `os_task_info` and is described below.

The following is a very simple example showing a single application task. This 
task simply toggles an LED at a one second interval.
 
```c 
/* Create a simple "project" with a task that blinks a LED every second */

/* Define task stack and task object */
#define MY_TASK_PRI         (OS_TASK_PRI_HIGHEST) 
#define MY_STACK_SIZE       (64) 
struct os_task my_task; 
os_stack_t my_task_stack[MY_STACK_SIZE]; 

/* This is the task function */
void my_task_func(void *arg) {
    /* Set the led pin as an output */
    hal_gpio_init_out(LED_BLINK_PIN, 1);

    /* The task is a forever loop that does not return */
    while (1) {
        /* Wait one second */ 
        os_time_delay(1000);

        /* Toggle the LED */ 
        hal_gpio_toggle(LED_BLINK_PIN);
    }
}

/* This is the main function for the project */
int main(void) {
    int rc;

    /* Initialize OS */
    os_init();

    /* Initialize the task */
    os_task_init(&my_task, "my_task", my_task_func, NULL, MY_TASK_PRIO, 
                 OS_WAIT_FOREVER, my_task_stack, MY_STACK_SIZE);

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);

    return rc;
}
``` 

## Data structures

```c
/* The highest and lowest task priorities */
#define OS_TASK_PRI_HIGHEST         (0)
#define OS_TASK_PRI_LOWEST          (0xff)

/* Task states */
typedef enum os_task_state {
    OS_TASK_READY = 1, 
    OS_TASK_SLEEP = 2
} os_task_state_t;

/* Task flags */
#define OS_TASK_FLAG_NO_TIMEOUT     (0x0001U)
#define OS_TASK_FLAG_SEM_WAIT       (0x0002U)
#define OS_TASK_FLAG_MUTEX_WAIT     (0x0004U)

typedef void (*os_task_func_t)(void *);

#define OS_TASK_MAX_NAME_LEN (32)
```
<br>
```c
struct os_task {
    os_stack_t *t_stackptr;
    os_stack_t *t_stacktop;

    uint16_t t_stacksize;
    uint16_t t_flags;

    uint8_t t_taskid;
    uint8_t t_prio;
    uint8_t t_state;
    uint8_t t_pad;

    char *t_name;
    os_task_func_t t_func;
    void *t_arg;

    void *t_obj;

    struct os_sanity_check t_sanity_check; 

    os_time_t t_next_wakeup;
    os_time_t t_run_time;
    uint32_t t_ctx_sw_cnt;

    /* Global list of all tasks, irrespective of run or sleep lists */
    STAILQ_ENTRY(os_task) t_os_task_list;

    /* Used to chain task to either the run or sleep list */ 
    TAILQ_ENTRY(os_task) t_os_list;

    /* Used to chain task to an object such as a semaphore or mutex */
    SLIST_ENTRY(os_task) t_obj_list;
};
```

| **Element** | **Description** |
|-----------|-------------|
| t_stackptr | Current stack pointer |
| t_stacktop | The address of the top of the task stack. The stack grows downward |
| t_stacksize | The size of the stack, in units of os_stack_t (not bytes!)  |
| t_flags | Task flags (see flag definitions)  |
| t_taskid | A numeric id assigned to each task  |
| t_prio | The priority of the task. The lower the number, the higher the priority  |
| t_state | The task state (see state definitions)  |
| t_pad | padding (for alignment)  |
| t_name | Name of task  |
| t_func | Pointer to task function  |
| t_obj | Generic object used by mutexes and semaphores when the task is waiting on a mutex or semaphore
| t_sanity_check | Sanity task data structure |
| t_next_wakeup | OS time when task is next scheduled to wake up |
| t_run_time | The amount of os time ticks this task has been running |
| t_ctx_sw_cnt | The number of times that this task has been run |
| t_os_task_list | List pointer for global task list. All tasks are placed on this list |
| t_os_list | List pointer used by either the active task list or the sleeping task list | 
| t_obj_list | List pointer for tasks waiting on a semaphore or mutex |

<br>
```c
struct os_task_info {
    uint8_t oti_prio;
    uint8_t oti_taskid;
    uint8_t oti_state;
    uint8_t oti_flags;
    uint16_t oti_stkusage;
    uint16_t oti_stksize;
    uint32_t oti_cswcnt;
    uint32_t oti_runtime;
    os_time_t oti_last_checkin;
    os_time_t oti_next_checkin;

    char oti_name[OS_TASK_MAX_NAME_LEN];
};
```

| **Element** | **Description** |
|-----------|-------------|
| oti_prio | Task priority |
| oti_taskid | Task id |
| oti_state | Task state |
| oti_flags | Task flags |
| oti_stkusage | Amount of stack used by the task (in os_stack_t units) |
| oti_stksize | The size of the stack (in os_stack_t units) |
| oti_cswcnt | The context switch count |
| oti_runtime | The amount of time that the task has run (in os time ticks) |
| oti_last_checkin | The time (os time) at which this task last checked in to the sanity task |
| oti_next_checkin | The time (os time) at which this task last checked in to the sanity task |
| oti_name | Name of the task |

<br>
## List of Functions

The functions available in task are:
| **Function** | **Description** |
|-----------|-------------|
| [os_task_init](os_task_init.md) | Called to create a task. This adds the task object to the list of ready to run tasks. |
| [os_task_count](os_task_count.md) | Returns the number of tasks that have been created. |
| [os_task_info_get_next](os_task_info_get_next.md) | Populates the os task info structure given with task information. |
