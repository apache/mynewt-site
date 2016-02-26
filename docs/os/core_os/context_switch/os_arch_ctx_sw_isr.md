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


---------------------
