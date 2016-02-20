## <font color="#F2853F" style="font-size:24pt"> os_callout_stop </font>

```no-highlight
void os_callout_stop(struct os_callout *c)
```

Disarms a timer.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c | Pointer to os_callout being stopped |


#### Returned values

N/A

#### Notes



#### Example

<Add text to set up the context for the example here>

```no-highlight
struct os_callout_func g_native_cputimer;

     os_callout_stop(&g_native_cputimer.cf_c);
```


---------------------
