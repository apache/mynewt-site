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

As more and more devices get connected, these interconnected devices perform complex tasks. To
perform these tasks, you need low-level operational functionality built into the operating system.
Typically, connected devices built with these microcontrollers perform a myriad of functions: 

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

### Build your first Mynewt App with Newt ###

Before you start your first Mynewt application, you must first create a new Mynewt
project with the *newt* tool: 

```no-highlight
$ newt new my_project
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in my_app...
Project my_app successfully created.
```

Newt populates this new project with a base skeleton of a new Apache Mynewt 
project.  It has the following structure:

```no-highlight 
$ cd my_project
$ tree -L 3
.
├── DISCLAIMER
├── LICENSE
├── NOTICE
├── README.md
├── apps
│   └── blinky
│       ├── pkg.yml
│       └── src
├── project.yml
└── targets
    ├── my_blinky_sim
    │   ├── pkg.yml
    │   └── target.yml
    └── unittest
        ├── pkg.yml
        └── target.yml

6 directories, 10 files
$ 
```

Once you've switched into your new project's directory, the next step is to fetch
any dependencies this project has.  By default, all Newt projects rely on a single
remote repository, apache-mynewt-core.  Newt install will fetch this locally:

```no-highlight
$ newt install
apache-mynewt-core
$
```

*NOTE:* ```apache-mynewt-core``` may take a while to download, to see progress, use
the ```-v``` (verbose) option to install. 


Once ```newt install``` has successfully finished, the contents of ```apache-mynewt-core```
will have been downloaded into your local directory.  You can view them by issuing the 
following commands in the base directory of the new project:

```no-highlight
$ cd repos/apache-mynewt-core
$ tree -L2
.
<snip>
├── fs
│   ├── fs
│   └── nffs
├── hw
│   ├── bsp
│   ├── hal
│   └── mcu
├── libs
│   ├── baselibc
│   ├── bootutil
│   ├── cmsis-core
│   ├── console
│   ├── elua
│   ├── flash_test
│   ├── imgmgr
│   ├── json
│   ├── mbedtls
│   ├── newtmgr
│   ├── os
│   ├── shell
│   ├── testreport
│   ├── testutil
│   └── util
├── net
│   └── nimble
<snip>
```

As you can see, the core of the Apache Mynewt operating system has been brought 
into your local directory!  

New projects created with Newt, come with by default an example application 
(```apps/blinky```) and an example target (```my_blinky_sim```) which allows you to 
build that application for the simulated platform.  

With your new project, all you need to build and run your new application is to 
issue the following commands: 

```no-highlight
$ newt build my_blinky_sim 
Compiling base64.c
Compiling cbmem.c
Compiling datetime.c
Compiling tpq.c
Archiving util.a
Compiling main.c
Archiving blinky.a
Compiling flash_map.c
Compiling hal_flash.c
Archiving hal.a
Compiling cons_fmt.c
Compiling cons_tty.c
<snip>
Linking blinky.elf
App successfully built: /Users/sterling/dev/tmp/my_app/bin/my_blinky_sim/apps/blinky/blinky.elf
$ newt run my_blinky_sim
(runs target my_blinky_sim on the simulator)
```

At this point you have your first Mynewt application!

Apache Mynewt has a lot more functionality than just running simulated applications.  It provides all 
the features you'll need to cross-compile your application, run it on real hardware and develop a 
full featured application.

If you're interested in learning more, a good next step is to choose a project to 
[Get Started](http://mynewt.apache.org/os/get_started/project1/) with, and begin to familiarize 
yourself with operating within the newt environment.  These projects will get your toolchain installed, 
and get you blinking an LED with the Apache Mynewt OS.

After you've tried a few getting started projects, there are plenty of tutorials that will help 
expose you to much of the functionality provided by the Apache Mynewt Core Operating System.   There is 
also full reference documentation for all of the Core Apache Mynewt APIs.

Happy Hacking!


