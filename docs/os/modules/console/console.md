#Console


The console is an operating system window where users interact with the OS subsystems or a console 
application.  A user typically inputs text from a keyboard and reads the OS output text on a computer
monitor.  The text are sent as a sequence of characters between the user and the OS. 
 
Support is currently available for console access via the serial port on the hardware board.


###Description

In the Mynewt OS, the console library comes in two versions:

* The `sys/console/full` package implements the complete console functionality and API.

* The `sys/console/stub` package implements stubs for the API.

Both packages export the `console` API, and any package that uses 
the console API must list `console` as a requirement. For example, the shell package defines the following `pkg.yml`
file:

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

The project `pkg.yml` file specifies the version of the console package to use.
A project that requires the full console capability must list the `sys/console/full` package as a dependency 
in its `pkg.yml` file.

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

On the other hand, a project may not have a physical console (e.g. a UART port to connect a terminal to) 
but may have a dependency on a package that has console capability. In this case, you use 
the console stub API and list the `sys/console/stub` package as a dependency in its `pkg.yml` file. 

An example is the bootloader project where we want to keep the size of the image small. It includes 
the `kernel/os` package that can print out messages on a console (e.g. if there is a hard fault).
However, we do not want to use any console I/O capability in this particular bootloader project to 
keep the size small. The project uses the console stub API and has the following `pkg.yml` file: 

```no-highlight
pkg.name: apps/boot
pkg.deps:
    - boot/bootutil
    - kernel/os
    - sys/console/stub

```

Console has 2 modes for transmit; *blocking mode* and *non-blocking mode*. Usually the *non-blocking mode* is the 
active one; the output buffer is drained by getting TX completion interrupts from hardware, and more data is added 
based on these interrupts.

*Blocking mode* is used when we don't want TX completion interrupts. It is used when system crashes, and we still 
want to output info related to that crash.

Console, by default, echoes everything it receives back. Terminal programs expect this, and is a way for the user to 
know that the console is connected and responsive. Whether echoing happens or not can be controlled programmatically.

The Console also has a prompt that is configurable. It is off by default but can be turned on programmatically. The
prompt character can also be changed by the user.

###Data structures

N/A

###List of Functions

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



