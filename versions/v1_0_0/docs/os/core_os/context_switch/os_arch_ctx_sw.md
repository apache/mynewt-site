##<font color="#F2853F" style="font-size:24pt"> os_arch_ctx_sw </font>

```c
void os_arch_ctx_sw(struct os_task *next_t)
```

Change the state of task pointed by `next_t` to be *running*.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `next_t` | Pointer to task which must run next |

#### Returned values

N/A

#### Notes

This would get called from another task's context.

#### Example

<Add text to set up the context for the example here>

```c
void
    os_sched(struct os_task *next_t)
    {
        os_sr_t sr;

        OS_ENTER_CRITICAL(sr);

        if (!next_t) {
            next_t = os_sched_next_task();
        }
    
        if (next_t != g_current_task) {
            os_arch_ctx_sw(next_t);
        }
    
        OS_EXIT_CRITICAL(sr);
    }
```


