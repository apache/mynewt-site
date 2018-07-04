## <font color="F2853F" style="font-size:24pt">os_cputime_delay_usecs</font>

```c
void os_cputime_delay_usecs(uint32_t usecs)
```
Waits for a specified number of microseconds to elapse before returning.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| `usecs` |  Number of microseconds to delay for.


#### Returned values
N/A

#### Notes

#### Example
Delays for 250000 usecs:
```c
os_cputime_delay_usecs(250000)
```
