## <font color="F2853F" style="font-size:24pt">os_cputime_delay_ticks</font>

```c
void os_cputime_delay_ticks(uint32_t ticks)
```
Waits for a specified number of ticks to elapse before returning.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| `ticks` |  Number of ticks to delay for.


#### Returned values
N/A

#### Notes

#### Example
Delays for 100000 ticks:
```c
os_cputime_delay_ticks(100000)
```
