## <font color="#F2853F" style="font-size:24pt">ble\_gattc\_notify\_custom</font>

```c
int
ble_gattc_notify_custom(
      uint16_t  conn_handle,
      uint16_t  chr_val_handle,
    const void *attr_data,
      uint16_t  attr_data_len
)
```

### Description

Sends a "free-form" characteristic notification.  The content of the message is specified in the attr parameter. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | The connection over which to execute the procedure. |
| chr\_val\_handle | The attribute handle to indicate in the outgoing notification. |
| attr\_data | The characteristic value to include in the outgoing notification. |
| attr\_data\_len | The number of bytes of attribute data to include in the notification. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
