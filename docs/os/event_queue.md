# Event Queues


Event queue is a way of serializing events arring to a task. This makes it easy to queue processing to happen inside task's context. This would be done either from an interrupt handler, or from another task.

Events arrive in a form of a data structure *struct os_event*.

## Description

Events are in form of a data structure *struct os_event*, and they are queued to data structure *struct os_eventq*.

Queue must be initialized before trying to add events to it. This is done using *os_eventq_init()*.

Common way of using event queues is to have a task loop while calling *os_eventq_get()*, waiting for work to do.
Other tasks (or interrupts) then call *os_eventq_put()* to wake it up. Once event has been queued task waiting on that queue is woken up, and will get a pointer to queued event structure.
Processing task would then act according to event type.

When *os_event* is queued, it should not be freed until processing task is done with it.

It is assumed that there is only one task consuming events from an event queue. Only one task should be sleeping on a particular *os_eventq* at a time.

Note that os_callout subsystem assumes that event queue is used as the wakeup mechanism.

## Data structures

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

## List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in this OS feature are:

* [os_eventq_init](#os_eventq_init)
* [os_eventq_put](#os_eventq_put)
* [os_eventq_put2](#os_eventq_put2)
* [os_eventq_get](#os_eventq_get)
* [os_eventq_remove](#os_eventq_remove)


## Function Reference

------------------

## <font color="F2853F" style="font-size:24pt"> os_eventq_init</font>

```no-highlight
   void
    os_eventq_init(struct os_eventq *evq)
```

Initializes *struct os_eventq*, making it ready for use.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| evq |  Pointer to event queue getting initialized  |

#### Returned values

None

#### Notes

Usually done at subsystem init time; before OS has been started, and before interrupts generating events have been enabled.


#### Example

<Add text to set up the context for the example here>
This initializes event queue used by newtmgr task.


```c
struct os_eventq g_nmgr_evq;

int
nmgr_task_init(uint8_t prio, os_stack_t *stack_ptr, uint16_t stack_len)
{
    /* variable declarations here */

    os_eventq_init(&g_nmgr_evq);

    /* initialization continues here */
}
```

---------------------

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

#### Notes 

Functionality is of *os_eventq_put2()*, but this is to be called from a task context only.

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

---------------------
   
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
   
## <font color="#F2853F" style="font-size:24pt"> os_eventq_get</font>

```no-highlight
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

```no-highlight
    while (1) {
        ev = os_eventq_get(&task1_evq);
        assert(ev);
        if (ev->ev_type == CONS_EV_TYPE) {
			/* XXX do stuff */
        }
    }

```

---------------------

## <font color="#F2853F" style="font-size:24pt"> os_eventq_remove</font>

```no-highlight
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

```no-highlight
    if (c->c_evq) {
        os_eventq_remove(c->c_evq, &c->c_ev);
    }
```

