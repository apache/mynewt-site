## <font color="#F2853F" style="font-size:24pt"> os_sem_release </font>

```no-highlight
os_error_t os_sem_release(struct os_sem *sem)
```

Release a semaphore that you are holding. This adds a token to the semaphore.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |

#### Returned values

OS_NOT_STARTED: Called before os has been started.

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore released successfully.

#### Notes 


#### Example

```no-highlight
struct os_sem g_os_sem;
os_error_t err;

err = os_sem_pend(&g_os_sem, OS_TIMEOUT_NEVER);
assert(err == OS_OK);

/* Perform operations requiring semaphore lock */

err = os_sem_release(&g_os_sem);
assert(err == OS_OK);
```
