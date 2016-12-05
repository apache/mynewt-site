#Console


The console is an operating system window where users interact with system programs of the operating system or a console application by entering text input (typically from a keyboard) and reading text output (typically on the computer terminal or monitor). The text written on the console brings some information and is a sequence of characters sent by the OS or programs running on the OS. 

Support is currently available for console access via the serial port on the hardware board.


###Description

In the Mynewt OS, the console library comes in two versions:

* full - containing the full implementation
* stub - containing stubs for the API

Both of these have `pkg.yml` file which states that they provide the `console` API. If a pkg uses this API, it should list `console` as a requirement.
For example, the shell pkg is defined by the following pkg.yml file:
```no-highlight
    pkg.name: libs/shell 
    pkg.vers: 0.1
    pkg.deps:
        - libs/os
        - libs/util
    pkg.reqs:
        - console
    pkg.identities:
        - SHELL 
```
The project .yml file decides which version of the console pkg should be included. 
If project requires the full console capability it lists dependency `libs/console/full` in its pkg.yml file. On the other hand, a project may not have a physical console (e.g. a UART port to connect a terminal to) but may have a dependency on a pkg that has console capability. In that case you would use a console stub. 


Another example would be the bootloader project where we want to keep the size of the image small. It includes the `libs/os` pkg that can print out messages on a console (e.g. if there is a hard fault) and the `libs/util` pkg that uses full console (but only if SHELL is present to provide a CLI). However, we do not want to use any console I/O capability in this particular bootloader project to keep the size small. We simply use the console stub instead, and the pkg.yml file for the project boot pkg looks like the following:
```no-highlight
    project.name: boot
    project.identities: bootloader
    project.pkgs:
        - libs/os
        - libs/bootutil
        - libs/nffs
        - libs/console/stub
        - libs/util 
```

Console has 2 modes for transmit; *blocking mode* and *non-blocking mode*. Usually the *non-blocking mode* is the active one; the output buffer is drained by getting TX completion interrupts from hardware, and more data is added based on these interrupts.
*Blocking mode* is used when we don't want TX completion interrupts. It is used when system crashes, and we still want to output info related to that crash.

Console, by default, echoes everything it receives back. Terminal programs expect this, and is a way for the user to know that the console is connected and responsive. Whether echoing happens or not can be controlled programmatically.

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



