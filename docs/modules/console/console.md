# Console


The console is an operating system window where users interact with system programs of the operating system or a console application by entering text input (typically from a keyboard) and reading text output (typically on the computer terminal or monitor). The text written on the console brings some information and is a sequence of characters sent by the OS or programs running on the OS. 

Support is currently available for console access via the serial port on the hardware board.


## Description

In the Mynewt OS, the console library comes in two versions:

* full - containing the full implementation
* stub - containing stubs for the API

Both of these have `egg.yml` file which states that they provide the `console` API. If an egg uses this API, it should list `console` as a requirement.
For example, the shell egg is defined by the following egg.yml file:
```no-highlight
    egg.name: libs/shell 
    egg.vers: 0.1
    egg.deps:
        - libs/os
        - libs/util
    egg.reqs:
        - console
    egg.identities:
        - SHELL 
```
The project .yml file decides which version of the console egg should be included. 
If project requires the full console capability it lists dependency `libs/console/full` in its egg.yml file. 
On the other hand, a project may not have a physical console (e.g. a UART port to connect a terminal to) but may have a dependency on an egg that has console capability. In that case you would use a console stub. Another example would be the bootloader project where we want to keep the size of the image small. It includes the `libs/os` egg that can print out messages on a console (e.g. if there is a hard fault) and the `libs/util` egg that uses full console (but only if SHELL is present to provide a CLI). However, we do not want to use any console I/O capability in this particular bootloader project to keep the size small. We simply use the console stub instead and the egg.yml file for the project boot egg looks like the following:
```no-highlight
    project.name: boot
    project.identities: bootloader
    project.eggs:
        - libs/os
        - libs/bootutil
        - libs/nffs
        - libs/console/stub
        - libs/util 
```

Console has 2 modes for transmit; blocking and non-blocking mode. Usually the non-blocking mode is the active one; the output buffer is drained by getting TX completion interrupts from hardware, and more data is added based on these interrupts.
Blocking mode is used when we don't want TX completion interrupts. This is used when system crashes, and we still want to output info related to that crash.

## Data structures


Console interaction is intrinsically composed of two unidirectional systems. The console implementation uses two ring buffers containing input (receive) and output (transmit) characters, respectively. Read and write operations on the console_ring structure are managed by labeling the read location indicator the `cr_tail` and the write location indicator the `cr_head`. The console ring length is variable and is specified as the `cr_size` member of the data structure. `cr_buf` is the pointer to the actual array of data contained.


```no-highlight
struct console_ring {
  32     uint8_t cr_head;
  33     uint8_t cr_tail;
  34     uint8_t cr_size;
  35     uint8_t _pad;
  36     uint8_t *cr_buf;
  37 }
```


```no-highlight
struct console_tty {
  40     struct console_ring ct_tx;
  41     uint8_t ct_tx_buf[CONSOLE_TX_BUF_SZ]; /* must be after console_ring */
  42     struct console_ring ct_rx;
  43     uint8_t ct_rx_buf[CONSOLE_RX_BUF_SZ]; /* must be after console_ring */
  44     console_rx_cb ct_rx_cb;     /* callback that input is ready */
  45     console_write_char ct_write_char;
  46 } console_tty
```

## List of Functions

The functions available in console are:

* [console_add_char](console_add_char.md)
* [console_blocking_mode](console_blocking_mode.md)
* [console_blocking_tx](console_blocking_tx.md)
* [console_init](console_init.md)
* [console_printf](console_printf.md)
* [console_pull_char](console_pull_char.md)
* [console_pull_char_head](console_pull_char_head.md)
* [console_queue_char](console_queue_char.md)
* [console_read](console_read.md)
* [console_rx_char](console_rx_char.md)
* [console_tx_char](console_tx_char.md)
* [console_write](console_write.md)



