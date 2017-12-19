## <font color="#F2853F" style="font-size:24pt">ble\_gap\_adv\_set\_tx\_power</font><font color="red" style="font-size:18pt"> [experimental] </font>

```c
int
ble_gap_adv_set_tx_power(int8_t  tx_power)
```

### Description

Set Tx Power level for extended advertising procedure.

### Parameters

None

| *Parameter* | *Description*                                             |
|-------------|-----------------------------------------------------------|
| tx_power    | Tx Power level to use for extended advertising procedure. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
