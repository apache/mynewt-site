## <font color="#F2853F" style="font-size:24pt"> os_callout_reset </font>

```no-highlight
void os_callout_reset(struct os_callout *c, int32_t timo)
```

Resets the callout to happen *timo* in OS ticks.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c | Pointer to os_callout being reset |
| timo | OS ticks the timer is being set to |


#### Returned values

N/A

#### Notes 



#### Example

<Add text to set up the context for the example here>

```no-highlight
    /* Re-start the timer (run every 50 msecs) */
    os_callout_reset(&g_bletest_timer.cf_c, OS_TICKS_PER_SEC / 20);
```
