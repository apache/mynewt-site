## <font color="#F2853F" style="font-size:24pt">ble\_gap\_conn\_rssi</font>

```c
int
ble_gap_conn_rssi(
    uint16_t  conn_handle,
      int8_t *out_rssi
)
```

### Description

Retrieves the most-recently measured RSSI for the specified connection.  A connection's RSSI is updated whenever a data channel PDU is received. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle | Specifies the connection to query. |
| out\_rssi | On success, the retrieved RSSI is written here. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [HCI return code](../../ble_hs_return_codes/#return-codes-hci) | The controller rejected the request. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
