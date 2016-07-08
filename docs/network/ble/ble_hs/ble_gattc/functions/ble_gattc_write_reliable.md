## <font color="#F2853F" style="font-size:24pt">ble\_gattc\_write\_reliable</font>

```c
int
ble_gattc_write_reliable(uint16_t conn_handle,
                         const struct ble_gatt_attr *attrs,
                         int num_attrs, ble_gatt_reliable_attr_fn *cb,
                         void *cb_arg)
```

### Description

Initiates GATT procedure: Reliable Writes. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The connection over which to execute the procedure. |
| attrs | An array of attribute descriptors; specifies which characteristics to write to and what data to write to them. |
| num\_attrs | The number of characteristics to write; equal to the number of elements in the 'attrs' array. |
| cb | The function to call to report procedure status updates; null for no callback. |
| cb\_arg | The optional argument to pass to the callback function. |

### Returned values

None
