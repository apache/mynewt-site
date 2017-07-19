## <font color="#F2853F" style="font-size:24pt">OS_MEMPOOL_SIZE</font>

```c
OS_MEMPOOL_SIZE(n,blksize)
```

Calculates the number of os_membuf_t elements used by *n* blocks of size *blksize* bytes.

Note that os_membuf_t is used so that memory blocks are aligned on OS_ALIGNMENT boundaries.

The *blksize* variable is the minimum number of bytes required for each block; the actual block size is padded so that each block is aligned on OS_ALIGNMENT boundaries.  

<br>
#### Arguments

| Arguments | Description |
|-----------|-------------|
| n |  Number of elements  |
| blksize |  Size of an element is number of bytes  |

#### Returned values
The number of os_membuf_t elements used by the memory pool. Note that os_membuf_t is defined to be a unsigned, 32-bit integer when OS_ALIGNMENT is 4 and an unsigned, 64-bit integer when OS_ALIGNMENT is 8.

<br>
#### Notes
OS_MEMPOOL_SIZE is a macro and not a function.

<br>
#### Example

Here we define a memory buffer to be used by a memory pool using OS_MEMPOOL_SIZE

```c
#define NUM_BLOCKS      (16)
#define BLOCK_SIZE      (32)

os_membuf_t my_pool_memory[OS_MEMPOOL_SIZE(NUM_BLOCKS, BLOCK_SIZE)]
```


