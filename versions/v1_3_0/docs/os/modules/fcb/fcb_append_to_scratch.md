## <font color="F2853F" style="font-size:24pt">fcb_append_to_scratch</font>

```no-highlight
int fcb_append_to_scratch(struct fcb *fcb);
```

This can be used if FCB created to have scratch block(s). Once FCB fills up with data, fcb_append() will fail. This routine can be called to start using the reserve block.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fcb | Points to FCB. |


#### Returned values

Returns 0 on success; nonzero on failure.

#### Notes

#### Example

