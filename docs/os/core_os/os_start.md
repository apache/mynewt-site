## <font color="#F2853F" style="font-size:24pt">os_start</font>

```no-highlight
void os_start(void)
```

Starts the OS by initializing and enabling the OS time tick and starting the scheduler.

This function does not return.

<br>

#### Arguments

None

<br>

#### Returned values
None (does not return).

<br>

#### Notes

Once os_start has been called, context is switched to the highest priority task that was initialized prior to calling os_start.

<br>

---------------------
