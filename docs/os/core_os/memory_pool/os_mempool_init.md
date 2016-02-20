## <font color="F2853F" style="font-size:24pt"> os_mempool_init</font>

```no-highlight
os_error_t os_mempool_init(struct os_mempool *mp, int blocks, int block_size, void *membuf, char *name)
```

Initializes the memory pool. Memory pointed by *membuf* is taken and *blocks* number of elements of size *block_size* are added to the pool. *name* is optional, and names the memory pool.

It is assumed that the amount of memory pointed by *membuf* has at least *OS_MEMPOOL_BYTES(blocks, block_size)* number of bytes.

*name* is not copied, so caller should make sure that the memory does not get reused.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| mp |  Memory pool being initialized  |
| blocks |  Number of elements in the pool  |
| block_size | Size of an individual element in pool |
| membuf | Backing store for the memory pool elements |
| name | Name of the memory pool |

#### Returned values

OS_OK: operation was successful.
OS_INVALID_PARAM: invalid parameters. Block count or block size was negative, or membuf or mp was NULL.
OS_MEM_NOT_ALIGNED: membuf has to be aligned to 4 byte boundary.

#### Notes 

Note that os_mempool_init() does not allocate backing storage. *membuf* has to be allocated by the caller.

It's recommended that you use *OS_MEMPOOL_BYTES()* to figure out how much memory to allocate for the pool.

#### Example

<Add text to set up the context for the example here>

```no-highlight
    rc = os_mempool_init(&nffs_file_pool, nffs_config.nc_num_files,
                         sizeof (struct nffs_file), nffs_file_mem,
                         "nffs_file_pool");
    if (rc != 0) {
        return FS_EOS;
    }

```

---------------------
