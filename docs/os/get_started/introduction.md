## Introduction

### Welcome to Apache Mynewt

Apache Mynewt is an Operating System that makes it easy to develop
applications for Microcontroller environments where power and cost 
are driving factors.  Examples of these devices are connected locks, 
lights, and wearables.

Microcontroller environments have a number of characteristics that 
makes the operating system requirements for them unique: 

* Low memory footprint: memory on these systems is anywhere from 
8-16KB on the low end to 16MB on the high end.

* Reduced code size: code often runs out of flash, and total 
available code size ranges from 64-128KB up to 16-32MB.

* Low processing speed: processor speeds are anywhere from 10-12MHz
up to 160-200MHz.  

* Low power operation: due to battery requirements, devices have to 
operate in mostly sleeping mode in order to achieve battery 
requirements.

However, with more and more devices getting connected, the complexity
of these systems is increasing.  Typically, products built around 
these microcontrollers have to deal with a number of tasks: 

* Networking Stacks: Bluetooth Low Energy and Thread

* Peripherals: PWM to drive motors, ADCs to measure sensor data, RTCs
to keep time.

* Scheduled Processing: actions must happen on a calendared or 
periodic basis.

Apache Mynewt makes it easy to accomplish this, by providing a complete
Operating System for constrained devices, including:

* A fully open-source Bluetooth Low Energy stack with both Host and 
Controller implementations. 

* A pre-emptive, multi-tasking Real Time operating system kernel

* A Hardware Abstraction Layer (HAL) that abstracts the MCU's 
peripheral functions, allowing developers to easily write cross-platform
code.


In order to provide all this functionality, and operate in an extremely 
low resource environment, Mynewt provides a very fine-grained source 
package management and build system, called Newt.

When you start your Mynewt application, you first create a new 
application with the newt tool: 

```no-highlight
$ newt new my_app
Downloading application skeleton from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-tadpole.git... ok!
Application my_app successfully created in /Users/mynewt/dev/my_app
$ 
```

This new application contains the core of the operating system, 
and the HW abstraction layer.  All of this fits into less than 5KB 
of compiled code size.

Once the application is created, you can then install the packages
you need, and Mynewt will automatically download them, and their 
dependencies into your application.

As an example, let's install a file system into the "my\_app" application.
First, we'll search for file system packages: 

```no-highlight
$ newt pkg search fs
Package list larva has package fs/nffs@0.8.0
Package list larva has package fs/fs@0.0.0
Package list larva has package project/ffs2native@0.0.0
```

We can then install the nffs package (Newtron Flash File System), using
newt: 

```no-highlight
$ newt pkg install fs/nffs
Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/master... ok!
Installing fs/nffs
Installing fs/fs
Installation was a success!
```

And it's that simple!  Mynewt contains all the packages and reusable
software components you need to develop a device using a 32-bit 
Microcontroller.  And by providing a robust package management and 
build system, Mynewt allows you to scale from 5KB of code size, all 
the way to MBs of compiled code size.


