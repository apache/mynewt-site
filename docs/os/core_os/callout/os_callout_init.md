## <font color="#F2853F" style="font-size:24pt">os_callout_init </font>

```c
    void os_callout_init(struct os_callout *c, struct os_eventq *evq, void *ev_arg)
```

Initializes `struct os_callout`. Event type will be set to `OS_EVENT_T_TIMER`.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| `c` |  Pointer to os_callout to initialize  |
| `evq` |  Event queue where this gets delivered to |
| `ev_arg` | Generic argument which is filled in for the event |

#### Returned values

N/A

#### Notes 

Be careful not to call this if the callout is armed, because that will mess up the list of pending callouts.
Or if the timer has already fired, it will mess up the event queue where the callout was delivered to.

#### Example

<Add text to set up the context for the example here>

```c
    struct os_eventq my_evq;
    struct os_callout my_callouts[8];

        for (i = 0; i < 8; i++) {
            os_callout_init(&my_callouts[i], &my_evq, (void *)i);
    }
```
