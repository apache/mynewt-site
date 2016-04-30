# hal_uart


The hardware independent UART interface for Mynewt.

###Description

Contains the basic operations to send and receive data over a UART
(Universal Asynchronous Receiver Transmitter).

###Definition

[hal_uart.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_uart.h)

###Examples

This example shows a user writing a character to the uart

```no-highlight
/* write to the console with blocking */
{
    char *str = "Hello World!";
    char *ptr = str;

    while(*ptr) {
        hal_uart_blocking_tx(MY_UART, *ptr++);
    }
    hal_uart_blocking_tx(MY_UART, '\n');
}
```


