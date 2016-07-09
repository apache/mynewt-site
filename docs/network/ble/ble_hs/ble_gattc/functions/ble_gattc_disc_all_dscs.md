## <font color="#F2853F" style="font-size:24pt">ble\_gattc\_disc\_all\_dscs</font>

```c
int
ble_gattc_disc_all_dscs(
           uint16_t  conn_handle,
           uint16_t  chr_def_handle,
           uint16_t  chr_end_handle,
    ble_gatt_dsc_fn *cb,
               void *cb_arg
)
```

### Description

Initiates GATT procedure: Discover All Characteristic Descriptors. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The connection over which to execute the procedure. |
| chr\_def\_handle | The handle of the characteristic definition attribute. |
| chr\_end\_handle | The last handle in the characteristic definition. |
| cb | The function to call to report procedure status updates; null for no callback. |
| cb\_arg | The optional argument to pass to the callback function. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
