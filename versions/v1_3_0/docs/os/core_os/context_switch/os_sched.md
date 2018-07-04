## <font color="#F2853F" style="font-size:24pt"> os_sched </font>

```c
void os_sched(struct os_task *next_t)
```

Performs context switch if needed. If *next_t* is set, that task will be made *running*. If *next_t* is NULL, highest priority *ready to run* is swapped in. This function can be called when new tasks were made *ready to run* or if the current task is moved to *sleeping* state.

This function will call the architecture specific routine to swap in the new task.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| next_t | Pointer to task which must run next (optional) |

#### Returned values

N/A

#### Notes

Interrupts must be disabled when calling this.

#### Example

<Add text to set up the context for the example here>

```c
os_error_t
os_mutex_release(struct os_mutex *mu)
{
    ...
    OS_EXIT_CRITICAL(sr);

    /* Re-schedule if needed */
    if (resched) {
        os_sched(rdy);
    }

    return OS_OK;

}
```


