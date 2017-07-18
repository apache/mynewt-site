## <font color="#F2853F" style="font-size:24pt">OS_MBUF_USRHDR_LEN</font>

```c
OS_MBUF_USRHDR_LEN(__om)
```

Macro used to retrieve the length of the user packet header in an mbuf.

<br>


#### Arguments

| Arguments | Description |
|-----------|-------------|
| `__om` |  Pointer to mbuf (struct os_mbuf *). Must be head of chain (i.e. a packet header mbuf) |


<br>

#### Example

```c
    uint16_t user_length;
    struct os_mbuf *om
    struct user_header *hdr;

    user_length  = OS_MBUF_USRHDR_LEN(om);
```



