## <font color="#F2853F" style="font-size:24pt">ble\_gatts\_find\_svc</font>

```c
int
ble_gatts_find_svc(
    const void *uuid128,
      uint16_t *out_handle
)
```

### Description

Retrieves the attribute handle associated with a local GATT service.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| uuid128 | The UUID of the service to look up. |
| out\_handle | On success, populated with the handle of the service attribute.  Pass null if you don't need this value. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_ENOENT | The specified service could not be found. |
