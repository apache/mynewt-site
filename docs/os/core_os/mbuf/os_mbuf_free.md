## <font color="#F2853F" style="font-size:24pt"> os_mbuf_free</font>

```no-highlight
int os_mbuf_free(struct os_mbuf *om);
```

Free a single mbuf

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| om | Pointer to single mbuf |

<br>

#### Returned values

0: success  
Any other value indicates error

<br>

#### Notes
The mbuf is freed to the pool pointed to by *om_omp* in the mbuf. If the pool pointer is NULL, no error is returned and the mbuf is not freed.

Care should be taked when using this function as any mbufs chained to *om* will be lost as this function assumes no mbufs are chained to *om*.

<br>

#### Example

```no-highlight
    int rc;
	struct os_mbuf *om;

    rc = os_mbuf_free(om);
    assert(rc == 0);
```

---------------------
