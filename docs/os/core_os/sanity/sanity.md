# Sanity

The Sanity task is a software watchdog task, which runs periodically to check
system state, and ensure that everything is still operating properly.

In a typical system design, there are multiple stages of watchdog: 

* Internal Watchdog

* External Watchdog 

* Sanity Watchdog 

The _Internal Watchdog_ is a typically a MCU watchdog, which is tickled in 
the core of the OS.  The internal watchdog is tickled frequently, and is 
meant to be an indicator the OS is running.

The _External Watchdog_ is a watchdog that's typically run slower.  The 
purpose of an external watchdog is to provide the system with a hard reset
when it has lost it's mind.  

The _Sanity Watchdog_ is the least frequently run watchdog, and is meant as 
an application watchdog.  

This document is about the operation of the Mynewt Sanity Watchdog.

## Description

### Initializing the Sanity Task

The Sanity Watchdog is a task in the Mynewt OS, which when enabled, runs 
every `sanity_seconds`.  In order to enable the Sanity Watchdog task, 
call the `os_sanity_task_init()` function.

```no-highlight
int os_sanity_task_init(int sanity_seconds);
```

By default, every operating system task provides the frequency it will 
check in with the sanity task, with the `sanity_itvl` parameter in the 
`os_task_init()` function:

```no-highlight
int os_task_init(struct os_task *t, char *name, os_task_func_t func, 
    void *arg, uint8_t prio, os_time_t sanity_itvl, os_stack_t *bottom,
    uint16_t stack_size);
```

`sanity_itvl` is the time in OS time ticks that the task being created 
must register in with the sanity task.  

### Checking in with Sanity Task

The task must then register in with the sanity task every `sanity_itvl` 
seconds.  In order to do that, the task should call the `os_sanity_task_checkin`
function, which will reset the sanity check associated with this task.
Here is an example of a task that uses a callout to checkin with the 
sanity task every 50 seconds:

```no-highlight
#define TASK1_SANITY_CHECKIN_ITVL (50 * OS_TICKS_PER_SEC) 
struct os_eventq task1_evq;

static void
task1(void *arg)
{
    struct os_task *t;
    struct os_event *ev;
    struct os_callout c;
    
    /* Get current OS task */
    t = os_sched_get_current_task();

    /* Initialize the event queue. */
    os_eventq_init(&task1_evq);

    /* Initialize the callout */
    os_callout_init(&c, &task1_evq, NULL);

    /* reset the callout to checkin with the sanity task 
     * in 50 seconds to kick off timing.
     */
    os_callout_reset(&c, TASK1_SANITY_CHECKIN_ITVL);

    while (1) {
        ev = os_eventq_get(&task1_evq);

        /* The sanity timer has reset */
        if (ev->ev_arg == &c) {
            os_sanity_task_checkin(t);
        } else {
            /* not expecting any other events */
            assert(0);
        }
    }
    
    /* Should never reach */
    assert(0);
}
```

### Registering a Custom Sanity Check


If a particular task wants to further hook into the sanity framework, to 
perform other checks during the sanity task's operation, it can do so by
registering a `struct os_sanity_check` using the `os_sanity_check_register`
function.


## Data structures

Replace this with the list of data structures used, why, any neat features

## List of Functions

The functions available in sanity are:

* [os_sanity_check_init](os_sanity_check_init.md)
* [os_sanity_check_register](os_sanity_check_register.md)
* [os_sanity_check_reset](os_sanity_check_reset.md)
* [os_sanity_task_checkin](os_sanity_task_checkin.md)
* [os_sanity_task_init](os_sanity_task_init.md)
