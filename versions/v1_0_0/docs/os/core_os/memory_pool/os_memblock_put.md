## <font color="#F2853F" style="font-size:24pt">os_memblock_put</font>

```c
os_error_t os_memblock_put(struct os_mempool *mp, void *block_addr)
```

Releases previously allocated element back to the pool.  

<br>
#### Arguments

| Arguments | Description |
|-----------|-------------|
| `mp` |  Pointer to memory pool from which block was allocated  |
| `block_addr` | Pointer to element getting freed |

<br>
#### Returned values

`OS_OK`: operation was a success:  
`OS_INVALID_PARAM`: If either `mp` or `block_addr` were **NULL**, or the block being freed was outside the range of the memory buffer or not on a true block size boundary.

<br>
#### Example

<Add text to set up the context for the example here>

```c
    if (file != NULL) {
        rc = os_memblock_put(&nffs_file_pool, file);
        if (rc != 0) {
            /* Error freeing memory block */
        }
    }
```

