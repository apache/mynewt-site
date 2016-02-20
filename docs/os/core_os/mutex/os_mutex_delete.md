## <font color="#F2853F" style="font-size:24pt">os_mutex_delete </font>

```no-highlight
os_error_t os_mutex_pend(struct os_mutex *mu)
```

Delete a mutex

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu |  Pointer to mutex  |

#### Returned values

OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex initialized successfully.

OS_NOT_STARTED: Attempt to release a mutex before the os has been started.

#### Example

```no-highlight
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_delete(&g_mutex1);
assert(err == OS_OK);
```

---------------------
