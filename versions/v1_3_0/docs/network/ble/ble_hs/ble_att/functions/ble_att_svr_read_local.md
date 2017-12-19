## <font color="#F2853F" style="font-size:24pt">ble\_att\_svr\_read\_local</font>

```c
int
ble_att_svr_read_local(
          uint16_t   attr_handle,
    struct os_mbuf **out_om
)
```

### Description

Reads a locally registered attribute.  If the specified attribute handle coresponds to a GATT characteristic value or descriptor, the read is performed by calling the registered GATT access callback.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| attr\_handle | The 16-bit handle of the attribute to read. |
| out\_om | On success, this is made to point to a newly-allocated mbuf containing the attribute data read. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [ATT return code](../../ble_hs_return_codes/#return-codes-att) | The attribute access callback reports failure. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
