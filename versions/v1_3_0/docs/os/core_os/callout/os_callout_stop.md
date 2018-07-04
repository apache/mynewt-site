## <font color="#F2853F" style="font-size:24pt"> os_callout_stop </font>


    void os_callout_stop(struct os_callout *c)


Disarms a timer.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c | Pointer to os_callout being stopped |


#### Returned values

N/A


#### Example



    struct os_callout_func g_native_cputimer;

         os_callout_stop(&g_native_cputimer.cf_c);



