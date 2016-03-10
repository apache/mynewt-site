## <font color="F2853F" style="font-size:24pt"> os_sanity_check_reset</font>

```no-highlight
int os_sanity_check_reset(struct os_sanity_check *sc)
```
Reset the sanity check pointed to by sc.  This tells the sanity task that 
this sanity check is considered valid for another `sc_checkin_itvl` time 
ticks.
 
<br>
#### Arguments

| Arguments | Description | 
|-----------|-------------| 
| `sc` | Pointer to sanity check | 

<br>
#### Returned values

`OS_OK`: sanity check reset successful

All other error codes indicate an error.

<br>
#### Example

```no-highlight
    int rc;

    rc = os_sanity_check_reset(&my_sc); 
    assert(rc == OS_OK);

```

