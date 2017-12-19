## <font color="F2853F" style="font-size:24pt">os_time_ms_to_ticks</font>

```c
int os_time_ms_to_ticks(uint32_t ms, uint32_t *out_ticks)
```
Converts milliseconds to OS ticks.

#### Arguments
| Arguments | Description |
|-----------|-------------|
| `ms` |  Number of milliseconds to convert to OS ticks. |
| `out_ticks` | Pointer to an uint32_t to return the number of OS ticks for `ms` milliseconds.|

N/A

#### Returned values
`0`:  Success
<br>`OS_EINVAL`:  Number of ticks is too large to fit in an uint32_t.

N/A

#### Notes


#### Example
```c
unint32_t num_ticks;
os_time_ms_to_ticks(50, &num_ticks);
```
