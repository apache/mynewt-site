
#Core OS Lesson: Tasks and Priority Management
**Target Platform: Arduino M0 Pro** (or legacy Arduino Zero or Zero Pro, but not Arduino M0)

This lesson is designed to teach core OS concepts and strategies encountered when building applications using Mynewt. Specifically, this lesson will cover tasks, simple multitasking, and priority management running on an Arduino M0 Pro.

##Prerequisites
Before starting, you should read about Mynewt in the [*Introduction*](http://mynewt.apache.org/os/introduction/) section and complete the [*QuickStart*](http://mynewt.apache.org/os/get_started/get_started/) guide and the [*Blinky*](http://mynewt.apache.org/os/tutorials/arduino_zero/) tutorial. Furthermore, it may be helpful to take a peek at the [*task documentation*](http://mynewt.apache.org/os/core_os/task/task/) for additional insights.

##Equipment
You will need the following equipment:

-   Arduino M0 Pro (or legacy Arduino Zero or Zero Pro, but not Arduino M0)
-   Computer with Mynewt installed
-   USB to Micro USB Cable

##Build Your Application
To save time, we will simply modify the Blinky app as it has the basic task structure already implemented. Follow the [*Arduino Zero Blinky tutorial*](http://mynewt.apache.org/os/tutorials/arduino_zero/) to create a new project and build your bootloader and application. Finally, build and load the application to your Arduino to verify that everything is in order. Now let’s get started!

##Create a New Task
The purpose of this section is to give an introduction to the important aspects of tasks and how to properly initialize them. First, let’s define a second task called `work_task` in main.c (located in apps/blinky/src):

```c
struct os_task work_task;
```

A task is represented by the [*os_task*](http://mynewt.apache.org/os/core_os/task/task/#data-structures)  struct which will hold the task’s information (name, state, priority, etc.). A task is made up of two main elements, a task function (also known as a task handler) and a task stack.

Next, let’s take a look at what is required to initialize our new task.

### Task Stack
The task stack is an array of type `os_stack_t` which holds the program stack frames. Mynewt gives us the ability to set the stack size for a task giving the application developer room to optimize memory usage. Since we’re not short on memory, our `blinky_stack` and `work_stack` are plenty large for the purpose of this lesson. Notice that the elements in our task stack are of type `os_stack_t` which are generally 32 bits, making our entire stack 1024 Bytes.

```c
  #define WORK_STACK_SIZE OS_STACK_ALIGN(256)
  os_stack_t work_stack[WORK_STACK_SIZE];
```


Note: The `OS_STACK_ALIGN` macro is used to align the stack based on the hardware architecture.

### Task Function
The task function is essentially an infinite loop which waits for some “event” to wake it up. In our Blinky app the task function, named `blinky_task_handler()`, is initially called when we call `os_start()` in `main()`. In general, the task function is where the majority of work is done by a task. Let’s write a task function for `work_task` called `work_task_handler()`:

```c
void
work_task_handler(void *arg)
{
    struct os_task *t;

    g_led_pin = LED_BLINK_PIN;
    hal_gpio_init_out(g_led_pin, 1);
    
    while (1) {
        t = os_sched_get_current_task();
        assert(t->t_func == work_task_handler);
        /* Do work... */
    }
}
```

The task function is called when the task is initially put into the *running* state by the scheduler. We use an infinite loop to ensure that the task function never returns. Our assertion that the current task's handler is the same as our task handler is for illustration purposes only and does not need to be in most task functions.

### Task Priority
As a preemptive, multitasking RTOS, Mynewt decides which tasks to run based on which has a higher priority; the highest priority being 0 and the lowest 255. Thus, before initializing our task, we must choose a priority defined as a macro variable.

Let’s set the priority of `work_task` to 0, because everyone knows that work is more important than blinking.
```c
  #define WORK_TASK_PRIO (0)
```

### Initialization
To initialize a new task we use [*os_task_init()*](http://mynewt.apache.org/os/core_os/task/os_task_init/) which takes a number of arguments including our new task function, stack, and priority. Much like `blinky_task`, we’re going to initialize `work_task` inside `init_tasks` to keep our main function clean.

```c
int
init_tasks(void)
{
    /* … */
    os_task_init(&work_task, "work", work_task_handler, NULL,
            WORK_TASK_PRIO, OS_WAIT_FOREVER, work_stack,
            WORK_STACK_SIZE);

    tasks_initialized = 1;
    return 0;
}
```

And that’s it! Now run your application using the newt run command.
```
$ newt run arduino_blinky 0.0.0
```
When GDB appears press C then Enter to continue and … *wait, why doesn't our LED blink anymore?*


#### Review
Before we run our new app, let’s review what we need in order to create a task. This is a general case for a new task called mytask:

 **1)**   Define a new task, task stack, and priority:
```c
/* My Task */
struct os_task mytask
/* My Task Stack */
#define MYTASK_STACK_SIZE OS_STACK_ALIGN(256)
os_stack_t mytask_stack[MYTASK_STACK_SIZE];
/* My Task Priority */
#define MYTASK_PRIO (0)
```
**2)** Define task function:
```c
void 
mytask_handler(void *arg)
{
  while (1) {
      /* ... */
  }
}
```
**3)** Initialize task before calling `os_start()`:
```c
os_task_init(&mytask, "mytask", mytask_handler, NULL, 
            MYTASK_PRIO, OS_WAIT_FOREVER, mytask_stack,
            MYTASK_STACK_SIZE);
```

##Task Priority, Preempting, and Context Switching
A preemptive RTOS is one in which a higher priority task that is *ready to run* will preempt (i.e. take the place of) the lower priority task which is *running*. When a lower priority task is preempted by a higher priority task, the lower priority task’s context data (stack pointer, registers, etc.) is saved and the new task is switched in.

In our example, `work_task` has a higher priority than `blinky_task` and, because it is never put into a *sleep* state, holds the processor focus on its context. Let’s give `work_task` a delay and some simulated work to keep it busy. Because the delay is measured in os ticks, the actual number of ticks per second is dependent on the board. Therefore, we multiply `OS_TICKS_PER_SEC`, which is defined in the MCU, by the number of seconds we wish to delay.

```c
void
work_task_handler(void *arg)
{
    struct os_task *t;

    g_led_pin = LED_BLINK_PIN;
    hal_gpio_init_out(g_led_pin, 1);

    while (1) {
        t = os_sched_get_current_t:ask();
        assert(t->t_func == work_task_handler);
        /* Do work... */
        int i;
        for(i = 0; i < 1000000; ++i) {
            /* Simulate doing a noticeable amount of work */
            hal_gpio_set(g_led_pin);
        }
        os_time_delay(3*OS_TICKS_PER_SECOND);
    }
}
```

In order to notice the LED changing, modify the time delay in `blinky_task_handler()` to blink at a higher frequency.
```c
os_time_delay(OS_TICKS_PER_SEC/10);
```
Before we run the app, let’s predict the behavior. With the newest additions to `work_task_handler()`, our first action will be to sleep for three seconds. This will allow `blinky_task` to take over the CPU and blink to its heart’s content. After three seconds, `work_task` will wake up and be made *ready to run*, causing it to preempt `blinky_task`. The LED will then remain lit for a short period while `work_task` loops, then blink again for another three seconds while `work_task` sleeps. 

Voila, you should see that our prediction was correct! 


###Priority Management Considerations
When projects grow in scope, from blinking LEDs into more sophisticated applications, the number of tasks needed increases alongside complexity. It remains important, then, that each of our tasks is capable of doing its work within a reasonable amount of time.

Some tasks, such as the Shell task, execute quickly and require almost instantaneous response. Therefore, the Shell task should be given a high priority. On the other hand, tasks which may be communicating over a network, or processing data, should be given a low priority in order to not hog the CPU.

The diagram below showcases the different scheduling patterns we. would expect from swapping blinky and work tasks priorities.

![Task Scheduling](pics/task_lesson.png)

In the second case where `blinky_task` has a higher priority, the “work” done by `work_task` would be executed during the millisecond delays in `blinky_task`, saving us idle time compared to the first case.

**Note:** Defining the same priority for two tasks leads to somewhat undefined behavior and should be avoided.

##Comparing Priority Strategies

Instead of stepping through a bunch of changes to our blinky app, clone my task lesson application from github and copy an existing target.

Change directory into apps and clone the repository to get our new
files:
```
$ cd apps
$ git clone https://github.com/bgiori/mynewt_tasks_lesson.git
```
Change directory back to your project root and copy  the arduino_blinky target to a new target called task_tgt.
```c
$ newt target copy arduino_blinky task_tgt
```
Set a new app location.
```c
$ newt target set task_tgt app=apps/mynewt_tasks_lesson
```

Now let’s take a look at our new code. First, notice that we have abandoned blinking, instead choosing to use the [*console*](http://mynewt.apache.org/latest/os/modules/console/console/) and [*shell*](http://mynewt.apache.org/latest/os/modules/shell/shell/) to follow our tasks through execution.

Additionally, we have a number of different tasks:

-   **Task A** (`a_task`):
    -   **Priority**: 3 → 2
    -   **Description**: Task A is supposed to represent a task which frequently does a small amount of work, such as one which rapidly polls a sensor for data. Much like `blinky_task`, Task A will loop 10,000 times then wait 1 millisecond. Priority is changed by `timer_task` after the first simulation.

-   **Task B** (`b_task`):
    -   **Priority**: 2 → 3
    -   **Description**: Task B is supposed to represent a task which does a large amount of work relatively infrequently, such as one which sends/receives data from the cloud. Like work\_task, Task B will loop 1,000,000 times then wait 3 seconds. Priority is changed by timer\_task after the first simulation.

-   **Timer Task** (`timer_task`):
    -   **Priority**: 1
    -   **Description**: With default settings, Timer Task will wait 20 seconds then print the first simulations data for Task A and B. Timer task will then swap A and B’s priorities and restart the simulation. After the second simulation, timer will again print simulation data then compare the two and calculate a final speedup (simulation2 / simulation1).

- **Shell Task**:
    -   **Priority**: 0
    -   **Description**: Task used by Shell behind the scenes to communicate with the serial port.

### Connecting to the Serial Console

Before running our new app, we must first connect to the serial console. First make sure the mynewt_arduino_zero repository is set to the develop branch. (Remove once changes have been moved to master). 
```
$ cd repos/mynewt_arduino_zero
$ git checkout develop
```

Open a new terminal window and list your serial connections to find our Arduino.
```c
$ ls /dev/tty.*

/dev/tty.Bluetooth-Incoming-Port /dev/tty.usbmodem14132
```

In the same window, connect to the serial port using a serial communication program. In this case I’ll be using mincom as it can scroll through output.
```c
$ minicom -D /dev/tty.usbmodem14132 -b 115200
```

If you see minicom welcome you, you’re ready to move on!

### Output Analysis

Run our new target, task_tgt, and you should see an output similar to this:

```
Starting First Simulation...
1:     Task B: 0% 
78:     Task B: 1% 
155:     Task B: 2% 
257:     Task B: 3% 
359:     Task B: 4% 
461:     Task B: 5% 

<snip>

========== Timer Expired ==========

 >>> Task A <<<
  Priority: 3
  Loop count: 162849
  Cycle count: 16.28
  Run time: 1.40 sec

 >>> Task B <<<
  Priority: 2
  Loop count: 1345852
  Cycle count: 1.34
  Run time: 17.0 sec

 Total loops: 1508709

20023:   Switching priorities and restarting...
20111:   Task A looped
20113:     Task B: 0% 
20191:     Task B: 1% 
20297:   Task A looped
20356:     Task B: 2% 
20483:   Task A looped
20545:     Task B: 3% 
20669:   Task A looped
20734:     Task B: 4% 
20855:   Task A looped
20923:     Task B: 5% 

<snip>

========== Timer Expired ==========

 >>> Task A <<<
  Priority: 2
  Loop count: 1080000
  Cycle count: 108.0
  Run time: 9.28 sec

 >>> Task B <<<
  Priority: 3
  Loop count: 830356
  Cycle count: 0.83
  Run time: 10.72 sec

 Total loops: 1910404

40058:

 Final Speedup (Sim2 / Sim1): 1.26

```

The console output reaffirms our previous prediction and makes both the scheduling differences and subsequent efficiency boost far more apparent. Let’s take a look at scheduling differences before we delve into efficiency.

In the first case, where Task B’s priority is higher than that of Task A, we see A get starved by Task B’s long execution time. **Starvation** occurs when one task hogs the processor, essentially “starving” other tasks which also need to run. At the end of the first 20 second simulation period, Task A has only run for 1.4 seconds compared to task B’s 17 second running time – ouch. As explained before, processes which are expected to run for long periods of time (e.g. network communication, data processing) should be given higher priorities in order to combat starvation.

In the second simulation with priorities swapped, we can see Task B only running during the millisecond delays when Task A is *sleeping*. Although having Task B only run during these delays slows its execution time, we benefit from un-starving Task A and using the processor at a higher efficiency.

The bottom line speedup gives us an immediate and clear indication that we have improved our ability to process work (i.e throughput). In our second run, we processed an additional 400,000 loop iterations, equating to a 26% increase in efficiency. On a standard multi-core processor found in every modern PC, a 1.26 speedup would be an ok result to adding multithreading capabilities to a serial program. However, we accomplished this by simply setting priorities on a single core processor – not bad!

NOTE: Usually the the term “speedup” is used within a parallel programming context and refers to the change in execution time between a serial and parallel program executing over the same problem. In this case we’re using the term loosely to illustrate the priority change’s effect on scheduling and throughput in our specific context.

### Efficiency Isn’t Everything

Using the processor during every OS tick isn’t always the best course of action. If we modify Task A’s delay to a tenth of a millisecond and turn off the console output, we can boost our speedup to 1.44. This, however, reduces our ability to process work from Task B who ends up only completing 18% of its work cycle after the second simulation. That would mean, at that rate, Task B would take over a minute to finish one cycle.

Feel free to play around with the testing parameters to study the different changes yourself!

##Conclusion
Moving forward, tasks are just the tip of the iceberg. The [*scheduler*](http://mynewt.apache.org/latest/os/core_os/context_switch/context_switch/), [*event queues*](http://mynewt.apache.org/latest/os/core_os/event_queue/event_queue/), [*semaphores*](http://mynewt.apache.org/latest/os/core_os/semaphore/semaphore/), and [*mutexes*](http://mynewt.apache.org/latest/os/core_os/mutex/mutex/) also add to tasks functionality, increasing our ability as the developer to control greater numbers of tasks more intricately. For example, when we switch the tasks priority, we have to tell the scheduler that our tasks priorities have changed, allowing us us to use priorities dynamically. When running multiple tasks, logging through either the built-in [*Logs*](http://mynewt.apache.org/latest/os/modules/logs/logs/) module (not covered in this lesson) or through the serial console/shell can be very useful for debugging your application. In the end, the way you manage your tasks depends on the context of your application. You should assign priorities based on execution time, urgency, and frequency, among other things.

Keep blinking and happy hacking!