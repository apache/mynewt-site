## <font color="#F2853F" style="font-size:24pt"> os_sem_delete </font>

```no-highlight
os_error_t os_sem_delete(struct os_sem *sem)
```

Delete a semaphore

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |

#### Returned values

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore deleted successfully.

OS_NOT_STARTED: Attempt to release a semaphore before os started.

#### Notes 

Care must be taken when deleting a semaphore as deleting a semaphore used by other tasks could causes unexpected/unwanted behavior.

#### Example

```no-highlight
struct os_sem g_os_sem;
os_error_t err;

err = os_sem_delete(&g_os_sem);
assert(err == OS_OK);
```

---------------------
