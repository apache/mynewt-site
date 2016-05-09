## <font color="#F2853F" style="font-size:24pt"> json_encode_object_finish </font>

```no-highlight
   int json_encode_object_finish(struct json_encoder *encoder)
```

This function finalizes the encoded JSON object. This means writing out the last "}" character.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| encoder |  json_encoder to use  |


#### Returned values

0 on success.

#### Notes

#### Example

```c
static int
imgr_list(struct nmgr_jbuf *njb)
{
    struct json_encoder *enc;
    struct json_value array;

    ...

    json_encode_object_start(enc);
    json_encode_object_entry(enc, "images", &array);
    json_encode_object_finish(enc);

    return 0;
}

```
