## <font color="#F2853F" style="font-size:24pt"> os_eventq_get</font>

```c
void
os_eventq_get(struct os_eventq *evq)
```

Fetches the first event from a queue. Task will sleep until something gets queued.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| evq |  Queue to wait on  |


#### Returned values

Will return with a pointer to first *struct event* which is in the queue.

#### Notes 


#### Example

Main loop of an example task.

```c
    while (1) {
        ev = os_eventq_get(&task1_evq);
        assert(ev);
        if (ev->ev_type == CONS_EV_TYPE) {
			/* XXX do stuff */
        }
    }

```

