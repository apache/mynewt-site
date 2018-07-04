## <font color="F2853F" style="font-size:24pt">fcb_init</font>

```no-highlight
int fcb_init(struct fcb *);
```

Initializes FCB. This function walks through the given sectors, finding out how much data already exists in the flash.
After calling this, you can start reading/writing data from FCB.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fcb | Structure describing the FCB. |

#### Returned values

Returns 0 on success; nonzero on failure.

#### Notes

User should fill in their portion of fcb before calling this function.

#### Example

