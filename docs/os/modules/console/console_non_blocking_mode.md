## <font color="#F2853F" style="font-size:24pt"> console_non_blocking_mode </font>

```c
void console_non_blocking_mode(void)
```

Sets the transmit mode to non-blocking. The default transmit mode is non-blocking. The caller only needs to call this function to switch the transmit mode back to non-blocking after transmit mode is set to the blocking mode via the `console_blocking_mode()` function.

#### Arguments

None


#### Returned values

N/A


#### Example

Here is an example that shows the function used to switch back to non blocking mode. 

```c

static void 
myapp_print(char *data, int cnt)
{

    /* Print data in blocking mode */
    console_blocking_mode();    
           ...
    console_write(data, cnt);

    /* Switch back to non-blocking mode for other writes */
    console_non_blocking_mode();
    return;
}

```
