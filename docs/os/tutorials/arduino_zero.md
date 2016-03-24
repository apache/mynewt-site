## Running Mynewt on Arduino Zero

This tutorial describes how to run Mynewt OS on Arduino Zero.  

### Prerequisites

Before tackling this tutorial, it's best to read about Mynewt in the [Introduction](../get_started/introduction) section of this documentation.

### Equipment

You will need the following equipment

* An Arduino Zero board.  NOTE: There are many flavors of Arduino. Ensure that 
you have an Arduino Zero. See below for the verions of Arduino Zero that are
compatible with this tutorial
* A computer that can connect to the Arduino Zero over USB
* A USB cable (Type A to micro B) that can connect the computer to the Arduino
* The Mynewt Release

### Arduino Boards

This tutorial has been tested on the following two Arduino Zero boards.

<img src="https://www.arduino.cc/en/uploads/Main/Zero_Usb_Ports.jpg" alt="Drawing" style="width: 400px;"/>
<img src="http://www.arduino.org//images/products/ArduinoZeroPro-flat-org.jpg" alt="Drawing" style="width: 330px;"/>


### Steps

Follow these simple steps and your board will be blinking in no time!

#### Install Mynewt and Newt

If you have not already done so, install Newt as shown in the [Newt install tutorial](../../newt/install/newt_mac.md) and cloned the Mynewt OS repository as shown in the [Get Started tutorial for Sim Blinky](../get_started/project_create.md)

### Fetch External Packages for Atmel SAMD21

Mynewt uses source code provided directly from the chip manufacturer for 
low level operations. This code is licensed only for Atmel parts, and 
cannot live in the Apache Mynewt repository. Fetch the package from 
the runtime github repository.

To fetch the package from the runtime git repository, you need to add 
the repository to the ```project.yml``` file in your base project directory.

Here is an example ```project.yml``` file with the Arduino Zero repository
added. The lines to be added are highlighted.

```hl_lines="6 14 15 16 17 18"
$ more project.yml 
project.name: "my_project"

project.repositories:
    - apache-mynewt-core
    - mynewt_arduino_zero

repository.apache-mynewt-core:
    type: github
    vers: 0-latest
    user: apache
    repo: incubator-mynewt-core

repository.mynewt_arduino_zero:
    type: github
    vers: 0-latest
    user: runtimeinc
    repo: mynewt_arduino_zero
$ 
```

In the above, the sections with ```mynewt_arduino_zero``` need to be added to 
your project file.

Once you've edited your ```project.yml``` file, the next step is to install the 
project dependencies, this can be done with the ```newt install``` command 
(to see more output, provide the ```-v``` verbose option.): 

```no-highlight
$ newt install 
apache-mynewt-core
mynewt_arduino_zero
$
```

### Create your bootloader Target

Next, you need to tell Newt what to build.  For the Arduino Zero, we are going to 
generate both a bootloader, and an image target.

To generate the bootloader target, you need to specify the following options:

```no-highlight
$ newt target create arduino_boot 
Target targets/arduino_boot successfully created
$ newt target set arduino_boot bsp=@mynewt_arduino_zero/hw/bsp/arduino_zero 
Target targets/arduino_boot successfully set target.bsp to @mynewt_arduino_zero/hw/bsp/arduino_zero
$ newt target set arduino_boot app=@apache-mynewt-core/apps/boot 
Target targets/arduino_boot successfully set target.app to @apache-mynewt-core/apps/boot
$ newt target set arduino_boot build_profile=optimized
Target targets/arduino_boot successfully set target.build_profile to optimized
$ newt target set arduino_boot features=arduino_zero_pro 
Target targets/arduino_boot successfully set pkg.features to arduino_zero_pro
```

These commands do a few things: 

  * Create a target named ```arduino_boot```, in order to build the Arduino Zero Bootloader.
  * Set the application for the ```arduino_boot``` target to the default Apache Mynewt 
    bootloader (```@apache-mynewt-core/apps/boot```)
  * Set the board support package for the target to 
    ```@mynewt_arduino_zero/hw/bsp/arduino_zero```.  This is a reference to the downloaded 
    Arduino Zero support from Github.
  * Use the "optimized" build profile for the ```arduino_boot``` target.  This
    instructs Newt to generate smaller and more efficient code for this target.
    This setting is necessary due to the bootloader's strict size constraints.
  * Tells the Board Support Package to enable support for the Arduino Zero Pro, and not 
    the Arduino Zero.  This is done through setting a build feature.  If you are building 
    for an Arduino Zero, and not a Zero Pro, this feature should be set to ```arduino_zero```.

Once you've configured the bootloader target, the next step is to build the bootloader for
your Arduino, you can do this by using the ```newt build``` command:

```no-highlight
$ newt build arduino_boot 
Compiling asprintf.c
Compiling atoi.c
Compiling atol.c
Compiling atoll.c
Compiling bsearch.c
Compiling bzero.c
Compiling calloc.c
Compiling fgets.c
Compiling inline.c
<snip>
App successfully built: myproject/bin/arduino_boot/apps/boot/boot.elf
```

If this command finishes successfully, you have successfully built the Arduino 
bootloader, and the next step is to build your application for the Arduino 
board.

To create and download your application, you create another target, this one pointing
to the application you want to download to the Arduino board.  In this tutorial, 
we will use the default application that comes with your project, ```apps/blinky```:

```no-highlight
$ newt target create arduino_blinky 
Target targets/arduino_blinky successfully created
$ newt target set arduino_blinky app=apps/blinky 
Target targets/arduino_blinky successfully set target.app to apps/blinky
$ newt target set arduino_blinky bsp=@mynewt_arduino_zero/hw/bsp/arduino_zero
Target targets/arduino_blinky successfully set target.bsp to @mynewt_arduino_zero/hw/bsp/arduino_zero
$ newt target set arduino_blinky build_profile=debug 
Target targets/arduino_blinky successfully set target.build_profile to debug
$ newt target set arduino_blinky features=arduino_zero_pro 
Target targets/arduino_blinky successfully set pkg.features to arduino_zero_pro
$ 
```

You can now build the target, with ```newt build```: 

```no-highlight
$ newt build arduino_blinky 
Compiling main.c
Archiving blinky.a
Compiling cons_fmt.c
Compiling cons_tty.c
Archiving full.a
Compiling case.c
Compiling suite.c
Compiling testutil.c
Archiving testutil.a
<snip>
App successfully built: myproject/bin/arduino_blinky/apps/blinky/blinky.elf
```

Congratulations!  You have successfully built your application, now it's 
time to load the bootloader and application onto the target.

### Connect the Target

Connect your computer to the Arduino Zero (from now on we'll call this the 
target) with the Micro-USB cable through the Programming Port as shown below. 
Mynewt will download and debug the target through this port. You should see a 
little green LED come on. That means the board has power.

No external debugger is required.  The Arduino Zero comes with an internal
debugger that can be accessed by Mynewt.

A image below shows the Arduino Zero Programming Port.

<img src="https://www.arduino.cc/en/uploads/Main/Zero_Usb_Ports.jpg" alt="Drawing" style="width: 400px;"/>
<img src="http://www.arduino.org//images/products/ArduinoZeroPro-flat-org.jpg" alt="Drawing" style="width: 330px;"/>

### Download the Bootloader

Execute the command to download the bootloader. 

```c
    $ newt load arduino_boot
```

If the newt tool finishes without error, that means the bootloader has been 
successfully loaded onto the target.


### Run the Image 

Now that the bootloader is downloaded to the target, the next step is to load 
your image onto the Arduino Zero.  The easiest way to do this, is to use the 
```newt run``` command.  ```newt run``` will automatically rebuild your program
(if necessary), create an image, and load it onto the target device.

Here, we will load our ```arduino_blinky``` target onto the device, and we 
should see it run:

```no-highlight
$ newt run arduino_blinky 0.0.0 
Debugging myproject/bin/arduino_blinky/apps/blinky/blinky.elf
Open On-Chip Debugger 0.9.0 (2015-09-23-21:46)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : only one transport option; autoselect 'swd'
adapter speed: 500 kHz
adapter_nsrst_delay: 100
cortex_m reset_config sysresetreq
Info : CMSIS-DAP: SWD  Supported
Info : CMSIS-DAP: JTAG Supported
Info : CMSIS-DAP: Interface Initialised (SWD)
Info : CMSIS-DAP: FW Version = 01.1F.0118
Info : SWCLK/TCK = 1 SWDIO/TMS = 1 TDI = 1 TDO = 1 nTRST = 0 nRESET = 1
Info : CMSIS-DAP: Interface ready
Info : clock speed 500 kHz
Info : SWD IDCODE 0x0bc11477
Info : at91samd21g18.cpu: hardware has 4 breakpoints, 2 watchpoints
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from myproject/bin/arduino_blinky/apps/blinky/blinky.elf...done.
target state: halted
target halted due to debug-request, current mode: Thread 
xPSR: 0x21000000 pc: 0x0000030e msp: 0x20008000
Info : accepting 'gdb' connection on tcp/3333
Info : SAMD MCU: SAMD21G18A (256KB Flash, 32KB RAM)
0x0000030e in ?? ()
(gdb) r
The "remote" target does not support "run".  Try "help target" or "continue".
(gdb) c
Continuing.
```

*NOTE:* The 0.0.0 specified after the target name to newt run, is the version 
of the image to load.  If you are not providing remote upgrade, and are just 
developing locally, you can provide 0.0.0 for every image version.

If you want the image to run without the debugger connected, simply quit the 
debugger and restart the board.  The image you programmed will come and run on the 
Arduino on next boot!  

### Watch the LED blink

Congratulations! You have created a Mynewt operating system running on the 
Arduino Zero. The LED right next to the power LED should be blinking. It is toggled by one task running on the Mynewt OS.   
