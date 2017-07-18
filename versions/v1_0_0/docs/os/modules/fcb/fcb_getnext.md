## <font color="F2853F" style="font-size:24pt">fcb_getnext</font>

```no-highlight
int fcb_getnext(struct fcb *, struct fcb_entry *loc);
```

Given element in location in loc, return with loc filled in with information about next element.

If loc->le_elem_off is set to 0, fcb_getnext() will return info about the oldest element in FCB.

Entry data can be read within the callback using flash_area_read(), using loc->fe_area, loc->fe_data_off, and loc->fe_data_len as arguments.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fcb | Points to FCB where data is written to. |
| loc | Info about element. On successful call 

#### Returned values

Returns 0 on success; nonzero on failure.
Returns FCB_ERR_NOVAR when there are no more elements left.

#### Notes

#### Example

