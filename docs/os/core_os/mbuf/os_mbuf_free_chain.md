## <font color="#F2853F" style="font-size:24pt"> os_mbuf_free_chain</font>

```c
int os_mbuf_free_chain(struct os_mbuf *om);
```

Frees a chain of mbufs

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `om` | Pointer to mbuf chain |

<br>

#### Returned values

0: success  
Any other value indicates error

<br>

#### Notes
Note that for each mbuf in the chain, `os_mbuf_free()` is called.

<br>

#### Example

```c
    int rc;
	struct os_mbuf *om;

    /* Free mbuf chain */
    rc = os_mbuf_free_chain(om);
    assert(rc == 0);
```

