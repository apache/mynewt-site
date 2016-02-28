## Introduction

### Welcome to Apache Mynewt

Apache Mynewt is an operating system that makes it easy to develop
applications for microcontroller environments where power and cost 
are driving factors. Examples of these devices are connected locks, 
lights, and wearables.

Microcontroller environments have a number of characteristics that 
makes the operating system requirements for them unique: 

* Low memory footprint: memory on these systems range from 
8-16KB (on the low end) to 16MB (on the high end).

* Reduced code size: code often runs out of flash, and total available code size ranges from 64-128KB to 16-32MB.

* Low processing speed: processor speeds vary from 10-12MHz to 160-200MHz.  

* Low power operation: devices operate in mostly sleeping mode, in order to conserve
battery power and maximize power usage.

As more and more devices get connected, these interconnected devies perfrom complex tasks. To
perform these tasks, you need low-level operational functionality built into the operating system.
Typically, connected devices built with these microcontrollers perform a myriad of low-level tasks: 

* Networking Stacks: Bluetooth Low Energy and Thread

* Peripherals: PWM to drive motors, ADCs to measure sensor data, and RTCs
to keep time.

* Scheduled Processing: actions must happen on a calendared or periodic basis.

Apache Mynewt accomplishes all the above easily, by providing a complete
operating system for constrained devices, including:

* A fully open-source Bluetooth Low Energy stack with both Host and 
Controller implementations. 

* A pre-emptive, multi-tasking Real Time operating system kernel

* A Hardware Abstraction Layer (HAL) that abstracts the MCU's 
peripheral functions, allowing developers to easily write cross-platform
code.

### Newt ###
In order to provide all this functionality, and operate in an 
extremely low resource environment, Mynewt provides a very fine-grained source 
package management and build system tool, called *newt*. 

You can install and build *newt* for [Linux](http://mynewt.apache.org/newt/newt_linux/) or [Mac](http://mynewt.apache.org/newt/newt_mac/). 

### Build Your First Mynewt App with Newt ###

Before you start your first Mynewt application, you must first create a new Mynewt
application with the *newt* tool: 

```no-highlight
$ newt new my_app
Downloading application skeleton from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-tadpole.git... ok!
Application my_app successfully created in /Users/mynewt/dev/my_app
$ 
```

This new application contains the core of the operating system and the hardware abstraction layer, which all fits into less than 5KB of compiled code size.

Once the application is created, you can then install the packages you need, as Mynewt will automatically download them, along with their dependencies into your application.

For example, let's install a file system into the "my\_app" application.

First, we'll search for file system packages: 

```no-highlight
$ newt pkg search fs
Package list larva has package fs/nffs@0.8.0
Package list larva has package fs/fs@0.0.0
Package list larva has package project/ffs2native@0.0.0
```

Once found, you can install the nffs package (Newtron Flash File System) with *newt*:

```no-highlight
$ newt pkg install fs/nffs
Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/master... ok!
Installing fs/nffs
Installing fs/fs
Installation was a success!
```

At this point you have your first Mynewt application. And it's that simple!

Mynewt contains all the packages and reusable software components you need to develop a device using a 32-bit 
Microcontroller. And by providing a robust package management and build system, to help you build building blocks, Mynewt allows you to scale from 5KB of code size to MBs of compiled code size.

Next, try doing your first project using *newt.* In the next section, [Get Started](http://mynewt.apache.org/os/get_started/project1/), we guide you how get a LED on a target board blink. 

So get on with it!


