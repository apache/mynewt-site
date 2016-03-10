## <font color="F2853F" style="font-size:24pt"> os_sanity_check_init</font>

```no-highlight
int os_sanity_check_init(struct os_sanity_check *sc)
```
Initialize the sanity check pointed to by `sc`.  Sets default values, and ensures
memory is cleared out.
 
<br>
#### Arguments

| Arguments | Description | 
|-----------|-------------| 
| `sc` | Pointer to sanity check | 

<br>
#### Returned values

`OS_OK`: sanity check initialization is successful 

All other error codes indicate an error.

<br>
#### Example

```no-highlight
    int rc;

    rc = os_sanity_task_check_init(&my_sanity_check); 
    assert(rc == OS_OK);

```

