## <font color="#F2853F" style="font-size:24pt">OS_MBUF_DATA</font>

```no-highlight
OS_MBUF_DATA(__om, __type)
```

Macro used to cast the data pointer of an mbuf to a given type.


<br>


#### Arguments

| Arguments | Description |
|-----------|-------------|
| __om |  Pointer to mbuf (struct os_mbuf *)  |
| __type |  Type to cast  |


<br>

#### Example

```no-highlight
    struct os_mbuf *om
    uint8_t *rxbuf;

    rxbuf = OS_MBUF_DATA(om, uint8_t *);
```

---------------------

