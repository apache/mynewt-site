##  Initialize the Device Address

The BLE specification requires that devices have an address (called a device address). This address can be either a public device address or a random device address. The current Nimble stack implementation requires that these addresses be defined somewhere in the application; they are not defined within the Nimble stack itself. This was done so that the entire application could have access to these addresses. We expect that we will move these addresses into the Nimble stack in a future release.

The two variables that must be defined are named `g_dev_addr` (public device address) and `g_random_addr` (static random address). The device address must be initialized prior to initializing the Nimble stack. The random address does not have to be initialized ahead of time as it is possible to set the random address in the Nimble controller when it is running. In this example, we only initialize the device address. The company OUI in this example is 0a:bb:cc; the unique portion is 11:22:33 for a device address equal to 0a:bb:cc:11:22:33. Note that we store the address in little endian order as BLE expects the OUI to be in the most significant bytes.

```c hl_lines="1 2 3 4 5 31 32 33 34 35 36 37"
/* Our global device address (public) */
uint8_t g_dev_addr[BLE_DEV_ADDR_LEN];

/* Our random address (static) */
uint8_t g_random_addr[BLE_DEV_ADDR_LEN];

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

    /* Initialize our device address */
    g_dev_addr[0] = 0x33;
    g_dev_addr[1] = 0x22;
    g_dev_addr[2] = 0x11;
    g_dev_addr[3] = 0xcc;
    g_dev_addr[4] = 0xbb;
    g_dev_addr[5] = 0x0a;

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

