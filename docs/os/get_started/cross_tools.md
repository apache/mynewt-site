# Installing Cross Tools for ARM 

This page shows how to install tools on your laptop/computer to use for direct communication (e.g. for debugging) with some ARM based HW platforms running Apache Mynewt.  It shows you how to install the following tools for Mac OS X and Linux:

* ARM Cross toolchain
* Debugger to load and debug your device

<br>

## Install ARM Cross Toolchain

### Install ARM Toolchain For Mac OS X

Install the PX4 Toolchain and check the version installed. ARM maintains a
pre-built GNU toolchain with a GCC source branch targeted at Embedded ARM
Processors, namely Cortex-R/Cortex-M processor families. After installing,
ensure that the symbolic link installed by Homebrew points to the correct
version of the debugger.

```no-highlight
$ brew tap PX4/homebrew-px4
$ brew update
$ brew install gcc-arm-none-eabi-49
$ arm-none-eabi-gcc --version  
arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors) 4.9.3 20150529 (release) [ARM/embedded-4_9-branch revision 224288]
Copyright (C) 2014 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
$ ls -al /usr/local/bin/arm-none-eabi-gdb
lrwxr-xr-x  1 aditihilbert  admin  69 Sep 22 17:16 /usr/local/bin/arm-none-eabi-gdb -> /usr/local/Cellar/gcc-arm-none-eabi-49/20150609/bin/arm-none-eabi-gdb
```
**Note:** If no version is specified, brew will install the latest version
available. Mynewt OS will eventually work with multiple versions available,
including the latest releases. However, at present we have tested only with
this version and recommend it for getting started. 

<br>
### Install ARM Toolchain For Linux

On a Debian-based Linux distribution, gcc 4.9.3 for ARM can be installed with
apt-get as documented below. The steps are explained in depth at
[https://launchpad.net/~team-gcc-arm-embedded/+archive/ubuntu/ppa](https://launchpad.net/~team-gcc-arm-embedded/+archive/ubuntu/ppa).

```no-highlight
$ sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi 
$ sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
$ sudo apt-get update 
$ sudo apt-get install gcc-arm-none-eabi
$ sudo apt-get install gdb-arm-none-eabi
```
<br>
## Install Debugger 
Mynewt uses, depending on the board, either the OpenOCD or SEGGER J-Link debugger. 


### Install OpenOCD
OpenOCD (Open On-Chip Debugger) is open-source software that allows your
computer to interface with the JTAG debug connector on a variety of boards.  A
JTAG connection lets you debug and test embedded target devices. For more on
OpenOCD go to [http://openocd.org](http://openocd.org).

OpenOCD version 0.10.0 with nrf52 support is required.  A binary for this version is available to download for Mac OS and Linux.

<br>
#### Install OpenOCD on Mac OS
Step 1: Download the [binary tarball for Mac OS](https://github.com/runtimeco/openocd-binaries/raw/master/openocd-bin-0.10.0-MacOS.tgz).

Step 2: Change to the root directory: 
```no-highlight 
$cd / 
```
<br>
Step 3: Untar the tarball and install into ** /usr/local/bin**.  You will need to replace ** ~/Downloads ** with the directory that the tarball is downloaded to.  
```no-highlight
sudo tar -xf ~/Downloads/openocd-bin-0.10.0-MacOS.tgz ` 
```
<br>
Step 4: Check the OpenOCD version you are using: 

```no-highlight
$which openocd
/usr/local/bin/openocd
$openocd -v
Open On-Chip Debugger 0.10.0
Licensed under GNU GPL v2
For bug reports, read
http://openocd.org/doc/doxygen/bugs.html
```

You should see version: **0.10.0**. 

<br>
#### Install OpenOCD on Linux 
Step 1: Download the [binary tarball for Linux](https://github.com/runtimeco/openocd-binaries/raw/master/openocd-bin-0.10.0-Linux.tgz)

Step 2: Change to the root directory: 
``` 
$cd / 
```
<br>
Step 3: Untar the tarball and install into ** /usr/local/bin**.  You will need to replace ** ~/Downloads ** with the directory that the tarball is downloaded to.  

** Note:** You must specify the -p option for the tar command.

```no-highlight
$sudo tar -xpf ~/Downloads/openocd-bin-0.10.0-Linux.tgz
```
<br>
Step 4: Check the OpenOCD version you are using: 

```no-highlight
$which openocd
/usr/local/bin/openocd
$openocd -v
Open On-Chip Debugger 0.10.0
Licensed under GNU GPL v2
For bug reports, read
http://openocd.org/doc/doxygen/bugs.html
```
You should see version: **0.10.0**. 

If you see any of these error messages:

* openocd: error while loading shared libraries: libhidapi-hidraw.so.0: cannot open shared object file: No such file or directory

* openocd: error while loading shared libraries: libusb-1.0.so.0: cannot open shared object file: No such file or directory 

run the following command to install the libraries: 
```no-highlight
$sudo apt-get install libhidapi-dev:i386
```
<br>
###Install SEGGAR J-Link 
You can download and install Segger J-LINK Software and documentation pack from [SEGGER](https://www.segger.com/jlink-software.html). 
