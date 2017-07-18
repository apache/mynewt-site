## <font color="#F2853F" style="font-size:24pt">ble\_uuid\_to\_str</font>

```c
char *
ble_uuid_to_str(
    const ble_uuid_t *uuid,
                char *dst
)
```

### Description

Converts the specified UUID to its string representation.  Example string representations: <ul><li>16-bit:  0x1234</li> <li>32-bit:  0x12345678</li> <li>128-bit: 12345678-1234-1234-1234-123456789abc</li></ul>

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| uuid | The source UUID to convert. |
| dst | The destination buffer. |

### Returned values

A pointer to the supplied destination buffer.
