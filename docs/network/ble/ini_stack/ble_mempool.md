## Create the System Memory Buffer Pool

The Nimble stack allocates packet buffers (called mbufs) from the system memory buffer pool (msys). The system memory buffer pool and mbufs are described in the OS manual; we suggest reading that section in order to become familiar with mbufs if you are not already familiar with them. Note that the application itself (the unique application code that you are writing) does not need to use mbufs and none of the BLE host API exposed to the application developer uses them. However, the Nimble stack does require the existence of the system memory pool.

Creating the memory pool and registering it with the system memory buffer pool can be a bit tricky the first time. However, using the template provided below it should be much easier. The header file /net/nimble/include/nimble/ble.h, which should be included in main.c, contains some MBUF macros that you will need to create the memory pool used by msys. The macro `BLE_MBUF_PAYLOAD_SIZE` defines the maximum amount of user payload, plus overhead, that a link layer BLE PDU can contain. The macro `BLE_MBUF_MEMBLOCK_OVERHEAD` is the amount of overhead required by the Nimble stack in each memory block used by the mbuf pool. The macro `MBUF_NUM_MBUFS` defines the number of mbufs in the mbuf pool and is defined locally. The user must determine, based on application requirements and platform memory size, how many mbufs are required. For example, if your application expects to have many simultaneous connections you may want to increase the size of the mbuf pool. In the example below, we assume you are only using a small number of active connections (2 to 3).

A note about the size of the mbufs and `BLE_MBUF_PAYLOAD_SIZE`. Msys allows for multiple mbuf pools of various size. Currently, the Nimble stack requires that msys has an mbuf pool registered that can accommodate the maximum size BLE LL PDU. Thus, we only show the creation of one mbuf pool of maximum size mbufs which gets registered to the system mbuf memory pool. We plan on modifying the Nimble stack so that smaller mbufs can be used (to conserve memory) but at this point in time you cannot modify `BLE_MBUF_PAYLOAD_SIZE`. Furthermore, you cannot add a mbuf pool of smaller size elements to the msys pool as the msys code might then allocate a mbuf that is too small for the nimble stack.

```c hl_lines="1 2 3 4 5 6 7 8 9 23 24 25 26 27 28 29 30 31 32 33"
    
/* Create a mbuf pool of BLE mbufs */
#define MBUF_NUM_MBUFS      (8)
#define MBUF_BUF_SIZE       OS_ALIGN(BLE_MBUF_PAYLOAD_SIZE, 4)
#define MBUF_MEMBLOCK_SIZE  (MBUF_BUF_SIZE + BLE_MBUF_MEMBLOCK_OVERHEAD)
#define MBUF_MEMPOOL_SIZE   OS_MEMPOOL_SIZE(MBUF_NUM_MBUFS, MBUF_MEMBLOCK_SIZE)

struct os_mbuf_pool g_mbuf_pool;
struct os_mempool g_mbuf_mempool;
os_membuf_t g_mbuf_buffer[MBUF_MEMPOOL_SIZE];

int
main(void)
{
	int rc;

    /* Initialize OS */
    os_init();

    /* Set cputime to count at 1 usec increments */
    rc = cputime_init(1000000);
    assert(rc == 0);

    /* Create memory pool for Nimble packets and register with Msys */
    rc = os_mempool_init(&g_mbuf_mempool, MBUF_NUM_MBUFS,
            MBUF_MEMBLOCK_SIZE, &g_mbuf_buffer[0], "mbuf_pool");
    assert(rc == 0);

    rc = os_mbuf_pool_init(&g_mbuf_pool, &g_mbuf_mempool, MBUF_MEMBLOCK_SIZE,
                           MBUF_NUM_MBUFS);
    assert(rc == 0);

    rc = os_msys_register(&g_mbuf_pool);
    assert(rc == 0);

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

