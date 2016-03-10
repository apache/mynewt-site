## <font color="#F2853F" style="font-size:24pt"> os_mbuf_dup</font>

```no-highlight
struct os_mbuf *os_mbuf_dup(struct os_mbuf *om)
```

Duplicate a chain of mbufs.  Return the start of the duplicated chain.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| om |  Pointer to mbuf chain to duplicate |

<br>

#### Returned values

Pointer to the duplicated chain or NULL if not enough mbufs were available to duplicate the chain.

<br>


#### Example

```no-highlight
	struct os_mbuf *om;
    struct os_mbuf *new_om;
	
    /* Make a copy of om, returning -1 if not able to duplicate om */
    new_om = os_mbuf_dup(om);
    if (!new_om) {
        return -1;
    }
```

