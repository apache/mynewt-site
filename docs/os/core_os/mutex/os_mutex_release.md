## <font color="#F2853F" style="font-size:24pt">os_mutex_release</font>

```no-highlight
os_error_t os_mutex_release(struct os_mutex *mu)
```

Release ownership of a mutex


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu|  Pointer to mutex  |

#### Returned values
OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex initialized successfully.

OS_BAD_MUTEX: The mutex was not owned by the task attempting to release it.

OS_NOT_STARTED: Attempt to release a mutex before the os has been started.


#### Example


```no-highlight
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_pend(&g_mutex1, 0);
assert(err == OS_OK);

/* Perform operations requiring exclusive access */

err = os_mutex_release(&g_mutex1);
assert(err == OS_OK);
```

---------------------
