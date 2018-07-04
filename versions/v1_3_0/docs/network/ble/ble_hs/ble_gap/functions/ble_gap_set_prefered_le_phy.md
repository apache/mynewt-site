## <font color="#F2853F" style="font-size:24pt">ble\_gap\_set\_prefered\_le\_phy</font>

```c
int
ble_gap_set_prefered_le_phy(
            uint16_t conn_handle,
             uint8_t tx_phys_mask,
             uint8_t rx_phys_mask,
             uint16_t phy_opts
)
```

### Description

Set prefered LE PHY mask for given connection.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| conn\_handle   | The handle corresponding to the connection where new PHY mask should be applied. | 
| tx\_phys\_mask | Prefered tx PHY mask is a bit mask of: <ul><li>BLE\_GAP\_LE\_PHY\_1M\_MASK</li> <li>BLE\_GAP\_LE\_PHY\_2M\_MASK</li><li>BLE\_GAP\_LE\_PHY\_CODED\_MASK</li></ul> |
| rx\_phys\_mask | Prefered rx PHY mask is a bit mask of: <ul><li>BLE\_GAP\_LE\_PHY\_1M\_MASK</li> <li>BLE\_GAP\_LE\_PHY\_2M\_MASK</li><li>BLE\_GAP\_LE\_PHY\_CODED\_MASK</li></ul> |
| phy\_opts | PHY options for coded PHY. One of: <ul><li>BLE\_GAP\_LE\_PHY\_CODED\_ANY</li> <li>BLE\_GAP\_LE\_PHY\_CODED\_S2</li><li>BLE\_GAP\_LE\_PHY\_CODED\_S8</li></ul> |
### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
