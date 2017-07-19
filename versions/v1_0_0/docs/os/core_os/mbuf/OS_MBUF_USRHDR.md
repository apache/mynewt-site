## <font color="#F2853F" style="font-size:24pt">OS_MBUF_USRHDR</font>

```c
OS_MBUF_USRHDR(__om)
```

Macro used to get a pointer to the user packet header of an mbuf.

<br>


#### Arguments

| Arguments | Description |
|-----------|-------------|
| `__om` |  Pointer to mbuf (struct os_mbuf *). Must be head of chain (i.e. a packet header mbuf) |


<br>

#### Example

```c
    struct os_mbuf *om
    struct user_header *hdr;

    hdr = OS_MBUF_USRHDR(om);
```



