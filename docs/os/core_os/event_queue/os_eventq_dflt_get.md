## <font color="F2853F" style="font-size:24pt"> os_eventq_dflt_get</font>

```c
   struct os_eventq 
   *os_eventq_dflt_get(void)
```

Gets the OS default event queue that Mynewt creates at startup.

#### Arguments

None

#### Returned values

`struct os_eventq *`: Pointer to OS the default event queue.  

#### Notes

None


#### Example

<Add text to set up the context for the example here>

This example shows an application's `main()` function processing events from the OS default event queue.


```c
void main(int argc, char**argv)
{
     sysinit();

      ...

     while (1) {
         os_eventq_run(os_eventq_dflt_get());
     }

}
```

