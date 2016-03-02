## <font color="#F2853F" style="font-size:24pt">OS_MBUF_PKTLEN</font>

```no-highlight
OS_MBUF_PKTLEN(__om)
```

Macro used to get the length of an entire mbuf chain.


<br>


#### Arguments

| Arguments | Description |
|-----------|-------------|
| __om |  Pointer to mbuf (struct os_mbuf *)  |


<br>

#### Example

```no-highlight
    uint16_t pktlen;
    struct os_mbuf *om;

    /* Check if there is any data in the mbuf chain */
    pktlen = OS_MBUF_PKTLEN(om);
    if (pktlen != 0) {
        /* mbuf chain has data */
    }
```

---------------------

