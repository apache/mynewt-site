## Blinky, Your Hello World!

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) in the safe haven of a simulation. 

This tutorial will guide to achieve the following: 

1. Set up the environment on your computer to use Mynewt OS and newt tool. 
2. Download packages for building and testing the project [on a simulated target](#build-test-code-on-simulator).

** Time Requirement**: Allow yourself an hour for this project if you are relatively new to embedded systems and want to understand each step.


### What you need

1. Personal Computer with Mac OS (Mac: OS X Yosemite Version 10.10.5) or Linux box (Ubuntu 14.10: Utopic Unicorn)
2. An account on Github repository and *git* installed on your computer.
3. It assumed you already installed native tools described [here](native_tools.md)

Also, we assume that you're familiar with UNIX shells.

Let's gets started!

### Install Native and Cross Tools


See [Installing Native Tools](../get_started/native_tools.md)
 and [Installing Cross Tools](../get_started/cross_tools.md) for ARM to install
the tools needed by newt.


### Install newt tool

There are two ways to install the *newt* tool on your computer. The easy way (and the recommeded way for this project) is to download the respective *newt* binaries from the links below:
* Mac OS 
* Linux

Include the *newt* in your $PATH.

Or if you're an adventurer then you can set up the environment on your computer, install the Go language, and build the *newt* tool from source as explained in the tutorials in the Newt Tool Manual. See [Install newt from source on Mac](../../newt/newt_mac.md) and [Install newt from source on Linux](../../newt/newt_linux.md).

### Build test code on simulator 


1\. Create a new project with newt 

```no-highlight
$ newt new my_project
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in my_project...
Project my_project successfully created.
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
  
2\. Install remote dependencies for the new project 

```no-highlight
$ newt install -v 
apache-mynewt-core
Downloading repository description for apache-mynewt-core... success!
Downloading repository incubator-mynewt-core (branch: master; commit: mynewt_0_8_0_b2_tag) at https://github.com/apache/incubator-mynewt-core.git
Cloning into '/var/folders/7l/7b3w9m4n2mg3sqmgw2q1b9p80000gn/T/newt-repo969988348'...
remote: Counting objects: 17935, done.
remote: Compressing objects: 100% (234/234), done.
remote: Total 17935 (delta 101), reused 0 (delta 0), pack-reused 17686
Receiving objects: 100% (17935/17935), 6.18 MiB | 315.00 KiB/s, done.
Resolving deltas: 100% (10541/10541), done.
Checking connectivity... done.
apache-mynewt-core successfully installed version 0.7.9-none
```

3\. Next, build the packages for the sim project using the *newt* tool. You should see lots of console output while *newt* is resolving dependencies and compiling the source code.  After a minute, it should complete with 
the `Successfully run!` text.

```no-highlight
$ newt build my_blinky_sim 
Compiling main.c
Archiving blinky.a
Compiling flash_map.c
Compiling hal_flash.c
Archiving hal.a
Compiling hal_cputime.c
Compiling hal_flash.c
Compiling hal_gpio.c
Compiling hal_system.c
Compiling hal_uart.c
Archiving native.a
Compiling base64.c
<snip>
```
For extra details, specify the ```-v``` (verbose) option.

4\.  Run the blinky target, and enjoy your first successful Apache Mynewt project:

```no-highlight
$ newt run my_blinky_sim 
<snip>
Compiling cons_fmt.c
Compiling cons_tty.c
Archiving full.a
Compiling hal_bsp.c
Compiling os_bsp.c
Compiling sbrk.c
Archiving native.a
Compiling os.c
Compiling os_callout.c
Compiling os_eventq.c
Compiling os_heap.c
Compiling os_mbuf.c
Compiling os_mempool.c
Compiling os_mutex.c
Compiling os_sanity.c
Compiling os_sched.c
Compiling os_sem.c
Compiling os_task.c
Compiling os_time.c
Compiling os_arch_sim.c
Compiling os_fault.c
Assembling os_arch_stack_frame.s
Archiving os.a
Linking blinky.elf
No download script for BSP hw/bsp/native
Debugging /Users/sterling/dev/site/my_project/bin/my_blinky_sim/apps/blinky/blinky.elf
GNU gdb (GDB) 7.10.1
Copyright (C) 2015 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-apple-darwin15.2.0".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /Users/sterling/dev/site/my_project/bin/my_blinky_sim/apps/blinky/blinky.elf...Reading symbols from /Users/sterling/dev/site/my_project/bin/my_blinky_sim/apps/blinky/blinky.elf.dSYM/Contents/Resources/DWARF/blinky.elf...done.
done.
(gdb) r
```

### Conclusion

In summation, you achieved and learned a fair amount in this hands-on tutorial, all in the simulation environment.  

Now you can turn to more fun tutorials where you can get your hands dirty with actual hardware. Be bold and try the Blinky [tutorials on Olimex board](../tutorials/olimex.md).

If you see anything missing or want to send us feeback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md)

Keep on hacking and blinking!
