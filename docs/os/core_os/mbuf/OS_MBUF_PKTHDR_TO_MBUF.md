## <font color="#F2853F" style="font-size:24pt">OS_MBUF_PKTHDR_TO_MBUF</font>

```no-highlight
OS_MBUF_PKTHDR_TO_MBUF(__hdr)
```

Macro used to get a pointer to the mbuf given a pointer to the os mbuf packet header

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| __hdr |  Pointer to os mbuf packet header (struct os_mbuf_pkthdr *)  |

<br>


#### Example

```no-highlight
    struct os_mbuf *om;
    struct os_mbuf_pkthdr *hdr;

    om = OS_MBUF_PKTHDR_TO_MBUF(hdr);
    os_mbuf_free_chain(om);
```



