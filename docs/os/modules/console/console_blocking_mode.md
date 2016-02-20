## <font color="#F2853F" style="font-size:24pt"> console_blocking_mode </font>

```no-highlight
   void
   console_blocking_mode(void)
```
   Calls the console_blocking_tx function to flush the buffered console output (transmit) queue. The function OS_ENTER_CRITICAL() is called to disable interrupts and OS_EXIT_CRITICAL() is called to enable interrupts back again once the buffer is flushed.

#### Arguments

| Arguments | Description |
|-------------------------|
| none |  none  |


#### Returned values

List any values returned.
Error codes?

#### Notes

Any special feature/special benefit that we want to tout.
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Here is an example of calling `console_blocking_mode` and printing crash information from an assert to help debug.

```no-highlight
void
_assert_func(const char *file, int line, const char *func, const char *e)
{
    int sr;

    OS_ENTER_CRITICAL(sr);
    (void)sr;
    os_die_line = line;
    os_die_module = file;
    console_blocking_mode();
    console_printf("Assert %s; failed in %s:%d\n", e ? e : "", file, line);
    system_reset();
}
```

