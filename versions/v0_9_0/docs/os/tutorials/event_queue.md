## How to define a task which uses event queues to manage multiple events

### Introduction

Event queue is a mechanism by which you can serialize incoming events for your task. You can use it to get info about arrived hardware interrupts, callout expirations and messages from other tasks.

The benefit of doing inter-task communication this way is that there should be less resources that need to be locked.

The benefit of doing interrupt processing in a task context instead of inside an interrupt context is that you are not blocking other HW interrupts when doing the work. The same goes for high priority tasks in the system; they're blocked until the interrupt handler returns. From the task context you'll also be able to access other OS facilities; you can sleep while waiting for a lock, for example.

<br>

### Example app

Here you are going to write an app which demonstrates the use of event queues for communication between tasks. You will  also use OS callouts for timer expiration and another event from a GPIO interrupt.

You will  use inputs from 3 sources to toggle 3 GPIO outputs on my STM32F3discovery board.

<br>

#### Create project

You start by creating a project and populating it with repositories incubator-mynewt-core and mynewt_stm32f3. See [STM32F3 tutorial](STM32F303.md) if you need help with this. You can also read the tutorial on [Additional Repositories](repo/add_repos.md) for a more thorough understanding. 

<br> 

#### Create application

Here's what the pkg.yml looks for the application.

```no-highlight
[marko@IsMyLaptop:~/src/events]$ cat apps/event_sample/pkg.yml
pkg.name: apps/event_sample
pkg.type: app

pkg.deps:
    - "@apache-mynewt-core/libs/os"
    - "@apache-mynewt-core/hw/hal"
    - "@apache-mynewt-core/libs/console/stub"
```

<br>

#### Initialize the event queue structure

This must be done before anyone tries to place events to the queue. Here it's done before any task gets created. Initialization is done by calling *os_eventq_init()*.

```c
#define MY_TASK_PRIO		4
#define MY_TASK_STACK_SZ	512
    
static struct os_eventq my_eventq;
static os_stack_t my_task_stack[MY_TASK_STACK_SZ];
static struct os_task my_task_str;

void
init_tasks(void)
{
	struct os_task taskid;

	os_eventq_init(&my_eventq);
	os_task_init(&my_task_str, "task", my_task, NULL, MY_TASK_PRIO,
	    OS_WAIT_FOREVER, my_task_stack, MY_TASK_STACK_SZ);

```

<br>

#### Processing events

Here event processing is done inside *my_task*. The main loop of the task is pulling events from the queue, and then taking action. We look at the type of the event to figure out what to do.

The code snippet shows what the main loop of the event handler looks like. Events are removed from the head of the queue using os_eventq_get

```c
void
my_task(void *arg)
{
	struct os_event *ev;

	while (1) {
		ev = os_eventq_get(&my_eventq);
		switch (ev->ev_type) {
		/* more event types here */
		default:
			assert(0);
		}
	}
}
```

<br>

#### Event types

You can define your own event types. Some numbers are already reserved by the OS, so you should not use those as your own types.

Reserved event types are defined in *libs/os/include/os/os_eventq.h*. One example of a reserved type is OS_EVENT_T_TIMER, which is used as type in OS callouts.

You should start your event numbers from *OS_EVENT_T_PERUSER*, and go higher.

You are going to generate events from GPIO interrupt handler, from another task as well as from a callout. OS callout already has a type, but you'll need to define types for the other uses.

```c
#define MY_TASK_GPIO_EVENT	(OS_EVENT_T_PERUSER)
#define MY_TASK_TASK_EVENT	(OS_EVENT_T_PERUSER + 1)
```

<br>

#### Posting events from another task

Events are posted to a queue by calling *os_eventq_put()*. You need to preallocate memory for the event structure. Here it's done by declaring the event structure as a global variable.

Note that you can call *os_eventq_put()* with an event which has already been queued. In that case, the call has no effect; the position of the event is not changed within the queue.

In the code snippet we declare the os_event structure, and initialize it. We also create the event generating task, and periodically post event to the event queue.

```c
#define GEN_TASK_PRIO		3
#define GEN_TASK_STACK_SZ	512
    
static struct os_event gen_task_ev;
static os_stack_t gen_task_stack[GEN_TASK_STACK_SZ];
static struct os_task gen_task_str;
    
void
gen_task(void *arg)
{
	while (1) {
		os_time_delay(OS_TICKS_PER_SEC / 4);
		os_eventq_put(&my_eventq, &gen_task_ev);
	}
}
    
void
init_tasks(void)
{
	/* .... */
	gen_task_ev.ev_type = MY_TASK_TASK_EVENT;
	os_task_init(&gen_task_str, "gen_task", gen_task, NULL, GEN_TASK_PRIO,
	    OS_WAIT_FOREVER, gen_task_stack, GEN_TASK_STACK_SZ);
}
```

<br>

#### Callout events

You can get timer events delivered to your task's event queue with OS callout. Check [callout documentation](../core_os/callout/callout.md) for description on how to use the API.

For this example, you'll use only one type of callout; so you can use the simpler structure.

In the code snippet we declare the os_callout structure and initialize it. Then we arm the timer.

```c
static struct os_callout my_callout;

void
init_tasks(void)
{
	/* .... */

	os_callout_init(&my_callout, &my_eventq, NULL);
	os_callout_reset(&my_callout, OS_TICKS_PER_SEC);
}

```

<br>


#### Posting events from interrupt handler

Another place where posting events makes sense is from an interrupt handler. In this tutorial you will do it when GPIO changes state.

You'll use HAL GPIO interface to register a routine which is getting called from the interrupt handler context. This routine will then post event to your queue.

On STM32F3Discovery board, there is a button connected to PA0. The identifier for this GPIO pin is 0.

```c
static struct os_event gpio_ev;

void
init_tasks(void)
{
	/* .... */

	gpio_ev.ev_type = MY_TASK_GPIO_EVENT;
	hal_gpio_irq_init(0, my_gpio_irq, NULL, GPIO_TRIG_RISING,
	    GPIO_PULL_NONE);
	hal_gpio_irq_enable(0);
}

static void
my_gpio_irq(void *arg)
{
	os_eventq_put(&my_eventq, &gpio_ev);
}
```

<br>

#### Event processing finalized

Now that you are posting events from different sources, you will fill in the parts in the task main loop to trigger different behaviors depending on event type.

You'll drive different LEDs depending on what type of event arrived. LEDs on this board are connected to PE8, PE9, PE10 and so on. These have GPIO identifiers starting from 72 onwards.

```c
#define TASK_LED		72
#define CALLOUT_LED		73
#define GPIO_LED		74

void
init_tasks(void)
{
	/* .... */
	hal_gpio_init_out(TASK_LED, 1);
	hal_gpio_init_out(CALLOUT_LED, 1);
	hal_gpio_init_out(GPIO_LED, 1);
}
```

And here is the new main loop for your task. Note that when callout event arrives, we re-arm the callout.

```c
void
my_task(void *arg)
{
	struct os_event *ev;
    
	while (1) {
		ev = os_eventq_get(&my_eventq);
		switch (ev->ev_type) {
		case MY_TASK_TASK_EVENT:
			hal_gpio_toggle(TASK_LED);
			break;
		case OS_EVENT_T_TIMER:
			hal_gpio_toggle(CALLOUT_LED);
			os_callout_reset(&my_callout, OS_TICKS_PER_SEC / 2);
			break;
		case MY_TASK_GPIO_EVENT:
			hal_gpio_toggle(GPIO_LED);
			break;
		default:
			assert(0);
		}
	}
}
```

<br>

Now you're done. Once you load this to your board, the task LED will blink at an interval of 250ms, the callout LED with an interval of 500ms, and the GPIO LED every time you press the button.

<br>

### Code for the example

```c
#include <os/os.h>
#include <bsp/bsp.h>
#include <hal/hal_gpio.h>
#include <assert.h>


#define MY_TASK_PRIO		4
#define MY_TASK_STACK_SZ	512

#define GEN_TASK_PRIO		3
#define GEN_TASK_STACK_SZ	512

#define MY_TASK_GPIO_EVENT	(OS_EVENT_T_PERUSER)
#define MY_TASK_TASK_EVENT	(OS_EVENT_T_PERUSER + 1)

#define TASK_LED		72
#define CALLOUT_LED		73
#define GPIO_LED		74

static struct os_eventq my_eventq;
static os_stack_t my_task_stack[MY_TASK_STACK_SZ];
static struct os_task my_task_str;

static struct os_event gen_task_ev;
static os_stack_t gen_task_stack[GEN_TASK_STACK_SZ];
static struct os_task gen_task_str;

static struct os_callout my_callout;

static struct os_event gpio_ev;

void
my_task(void *arg)
{
	struct os_event *ev;

	while (1) {
		ev = os_eventq_get(&my_eventq);
		switch (ev->ev_type) {
		case MY_TASK_TASK_EVENT:
			hal_gpio_toggle(TASK_LED);
			break;
		case OS_EVENT_T_TIMER:
			hal_gpio_toggle(CALLOUT_LED);
			os_callout_reset(&my_callout, OS_TICKS_PER_SEC / 2);
			break;
		case MY_TASK_GPIO_EVENT:
			hal_gpio_toggle(GPIO_LED);
			break;
		default:
			assert(0);
		}
	}
}

static void
my_gpio_irq(void *arg)
{
	os_eventq_put(&my_eventq, &gpio_ev);
}

void
gen_task(void *arg)
{
	while (1) {
		os_time_delay(OS_TICKS_PER_SEC / 4);
		os_eventq_put(&my_eventq, &gen_task_ev);
	}
}

void
init_tasks(void)
{
	os_eventq_init(&my_eventq);
	os_task_init(&my_task_str, "task", my_task, NULL, MY_TASK_PRIO,
	    OS_WAIT_FOREVER, my_task_stack, MY_TASK_STACK_SZ);

	gen_task_ev.ev_type = MY_TASK_TASK_EVENT;
	os_task_init(&gen_task_str, "gen_task", gen_task, NULL, GEN_TASK_PRIO,
	    OS_WAIT_FOREVER, gen_task_stack, GEN_TASK_STACK_SZ);

	os_callout_init(&my_callout, &my_eventq, NULL);
	os_callout_reset(&my_callout, OS_TICKS_PER_SEC);

	gpio_ev.ev_type = MY_TASK_GPIO_EVENT;
	hal_gpio_irq_init(0, my_gpio_irq, NULL, GPIO_TRIG_RISING,
	    GPIO_PULL_NONE);
	hal_gpio_irq_enable(0);

	hal_gpio_init_out(TASK_LED, 1);
	hal_gpio_init_out(CALLOUT_LED, 1);
	hal_gpio_init_out(GPIO_LED, 1);
}

int
main(int argc, char **argv)
{
	os_init();

	init_tasks();
	os_start();
	assert(0);
	return 0;
}

```
