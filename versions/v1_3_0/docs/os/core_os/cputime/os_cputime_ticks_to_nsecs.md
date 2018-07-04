## <font color="F2853F" style="font-size:24pt">os_cputime_ticks_to_nsecs</font>

```c
uint32_t os_cputime_ticks_to_nsecs(uint32_t ticks)
```
Converts cputime ticks to nanoseconds.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `ticks` |  Number of cputime ticks to convert to nanoseconds.


#### Returned values
The number of nanoseconds in `ticks` number of ticks.

#### Notes

#### Example
```c
uint32_t num_nsecs;
num_nsecs = os_cputime_ticks_to_nsecs(1000000);
```
