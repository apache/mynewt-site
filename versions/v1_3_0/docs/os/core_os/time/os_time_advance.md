## <font color="F2853F" style="font-size:24pt">os_time_advance</font>

```c
void os_time_advance(int ticks)
```
Moves the OS time forward by the value specified in `ticks`.  Typically, this is called in one place by the architecture specific OS code (kernel/os/src/arch)  timer_handler which is in turn called by the BSP specific code assigned to drive the OS timer tick. See Porting Mynewt OS for details.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `ticks` |  Number of ticks to move the OS time forward. |


#### Returned values

N/A

#### Notes


#### Example
