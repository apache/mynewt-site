## <font color="F2853F" style="font-size:24pt">fcb_walk</font>

```no-highlight
typedef int (*fcb_walk_cb)(struct fcb_entry *loc, void *arg);

int fcb_walk(struct fcb *fcb, struct flash_area *area, fcb_walk_cb cb,
	void *cb_arg);
```

Walks over all log entries in FCB. Callback function cb gets called for every entry. If cb wants to stop the walk, it should return a non-zero value.

If specific flash_area is specified, only entries within that sector are walked over.

Entry data can be read within the callback using flash_area_read(), using loc->fe_area, loc->fe_data_off, and loc->fe_data_len as arguments.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fcb | Points to FCB where data is written to. |
| area | Optional. Pointer to specific entry in fcb's array of sectors. |
| cb | Callback function which gets called for every valid entry fcb_walk encounters. |
| cb_arg | Optional. Parameter which gets passed to callback function.

#### Returned values

Returns 0 on success; nonzero on failure.

#### Notes

#### Example

