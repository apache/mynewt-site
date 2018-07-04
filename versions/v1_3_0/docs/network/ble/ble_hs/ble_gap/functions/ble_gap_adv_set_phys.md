## <font color="#F2853F" style="font-size:24pt">ble\_gap\_adv\_set\_phys</font><font color="red" style="font-size:18pt"> [experimental] </font>

```c
int
ble_gap_adv_set_phys(uint8_t primary_phy, uint8_t secondary_phy)
```

### Description

Set primary and secondary PHYs for extended advertising procedure.

### Parameters

None

| *Parameter*   | *Description*                                                                                                   |
|---------------|-----------------------------------------------------------------------------------------------------------------|
| primary_phy   | Primary PHY to use for extended advertising procedure. <ul><li>BLE\_HCI\_LE\_1M</li> <li>BLE\_HCI\_LE\_CODED</li></ul> |
| secondary_phy | Secondary PHY to use for extended advertising procedure. <ul><li>BLE\_HCI\_LE\_1M</li> <li>BLE\_HCI\_LE\_2M</li> <li>BLE\_HCI\_LE\_CODED</li></ul> |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
