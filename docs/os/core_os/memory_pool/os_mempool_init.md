## <font color="F2853F" style="font-size:24pt"> os_mempool_init</font>

```no-highlight
os_error_t os_mempool_init(struct os_mempool *mp, int blocks, int block_size, void *membuf, char *name)
```

Initializes the memory pool. Memory pointed to by *membuf* is divided into *blocks* number of elements of size OS_ALIGN(*block_size*). The *name* is optional, and names the memory pool.

It is assumed that the amount of memory pointed by *membuf* has at least *OS_MEMPOOL_BYTES(blocks, block_size)* number of bytes.

*name* is not copied, so caller should make sure that the memory does not get reused.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| mp |  Memory pool being initialized  |
| blocks |  Number of elements in the pool  |
| block_size | Minimum size of an individual element in pool |
| membuf | Backing store for the memory pool elements |
| name | Name of the memory pool |

#### Returned values

OS_OK: operation was successful.  
OS_INVALID_PARAM: invalid parameters. Block count or block size was negative, or membuf or mp was NULL.  
OS_MEM_NOT_ALIGNED: membuf was not aligned on correct byte boundary.

#### Notes 

Note that os_mempool_init() does not allocate backing storage; *membuf* has to be allocated by the caller.

It's recommended that you use *OS_MEMPOOL_BYTES()* or *OS_MEMPOOL_SIZE()* to figure out how much memory to allocate for the pool.

#### Example

<Add text to set up the context for the example here>

```no-highlight
    void *nffs_file_mem;
   
    nffs_file_mem = malloc(OS_MEMPOOL_BYTES(nffs_config.nc_num_files, sizeof (struct nffs_file)));
    										  
    rc = os_mempool_init(&nffs_file_pool, nffs_config.nc_num_files,
                         sizeof (struct nffs_file), nffs_file_mem,
                         "nffs_file_pool");
    if (rc != 0) {
        /* Memory pool initialization failure */
    }

```

---------------------
