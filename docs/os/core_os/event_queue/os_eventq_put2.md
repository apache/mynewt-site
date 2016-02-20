## <font color="#F2853F" style="font-size:24pt"> os_eventq_put2</font>

```no-highlight
void
os_eventq_put2(struct os_eventq *evq, struct os_event *ev, int isr)
```

Queues an event to tail of the event queue.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| evq |  Queue where event is being placed  |
| ev |  Event which is being queued  |
| isr | Tells whether call is being made from within interrupt handler or not |

#### Returned values

N/A

#### Notes 

If the event has already been queued, nothing happens. Including event's relative position within the queue itself.

This can be called either from interrupt handler (in which case *isr* should be set to 1), or from another task context (in which case *isr should be set as 0).

#### Example

This wakes up the task waiting on task1_evq, which processes console input (console input comes from UART, and is passed in in interrupt context).

```no-highlight
static void
my_cons_input(int full_line)
{
    os_eventq_put2(&task1_evq, &cons_ev, 1);
}
```

---------------------
