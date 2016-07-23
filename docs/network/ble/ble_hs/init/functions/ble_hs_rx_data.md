## <font color="#F2853F" style="font-size:24pt">ble\_hs\_rx\_data</font>

```c
int
ble_hs_rx_data(struct os_mbuf **om)
```

### Description

Called when a data packet is received from the controller.  This function consumes the supplied mbuf, regardless of the outcome.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| om | The incoming data packet, beginning with the HCI ACL data header. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
