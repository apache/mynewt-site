## <font color="#F2853F" style="font-size:24pt"> console_blocking_tx </font>

```no-highlight
    static void
    console_blocking_tx(char ch)
```

  Calls the hal function hal_uart_blocking_tx to transmit a byte to the console over UART in a blocking mode until the entire character has been sent. Hence it must be called with interrupts disabled. It is used when printing diagnostic output from system crash.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| ch |  8 bit character (data) to be transmitted |


#### Returned values

List any values returned.
Error codes?

#### Notes

Any special feature/special benefit that we want to tout.
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Here is an example of a console output queue being flushed.

```no-highlight
void
task(void)
{
    struct console_tty *ct = &console_tty;
    uint8_t byte;

    while (ct->ct_tx.cr_head != ct->ct_tx.cr_tail) {
        byte = console_pull_char(&ct->ct_tx);
        console_blocking_tx(byte);
    }
}
```


