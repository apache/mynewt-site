# Callout

Callouts are MyNewt OS timers.

## Description

Callout is a way of setting up an OS timer. When the timer fires, it is delivered as an event to task's event queue.

User would initialize their callout structure using *os_callout_init()*, or *os_callout_func_init()* and then arm it with *os_callout_reset()*.

If user wants to cancel the timer before it expires, they can either use *os_callout_reset()* to arm it for later expiry, or stop it altogether by calling *os_callout_stop()*.

There are 2 different options for data structure to use. First is *struct os_callout*, which is a bare-bones version. You would initialize this with *os_callout_init()*.

Second option is *struct os_callout_func*. This you can use if you expect to have multiple different types of timers in your task, running concurrently. The structure contains a function pointer, and you would call that function from your task's event processing loop.

Time unit when arming the timer is OS ticks. This rate of this ticker depends on the platform this is running on. You should use OS define *OS_TICKS_PER_SEC* to convert wallclock time to OS  ticks.

Callout timer fires out just once. For periodic timer type of operation you need to rearm it once it fires.

## Data structures

```no-highlight
struct os_callout {
    struct os_event c_ev;
    struct os_eventq *c_evq;
    uint32_t c_ticks;
    TAILQ_ENTRY(os_callout) c_next;
};
```

| Element | Description |
|---------|-------------|
| c_ev | Event structure of this callout |
| c_evq | Event queue where this callout is placed on timer expiry |
| c_ticks | OS tick amount when timer fires |
| c_next | Linkage to other unexpired callouts |

```no-highlight
struct os_callout_func {
    struct os_callout cf_c;
    os_callout_func_t cf_func;
    void *cf_arg;
};
```

| Element | Description |
|---------|-------------|
| cf_c | struct os_callout. See above |
| cf_func | Function pointer which should be called by event queue processing |
| cf_arg | Generic void * argument to that function |

## List of Functions


The functions available in this OS feature are:

* [os_callout_init](#os_callout_init)
* [os_callout_func_init](#os_callout_func_init)
* [os_callout_stop](#os_callout_stop)
* [os_callout_reset](#os_callout_reset)
* [os_callout_queued](#os_callout_queued)

## Function Reference

------------------

## <font color="#F2853F" style="font-size:24pt">os_callout_init </font>

```no-highlight
void os_callout_init(struct os_callout *c, struct os_eventq *evq, void *ev_arg)
```

Initializes *struct os_callout*. Event type will be set to *OS_EVENT_T_TIMER*.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c |  Pointer to os_callout to initialize  |
| evq |  Event queue where this gets delivered to |
| ev_arg | Generic argument which is filled in for the event |

#### Returned values

N/A

#### Notes 

Be careful not to call this if the callout is armed, because that will mess up the list of pending callouts.
Or if the timer has already fired, it will mess up the event queue where the callout was delivered to.

#### Example

<Add text to set up the context for the example here>

```no-highlight
struct os_eventq my_evq;
struct os_callout my_callouts[8];

    for (i = 0; i < 8; i++) {
        os_callout_init(&my_callouts[i], &my_evq, (void *)i);
    }
```

---------------------
   
## <font color="#F2853F" style="font-size:24pt"> os_callout_func_init </font>

```no-highlight
void os_callout_func_init(struct os_callout_func *cf, struct os_eventq *evq, os_callout_func_t timo_func, void *ev_arg)
```

Initializes the given *struct os_callout_func*. Data structure is filled in with elements given as argument.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| cf | Pointer to os_callout_func being initialized |
| evq | Event queue where this gets delivered to |
| timo_func | Timeout function. Event processing should call this |
| ev_arg | Generic argument for the event |

#### Returned values

N/A

#### Notes

The same notes as with *os_callout_init()*.

#### Example

<Add text to set up the context for the example here>

```no-highlight
struct os_callout_func g_native_cputimer;
struct os_eventq g_native_cputime_evq;
void native_cputimer_cb(void *arg);

    /* Initialize the callout function */
    os_callout_func_init(&g_native_cputimer,
                         &g_native_cputime_evq,
                         native_cputimer_cb,
                         NULL);

```


---------------------

## <font color="#F2853F" style="font-size:24pt"> os_callout_stop </font>

```no-highlight
void os_callout_stop(struct os_callout *c)
```

Disarms a timer.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c | Pointer to os_callout being stopped |


#### Returned values

N/A

#### Notes



#### Example

<Add text to set up the context for the example here>

```no-highlight
struct os_callout_func g_native_cputimer;

     os_callout_stop(&g_native_cputimer.cf_c);
```


---------------------

## <font color="#F2853F" style="font-size:24pt"> os_callout_reset </font>

```no-highlight
void os_callout_reset(struct os_callout *c, int32_t timo)
```

Resets the callout to happen *timo* in OS ticks.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c | Pointer to os_callout being reset |
| timo | OS ticks the timer is being set to |


#### Returned values

N/A

#### Notes 



#### Example

<Add text to set up the context for the example here>

```no-highlight
    /* Re-start the timer (run every 50 msecs) */
    os_callout_reset(&g_bletest_timer.cf_c, OS_TICKS_PER_SEC / 20);
```

---------------------
   
## <font color="#F2853F" style="font-size:24pt">os_callout_queued</font>

```no-highlight
int os_callout_queued(struct os_callout *c)
```

Tells whether the callout has been armed or not.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| c |  Pointer to callout being checked  |

#### Returned values

0: timer is not armed
non-zero: timer is armed

#### Notes 



#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

