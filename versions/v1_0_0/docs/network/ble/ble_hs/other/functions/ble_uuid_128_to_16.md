## <font color="#F2853F" style="font-size:24pt">ble\_uuid\_128\_to\_16</font>

```c
uint16_t
ble_uuid_128_to_16(const void *uuid128)
```

### Description

Attempts to convert the supplied 128-bit UUID into its shortened 16-bit form.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| uuid128 | The 128-bit UUID to attempt to convert. This must point to 16 contiguous bytes. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| A positive 16-bit unsigned integer | Success. |
| 0 | The uuid cannot be represented in 16 bits. |
