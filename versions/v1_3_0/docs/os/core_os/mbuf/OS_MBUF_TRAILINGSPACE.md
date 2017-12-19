## <font color="#F2853F" style="font-size:24pt">OS_MBUF_TRAILINGSPACE</font>

```c
OS_MBUF_TRAILINGSPACE(__om)
```

Macro used to get the amount of trailing space in an mbuf (in bytes).


<br>


#### Arguments

| Arguments | Description |
|-----------|-------------|
| __om |  Pointer to mbuf (struct os_mbuf *)  |


<br>

#### Notes
This macro works on both normal mbufs and packet header mbufs. The amount of trailing space is the number of bytes between the current om_data pointer of the mbuf and the end of the mbuf.

<br>

#### Example

```c
    uint16_t space;
    struct os_mbuf *om;
    struct my_data_struct my_data;

    /* Copy data from "my_data" to the end of an mbuf but only if there is enough room */
    space = OS_MBUF_TRAILINGSPACE(om);
    if (space >= sizeof(struct my_data_struct)) {
        memcpy(om->om_data, &my_data, sizeof(struct my_data_struct));
    }
```


