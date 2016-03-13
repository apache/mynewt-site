## <font color="#F2853F" style="font-size:24pt"> os_eventq_remove</font>

```c
void
os_eventq_remove(struct os_eventq *evq, struct os_event *ev)
```

Removes an event which has been placed in a queue.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| evq |  Queue where event is being removed from |
| ev |  Event which is being removed  |


#### Returned values

N/A

#### Notes


#### Example

<Add text to set up the context for the example here>
This is from os_callout_stop(). User wants to stop a callout from getting passed to a task. If the event has already been queued, then remove it before it is seen.

```c
    if (c->c_evq) {
        os_eventq_remove(c->c_evq, &c->c_ev);
    }
```

