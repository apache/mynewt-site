##Enabling The Console and Shell in a project

<br>

This tutorial explains how to add the Console and Shell task to a project so that you 
can interact with your project over a serial line connection.

<br>

### Prerequisites
Ensure that you have met the following prerequisites before continuing with this tutorial:

* Have Internet connectivity to fetch remote Mynewt components.  
* Have a cable to establish a serial USB connection between the board and the laptop
* Install the newt tool and toolchains (See [Basic Setup](/os/get_started/get_started.md)).
* Install the [Segger JLINK package]( https://www.segger.com/jlink-software.html) to load your project on the board.

<br>

### Use an existing project

Since all we're doing is adding the shell and console capability to a project, we assume 
that you have worked through at least some of the other tutorials, and have an existing project.
For this example, we'll be modifying the [ble_tiny](bletiny_project.md) project to enable 
the shell and console connectivity. We'll be calling our app myble as in that project as well. 
Feel free to use whatever project you'd like though.

<br>

###Modify the Dependencies and Configuration

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

### Build targets

We're not going to build the bootloader here since we are assuming that you have already
built and loaded it during previous tutorials.

```no-highlight
$ newt build myble
Archiving cbmem.a
Compiling crc16.c
Compiling crc8.c
Archiving crc.a
Compiling mem.c
Archiving mem.a
Linking ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.elf
Target successfully built: targets/myble
```

<br>

### Create the app image

Generate a signed application image for the `myble` target. The version number is arbitrary.

```
$ newt create-image myble 1.0.0
App image succesfully generated: ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.img
```

<br>

### Load the image

Make sure the USB connector is in place and the power LED on the board is lit. Use the Power ON/OFF switch to reset the board after loading the image.

```
$ newt load myble
```

<br>

### Set up Serial connection

You'll need a Serial connection to see the output of your program. You can reference the [Serial Port Setup](../get_started/serial_access.md) 
Tutorial for more information on setting up your serial communications.

<br>

###Connecting with your app

Once you have a connection set up, you can connect to your device as follows: 

* On Mac OS and Linux platforms, you can run ```minicom -D /dev/tty.usbserial-<port> -b 115200``` to connect to the console of your app. Note that on Linux, the format of the port name is `/dev/ttyUSB<N>`, where N is a number. 

* On Windows, you can use a terminal application such as PuTTY to connect to the device.  
	
	If you located your port from a MinGW terminal,  the port name format is `/dev/ttyS<N>`, where `N` is a number. You must map the port name to a Windows COM port: `/dev/ttyS<N>` maps to `COM<N+1>`. For example, `/dev/ttyS2` maps to  `COM3`. 
	
	You can also use the Windows Device Manager to locate the COM port.

<br>
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

