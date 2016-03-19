# Installing Cross Tools for ARM 

This page shows how to install tools to use some ARM based platforms with
Apache Mynewt.

<br>

## Install ARM Cross tools in Mac OS X

### Install Tool Chain

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

### Install OpenOCD
    
OpenOCD (Open On-Chip Debugger) is open-source software that allows your
computer to interface with the JTAG debug connector on a variety of boards.  A
JTAG connection lets you debug and test embedded target devices. For more on
OpenOCD go to [http://openocd.org](http://openocd.org).

Currently, only OpenOCD 0.8.0 is supported.

```no-highlight
$ brew install open-ocd
$ which openocd
/usr/local/bin/openocd
$ ls -l $(which openocd)
lrwxr-xr-x  1 <user>  admin  36 Sep 17 16:22 /usr/local/bin/openocd -> ../Cellar/open-ocd/0.8.0/bin/openocd
```

<br>

## Install ARM cross arm tools for Linux

### Install Tool Chain

On a Debian-based Linux distribution, gcc 4.9.3 for ARM can be installed with
apt-get as documented below. The steps are explained in depth at
[https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded](https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded).

```no-highlight
$ sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi 
$ sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded 
$ sudo apt-get update 
$ sudo apt-get install gcc-arm-none-eabi
```

<br>

###Install OpenOCD

OpenOCD (Open On-Chip Debugger) is open-source software that allows your
computer to interface with the JTAG debug connector on a variety of boards.  A
JTAG connection lets you debug and test embedded target devices. For more on
OpenOCD go to [http://openocd.org](http://openocd.org).

If you are running Ubuntu 15.x, then you are in luck and you can simply run: 
```no-highlight
$ sudo apt-get install openocd 
```
 For this project, you should download the openocd 0.8.0 package from
[https://launchpad.net/ubuntu/vivid/+source/openocd](https://launchpad.net/ubuntu/vivid/+source/openocd).
The direct link to the amd64 build is
[http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb](http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb). 
