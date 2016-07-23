## <font color="#F2853F" style="font-size:24pt">ble\_gatts\_find\_chr</font>

```c
int
ble_gatts_find_chr(
    const void *svc_uuid128,
    const void *chr_uuid128,
      uint16_t *out_def_handle,
      uint16_t *out_val_handle
)
```

### Description

Retrieves the pair of attribute handles associated with a local GATT characteristic.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| svc\_uuid128 | The UUID of the parent service. |
| chr\_uuid128 | The UUID of the characteristic to look up. |
| out\_def\_handle | On success, populated with the handle of the characteristic definition attribute. Pass null if you don't need this value. |
| out\_val\_handle | On success, populated with the handle of the characteristic value attribute. Pass null if you don't need this value. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_ENOENT | The specified service or characteristic could not be found. |
