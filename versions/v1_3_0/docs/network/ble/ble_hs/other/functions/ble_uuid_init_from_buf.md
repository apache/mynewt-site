## <font color="#F2853F" style="font-size:24pt">ble\_uuid\_init\_from\_buf</font>

```c
int
ble_uuid_init_from_buf(
    ble_uuid_any_t *uuid,
        const void *buf,
            size_t  len
)
```

### Description

Constructs a UUID object from a byte array.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| uuid | On success, this gets populated with the constructed UUID. |
| buf | The source buffer to parse. |
| len | The size of the buffer, in bytes. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EINVAL | The source buffer does not contain a valid uuid. |
