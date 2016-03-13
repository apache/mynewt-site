## <font color="F2853F" style="font-size:24pt"> os_sanity_task_init</font>

```c
int os_sanity_task_init(int num_secs);
```
Initialize the os sanity task.  `num_secs` is the number of seconds to wait
in between runs of the sanity task.

<br>
#### Arguments

| Arguments | Description | 
|-----------|-------------| 
| `num_secs` | Number of seconds to wait in between running sanity checks. | 

<br>
#### Returned values

`OS_OK`: Sanity task was successfully created.

All other error codes indicate an error.

<br>
#### Example

```c
/* Run sanity checks every 50 seconds */

#define SANITY_TASK_INTERVAL (50)
    int rc;

    rc = os_sanity_task_init(SANITY_TASK_INTERVAL); 
    assert(rc == OS_OK);
```

