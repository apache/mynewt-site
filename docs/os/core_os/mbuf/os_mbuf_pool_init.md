## <font color="#F2853F" style="font-size:24pt">os_mbuf_pool_init</font>

```no-highlight
int os_mbuf_pool_init(struct os_mbuf_pool *omp, struct os_mempool *mp, uint16_t buf_len, 
                      uint16_t nbufs)
```

Initialize a mbuf pool

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| omp | Pointer to mbuf pool to initialize |
| mp | Pointer to memory pool used by mbuf pool |
| buf_len | The size of the memory blocks in the memory pool used by the mbuf pool |
| nbufs | The number of mbufs in the pool |

<br>

#### Returned values
0 on success; all other values indicate an error.

<br>

#### Notes
The parameter *buf_len* is the total size of the memory block. This must accommodate the os_mbuf structure, the os_mbuf_pkthdr structure, any user headers plus the desired amount of user data.

<br>

#### Example

```no-highlight
#define MBUF_PKTHDR_OVERHEAD    sizeof(struct os_mbuf_pkthdr) + sizeof(struct user_hdr)
#define MBUF_MEMBLOCK_OVERHEAD  sizeof(struct os_mbuf) + MBUF_PKTHDR_OVERHEAD

#define MBUF_NUM_MBUFS      (32)
#define MBUF_PAYLOAD_SIZE   (64)
#define MBUF_BUF_SIZE       OS_ALIGN(MBUF_PAYLOAD_SIZE, 4)
#define MBUF_MEMBLOCK_SIZE  (MBUF_BUF_SIZE + MBUF_MEMBLOCK_OVERHEAD)
#define MBUF_MEMPOOL_SIZE   OS_MEMPOOL_SIZE(MBUF_NUM_MBUFS, MBUF_MEMBLOCK_SIZE)

struct os_mbuf_pool g_mbuf_pool; 
struct os_mempool g_mbuf_mempool;
os_membuf_t g_mbuf_buffer[MBUF_MEMPOOL_SIZE];

void
create_mbuf_pool(void)
{
    int rc;

    rc = os_mempool_init(&g_mbuf_mempool, MBUF_NUM_MBUFS, 
                          MBUF_MEMBLOCK_SIZE, &g_mbuf_buffer[0], "mbuf_pool");
    assert(rc == 0);

    rc = os_mbuf_pool_init(&g_mbuf_pool, &g_mbuf_mempool, MBUF_MEMBLOCK_SIZE, 
                           MBUF_NUM_MBUFS);
    assert(rc == 0);
}
```

---------------------
