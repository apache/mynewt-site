## <font color="#F2853F" style="font-size:24pt">ble\_gattc\_notify</font>

```c
int
ble_gattc_notify(uint16_t conn_handle, uint16_t chr_val_handle)
```

### Description

Sends a characteristic notification.  The content of the message is read from the specified characteristic. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The connection over which to execute the procedure. |
| chr\_val\_handle | The value attribute handle of the characteristic to include in the outgoing notification. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [BLE host core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
