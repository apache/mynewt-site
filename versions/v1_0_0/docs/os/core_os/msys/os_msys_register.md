## <font color="#F2853F" style="font-size:24pt">os_msys_register</font>

```c
int os_msys_register(struct os_mbuf_pool *new_pool) 
```

Register an mbuf pool for use as a system mbuf pool. The pool should be initialized prior to registration.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `new_pool` | Pointer to mbuf pool to add to system mbuf pools |

<br>

#### Returned values
0 on success; all other values indicate an error.

<br>

#### Example

```c
    rc = os_msys_register(&g_mbuf_pool);
    assert(rc == 0);
```

