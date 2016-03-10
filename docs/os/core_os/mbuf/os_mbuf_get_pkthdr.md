## <font color="#F2853F" style="font-size:24pt">os_mbuf_get_pkthdr</font>

```no-highlight
struct os_mbuf *os_mbuf_get_pkthdr(struct os_mbuf_pool *omp, uint8_t pkthdr_len);
```

Allocates a packet header mbuf from the mbuf pool pointed to by *omp*. Adds a user header of length *pkthdr_len* to packet header mbuf.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| om | Pointer to mbuf pool from which to allocate mbuf |
| pkthdr_len | The user header packet length to allocate for the packet header mbuf |

<br>

#### Returned values

Returns a pointer to the allocated mbuf or NULL if there are no mbufs available or the user packet header was too large.

<br>

#### Notes
The packet header mbuf returned will have its data pointer incremented by the sizeof(struct os_mbuf_pkthdr) as well as the amount of user header data (i.e. *pkthdr_len*). In other words, the data pointer is offset from the start of the mbuf by: sizeof(struct os_mbuf) + sizeof(struct os_mbuf_pkthdr) + pkthdr_len. The `om_pkthdr_len` element in the allocated mbuf is set to: sizeof(struct os_mbuf_pkthdr) + pkthdr_len.

<br>

#### Example

```no-highlight
	struct os_mbuf *om;
    struct my_user_header my_hdr;

    /* Get a packet header mbuf with a user header in it */
    om = os_mbuf_get_pkthdr(&g_mbuf_pool, sizeof(struct my_user_header));
    if (om) {
        /* Packet header mbuf was allocated */
    }
```


