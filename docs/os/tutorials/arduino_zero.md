# Running Mynewt on Arduino Zero

This tutorial describes how to run Mynewt OS on Arduino Zero.  

## Prerequisites

Before tackling this tutorial, it's best to read about Mynewt in the [Introduction](../get_started/introduction) section of this documentation.

## Equipment

You will need the following equipment

* An Arduino Zero board.  NOTE: There are many flavors of Arduino. Ensure that 
you have an Arduino Zero. See below for the verions of Arduino Zero that are
compatible with this tutorial
* A computer that can connect to the Arduino Zero over USB
* A USB cable (Type A to micro B) that can connect the computer to the Arduino
* The Mynewt Release

## Arduino Boards

This tutorial has been tested on the following two Arduino Zero boards.

<img src="https://www.arduino.cc/en/uploads/Main/Zero_Usb_Ports.jpg" alt="Drawing" style="width: 400px;"/>
<img src="http://www.arduino.org//images/products/ArduinoZeroPro-flat-org.jpg" alt="Drawing" style="width: 330px;"/>


## Steps

Follow these simple steps and your board will be blinking in no time!

### Install Mynewt and Newt

If you have not already done so, install Newt as shown in the [Newt install tutorial](../../newt/tutorials/newt_mac.md) and cloned the Mynewt OS repository as shown in the [Get Started tutorial for Blinky](../get_started/project1.md)

### Fetch External Packages for Atmel SAMD21

Mynewt uses source code provided directly from the chip manufacturer for 
low level operations. This code is licensed only for Atmel parts, and 
cannot live in the Apache Mynewt repository. Fetch the package from 
the runtime github repository

```no-highlight
    $ newt app add-pkg-list mynewt_arduino https://github.com/runtimeinc/mynewt_arduino_zero.git
```

Once that completes, install the arduino_zero bsp package.

```no-highlight
    $ newt pkg install hw/bsp/arduino_zero
```

### Create your bootloader Target

You need to tell Newt what you want to build.  This is done by setting up a 
target. It's easy - simply cut and paste the entire definition below.  You may have already seen how to set up a target definition one attribute (variable) at a time or by importing the entire definition in one command in this 
[Example](/newt/tutorials/define_target/) or in the [Manual](/newt/command_list/newt_target.md).

```no-highlight
    $ newt target import arduino_zero_bootloader
    @target=arduino_zero_bootloader
    name=arduino_zero_bootloader
    project=boot
    bsp=hw/bsp/arduino_zero
    compiler=arm-none-eabi-m0
    identities=arduino_zero_pro
    vers=0.0.1
    arch=cortex_m0
    compiler_def=optimized
    @endtargets
```

If your console blocks, you may need to do a `ctrl-D` to complete 
the import.

_NOTE: The identity in the target configuration above is for the Arduino 
Zero Pro board.  The BSP requires an option to specify `arduino_zero` or 
`arduino_zero_pro` target identity.  Regardless of the board you chose, 
you can leave this identity alone for this tutorial. The BSP differences 
are minor and not relevant for this tutorial._

### Create Your Image Target

You need to tell Newt what you want to build.  This is done by setting up a 
target.   You may have already seen this target definition in this 
[Example](/newt/tutorials/define_target/)

For simplicity, you can just import this target.  Just cut and paste
this into your Linux or MAC terminal from the larva directory.

```c
    $ newt target import arduino_zero_blinky 
    @target=arduino_zero_blinky 
    vers=0.0.1 
    arch=cortex_m0 
    compiler_def=debug 
    name=arduino_zero_blinky 
    bsp=hw/bsp/arduino_zero 
    compiler=arm-none-eabi-m0 
    identities=arduino_zero_pro
    project=blinky 
    @endtargets
```

If your console blocks, you may need to do a `ctrl-D` to complete 
the import.

_NOTE: The identity in the target configuration above is for the Arduino 
Zero Pro board.  The BSP requires an option to specify `arduino_zero` or 
`arduino_zero_pro` target identity.  Regardless of the board you chose, 
you can leave this identity alone for this tutorial. The BSP differences 
are minor and not relevant for this tutorial._

### Verify Your Targets

Depending on your shell you may need to do a `Ctrl-D` to terminate the import
operation. 

You can do a `newt target show` to see your results.

```c
arduino_zero_blinky
	arch=cortex_m0
	bsp=hw/bsp/arduino_zero
	compiler=arm-none-eabi-m0
	compiler_def=debug
	name=arduino_zero_blinky
	identities=arduino_zero
	project=blinky
	vers=0.0.1
arduino_zero_bootloader
	arch=cortex_m0
	bsp=hw/bsp/arduino_zero
	compiler=arm-none-eabi-m0
	compiler_def=optimized
	name=arduino_zero_bootloader
	identities=arduino_zero_pro
	project=boot
	vers=0.0.1
```

### Build the Bootloader

To Build the bootloader, use newt to do:

```c
    $ newt target build arduino_zero_bootloader
```

You should see lots of console output while newt is resolving dependencies
and compiling the source code.  After a minute, it should complete with 
the following text.

```c
    . . .
    Archiving libarduino_zero.a
    Compiling boot.c
    Building project boot
    Linking boot.elf
    Successfully run!
```
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
    $ newt target download arduino_zero_bootloader
```

The newt tool should respond with. Then 10-15 seconds later it will return a 
prompt indicating success.

```c
    Downloading with .../arduino_zero_download.sh
```

### Build the Target

To Build the target, use newt to do:

```c
    $ newt target build arduino_zero_blinky
```

You should see lots of console output while newt is resolving dependencies
and compiling the source code.  After a minute, it should complete with 
the following text.

```c
     Archiving libarduino_zero.a
    Compiling main.c
    Building project blinky
    Linking blinky.elf
    Successfully run!
```

### Build the Downloadable Image

This command attaches the image descriptor header with the specified version
number and prepares the image for download.

```c
    $ newt target create-image arduino_zero_blinky 1.2.3
```

### Download the Image

Execute the command to download the image. 

```c
    $ newt target download arduino_zero_blinky
```
The newt tool should respond with the following message. Then 10-15 seconds later it will return a prompt indicating success.
 
```c
    Downloading with .../arduino_zero_download.sh
```

### Watch the LED blink

Congratulations! You have created a Mynewt operating system running on the 
Arduino Zero. The LED right next to the power LED should be blinking. It is toggled by one task running on the Mynewt OS.   
