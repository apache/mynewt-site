## <font color="#F2853F" style="font-size:24pt"> os_sched_os_timer_exp </font>

```no-highlight
void os_sched_os_timer_exp(void)
```

Inform scheduler that OS time has moved forward, and it should inspect tasks which are *sleeping* to check whether they should be moved to *g_run_list* or not.

This function should be called from code which handles moving OS time forward. After calling it, the highest priority task which is *ready to run* might've changed, so call to *os_sched()* should be done.

#### Arguments

N/A

#### Returned values

N/A

#### Notes


#### Example

<Add text to set up the context for the example here>
```no-highlight
void
timer_handler(void)
{
    os_time_tick();
    os_callout_tick();
    os_sched_os_timer_exp();
    os_sched(NULL);
}
```

---------------------
