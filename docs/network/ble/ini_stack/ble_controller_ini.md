
## Initialize the NimBLE controller

The NimBLE controller is initialized via a call to `ble_ll_init()`.  This function is declared as follows:

```c
int ble_ll_init(uint8_t ll_task_prio, uint8_t num_acl_pkts, uint16_t acl_pkt_size)
```

This function's parameters are documented below.

| **Parameter** | **Description** |
| ------------- | --------------- |
| *prio*        | The priority of the NimBLE controller task.  A lower number corresponds to higher priority. |
| *num_acl_pkts*         |  The maximum number of outstanding data packets that the controller will accept from the host. |
| *acl_pkt_size*         |  The maximum data packet size that the controller will accept from the host. |

**prio**:

If you are not familiar with multitasking, preemptive operating systems we
highly encourage you to read the Core OS section of Mynewt OS manual. It is up
to the application developer to decide the priority of tasks in the system.
Note that the lower the priority number the higher the priority in the OS. For
example, if a task is running at priority 5 and a task at priority 3 wants to
run, the task at priority 5 gets preempted as the other task is a higher
proiority.

In the example shown below, the LL task is configured to have the highest
priority (priority 0). We recommend making the BLE LL task the highest priority
task in your application as it has fairly rigorous timing requirements and
allowing other tasks to preempt the LL task could cause undesirable behavior.
Note that we do not force this to be the case as an application may require a
task to be even higher priority than the LL task.  Just be warned: a task
higher in priority than the LL task should not perform actions that take too
long; even a few milliseconds could cause undesirable behavior.

**num_acl_pkts** and **acl_pkt_size**:

These two parameters are used to limit the amount of data the host tries to send through the controller.  NimBLE uses the msys facility for allocating data packets, so the product of these arguments must not be larger than the total amount of memory allocated for msys.  The below example uses some values that are reasonable for most uses.

```c hl_lines="1 40 41 42"
#include "controller/ble_ll.h"

int
main(void)
{
	int rc;
    struct ble_hs_cfg cfg;

    /* Initialize OS */
    os_init();

    /* Set cputime to count at 1 usec increments */
    rc = cputime_init(1000000);
    assert(rc == 0);

    /* Create memory pool for NimBLE packets and register with Msys */
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

    /* Initialize the BLE LL */
    rc = ble_ll_init(0, 7, 260);
    assert(rc == 0);

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```
<br>

