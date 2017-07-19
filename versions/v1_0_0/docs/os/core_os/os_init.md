## <font color="#F2853F" style="font-size:24pt">os_init</font>

```c
void os_init(void)
```

Initializes the OS. Must be called before the OS is started (i.e. `os_start()` is called).

<br>

#### Arguments

None

<br>

#### Returned values
None

<br>

#### Notes

The call to `os_init()` performs architecture and bsp initializations and initializes the idle task.

This function does not start the OS, the OS time tick interrupt, or the scheduler.
