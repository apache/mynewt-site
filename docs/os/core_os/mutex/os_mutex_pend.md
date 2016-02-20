## <font color="#F2853F" style="font-size:24pt">os_mutex_pend </font>

```no-highlight
os_error_t os_mutex_pend(struct os_mutex *mu, uint32_t timeout) 
```

Acquire ownership of a mutex.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu |  Pointer to mutex  |
| timeout | Timeout, in os ticks. A value of 0 means no timeout. A value of 0xFFFFFFFF means to wait forever.   |

#### Returned values

OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex was successfully acquired.

OS_TIMEOUT: the mutex was not available within the timeout specified.

OS_NOT_STARTED: Attempt to release a mutex before the os has been started.


#### Notes 

If the mutex is owned by another task and the timeout is 0 the function returns immediately with the error code OS_TIMEOUT. The calling task *does not* own the mutex when this occurs.

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
