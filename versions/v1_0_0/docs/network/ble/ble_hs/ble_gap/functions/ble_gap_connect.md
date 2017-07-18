## <font color="#F2853F" style="font-size:24pt">ble\_gap\_connect</font>

```c
int
ble_gap_connect(
                             uint8_t  own_addr_type,
                             uint8_t  peer_addr_type,
                       const uint8_t *peer_addr,
                             int32_t  duration_ms,
    const struct ble_gap_conn_params *conn_params,
                    ble_gap_event_fn *cb,
                                void *cb_arg
)
```

### Description

Initiates a connect procedure.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| own\_addr\_type | The type of address the stack should use for itself during connection establishment. <ul><li>BLE\_ADDR\_TYPE\_PUBLIC</li> <li>BLE\_ADDR\_TYPE\_RANDOM</li> <li>BLE\_ADDR\_TYPE\_RPA\_PUB\_DEFAULT</li> <li>BLE\_ADDR\_TYPE\_RPA\_RND\_DEFAULT</li></ul> |
| peer\_addr\_type | The peer's address type.  One of: <ul><li>BLE\_HCI\_CONN\_PEER\_ADDR\_PUBLIC</li> <li>BLE\_HCI\_CONN\_PEER\_ADDR\_RANDOM</li> <li>BLE\_HCI\_CONN\_PEER\_ADDR\_PUBLIC\_IDENT</li> <li>BLE\_HCI\_CONN\_PEER\_ADDR\_RANDOM\_IDENT</li> <li>BLE\_GAP\_ADDR\_TYPE\_WL</li></ul> |
| peer\_addr | The identity address of the peer to connect to. This parameter is ignored when the white list is used. |
| duration\_ms | The duration of the discovery procedure. On expiration, the procedure ends and a BLE\_GAP\_EVENT\_DISC\_COMPLETE event is reported.  Units are milliseconds. |
| conn\_params | Additional arguments specifying the particulars of the connect procedure.  Specify null for default values. |
| cb | The callback to associate with this connect procedure.  When the connect procedure completes, the result is reported through this callback.  If the connect procedure succeeds, the connection inherits this callback as its event-reporting mechanism. |
| cb\_arg | The optional argument to pass to the callback function. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
