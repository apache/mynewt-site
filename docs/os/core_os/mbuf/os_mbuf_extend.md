## <font color="#F2853F" style="font-size:24pt"> os_mbuf_extend</font>

```no-highlight
void *os_mbuf_extend(struct os_mbuf *om, uint16_t len);
```

Increases the length of an mbuf chain by the specified amount.  If there is not sufficient room in the last buffer, a new buffer is allocated and appended to the chain.  It is an error to request more data than can fit in a single buffer.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| om | Pointer to mbuf chain |
| len | Number of bytes to increase packet header |

<br>

#### Returned values

Pointer to start of extended data. Caller is guaranteed that there are at least *len* bytes from this pointer to the end of the mbuf.

Returns NULL if extension fails due to insufficient mbufs or *len* too large.
<br>



#### Example

```no-highlight
    uint8_t *dptr;
	struct os_mbuf *om;
    struct my_data_struct my_data;	
	
    /* Obtain enough room to add "my_data" to an mbuf chain */
    dptr = os_mbuf_extend(om, sizeof(struct my_data_struct));
    if (dptr) {
        memcpy(dptr, &my_data, sizeof(struct my_data_struct));
    }
```

---------------------
