## <font color="#F2853F" style="font-size:24pt">ble\_hs\_mbuf\_to\_flat</font>

```c
int
ble_hs_mbuf_to_flat(
    const struct os_mbuf *om,
                    void *flat,
                uint16_t  max_len,
                uint16_t *out_copy_len
)
```

### Description

Copies the contents of an mbuf into the specified flat buffer.  If the flat buffer is too small to contain the mbuf's contents, it is filled to capacity and BLE\_HS\_EMSGSIZE is returned.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| om | The mbuf to copy from. |
| flat | The destination flat buffer. |
| max\_len | The size of the flat buffer. |
| out\_copy\_len | The number of bytes actually copied gets written here. |

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| BLE\_HS\_EMSGSIZE | The flat buffer is too small to contain the mbuf's contents. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
