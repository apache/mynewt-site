# Console


The console is an operating system window where users interact with the OS subsystems or a console 
application.  A user typically inputs text from a keyboard and reads the OS output text on a computer
monitor.  The text are sent as a sequence of characters between the user and the OS. 
 
Support is currently available for console access via the serial port on the hardware board.


### Description

In the Mynewt OS, the console library comes in three versions:

* The `sys/console/full` package implements the complete console functionality and API.
* The `sys/console/stub` package implements stubs for the API.
* The `sys/console/minimal` package implements minimal console functionality of reading from and writing to console.  It implements the `console_read()` and `console_write()` functions and stubs for all the other console functions.

All the packages export the `console` API, and any package that uses the console API must list `console` as a requirement its `pkg.yml` file:  

```no-highlight

pkg.name: sys/shell
pkg.deps:
    - kernel/os
    - encoding/base64
    - time/datetime
    - util/crc
pkg.req_apis:
    - console

```
<br>
The project `pkg.yml` file also specifies the version of the console package to use.

<br>
####Using the Full Console Package
A project that requires the full console capability must list the `sys/console/full` package as a dependency in its `pkg.yml` file.

An example is the `slinky` application. It requires the full console capability and has the following
`pkg.yml` file: 

```no-highlight
pkg.name: apps/slinky
pkg.deps:
    - test/flash_test
    - mgmt/imgmgr
    - mgmt/newtmgr
    - mgmt/newtmgr/transport/nmgr_shell
    - kernel/os
    - boot/bootutil
    - sys/shell
    - sys/console/full
       ...
    - sys/id
```
<br>
####Using the Stub Console Package

A project that uses console stub API must list the `sys/console/stub` package as a dependency in its `pkg.yml` file.

Examples of when a project would use the console stubs might be:

* A project may not have a physical console (e.g. a UART port to connect a terminal to) 
but may have a dependency on a package that has console capability. 
* A bootloader project where we want to keep the size of the image small. It includes 
the `kernel/os` package that can print out messages on a console (e.g. if there is a hard fault).
However, we do not want to use any console I/O capability in this particular bootloader project to 
keep the size small. 

The project would use the console stub API and has the following `pkg.yml` file: 

Another example would be the bootloader project where we want to keep the size of the image small. It includes the `libs/os` pkg that can print out messages on a console (e.g. if there is a hard fault) and the `libs/util` pkg that uses full console (but only if SHELL is present to provide a CLI). However, we do not want to use any console I/O capability in this particular bootloader project to keep the size small. We simply use the console stub instead, and the pkg.yml file for the project boot pkg looks like the following:
```no-highlight
pkg.name: apps/boot
pkg.deps:
    - boot/bootutil
    - kernel/os
    - sys/console/stub

```
<br>

#### Using the Minimal Console Package

There might be projects that need to read and write data on a serial connection but do not need the full console capability. An example might be a project that supports serial image upgrade but does not need full newtmgr capability.  The project would use the console minimal API and has the following `pkg.yml` file: 

```no-highlight
pkg.name: apps/boot
pkg.type: app
pkg.description: Boot loader application.
pkg.author: "Apache Mynewt <dev@mynewt.apache.org>"
pkg.homepage: "http://mynewt.apache.org/"
pkg.keywords:
    - loader

pkg.deps:
    - boot/bootutil
    - kernel/os
    - sys/console/stub

pkg.deps.BOOT_SERIAL.OVERWRITE:
    - sys/console/minimal
    - boot/boot_serial

```			

<br>
Console has 2 modes for transmit; *blocking mode* and *non-blocking mode*. Usually the *non-blocking mode* is the 
active one; the output buffer is drained by getting TX completion interrupts from hardware, and more data is added 
based on these interrupts.

*Blocking mode* is used when we don't want TX completion interrupts. It is used when system crashes, and we still 
want to output info related to that crash.

Console, by default, echoes everything it receives back. Terminal programs expect this, and is a way for the user to 
know that the console is connected and responsive. Whether echoing happens or not can be controlled programmatically.

The Console also has a prompt that is configurable. It is off by default but can be turned on programmatically. The
prompt character can also be changed by the user.

### Data structures

N/A

### List of Functions

The functions available in console are:

| Function | Description |
|---------|-------------|
| [console_blocking_mode](console_blocking_mode.md) | Calls the `console_blocking_tx` function to flush the buffered console output (transmit) queue. |
| [console_echo](console_echo.md) | Controls whether echoing is on or off for the console. |
| [console_init](console_init.md) | Initialize the console. |
| [console_is_init](console_is_init.md) | Returns whether console has been initialized or not. |
| [console_printf](console_printf.md) | Writes a formatted message instead of raw output to the console. |
| [console_read](console_read.md) | Copies up the to given number of bytes to the input string. |
| [console_write](console_write.md) | Queues characters to console display over serial port. |



