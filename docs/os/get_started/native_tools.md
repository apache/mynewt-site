# Installing Native Mynewt Tools

This page shows how to install tools for native Mynewt targets (simulated targets on your laptop/computer) without using a Docker container. In other words, it allows you to run Mynewt OS as a native application on your Mac or Linux machine to simulate a target and use the Newt tool running natively on your machine to manage the simulated target. It also allows you to run the test suites for all packages not requiring HW support. You may choose to do this instead of using the build toolchain and Newt tool available in a Docker container.

This page provides guidance for MAC and Linux. See the relevant sections below.

<br>

## Set up toolchain for Mac

### Install Brew

If you have not already installed Homebrew from the 
[`newt` tutorials pages](../../newt/install/newt_mac.md), install it. 

<br>

###Install gcc/libc 

OS X ships with a C compiler called Clang.  To build applications for the Mynewt simulator, you will need a different compiler: gcc.

```no-highlight
$ brew install gcc
...
...
==> Summary
🍺  /usr/local/Cellar/gcc/5.2.0: 1353 files, 248M
```

<br>

###Install gdb 

```no-highlight
$ brew install gdb
...
...
==> Summary
🍺  /usr/local/Cellar/gdb/7.10.1: XXX files,YYM
```

<br>

**NOTE:** When running a program with gdb, you may need to sign your gdb
executable.  [This page](https://gcc.gnu.org/onlinedocs/gnat_ugn/Codesigning-the-Debugger.html)
shows a recipe for gdb signing. Alternately you can skip this step and
continue without the ability to debug your mynewt application on your PC.*

<br>

## Set up toolchain for Linux 

The below procedure can be used to set up a Debian-based Linux system (e.g.,
Ubuntu).  If you are running a different Linux distribution, you will need to
substitute invocations of _apt-get_ in the below steps with the package manager
that your distro uses.

<br>

###Install gcc/libc that will produce 32-bit executables: 
```no-highlight
$ sudo apt-get install gcc-multilib libc6-i386
``` 

<br>
       
###Install gdb 

```no-highlight
$ sudo apt-get install gdb

Reading package lists... Done
Building dependency tree       
Reading state information... Done
Suggested packages:
  gdb-doc gdbserver
The following NEW packages will be installed:
  gdb
...
Processing triggers for man-db (2.6.7.1-1ubuntu1) ...
Setting up gdb (7.7.1-0ubuntu5~14.04.2) ...

```

<br>

At this point you have installed all the necessary software to build and test code on a simluator running on your Mac or Linux. Proceed to the [Build test code on simulator](#build-test-code-on-simulator) section.
