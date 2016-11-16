## <font color="F2853F" style="font-size:24pt"> os_eventq_dflt_get</font>

```c
   struct os_eventq 
   *os_eventq_dflt_get(void)
```

Get the default event queue that was set

#### Arguments

None

#### Returned values

`struct os_eventq *` A pointer to the default event queue, if set.  

#### Notes

None


#### Example

<Add text to set up the context for the example here>
This checks the default event queue and sets it if not already set.


```c
struct os_eventq g_my_evq;

int
event_q_check()
{    
    if(os_eventq_dflt_get() == NULL)
    {
        os_eventq_dflt_set(g_my_evq);
    }

}
```

