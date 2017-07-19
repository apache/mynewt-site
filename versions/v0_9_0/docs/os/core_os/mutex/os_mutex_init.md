## <font color="#F2853F" style="font-size:24pt">os_mutex_init</font>

```c
os_error_t os_mutex_init(struct os_mutex *mu)
```

Initialize the mutex. Must be called before the mutex can be used.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu|  Pointer to mutex  |

#### Returned values

OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex initialized successfully.

#### Notes 

<Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).>

#### Example


```c
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_init(&g_mutex1);
assert(err == OS_OK);
```


   
