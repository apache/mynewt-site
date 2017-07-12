## <font color="#F2853F" style="font-size:24pt">ble\_gap\_adv\_set\_fields</font>

```c
int
ble_gap_adv_set_fields(const struct ble_hs_adv_fields *adv_fields)
```

### Description

Configures the fields to include in subsequent advertisements.  This is a convenience wrapper for ble\_gap\_adv\_set\_data().

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| adv\_fields | Specifies the advertisement data. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EBUSY | Advertising is in progress. |
| BLE\_HS\_EMSGSIZE | The specified data is too large to fit in an advertisement. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
