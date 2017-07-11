## <font color="#F2853F" style="font-size:24pt">ble\_gap\_update\_params</font>

```c
int
ble_gap_update_params(
                           uint16_t  conn_handle,
    const struct ble_gap_upd_params *params
)
```

### Description

Initiates a connection parameter update procedure.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The handle corresponding to the connection to update. |
| params | The connection parameters to attempt to update to. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_ENOTCONN | The there is no connection with the specified handle. |
| BLE\_HS\_EALREADY | A connection update procedure for this connection is already in progress. |
| BLE\_HS\_EINVAL | Requested parameters are invalid. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
