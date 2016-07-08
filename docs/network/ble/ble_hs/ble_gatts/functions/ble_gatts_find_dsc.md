## <font color="#F2853F" style="font-size:24pt">ble\_gatts\_find\_dsc</font>

```c
int
ble_gatts_find_dsc(const void *svc_uuid128, const void *chr_uuid128,
                   const void *dsc_uuid128, uint16_t *out_handle)
```

### Description

Retrieves the attribute handle associated with a local GATT descriptor. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| svc\_uuid128 | The UUID of the grandparent service. |
| chr\_uuid128 | The UUID of the parent characteristic. |
| dsc\_uuid128 | The UUID of the descriptor ro look up. |
| out\_handle | On success, populated with the handle of the descripytor attribute.  Pass null if you don't need this value. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_ENOENT | The specified service, characteristic, or descriptor could not be found. |
