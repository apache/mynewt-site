## <font color="F2853F" style="font-size:24pt"> os_sanity_check_register</font>

```no-highlight
int os_sanity_check_register(struct os_sanity_check *sc)
```
Register the sanity check pointed to by `sc` with the sanity task.  After registration
the sanity task will check this sanity check with every run of the sanity task.
 
<br>
#### Arguments

| Arguments | Description | 
|-----------|-------------| 
| `sc` | Pointer to sanity check | 

<br>
#### Returned values

`OS_OK`: sanity check successfully registered

All other error codes indicate an error.

<br>
#### Example

```no-highlight
    int rc;

    rc = os_sanity_check_register(&my_sc); 
    assert(rc == OS_OK);

```

