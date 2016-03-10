# Event Queues


Event queue is a way of serializing events arring to a task. This makes it easy to queue processing to happen inside task's context. This would be done either from an interrupt handler, or from another task.

Events arrive in a form of a data structure *struct os_event*.

### Description

Events are in form of a data structure *struct os_event*, and they are queued to data structure *struct os_eventq*.

Queue must be initialized before trying to add events to it. This is done using *os_eventq_init()*.

Common way of using event queues is to have a task loop while calling *os_eventq_get()*, waiting for work to do.
Other tasks (or interrupts) then call *os_eventq_put()* to wake it up. Once event has been queued task waiting on that queue is woken up, and will get a pointer to queued event structure.
Processing task would then act according to event type.

When *os_event* is queued, it should not be freed until processing task is done with it.

It is assumed that there is only one task consuming events from an event queue. Only one task should be sleeping on a particular *os_eventq* at a time.

Note that os_callout subsystem assumes that event queue is used as the wakeup mechanism.

### Data structures

```no-highlight
struct os_event {
    uint8_t ev_queued;
    uint8_t ev_type;
    void *ev_arg;
    STAILQ_ENTRY(os_event) ev_next;
};
```

| Element | Description |
|---------|-------------|
| ev_queued | Internal field, which tells whether event is linked into an *os_eventq* already |
| ev_type | Type of an event. This should be unique, as it should be used by processing task to figure out what the event means |
| ev_arg | Can be used further as input to task processing this event |
| ev_next | Linkage attaching this event to an event queue |


```no-highlight
struct os_eventq {
    struct os_task *evq_task;
    STAILQ_HEAD(, os_event) evq_list;
};
```


| Element | Description |
|---------|-------------|
| evq_task | Pointer to task if there is task sleeping on *os_eventq_get()* |
| evq_list | Queue head for list of events in this queue |

### List of Functions


The functions available in event queue feature are:

* [os_eventq_get](os_eventq_get.md)
* [os_eventq_init](os_eventq_init.md)
* [os_eventq_put](os_eventq_put.md)
* [os_eventq_remove](os_eventq_remove.md)

