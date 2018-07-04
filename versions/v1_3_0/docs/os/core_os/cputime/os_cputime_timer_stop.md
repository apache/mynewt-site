## <font color="F2853F" style="font-size:24pt">os_cputime_timer_stop</font>

```c
void os_cputime_timer_stop(struct hal_timer *timer)
```
Stops a timer from running. The timer is removed from the timer queue and interrupts are disabled if there are no more timers on the timer queue.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `timer` |  Pointer to the timer to stop.


#### Returned values
N/A

#### Notes

#### Example

```c
void
ble_ll_wfr_disable(void)
{
    os_cputime_timer_stop(&g_ble_ll_data.ll_wfr_timer);
}

```

