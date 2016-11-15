## <font color="F2853F" style="font-size:24pt"> os_eventq_init</font>

```c
   void
    os_eventq_init(struct os_eventq *evq)
```

Initializes `struct os_eventq`, making it ready for use.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `evq` |  Pointer to event queue getting initialized  |

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

