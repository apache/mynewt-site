# Memory Pools


Memory can be pre-allocated to a pool of fixed size elements.


## Description

Sometimes it's useful to have several memory blocks of same size preallocated for specific use. E.g. you want to limit the amount of memory used for it, or you want to make sure that there is memory available when you ask for it.

This can be done using a memory pool. You allocate memory either statically or from heap, and then designate that memory to be used as storage for fixed size elements.

Pool will be initialized by calling *os_mempool_init()*. Element can be allocated from it with *os_mempool_get()*, and released back with *os_mempool_put()*.

## Data structures

```no-highlight
struct os_mempool {
    int mp_block_size;
    int mp_num_blocks;
    int mp_num_free;
    SLIST_HEAD(,os_memblock);
    char *name;
};
```
| Element | Description |
|-----------|-------------|
| mp_block_size | Size of the memory blocks, in bytes |
| mp_num_blocks | Number of memory blocks in the pool |
| mp_num_free | Number of free blocks left |
| name | Name for the memory block |

## List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in this OS feature are:

* [os_mempool_init](#os_mempool_init)
* [os_memblock_get](#os_memblock_get)
* [os_memblock_put](#os_memblock_put)
* [OS_MEMPOOL_BYTES](#OS_MEMPOOL_BYTES)


## Function Reference

------------------

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
   
## <font color="#F2853F" style="font-size:24pt"> os_memblock_get</font>

```no-highlight
void *os_memblock_get(struct os_mempool *mp)
```

Allocate an element from the memory pool. If succesful, you'll get a pointer to allocated element. If there are no elements available, you'll get NULL as response.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| mp |  Pool where element is getting allocated from  |

#### Returned values

NULL: no elements available.
<pointer>: pointer to allocated element.

#### Notes


#### Example

<Add text to set up the context for the example here>

```no-highlight
	struct nffs_file *file;

    file = os_memblock_get(&nffs_file_pool);
    if (file != NULL) {
        memset(file, 0, sizeof *file);
    }

```

---------------------

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
   
## <font color="#F2853F" style="font-size:24pt">OS_MEMPOOL_BYTES</font>

```no-highlight
OS_MEMPOOL_BYTES(n,blksize)
```

Calculates how many bytes of memory is used by *n* number of elements, when individual element size is *blksize* bytes.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| n |  Number of elements  |
| blksize |  Size of an element is number of bytes  |

#### Returned values

List any values returned.
Error codes?

#### Notes


#### Example

Here we allocate memory to be used as a pool.

```no-highlight
void *nffs_file_mem;

nffs_file_mem = malloc(
        OS_MEMPOOL_BYTES(nffs_config.nc_num_files, sizeof (struct nffs_file)));
    if (nffs_file_mem == NULL) {
        return FS_ENOMEM;
    }
```

---------------------

