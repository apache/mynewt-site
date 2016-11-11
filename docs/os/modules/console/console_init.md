## <font color="#F2853F" style="font-size:24pt"> console_init </font>

```c
int console_init(console_rx_cb rx_cb)
```
       
Initializes the console receive buffer and calls hal funtions `hal_uart_init_cbs` and `hal_uart_config` to 
initialize the serial port connection and configure it (e.g. baud rate, flow control etc.)

Caller registers a function pointer of `type void (*console_rx_cb)(int full_line)`. This function will be 
called when the console receives either a) full line of data or b) when RX buffer in console is full. 
Note that this function is most likely getting called from an interrupt context.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `rx_cb` | Function pointer, which gets called when input is received.  |

#### Returned values

Returns 0 on success.
Non-zero if HAL UART function calls fail.

#### Example

```c
int
main(int argc, char **argv)
{
    ....

    /* Init tasks */
    shell_task_init(SHELL_TASK_PRIO, shell_stack, SHELL_TASK_STACK_SIZE,
                         SHELL_MAX_INPUT_LEN);
    console_init(shell_console_rx_cb);

    ....
}
```
