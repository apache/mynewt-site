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

The functions available in mem_pool are:

* [os_memblock_get](os_memblock_get)
* [os_mempool_init](os_mempool_init)
* [os_memblock_put](os_memblock_put)
* [OS_MEMPOOL_BYTES](OS_MEMPOOL_BYTES)


