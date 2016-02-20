## <font color="F2853F" style="font-size:24pt"> os_sem_init</font>

```no-highlight
os_error_t os_sem_init(struct os_sem *sem, uint16_t tokens)    
```

Initialize a semaphore with a given number of tokens. Should be called before the semaphore is used.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |
| tokens |  Initial number of tokens allocated to semaphore  |

#### Returned values

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore initialized successfully.

#### Notes 

<Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).>

#### Example

The following example shows how to initialize a semaphore used for exclusive access.

```no-highlight
struct os_mutex g_os_sem;
os_error_t err;

err = os_sem_init(&g_os_sem, 1);
assert(err == OS_OK);
```

---------------------
