## <font color="#F2853F" style="font-size:24pt">ble\_gap\_set\_prefered\_default\_le\_phy</font>

```c
int
ble_gap_set_prefered_default_le_phy(
            uint8_t tx_phys_mask,
            uint8_t rx_phys_mask
)
```

### Description

Set prefered default LE PHY mask. It is used for new connections.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| tx\_phys\_mask | Prefered tx PHY mask is a bit mask of: <ul><li>BLE\_GAP\_LE\_PHY\_1M\_MASK</li> <li>BLE\_GAP\_LE\_PHY\_2M\_MASK</li><li>BLE\_GAP\_LE\_PHY\_CODED\_MASK</li></ul> |
| rx\_phys\_mask | Prefered rx PHY mask is a bit mask of: <ul><li>BLE\_GAP\_LE\_PHY\_1M\_MASK</li> <li>BLE\_GAP\_LE\_PHY\_2M\_MASK</li><li>BLE\_GAP\_LE\_PHY\_CODED\_MASK</li></ul> |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
