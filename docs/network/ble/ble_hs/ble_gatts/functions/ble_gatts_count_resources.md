## <font color="#F2853F" style="font-size:24pt">ble\_gatts\_count\_resources</font>

```c
int
ble_gatts_count_resources(
    const struct ble_gatt_svc_def *svcs,
        struct ble_gatt_resources *res
)
```

### Description

Accumulates counts of each resource type required by the specified service definition array.  This function is generally used to calculate some host configuration values prior to initialization.  This function adds the counts to the appropriate fields in the supplied ble\_gatt\_resources object without clearing them first, so it can be called repeatedly with different inputs to calculate totals.  Be sure to zero the resource struct prior to the first call to this function.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| svcs | The service array containing the resource definitions to be counted. |
| res | The resource counts are accumulated in this struct. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EINVAL | The svcs array contains an invalid resource definition. |
