# hal_timer

The hardware independent timer structure and API to configure, initialize, and run timers.

### Description

The HAL timer structure is shown below. The user can declare as many of these structures as required. They are enqueued on a particular HW timer queue when the user calls the hal_timer_start or hal_timer_start_at API. The user must have called hal_timer_set_cb before starting a timer.

NOTE: the user should not have to modify/examine the contents of this structure; the hal timer API should be used.

```c
struct hal_timer
{
    void                *bsp_timer; /* Internal platform specific pointer */
    hal_timer_cb        cb_func;    /* Callback function */
    void                *cb_arg;    /* Callback argument */
    uint32_t            expiry;     /* Tick at which timer should expire */
    TAILQ_ENTRY(hal_timer) link;    /* Queue linked list structure */
};
```

### Definition

[hal_timer.h](https://github.com/apache/incubator-mynewt-core/blob/master/hw/hal/include/hal/hal_timer.h)

### Examples

