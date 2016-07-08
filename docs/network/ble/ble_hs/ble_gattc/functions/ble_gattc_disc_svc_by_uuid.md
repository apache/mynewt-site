## <font color="#F2853F" style="font-size:24pt">ble\_gattc\_disc\_svc\_by\_uuid</font>

```c
int
ble_gattc_disc_svc_by_uuid(uint16_t conn_handle, const void *svc_uuid128,
                           ble_gatt_disc_svc_fn *cb, void *cb_arg)
```

### Description

Initiates GATT procedure: Discover Primary Service by Service UUID. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The connection over which to execute the procedure. |
| service\_uuid128 | The 128-bit UUID of the service to discover. |
| cb | The function to call to report procedure status updates; null for no callback. |
| cb\_arg | The optional argument to pass to the callback function. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [BLE host core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
