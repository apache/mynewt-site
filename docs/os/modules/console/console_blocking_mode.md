## <font color="#F2853F" style="font-size:24pt"> console_blocking_mode </font>

```no-highlight
   void
   console_blocking_mode(void)
```
Sets the transmit mode to blocking. The function flushes the buffered console output.  The function `OS_ENTER_CRITICAL()` is called to disable interrupts and `OS_EXIT_CRITICAL()` is called to enable interrupts back again once the buffer is flushed.

#### Arguments

None


#### Returned values

N/A


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

