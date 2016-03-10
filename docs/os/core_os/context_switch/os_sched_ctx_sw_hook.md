## <font color="#F2853F" style="font-size:24pt"> os_sched_ctx_sw_hook </font>

```no-highlight
void os_sched_ctx_sw_hook(struct os_task *next_t)
```

Performs task accounting when context switching.

This function must be called from the architecture specific context switching routine *os_arch_ctx_sw()* before resuming execution of the *running* task.

#### Arguments

N/A

#### Returned values

N/A

#### Notes


#### Example

<Add text to set up the context for the example here>

```no-highlight
void
os_arch_ctx_sw(struct os_task *t)
{
    os_sched_ctx_sw_hook(t);

    /* Set PendSV interrupt pending bit to force context switch */
    SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}
```


