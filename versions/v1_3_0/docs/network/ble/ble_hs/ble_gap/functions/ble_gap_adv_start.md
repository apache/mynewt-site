## <font color="#F2853F" style="font-size:24pt">ble\_gap\_adv\_start</font>

```c
int
ble_gap_adv_start(
                            uint8_t  own_addr_type,
                   const ble_addr_t *direct_addr,
                            int32_t  duration_ms,
    const struct ble_gap_adv_params *adv_params,
                   ble_gap_event_fn *cb,
                               void *cb_arg
)
```

### Description

Initiates advertising.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| own\_addr\_type | The type of address the stack should use for itself.  Valid values are: <ul><li>BLE\_OWN\_ADDR\_PUBLIC</li> <li>BLE\_OWN\_ADDR\_RANDOM</li> <li>BLE\_OWN\_ADDR\_RPA\_PUBLIC\_DEFAULT</li> <li>BLE\_OWN\_ADDR\_RPA\_RANDOM\_DEFAULT</li></ul> |
| direct\_addr | The peer's address for directed advertising. This parameter shall be non-NULL if directed advertising is being used. |
| duration\_ms | The duration of the advertisement procedure. On expiration, the procedure ends and a BLE\_GAP\_EVENT\_ADV\_COMPLETE event is reported.  Units are milliseconds.  Specify BLE\_HS\_FOREVER for no expiration. |
| adv\_params | Additional arguments specifying the particulars of the advertising procedure. |
| cb | The callback to associate with this advertising procedure.  If advertising ends, the event is reported through this callback.  If advertising results in a connection, the connection inherits this callback as its event-reporting mechanism. |
| cb\_arg | The optional argument to pass to the callback function. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
