## <font color="#F2853F" style="font-size:24pt">ble\_gap\_wl\_set</font>

```c
int
ble_gap_wl_set(const struct ble_gap_white_entry *white_list,
               uint8_t white_list_count)
```

### Description

Overwrites the controller's white list with the specified contents. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| white\_list | The entries to write to the white list. |
| white\_list\_count | The number of entries in the white list. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [BLE host core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
