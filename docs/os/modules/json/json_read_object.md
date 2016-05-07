## <font color="#F2853F" style="font-size:24pt"> json_read_object </font>

```no-highlight
   int json_read_object(struct json_buffer *jb, const struct json_attr_t *attrs)
```

This function reads in JSON data stream, while looking for name/value pairs described in *attrs*. *attrs* is an array; end of the array is indicated by an entry with *NULL* as the name.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| jb |  json_decoder to use  |
| attrs | array of attributes to look for |

#### Returned values

0 on success.

#### Notes

#### Example
