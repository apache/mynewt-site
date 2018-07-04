## <font color="F2853F" style="font-size:24pt"> os_eventq_init</font>

```c
   void
    os_eventq_init(struct os_eventq *evq)
```

Initializes an event queue. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `evq` |  Pointer to the event queue to initialize |

#### Returned values

None

#### Notes

Called during OS, package, and application initialization and before interrupts generating events have been enabled.


#### Example

<Add text to set up the context for the example here>
This example shows the `app/bletest` application initializing the `g_bletest_evq` event queue.

```c
struct os_eventq g_bletest_evq;

int
main(void)
{
    /* variable declarations here */

    os_eventq_init(&g_bletest_evq);

    /* initialization continues here */

}
```

