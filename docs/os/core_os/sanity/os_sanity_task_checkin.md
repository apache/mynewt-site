## <font color="F2853F" style="font-size:24pt"> os_sanity_task_checkin</font>

```no-highlight
int os_sanity_task_checkin(struct os_task *t)
```
Used by a task to check in to the sanity task. This informs the sanity task that 
*task* is still alive and working normally.
 
<br>
#### Arguments

| Arguments | Description | 
|-----------|-------------| 
| `t` | Pointer to task | 

<br>
#### Returned values

`OS_OK`: sanity check-in successful

All other error codes indicate an error.

<br>
#### Example

```no-highlight
    int rc;

    rc = os_sanity_task_checkin(&my_task); 
    assert(rc == OS_OK);

```

---------------------
