## <font color="#F2853F" style="font-size:24pt"> os_sched_wakeup </font>

```no-highlight
int
os_sched_wakeup(struct os_task *t)
```

Called to make task *ready to run*. If task is *sleeping*, it is woken up.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| t | Pointer to task |

#### Returned values

Returns 0 on success.

#### Notes


#### Example

<Add text to set up the context for the example here>
```no-highlight
void
os_eventq_put(struct os_eventq *evq, struct os_event *ev)
{
    ....
        /* If task waiting on event, wake it up. */
    resched = 0;
    if (evq->evq_task) {
        os_sched_wakeup(evq->evq_task);
        evq->evq_task = NULL;
        resched = 1;
    }
    ....
}
```


