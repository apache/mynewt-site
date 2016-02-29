## <font color="#F2853F" style="font-size:24pt"> os_arch_ctx_sw_isr </font>

```no-highlight
void os_arch_ctx_sw_isr(struct os_task *next_t)
```

Change the state of task pointed by *next_t* to be *running*.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| next_t | Pointer to task which must run next |

#### Returned values

N/A

#### Notes

This would get called from interrupt context.

#### Example

<Add text to set up the context for the example here>
```no-highlight
void
os_sched(struct os_task *next_t, int isr) 
{
    os_sr_t sr;

    OS_ENTER_CRITICAL(sr);

    if (!next_t) {
        next_t = os_sched_next_task();
    }

    if (next_t != g_current_task) {
        OS_EXIT_CRITICAL(sr);
        if (isr) {
            os_arch_ctx_sw_isr(next_t);
        } else {
            os_arch_ctx_sw(next_t);
        }

    } else {
        OS_EXIT_CRITICAL(sr);
    }
}
```

---------------------
