## <font color="F2853F" style="font-size:24pt">os_get_uptime_usec</font>

```c
int64_t os_get_uptime_usec(void)
```
Gets the time duration, in microseconds, since boot.

#### Arguments

N/A

#### Returned values
Time since boot in microseconds. 

#### Notes

#### Example

<Add text to set up the context for the example here>

```c
   int64_t time_since_boot;
   time_since_boot = os_get_uptime_usec();
```
