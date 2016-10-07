## <font color="F2853F" style="font-size:24pt">os_time_tick</font>

```c
void os_time_tick(void)
```

Increments the OS time tick for the system.  Typically, this is called in one place by the architecture specific OS code (`libs/os/arch`) `timer_handler` which is in turn called by the BSP specific code assigned to drive the OS timer tick. See [Porting Mynewt OS](../porting/port_os) for details.

#### Arguments

N/A

#### Returned values

N/A

#### Notes

Called for every single tick by the architecture specific functions.

#### Example

<Add text to set up the context for the example here>

```c
   os_time_tick();
```
