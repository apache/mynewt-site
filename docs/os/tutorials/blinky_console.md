## Enabling The Console and Shell for Blinky

<br>

This tutorial explains how to add the Console and Shell task to the blinky app so that you 
can interact with it over a serial line connection.

<br>

### Pre-Requisites

* Ensure you have installed [newt](../../newt/install/newt_mac.md) and that the 
newt command is in your system path. 
* You must have Internet connectivity to fetch remote Mynewt components.
* You must [install the compiler tools](../get_started/native_tools.md) to 
support native compiling to build the project this tutorial creates.  
* You must install the [Segger JLINK package]( https://www.segger.com/jlink-software.html) to 
load your project on the board.
* Cable to establish a serial USB connection between the board and the laptop

<br>

### Use an existing project

Since all we're doing is adding the shell and console capability to blinky, we assume 
that you have worked through at least some of the other tutorials, and have an existing project.
For this example, we'll be modifying the [blinky on nrf52](./nRF52.md) project to enable 
the shell and console connectivity. Feel free to use whatever version of blinky you'd like though.

<br>

### Modify the Dependencies and Configuration

The first thing you'll need to add is a few new dependencies for your app. To add shell support to 
your app make sure the following `pkg.deps` are defined in your target's pkg.yml file:

```
pkg.deps:
    - "@apache-mynewt-core/sys/console/full"
    - "@apache-mynewt-core/sys/shell"
    - "@apache-mynewt-core/sys/sysinit"
```

This lets the newt system know that it needs to pull in the code for the console and the shell.

Now we'll need to modify the settings for the app to turn on the shell, etc. by modifying the
`syscfg.yml` file for your target. (Remember, these files are in the targets/<app-name> directory.)
If there isn't a `syscfg.yml` file in your target's directory, you will need to create one.

```no-highlight
# Package: apps/bletiny

syscfg.vals:
    # Enable the shell task.
    SHELL_TASK: 1
    # Enable Console OS Ticks
    CONSOLE_TICKS: 1
    # Enable Console Prompt
    CONSOLE_PROMPT: 1 
```

### Add an Event Queue

Blinky is a small app that doesn't make use of tasks or an event queue as many other apps do, so
we'll have to modify the source for the app in order to add one. 

```c
/* System event queue task handler */
#define SYSEVQ_PRIO (1)
#define SYSEVQ_STACK_SIZE    OS_STACK_ALIGN(512)
static struct os_task task_sysevq;
os_stack_t sysevq_stack[SYSEVQ_STACK_SIZE];

/* Event queue for events handled by the system (shell, etc.) */
static struct os_eventq sys_evq;
``` 

We define a new `os_task` a task stack (`sysevq_stack`) and new system event queue 
(`sys_evq`) so that the shell and console will have an event queue to run in.

Next we go down to our `init_tasks()` function and initialize it

```c
os_task_init(&task_sysevq, "sysevq", sysevq_handler, NULL,
        SYSEVQ_PRIO, OS_WAIT_FOREVER, sysevq_stack, SYSEVQ_STACK_SIZE);
os_eventq_init(&sys_evq);
os_eventq_dflt_set(&sys_evq);
```

This will initialize the task, initialize the event queue, and then set the new event queue as
the default event queue.        

### Build targets

We're not going to build the bootloader here since we are assuming that you have already
built and loaded it during previous tutorials.

```no-highlight
$ newt build blinky
Archiving cbmem.a
Compiling crc16.c
Compiling crc8.c
Archiving crc.a
Compiling mem.c
Archiving mem.a
Linking ~/dev/myproj/bin/targets/blinky/app/apps/blinky/blinky.elf
Target successfully built: targets/blinky
```

<br>

### Create the app image

Generate a signed application image for the `blinky` target. The version number is arbitrary.

```
$ newt create-image blinky 1.0.0
App image succesfully generated: ~/dev/myproj/bin/targets/blinky/app/apps/blinky/blinky.img
```

<br>

### Load the image

Make sure the USB connector is in place and the power LED on the board is lit. Use the Power ON/OFF switch to reset the board after loading the image.

```
$ newt load blinky
```

<br>

### Set up Serial connection

You'll need a Serial connection to see the output of your program. You can reference the [Serial Port Setup](../get_started/serial_access.md) 
Tutorial for more information on setting up your serial communications.

<br>

### Connecting with your app

Once you have a connection set up, you can connect to your device with ```minicom -D /dev/tty.usbmodem<port> -b 115200``` to run connect
to the console of your app. 
    
To test and make sure that the Shell is running, first just hit <return>:
    
```no-highlight
3534: >
```

Remember, we turned the CONSOLE_PROMPT and the CONSOLE_TICKS on earlier. You can try some commands now:

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

And there you have the Console and Shell working in an app that previously had no event queue! 