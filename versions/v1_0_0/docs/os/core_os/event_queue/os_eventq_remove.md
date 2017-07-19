## <font color="#F2853F" style="font-size:24pt"> os_eventq_remove</font>

```c
void
os_eventq_remove(struct os_eventq *evq, struct os_event *ev)
```

Removes an event from an event queue.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| `evq` |  Event queue to remove the event from |
| `ev` |  Event to remove  |


#### Returned values

N/A

#### Notes


#### Example

<Add text to set up the context for the example here>
This example from the `os_callout_stop()` function shows how to remove a callout event from an event queue. It removes
the event from the queue if the event is queued.

```c
void
os_callout_stop(struct os_callout *c)
{
    os_sr_t sr;

    OS_ENTER_CRITICAL(sr);

    if (os_callout_queued(c)) {
        TAILQ_REMOVE(&g_callout_list, c, c_next);
        c->c_next.tqe_prev = NULL;
    }

    if (c->c_evq) {
        os_eventq_remove(c->c_evq, &c->c_ev);
    }

    OS_EXIT_CRITICAL(sr);
}
```

