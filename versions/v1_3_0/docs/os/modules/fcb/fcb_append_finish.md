## <font color="F2853F" style="font-size:24pt">fcb_append_finish</font>

```no-highlight
int fcb_append_finish(struct fcb *fcb, struct fcb_entry *append_loc);
```

Finalizes the write of new element. FCB computes the checksum over the element and updates it in flash.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fcb | Points to FCB where data is written to. |
| append_loc | Pointer to fcb_entry. Use the fcb_entry returned by fcb_append(). |

#### Returned values

Returns 0 on success; nonzero on failure.

#### Notes

You need to call fcb_append_finish() after writing the element contents. Otherwise FCB will consider this entry to be invalid, and skips over it when reading.

#### Example

