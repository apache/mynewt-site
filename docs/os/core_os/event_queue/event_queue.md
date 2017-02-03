# Event Queues


Event queue is a way of serializing events arring to a task. This makes it easy to queue processing to happen inside task's context. This would be done either from an interrupt handler, or from another task.

Events arrive in a form of a data structure *struct os_event*.

### Description

<<<<<<< HEAD
Events are in form the of a data structure `struct os_event` and 
they are queued to another data structure `struct os_eventq`.

The Event Queue must be initialized before trying to add events to 
it. This is done using `os_eventq_init()`.

A common way of using event queues is to have a task loop while calling `os_eventq_get()`, 
waiting for work to do. Other tasks (or interrupts) then call `os_eventq_put()` 
to wake it up. Once event has been queued task waiting on that queue is woken up, 
and will get a pointer to queued event structure. Processing task would then act according to event type. This
method of event handling requires that the task handler itself would dispatch the
events based on the event's type. 

Mynewt has moved the event dispatching logic out of the task handler and instead the
logic is built in to each event via a callback function pointer. The task handler no longer
needs to dispatch events based on their types but instead can simply pull events
off the queue and call it's callback handler. 
=======
Events are in form of a data structure *struct os_event*, and they are queued to data structure *struct os_eventq*.

Queue must be initialized before trying to add events to it. This is done using *os_eventq_init()*.

Common way of using event queues is to have a task loop while calling *os_eventq_get()*, waiting for work to do.
Other tasks (or interrupts) then call *os_eventq_put()* to wake it up. Once event has been queued task waiting on that queue is woken up, and will get a pointer to queued event structure.
Processing task would then act according to event type.
>>>>>>> apache/master

When *os_event* is queued, it should not be freed until processing task is done with it.

It is assumed that there is only one task consuming events from an event queue. Only one task should be sleeping on a particular *os_eventq* at a time.

Note that os_callout subsystem assumes that event queue is used as the wakeup mechanism.

### Data structures

```c
typedef void os_event_fn(struct os_event *ev);

struct os_event {
    uint8_t ev_queued;
    os_event_fn *ev_cb;
    void *ev_arg;
    STAILQ_ENTRY(os_event) ev_next;
};
```

| Element | Description |
|---------|-------------|
| `ev_queued` | Internal field, which tells whether event is linked into an *os_eventq* already |
| `ev_cb` | A callback function pointer that is called when a new event arrives on the queue |
| `ev_arg` | Can be used further as input to task processing this event |
| `ev_next` | Linkage attaching this event to an event queue |

With the addition of a callback function pointer, the dispatch logic 
is moved out of the task handler and gets built into each event.  A 
task handler now just pulls an event off its queue and blindly calls 
its callback function.  A helper function was added to do just this: 
`os_eventq_run()`.  As an example, the task handler
for the bleprph application is below:

```c
static void
bleprph_task_handler(void *unused)
{
    while (1) {
        os_eventq_run(&bleprph_evq);
    }
}
```
  
The callback associated with an event is specified when the event gets
initialized.  For example, here are some statically-initialized events
in the nimble host:

```c
static void ble_hs_event_tx_notify(struct os_event *ev);
static void ble_hs_event_reset(struct os_event *ev);

/** OS event - triggers tx of pending notifications and indications. */
static struct os_event ble_hs_ev_tx_notifications = {
    .ev_cb = ble_hs_event_tx_notify,
};

/** OS event - triggers a full reset. */
static struct os_event ble_hs_ev_reset = {
    .ev_cb = ble_hs_event_reset,
};
```

The callback function receives a single parameter: a
pointer to the event being processed.  If the event is allocated
dynamically, the callback function should free the event.   
   
   
```c
struct os_eventq {
    struct os_task *evq_task;
    STAILQ_HEAD(, os_event) evq_list;
};
```


| Element | Description |
|---------|-------------|
| `evq_task` | Pointer to task if there is task sleeping on *os_eventq_get()* |
| `evq_list` | Queue head for list of events in this queue |

### List of Functions


The functions available in event queue feature are:

| **Function** | **Description** |
|---------|-------------|
| [`os_eventq_init`](os_eventq_init.md) | Initializes the given event queue, making it ready for use. |
| [`os_eventq_inited`](os_eventq_inited.md) | Has the event queue been initialized. |
| [`os_eventq_get`](os_eventq_get.md) | Fetches the first event from a queue. Task will sleep until something gets queued. |
| [`os_eventq_put`](os_eventq_put.md) | Queues an event to tail of the event queue. |
| [`os_eventq_remove`](os_eventq_remove.md) | Removes an event which has been placed in a queue. |
| [`os_eventq_dflt_set`](os_eventq_dflt_set.md) | Set the default event queue. |
| [`os_eventq_dflt_get`](os_eventq_dflt_get.md) | Get the default event queue. |



