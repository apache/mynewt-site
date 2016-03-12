# Installing Native Mynewt Tools

This page shows how to install tools for native Mynewt targets. This
allows you to run Mynewt OS as a native application.  It also allows
you to run the test suites for all packages not requiring HW support. 

This page provides guidance for MAC and Linux. See the relevant sections below.

## Set up toolchain for Mac

### Install Brew

if you have not already installed Homebrew from the 
[`newt` tutorials pages](../../newt/newt_mac.md). 

###Install gcc/libc 

Use brew to install gcc.

```no-highlight
        $ brew install gcc
        ...
        ...
        ==> Summary
        🍺  /usr/local/Cellar/gcc/5.2.0: 1353 files, 248M
```

###Install gdb 

```no-highlight
        $ brew install gdb
        ...
        ...
        ==> Summary
        🍺  /usr/local/Cellar/gdb/7.10.1: XXX files,YYM
```

_NOTE: When running a program with gdb, you may need to sign your gdb
executable.  [This page](https://gcc.gnu.org/onlinedocs/gnat_ugn/Codesigning-the-Debugger.html)
shows a recipe for gdb signing. Alternately you can skip this step and
continue without the ability to debug your mynewt application on your PC._

## Set up toolchain for Linux 

###Install gcc/libc that will produce 32-bit executables: 
```no-highlight
        $ sudo apt-get install gcc-multilib libc6-i386
```        
###Install gdb 

```no-highlight
$sudo apt-get install gdb

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
$ 

```

At this point you have installed all the necessary software to build and test code on a simluator for Linux. Proceed to the [Build test code on simulator](#build-test-code-on-simulator) section.
