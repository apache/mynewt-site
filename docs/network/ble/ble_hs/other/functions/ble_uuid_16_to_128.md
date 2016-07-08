## <font color="#F2853F" style="font-size:24pt">ble\_uuid\_16\_to\_128</font>

```c
int
ble_uuid_16_to_128(uint16_t uuid16, void *out_uuid128)
```

### Description

Expands a 16-bit UUID into its 128-bit form. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| uuid16 | The 16-bit UUID to convert. |
| out\_uuid128 | On success, the resulting 128-bit UUID gets written here. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EINVAL | Uuid16 is not a valid 16-bit uuid. |
