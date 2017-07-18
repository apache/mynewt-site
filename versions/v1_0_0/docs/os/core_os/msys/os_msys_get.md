## <font color="#F2853F" style="font-size:24pt">os_msys_get</font>

```c
struct os_mbuf *os_msys_get(uint16_t dsize, uint16_t leadingspace)
```

Retrieve an mbuf from the system mbuf pools with `leadingspace` bytes available in the mbuf.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `dsize` | Minimum requested size of mbuf. Actual mbuf allocated may not accommodate *dsize* |
| `leadingspace` | Number of bytes for leading space in mbuf (space at start of mbuf) |

<br>

#### Returned values
Pointer to mbuf or **NULL** if no mbufs were available.

<br>

#### Notes
As described in the overview section, `os_msys_get()` may return an mbuf that is smaller than `dsize`, meaning that the mbuf user data buffer does not have enough contiguous space to hold `dsize` bytes.

This API will not return an mbuf from a larger mbuf pool if the appropriate msys mbuf pool is empty. See the overview for more information.

<br>

#### Example

```c
    struct os_mbuf *om;

    /* Allocate an mbuf with hopefully at least 100 bytes in its user data buffer */
    om = os_msys_get(100, 0);
    if (!om) {
        /* No mbufs available. */
        return -1;
    }
}
```

