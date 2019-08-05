Debugging Mynewt
=============================

If you run into issues with Mynewt applications, you may need to use the debugger. This page will show
you how to set up and use the debugger in Mynewt. 

.. contents::
 :local:
 :depth: 2

Prerequisites
-----------------------------

- You have installed the Newt tool and toolchains on your machine. Visit the :doc:`Native Installation <native_install/index>` page to get started.
- You have run through one of the tutorials, created a project, or have an existing one. 
- Familiarity with GDB; for more information refer to the `GDB documentation <https://sourceware.org/gdb/current/onlinedocs/gdb/>`__.

Starting the Debugger
-----------------------------

Mynewt uses GDB to debug applications. To open a debugger session for Mynewt, you can run
either of the following newt commands:

- ``newt debug <target_name>``
- ``newt run <target_name> <version_number>``

The ``newt debug`` command will start the debugger for the specified target. That target
should be running on the device you are debugging on. For more information on the command, take a look at
the :doc:`command structure in the Newt Tool Guide <../../../../../newt/command_list/newt_debug>`. 

The ``newt run`` command also starts the debugger, but will also build the target, create
an image with the specified version number, and load it onto the board. More details on its usage and syntax are
on the :doc:`Newt Tool command guide <../../../../newt/command_list/newt_run>`.


Starting the debugger will bring up the GDB session in the console:

.. code:: console

    ~/test/1.5 $ newt debug pca40blinky
    [/Users/dlee/test/1.5/repos/apache-mynewt-core/hw/bsp/nordic_pca10040/nordic_pca10040_debug.sh /Users/dlee/test/1.5/repos/apache-mynewt-core/hw/bsp/nordic_pca10040 bin/targets/pca40blinky/app/apps/blinky/blinky]

    Debugging bin/targets/pca40blinky/app/apps/blinky/blinky.elf
    GNU gdb (GNU Tools for Arm Embedded Processors 7-2018-q2-update) 8.1.0.20180315-git
    Copyright (C) 2018 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>.
    Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
    For help, type "help".
    Type "apropos word" to search for commands related to "word"...
    Reading symbols from bin/targets/pca40blinky/app/apps/blinky/blinky.elf...done.
    os_tick_idle (ticks=128)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:164
    164     if (ticks > 0) {
    (gdb) 


