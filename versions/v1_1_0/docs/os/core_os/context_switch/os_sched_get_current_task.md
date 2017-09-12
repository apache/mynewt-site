## <font color="#F2853F" style="font-size:24pt"> os_sched_get_current_task </font>

```c
struct os_task *os_sched_get_current_task(void)
```

Returns the pointer to task which is currently *running*.

#### Arguments

N/A

#### Returned values

See description.

#### Notes


#### Example

<Add text to set up the context for the example here>

```c
void
os_time_delay(int32_t osticks)
{
    os_sr_t sr;

    if (osticks > 0) {
        OS_ENTER_CRITICAL(sr);
        os_sched_sleep(os_sched_get_current_task(), (os_time_t)osticks);
        OS_EXIT_CRITICAL(sr);
        os_sched(NULL);
    }
}
```


