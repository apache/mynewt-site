## <font color="#F2853F" style="font-size:24pt"> os_sched_insert </font>

```no-highlight
os_error_t
os_sched_insert(struct os_task *t)
```

Insert task into scheduler's *ready to run* list.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| t | Pointer to task |

#### Returned values

Returns OS_EINVAL if task state is not *READY*.
Returns 0 on success.

#### Notes

You probably don't need to call this.


