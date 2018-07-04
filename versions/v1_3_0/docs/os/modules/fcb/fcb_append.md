## <font color="F2853F" style="font-size:24pt">fcb_append</font>

```no-highlight
int fcb_append(struct fcb *fcb, uint16_t len, struct fcb_entry *append_loc);
```

Start writing a new element to flash. This routine reserves the space in the flash by writing out the element header.

When writing the contents for the entry, use append_loc->fl_area and append_loc->fl_data_off as arguments to flash_area_write(). When finished, call fcb_append_finish() with append_loc as argument.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fcb | Points to FCB where data is written to. |
| len | Number of bytes to reserve for the element. |
| loc | Pointer to fcb_entry. fcb_append() will fill this with info about where the element can be written to. |

#### Returned values

Returns 0 on success; nonzero on failure.
FCB_ERR_NOSPACE is returned if FCB is full.

#### Notes

If FCB is full, you need to make more space. This can be done by calling fcb_rotate(). Or if you've reserved scratch sectors, you can take those into use by calling fcb_append_to_scratch().

#### Example

