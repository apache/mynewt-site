## <font color="#F2853F" style="font-size:24pt">ble\_gap\_disc\_cancel</font>

```c
int
ble_gap_disc_cancel(void)
```

### Description

Cancels the discovery procedure currently in progress.  A success return code indicates that scanning has been fully aborted; a new discovery or connect procedure can be initiated immediately.

### Parameters

None

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EALREADY | There is no discovery procedure to cancel. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
