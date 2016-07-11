## <font color="#F2853F" style="font-size:24pt">ble\_att\_svr\_write\_local</font>

```c
int
ble_att_svr_write_local(
      uint16_t  attr_handle,
    const void *data,
      uint16_t  data_len
)
```

### Description

Writes a locally registered attribute.  If the specified attribute handle corresponds to a GATT characteristic value or descriptor, the write is performed by calling the registered GATT access callback. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| attr\_handle | The 16-bit handle of the attribute to write. |
| data | Buffer containing the data to write to the attribute. |
| data\_len | The number of bytes to write. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success | 
| [ATT return code](../../ble_hs_return_codes/#return-codes-att) | NimBLE host att return code if the attribute access callback reports failure. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
