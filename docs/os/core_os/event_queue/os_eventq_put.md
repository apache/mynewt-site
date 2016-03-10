## <font color="#F2853F" style="font-size:24pt"> os_eventq_put</font>

```no-highlight
void
os_eventq_put(struct os_eventq *evq, struct os_event *ev)
```

Queues an event to tail of the event queue.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| evq |  Queue where event is being placed  |
| ev |  Event which is being queued  |


#### Returned values

N/A

#### Example

<Add text to set up the context for the example here>
This is used to pass info about an event to a task handling it.

```no-highlight
    /* Get an event structure off the queue */
    ev = (struct os_event *)os_memblock_get(&g_hci_os_event_pool);
    if (!ev) {
        err = os_memblock_put(&g_hci_cmd_pool, hci_ev);
        assert(err == OS_OK);
        return -1;
    }

    /* Fill out the event and post to Link Layer */
    ev->ev_queued = 0;
    ev->ev_type = BLE_HOST_HCI_EVENT_CTLR_EVENT;
    ev->ev_arg = hci_ev;
    os_eventq_put(&ble_hs_evq, ev);

```

