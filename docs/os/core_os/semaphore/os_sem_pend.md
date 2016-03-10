## <font color="#F2853F" style="font-size:24pt"> os_sem_pend </font>

```no-highlight
os_error_t os_sem_pend(struct os_sem *sem, uint32_t timeout)
```

Wait for a semaphore for a given amount of time.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |
| timeout |  Amount of time, in os ticks, to wait for semaphore. A value of 0 means no wait. A value of 0xFFFFFFFF means wait forever.  |

#### Returned values

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore acquired successfully.

OS_TIMEOUT: the semaphore was not available within the timeout specified.

OS_NOT_STARTED: Attempt to release a semaphore before os started.

#### Notes 

If a timeout of 0 is used and the function returns OS_TIMEOUT, the semaphore was not available and was not acquired. No release of the semaphore should occur and the calling task does not own the semaphore.

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

