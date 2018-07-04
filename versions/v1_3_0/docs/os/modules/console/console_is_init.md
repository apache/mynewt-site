## <font color="#F2853F" style="font-size:24pt"> console_is_init </font>

```no-highlight
   int console_is_init(void)
```

Returns whether console has been initialized or not. 

#### Arguments

None

#### Returned values

1 if console has been initialized. 

0 if console has not been initialized.


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

