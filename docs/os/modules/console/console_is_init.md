## <font color="#F2853F" style="font-size:24pt"> console_is_init </font>

```no-highlight
   int console_is_init(void)
```

  Returns whether console has been initialized or not. I.e. whether *console_init()* has been called yet.

#### Arguments

None

#### Returned values

Returns 1 if console has been initialized. 0 if not.

#### Notes

#### Example

```no-highlight
static int
log_console_append(struct log *log, void *buf, int len)
{
    ....

    if (!console_is_init()) {
        return (0);
    }

    /* print log entry to console */
    ....
}
```

