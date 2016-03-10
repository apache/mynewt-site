## <font color="#F2853F" style="font-size:24pt">os_msys_get_pkthdr</font>

```no-highlight
struct os_mbuf *os_msys_get_pkthdr(uint16_t dsize, uint16_t user_hdr_len)
```

Retrieve a packet header mbuf from the system mbuf pools with *user_hdr_len* bytes available for the user header in the mbuf.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| dsize | Minimum requested size of mbuf. Actual mbuf allocated may not accommodate *dsize* |
| user_hdr_len | Size, in of bytes, of user header in the mbuf |

<br>

#### Returned values
Pointer to mbuf or NULL if no mbufs were available.

<br>

#### Notes
The same notes apply to this API as to `os_msys_get()`.

<br>

#### Example

```no-highlight
    struct os_mbuf *om;
    struct my_user_hdr_struct my_usr_hdr;

    /*
     * Allocate an mbuf with hopefully at least 100 bytes in its user data buffer
     * and that has a user header of size sizeof(struct my_user_hdr_struct)
     */
    om = os_msys_get_pkthdr(100, sizeof(struct my_user_hdr_struct));
    if (!om) {
        /* No mbufs available. */
        return -1;
    }
}
```

