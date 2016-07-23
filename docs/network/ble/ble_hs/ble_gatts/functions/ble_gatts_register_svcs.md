## <font color="#F2853F" style="font-size:24pt">ble\_gatts\_register\_svcs</font>

```c
int
ble_gatts_register_svcs(
    const struct ble_gatt_svc_def *svcs,
             ble_gatt_register_fn *cb,
                             void *cb_arg
)
```

### Description

Registers a set of services, characteristics, and descriptors to be accessed by GATT clients.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| svcs | A table of the service definitions to be registered. |
| cb | The function to call for each service, characteristic, and descriptor that gets registered. |
| cb\_arg | The optional argument to pass to the callback function. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_ENOMEM | Registration failed due to resource exhaustion. |
| BLE\_HS\_EINVAL | The service definition table contains an invalid element. |
