# Running Mynewt on Arduino Zero

This tutorial describes how to run Mynewt OS on Arduino Zero.  

## Prerequisites

Before tackling this tutorial, its best to read about Mynewt in the 
[Introduction](../get_started/introduction) section of this documentation.

## Equipment

You will need the following equipment

* An Arduino Zero board.  NOTE: There are many flavors of Arduino. Ensure that 
you have an arduino Zero.  
* A computer that can connect to the Arduino Zero over USB
* A USB cable (Type A to micro B) that can connect the computer to the Arduino
* The Mynewt Release

## Steps

Follow these simple steps and you be blinking in no time.

### Install Mynewt and Newt

If you have not already done so, install Newt, Mynewt and other
prerequisites as shown [here](ugh)

### Fetch External Packages for Atmel SAMD21

Mynewt uses source code provided directly from the chip manufacturer for 
low level operations. This code is licensed only for Atmel parts, and 
cannot live in the Apache Mynewt repository. Fetch the package from 
the runtime github repository

```no-highlight
newt app add-pkg-list mynewt_arduino https://github.com/runtimeinc/mynewt_arduino_zero.git
```

Once that completes install the arduino_zero bsp package

```no-highlight
newt pkg install hw/bsp/arduino_zero
```

### Create your bootloader Target

You need to tell Newt what you want to build.  This is done by setting up a 
target.   You may have already seen this target definition in this 
[Example](/newt/tutorials/define_target/)

```no-highlight
newt target import arduino_zero_bootloader
@target=arduino_zero_bootloader
name=arduino_zero_bootloader
project=boot
bsp=hw/bsp/arduino_zero
compiler=arm-none-eabi-m0
vers=0.0.1
arch=cortex_m0
compiler_def=optimized
@endtargets
```

If your console blocks, you may need to do a `ctrl-D` to complete 
the import.

### Create Your Image Target

You need to tell Newt what you want to build.  This is done by setting up a 
target.   You may have already seen this target definition in this 
[Example](/newt/tutorials/define_target/)

For simplicity, you can just import this target.  Just cut and paste
this into your Linux or MAC terminal from the larva directory.

```no-highlight
newt target import arduino_zero_blinky 
@target=arduino_zero_blinky 
vers=0.0.1 
arch=cortex_m0 
compiler_def=debug 
name=arduino_zero_blinky 
bsp=hw/bsp/arduino_zero 
compiler=arm-none-eabi-m0 
project=blinky 
@endtargets
```

If your console blocks, you may need to do a `ctrl-D` to complete 
the import.

### Verify Your Targets

Depending on your shell you may need to do a `Ctrl-D` to terminate the import
operation. 

You can do a `newt target show` to see your results.

```no-highlight
arduino_zero_blinky
	arch=cortex_m0
	bsp=hw/bsp/arduino_zero
	compiler=arm-none-eabi-m0
	compiler_def=debug
	name=arduino_zero_blinky
	project=blinky
	vers=0.0.1
arduino_zero_bootloader
	arch=cortex_m0
	bsp=hw/bsp/arduino_zero
	compiler=arm-none-eabi-m0
	compiler_def=optimized
	name=arduino_zero_bootloader
	project=boot
	vers=0.0.1
```

### Build the Bootloader

To Build the bootloader, use newt to do:

```no-highlight
newt target build arduino_zero_bootloader
```

You should see lots of console output while newt is resolving dependencies
and compiling the source code.  After a minute, it should complete with 
the following text.

```no-highlight
. . .
Archiving libarduino_zero.a
Compiling boot.c
Building project boot
Linking boot.elf
Successfully run!
```
### Connect the Target

Connect your computer to the Arduino Zero (from now on we'll call this the 
target) with the Micro-USB cable through the Programming Port. Mynewt will
download and debug the target through this port.

No external debugger is required.  The Arduino Zero comes with an internal
debugger that can be accessed by Mynewt.

A image below shows the Arduino Zero Programming Port.

<img src="https://www.arduino.cc/en/uploads/Main/Zero_Usb_Ports.jpg" alt="Drawing" style="width: 400px;"/>

### Download the Bootloader

Execute the command to download the bootloader. 

```no-highlight
newt target download arduino_zero_bootloader
```

The newt tool should respond with. Then 10-15 seconds later it will return a 
prompt indicating success.

```no-highlight
Downloading with .../arduino_zero_download.sh
```

### Build the Target

To Build the target, use newt to do:

```no-highlight
newt target build arduino_zero_blinky
```

You should see lots of console output while newt is resolving dependencies
and compiling the source code.  After a minute, it should complete with 
the following text.

```no-highlight
Archiving libarduino_zero.a
Compiling main.c
Building project blinky
Linking blinky.elf
Successfully run!
```

### Build the Downloadable Image

This command attaches the image descriptor header with the specicifed version
number and prepares the image for download.

```no-highlight
newt target create-image arduino_zero_blinky 1.2.3
```

### Download the Image

Execute the command to download the image. 

```no-highlight
newt target download arduino_zero_blinky
```
The newt tool should respond with. Then 10-15 seconds later it will return a 
prompt indicating success.
 
```no-highlight
Downloading with .../arduino_zero_download.sh
```

### Watch the LED blink

Congratulations!. You have create a Mynewt operating system running on the 
Arduino Zero. The LED is toggled by one task running on the Mynewt OS.   
