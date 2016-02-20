## <font color="#F2853F" style="font-size:24pt">os_memblock_put</font>

```no-highlight
os_error_t os_memblock_put(struct os_mempool *mp, void *block_addr)
```

Releases previously allocated element back to the pool.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| mp |  Pointer to memory pool where element is put  |
| block_addr | Pointer to element getting freed |

#### Returned values

OS_OK: operation was a success:
OS_INVALID_PARAM: If either mp or block_addr were NULL.

#### Notes 



#### Example

<Add text to set up the context for the example here>

```no-highlight
    if (file != NULL) {
        rc = os_memblock_put(&nffs_file_pool, file);
        if (rc != 0) {
            return FS_EOS;
        }
    }
```

---------------------
