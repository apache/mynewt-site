## <font color="#F2853F" style="font-size:24pt">ble\_gap\_security\_initiate</font>

```c
int
ble_gap_security_initiate(uint16_t conn_handle)
```

### Description

Initiates the GAP encryption procedure.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The handle corresponding to the connection to encrypt. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_ENOTCONN | The there is no connection with the specified handle. |
| BLE\_HS\_EALREADY | An encrpytion procedure for this connection is already in progress. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
