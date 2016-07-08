## <font color="#F2853F" style="font-size:24pt">ble\_hs\_id\_copy\_addr</font>

```c
int
ble_hs_id_copy_addr(uint8_t id_addr_type, uint8_t *out_id_addr,
                    int *out_is_nrpa)
```

### Description

Retrieves one of the device's identity addresses.  The device can have two identity addresses: one public and one random.  The id\_addr\_type argument specifies which of these two addresses to retrieve. 

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| id\_addr\_type | The type of identity address to retrieve. Valid values are: <ul><li>BLE\_ADDR\_TYPE\_PUBLIC</li> <li>BLE\_ADDR\_TYPE\_RANDOM</li></ul> |
| out\_id\_addr | On success, the requested identity address is copied into this buffer.  The buffer must be at least six bytes in size. |
| out\_is\_nrpa | On success, the pointed-to value indicates whether the retrieved address is a non-resolvable private address. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EINVAL | An invalid address type was specified. |
| BLE\_HS\_ENOADDR | The device does not have an identity address of the requested type. |
| other | Other ble host core code on error. |
