## <font color="#F2853F" style="font-size:24pt"> os_callout_func_init </font>

```no-highlight
void os_callout_func_init(struct os_callout_func *cf, struct os_eventq *evq, os_callout_func_t timo_func, void *ev_arg)
```

Initializes the given *struct os_callout_func*. Data structure is filled in with elements given as argument.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| cf | Pointer to os_callout_func being initialized |
| evq | Event queue where this gets delivered to |
| timo_func | Timeout function. Event processing should call this |
| ev_arg | Generic argument for the event |

#### Returned values

N/A

#### Notes

The same notes as with *os_callout_init()*.

#### Example

<Add text to set up the context for the example here>

```no-highlight
struct os_callout_func g_native_cputimer;
struct os_eventq g_native_cputime_evq;
void native_cputimer_cb(void *arg);

    /* Initialize the callout function */
    os_callout_func_init(&g_native_cputimer,
                         &g_native_cputime_evq,
                         native_cputimer_cb,
                         NULL);

```


