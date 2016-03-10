## <font color="#F2853F" style="font-size:24pt">OS_MBUF_PKTHDR</font>

```no-highlight
OS_MBUF_PKTHDR(__om)
```

Macro used to get a pointer to the os mbuf packet header of an mbuf.


<br>


#### Arguments

| Arguments | Description |
|-----------|-------------|
| __om |  Pointer to mbuf (struct os_mbuf *)  |


<br>

#### Example

```no-highlight
int
does_packet_have_data(struct os_mbuf *om)
{
    struct os_mbuf_pkthdr *hdr;

    hdr = OS_MBUF_PKTHDR(om);
    if (hdr->omp_len != 0) {
    	/* Packet has data in it */
    	return TRUE
    } else {
        /* Packet has no data */
        return FALSE;
    }
}
```


