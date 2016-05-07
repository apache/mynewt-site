## <font color="#F2853F" style="font-size:24pt"> json_encode_object_entry </font>

```no-highlight
   int json_encode_object_entry(struct json_encoder *encoder, char *key, struct json_value *val)
```

This function writes out a name for a field, followed by ":" character, and the value itself. How value is treated depends on the type of the value.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| encoder |  json_encoder to use  |
| key | name to write out |
| val | value to write out |


#### Returned values

0 on success.

#### Notes

#### Example
