## <font color="F2853F" style="font-size:24pt"> os_eventq_inited</font>

```c
   int
    os_eventq_inited(const struct os_eventq *evq)
```

<<<<<<< HEAD
Check if event queue `const struct os_eventq`, is it ready for use.
=======
Check if event queue `const struct os_eventq` is ready for use.
>>>>>>> apache/master

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `evq` |  Pointer to event queue to check  |

#### Returned values

`0` if event queue is ready

#### Notes

If an event queue was properly initialized (and the proper checks were done at initialization)
this check is not needed prior to using an event queue.


#### Example

<Add text to set up the context for the example here>
This checks an event queue before using it.


```c
struct os_eventq g_my_evq;

int
my_task_init(uint8_t prio, os_stack_t *stack_ptr, uint16_t stack_len)
{
    /* variable declarations here */

    if(os_eventq_inited(&g_my_evq))
    {
        /* deal with the event queue */
    };

}
```

