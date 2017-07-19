## <font color="F2853F" style="font-size:24pt">os_cputime_ticks_to_usecs</font>

```c
uint32_t os_cputime_ticks_to_usecs(uint32_t ticks)
```
Converts a specified number of cputime ticks to microseconds.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `ticks` |  Number of cputime ticks to convert to microseconds.


#### Returned values
The number of microseconds in `ticks` number of ticks.

#### Notes

#### Example
```c
uint32_t num_usecs;
num_usecs = os_cputime_ticks_to_usecs(1000000);
```
