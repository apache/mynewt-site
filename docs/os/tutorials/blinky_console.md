##Enabling The Console and Shell for Blinky

This tutorial shows you how to add the Console and Shell to the Blinky application and interact with it over a serial line connection.
<br>

### Prerequisites

* Work through one of the Blinky Tutorials to create and build a Blinky application for one of the boards.
* Have a [serial setup](/os/get_started/serial_access.md).

<br>

### Use an Existing Project

Since all we're doing is adding the shell and console capability to blinky, we assume 
that you have worked through at least some of the other tutorials, and have an existing project.
For this example, we'll be modifying the [blinky on nrf52](./nRF52.md) project to enable 
the shell and console connectivity. You can use blinky on a different board.

<br>

###Modify the Dependencies and Configuration

Add the following dependencies to your application target's `pkg.yml` file:

```
pkg.deps:
    - "@apache-mynewt-core/sys/console/full"
    - "@apache-mynewt-core/sys/shell"
    - "@apache-mynewt-core/sys/sysinit"
```

This lets the newt system know that it needs to pull in the code for the console and the shell.

Modify the system configuration settings to enable Shell and Console ticks and prompt.  Add the following to your application target's `syscfg.yml` file:

```no-highlight

syscfg.vals:
    # Enable the shell task.
    SHELL_TASK: 1
    # Enable Console OS Ticks
    CONSOLE_TICKS: 1
    # Enable Console Prompt
    CONSOLE_PROMPT: 1 
```

<br>
### Use the OS Default Event Queue to Process Blinky Timer and Shell Events
Mynewt creates a main task that executes the application `main()` function. It also creates an OS default event queue that packages can use to queue their events.   Shell uses the OS default event queue for Shell events,  and `main()` can process the events in the context of the main task. 

Blinky's main.c is very simple. It only has a `main()` function that executes an infinite loop to toggle the LED and sleep for one second.  We will modify blinky:

* To use os_callout to generate a timer event every one second instead of sleeping.  The timer events are added to the OS default event queue.
* To process events from the OS default event queue inside the infinite loop in `main()`.

This allows the main task to process both Shell events and the timer events to toggle the LED from the OS default event queue.

<br>
### Modify main.c

Initialize a os_callout timer and move the toggle code from the while loop in `main()` to the event callback function. Add the following code above the `main()` function:

```c
/* The timer callout */
static struct os_callout blinky_callout;

/*
 * Event callback function for timer events. It toggles the led pin.
 */
static void timer_ev_cb(struct os_event *ev)
{
    assert(ev != NULL);

    ++g_task1_loops;
    hal_gpio_toggle(g_led_pin);

    os_callout_reset(&blinky_callout, OS_TICKS_PER_SEC);
}

static void init_timer(void)
{
    /*
     * Initialize the callout for a timer event.
     */
    os_callout_init(&blinky_callout, os_eventq_dflt_get(),
                    timer_ev_cb, NULL);

    os_callout_reset(&blinky_callout, OS_TICKS_PER_SEC);

}
```

In `main()`, add the call to the `init_timer()` function before the while loop and modify the while loop to process events from the OS default event queue:

```c
main(int argc, char **argv)
{

    int rc;

#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif

    sysinit();

    g_led_pin = LED_BLINK_PIN;
    hal_gpio_init_out(g_led_pin, 1);
    init_timer();
    while (1) {
        os_eventq_run(os_eventq_dflt_get());
    }
    assert(0)
    return rc;
}

```
<br>
### Build the Blinky Application Target

We're not going to build the bootloader here since we are assuming that you have already
built and loaded it during previous tutorials.

Run the `newt build nrf52_blinky` command to build the Blinky application:

```no-highlight
$ newt build nrf52_blinky

   ...

Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/nrf52_blinky/app/apps/blinky/blinky.elf
Target successfully built: targets/nrf52_blinky
```

<br>

### Sign and Create the Blinky Application Image

Run the `newt create-image nrf52_blinky 1.0.0` command to create and sign the application image. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```no-highlight
$ newt create-image nrf52_blinky 1.0.0
App image succesfully generated: ~/dev/myproj/bin/targets/nrf52_blinky/app/apps/blinky/blinky.img
```

<br>

### Load the Image

Make sure the USB connector is in place and the power LED on the board is lit. Use the Power ON/OFF switch to reset the board after loading the image.

Run the `newt load nrf52_blinky` command to load the Blinky application image onto the board.
```no-highlight
$ newt load nrf52_blinky
Loading app image into slot 1
```

<br>

### Set Up a Serial Connection

You'll need a Serial connection to see the output of your program. You can reference the [Serial Port Setup](../get_started/serial_access.md) 
Tutorial for more information on setting up your serial communication.

<br>

###Communicate with the Application

Once you have a connection set up, run ```minicom -D /dev/tty.usbserial<port> -b 115200``` to connect to the application console.
    
To test and make sure that the Shell is running, first just hit <return>:
    
```no-highlight
3534: >
```

You can try some commands:

```no-highlight
3609: > ?
Commands:
8841:     echo         ?    prompt     ticks     tasks  mempools
8843:     date         b
8844: > ticks off
 Console Ticks off
 > prompt off
 Prompt now off.
ticks on
33383: Console Ticks on

33568:
prompt on
39108: Prompt now on.
39108: >
```

