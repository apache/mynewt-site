## <font color="F2853F" style="font-size:24pt"> os_eventq_run</font>

```c
   void
    os_eventq_run(struct os_eventq *evq)
```
Wrapper function that calls the `os_eventq_get()` function to dequeue the event from the head of the event queue and then calls the callback function for the event.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `evq`|  Event queue to dequeue the event from |

#### Returned values

None

#### Notes


#### Example

<Add text to set up the context for the example here>
This example shows an application `main()` that calls the `os_eventq_run()` function to process events from the OS default event queue in an infinite loop.

```c
int
main(int argc, char **argv)
{

     sysinit();
       ...

     while (1) {
        os_eventq_run(os_eventq_dflt_get());
     }
}
```

