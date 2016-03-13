## <font color="#F2853F" style="font-size:24pt"> os_sched_next_task </font>

```c
struct os_task *os_sched_next_task(void)
```

Returns the pointer to highest priority task from the list which are *ready to run*.

#### Arguments

N/A

#### Returned values

See description.

#### Notes

Should be called with interrupts disabled.



