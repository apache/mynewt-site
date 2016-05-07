## <font color="#F2853F" style="font-size:24pt"> json_encode_object_key </font>

```no-highlight
   int json_encode_object_key(struct json_encoder *encoder, char *key)
```

This function writes out a name for a field, followed by ":" character. You would use this e.g. when the value that follows is a JSON object.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| encoder |  json_encoder to use  |
| key | name to write out |


#### Returned values

0 on success.

#### Notes

#### Example
