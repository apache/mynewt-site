# Memory Pools


A memory pool is a collection of fixed sized elements called memory blocks. Generally, memory pools are used when the developer wants to allocate a certain amount of memory to a given feature. Unlike the heap, where a code module is at the mercy of other code modules to insure there is sufficient memory, memory pools can insure sufficient memory allocation.


### Description

In order to create a memory pool the developer needs to do a few things. The first task is to define the memory pool itself. This is a data structure which contains information about the pool itself (i.e. number of blocks, size of the blocks, etc).

```c
struct os_mempool my_pool;
```
<br>
The next order of business is to allocate the memory used by the memory pool. This memory can either be statically allocated (i.e. a global variable) or dynamically allocated (i.e. from the heap). When determining the amount of memory required for the memory pool, simply multiplying the number of blocks by the size of each block is not sufficient as the OS may have alignment requirements. The alignment size definition is named `OS_ALIGNMENT` and can be found in os_arch.h as it is architecture specific. The memory block alignment is usually for efficiency but may be due to other reasons. Generally, blocks are aligned on 32-bit boundaries. Note that memory blocks must also be of sufficient size to hold a list pointer as this is needed to chain memory blocks on the free list.

In order to simplify this for the user two macros have been provided: `OS_MEMPOOL_BYTES(n, blksize)` and `OS_MEMPOOL_SIZE(n, blksize)`. The first macro returns the number of bytes needed for the memory pool while the second returns the number of `os_membuf_t` elements required by the memory pool. The `os_membuf_t` type is used to guarantee that the memory buffer used by the memory pool is aligned on the correct boundary. 

Here are some examples. Note that if a custom malloc implementation is used it must guarantee that the memory buffer used by the pool is allocated on the correct boundary (i.e. `OS_ALIGNMENT`).

```c
void *my_memory_buffer;
my_memory_buffer = malloc(OS_MEMPOOL_BYTES(NUM_BLOCKS, BLOCK_SIZE));
```

```c
os_membuf_t my_memory_buffer[OS_MEMPOOL_SIZE(NUM_BLOCKS, BLOCK_SIZE)];
```
<br>
Now that the memory pool has been defined as well as the memory required for the memory blocks which make up the pool the user needs to initialize the memory pool by calling `os_mempool_init`.

```c
os_mempool_init(&my_pool, NUM_BLOCKS, BLOCK_SIZE, my_memory_buffer,
                         "MyPool");
```
<br>
Once the memory pool has been initialized the developer can allocate memory blocks from the pool by calling `os_memblock_get`. When the memory block is no longer needed the memory can be freed by calling `os_memblock_put`. 

### Data structures
```c
struct os_mempool {
    int mp_block_size;
    int mp_num_blocks;
    int mp_num_free;
    uint32_t mp_membuf_addr;
    STAILQ_ENTRY(os_mempool) mp_list;    
    SLIST_HEAD(,os_memblock);
    char *name;
};
```
<br>

| **Element** | **Description** |
|-----------|-------------|
| mp_block_size | Size of the memory blocks, in bytes. This is not the actual  number of bytes used by each block; it is the requested size of each block. The actual memory block size will be aligned to OS_ALIGNMENT bytes |
| mp_num_blocks | Number of memory blocks in the pool |
| mp_num_free | Number of free blocks left |
| mp_membuf_addr | The address of the memory block. This is used to check that a valid memory block is being freed. |
| mp_list | List pointer to chain memory pools so they can be displayed by newt tools |
| SLIST_HEAD(,os_memblock) | List pointer to chain free memory blocks |
| name | Name for the memory block |
  
  
### List of Functions/Macros

The functions/macros available in mem_pool are:

| **Function** | **Description** |
|-----------|-------------|
| [os_memblock_get](os_memblock_get) | Allocate an element from the memory pool. |
| [os_mempool_init](os_mempool_init) | Initializes the memory pool. |
| [os_memblock_put](os_memblock_put) | Releases previously allocated element back to the pool. |
| [OS_MEMPOOL_BYTES](OS_MEMPOOL_BYTES) | Calculates how many bytes of memory is used by n number of elements, when individual element size is blksize bytes. |
| [OS_MEMPOOL_SIZE](OS_MEMPOOL_SIZE) | Calculates the number of os_membuf_t elements used by n blocks of size blksize bytes. |


