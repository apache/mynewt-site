##  Initializing the console package
The console is also required by the Nimble stack. The console is currently used for log output so it needs to be initialized. For this example, we are not going to use a console receive callback. All this means is that input from the console will not be accepted by default; the developer will have to install their own handler or use one provided by another package (the shell, for example). Just like statistics, the console is initialized by calling the console initialization function `console_init()`.

```c hl_lines="1 39 40 41"
#include "console/console.h"

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

	/* Initialize the statistics package */
    rc = stats_module_init();
    assert(rc == 0);

    /* Init the console */
    rc = console_init(NULL);
    assert(rc == 0);

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

