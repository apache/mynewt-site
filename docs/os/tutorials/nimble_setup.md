## Nimble stack setup for BLE applications

This tutorial explains how to setup an application using the Nimble stack. The end result will be a framework that you can use to create your own BLE application using the nimble stack.

This tutorial assumes that you have already installed a source tree and are familiar with the newt tools and concepts. 

### Creating the application directory
<This needs to be added. This should talk about how you create the pkg.yml file in the apps directory that the user will create. Also, discuss other application dir stuff>

### Creating the target

The first step will be to create the target that you will use to build your application. We will call this target "ble_tgt". Type the `newt target create ble_tgt` command. You should get this:

```no-highlight
$ newt target create ble_tgt
Target targets/ble_tgt successfully created
```

What this command just did was to create a directory called `ble_tgt` in the targets directory of your project. Two files are created in that directory: pkg.yml and target.yml.

The target is not yet complete though! We need to set some target variables for this project. Currently, the nimble stack has been ported to the Nordic nrf5x chipsets; specifically the nrf51 and nrf52. This application will use the nrf52 but we will also show the setup for the nrf51 in case your project uses that chip.

Here are the commands you will need to setup your target for the nrf52:

```no-highlight
$ newt target set ble_tgt arch=cortex_m4
Target targets/ble_tgt successfully set target.arch to cortex_m4
$ newt target set ble_tgt bsp=hw/bsp/nrf52pdk
Target targets/ble_tgt successfully set target.bsp to hw/bsp/nrf52pdk
$ newt target set ble_tgt build_profile=optimized
Target targets/ble_tgt successfully set target.build_profile to optimized
$newt target set ble_tgt app=apps/ble_app
Target targets/ble_tgt successfully set target.app to apps/ble_app
```

Here are the commands you will need to setup your target for the nrf51:

```no-highlight
$ newt target set ble_tgt arch=cortex_m0
Target targets/ble_tgt successfully set target.arch to cortex_m0
$ newt target set ble_tgt bsp=hw/bsp/nrf51dk
Target targets/ble_tgt successfully set target.bsp to hw/bsp/nrf51dk
$ newt target set ble_tgt build_profile=optimized
Target targets/ble_tgt successfully set target.build_profile to optimized
$newt target set ble_tgt app=apps/ble_app
Target targets/ble_tgt successfully set target.app to apps/ble_app
```

<br>


### Nimble stack initialization

We are now going to explain how to setup your application to initialize the nimble stack and to get the basic stack, and its required modules, initialized and up and running. Note that the code shown here is an example of what is required for nimble stack operation; it is not intended to dictate to the developer exactly how to organize/setup your code. For example, the code sample shows modification of main.c in the application /src folder. The developer has the flexibility to organize the code as they see fit so this code does not need to reside in /src/main.c nor in the main() function itself. The only possible issue is the order of some of the initializations. Where this order is important it is indicated in the tutorial.

A note about the code samples: the main() function in each code sample builds upon the previous example. However, code outside of main() shows only what we add for each step. The last code sample shows the entire main.c that we created.

Let's start with a very basic main() function (shown below). In this main all we are doing is initializing the Mynewt OS and starting it.

```no-highlight
#include "os/os.h"

int
main(void)
{
    /* Initialize OS */
    os_init();

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```
The Nimble stack requires a number of packages/modules to be initialized prior to being initialized. We are going to add these one by one to the application and describe each.

<br>

#### Add cputime

The Nimble stack requires "cputime". This is provided by the Mynewt HAL of the same name. The cputime HAL provides a high resolution timer that is used by the nimble stack (as the BLE specification requires a fairly high resolution timer and has fairly tight timing requirements). The cputime HAL allows the user to specify the timer resolution as different applications may require a different resolution. While the Nimble stack does not require a specific timer resolution per se, a resolution that is too large may affect performance and power efficiency. A suggested clock rate for HAL cputime for the nimble stack is 1 MHz, or 1 microsecond per cputime tick. This provides enough resolution for most needs while providing the Nimble stack enough resolution to implement the BLE specification.

Add the initialization of cputime to your application:

```no-highlight
#include "hal/hal_cputime.h"

int
main(void)
{
	int rc;
	
    /* Initialize OS */
    os_init();
    
    /* Set cputime to count at 1 usec increments */
    rc = cputime_init(1000000);
    assert(rc == 0);

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

####  Create the system memory buffer pool
The Nimble stack allocates packet buffers (called mbufs) from the system memory buffer pool (msys). The system memory buffer pool and mbufs are described in the OS manual; we suggest reading that section in order to become familiar with mbufs if you are not already familiar with them. Note that the application itself (the unique application code that you are writing) does not need to use mbufs and none of the BLE host API exposed to the application developer uses them. However, the Nimble stack does require the existence of the system memory pool.

Creating the memory pool and registering it with the system memory buffer pool can be a bit tricky the first time. However, using the template provided below it should be much easier. The header file /net/nimble/include/nimble/ble.h, which should be included in main.c, contains some MBUF macros that you will need to create the memory pool used by msys. The macro `BLE_MBUF_PAYLOAD_SIZE` defines the maximum amount of user payload, plus overhead, that a link layer BLE PDU can contain. The macro `BLE_MBUF_MEMBLOCK_OVERHEAD` is the amount of overhead required by the Nimble stack in each memory block used by the mbuf pool. The macro `MBUF_NUM_MBUFS` defines the number of mbufs in the mbuf pool and is defined locally. The user must determine, based on application requirements and platform memory size, how many mbufs are required. For example, if your application expects to have many simultaneous connections you may want to increase the size of the mbuf pool. In the example below, we assume you are only using a small number of active connections (2 to 3).

A note about the size of the mbufs and `BLE_MBUF_PAYLOAD_SIZE`. Msys allows for multiple mbuf pools of various size. Currently, the Nimble stack requires that msys has an mbuf pool registered that can accommodate the maximum size BLE LL PDU. Thus, we only show the creation of one mbuf pool of maximum size mbufs which gets registered to the system mbuf memory pool. We plan on modifying the Nimble stack so that smaller mbufs can be used (to conserve memory) but at this point in time you cannot modify `BLE_MBUF_PAYLOAD_SIZE`. Furthermore, you cannot add a mbuf pool of smaller size elements to the msys pool as the msys code might then allocate a mbuf that is too small for the nimble stack.

```no-highlight
#include "nimble/ble.h"


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

####  Initializing the device address
The BLE specification requires that devices have an address (called a device address). This address can be either a public device address or a random device address. The current Nimble stack implementation requires that these addresses be defined somewhere in the application; they are not defined within the Nimble stack itself. This was done so that the entire application could have access to these addresses. We expect that we will move these addresses into the Nimble stack in a future release.

The two variables that must be defined are named `g_dev_addr` (public device address) and `g_random_addr` (static random address). The device address must be initialized prior to initializing the Nimble stack. The random address does not have to be initialized ahead of time as it is possible to set the random address in the Nimble controller when it is running. In this example, we only initialize the device address. The company OUI in this example is 0a:bb:cc; the unique portion is 11:22:33 for a device address equal to 0a:bb:cc:11:22:33. Note that we store the address in little endian order as BLE expects the OUI to be in the most significant bytes.

```no-highlight
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

####  Initializing the statistics package
The Nimble stack uses the statistics package and this must be initialized prior to initializing the Nimble stack. Initializing the statistics package is quite simple; all you need to do is call the initialization function `stats_module_init()`.

```no-highlight
#include "stats/stats.h"

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
	
    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

####  Initializing the console package
The console is also required by the Nimble stack. The console is currently used for log output so it needs to be initialized. For this example, we are not going to use a console receive callback. All this means is that input from the console will not be accepted by default; the developer will have to install their own handler or use one provided by another package (the shell, for example). Just like statistics, the console is initialized by calling the console initialization function `console_init()`. 

```no-highlight
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

####  Initializing the Nimble stack
We are now ready to initialize the Nimble stack! There are two API that need to be called to initialize the Nimble stack: `ble_hs_init()` and `ble_ll_init()`. The first call initializes the host and the second initializes the controller (the Link Layer) of the Nimble stack.

At this point it is a good idea to talk about the Mynewt OS, tasks, and task priorities. If you are not familiar with multitasking, preemptive operating systems we highly encourage you to read the Core OS section of Mynewt OS manual. It is up to the application developer to decide the priority of tasks in the system. Note that the lower the priority number the higher the priority in the OS. For example, if a task is running at priority 5 and a task at priority 3 wants to run, the task at priority 5 gets preempted as the other task is a higher proiority.

When initializing the Nimble stack the developer must assign a higher priority to the LL task than the Host task. In the example shown below, `HOST_TASK_PRIO` is defined to be 1 and the LL task priority (`BLE_LL_TASK_PRI`) is defined to be the highest priority task (priority 0). We recommend making the BLE LL task the highest priority task in your application as it has fairly rigorous timing requirements and allowing other tasks to preempt the LL task could cause undesirable behavior. Note that we do not force this to be the case as an application may require a task to be even higher priority than the LL task. Just be warned: a task higher in priority than the LL task should not perform actions that take too long; even a few milliseconds could cause undesirable behavior.

To initialize the host...
<Need content here>

Initializing the LL task is done by caling `ble_ll_init()`. The caller passes the task priority of the LL task when calling this API.


```no-highlight
#include "host/ble_hs.h"
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

    /* Initialize the BLE host. */
    cfg = ble_hs_cfg_dflt;
    cfg.max_hci_bufs = 3;
    cfg.max_attrs = 32;
    cfg.max_services = 4;
    cfg.max_client_configs = 6;
    cfg.max_gattc_procs = 2;
    cfg.max_l2cap_chans = 3;
    cfg.max_l2cap_sig_procs = 2;

    rc = ble_hs_init(HOST_TASK_PRIO, &cfg);
    assert(rc == 0);

    /* Initialize the BLE LL */
    ble_ll_init(BLE_LL_TASK_PRI);
		
    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

####  Configuring the Nimble stack
<Add content here. We should discuss nimble_opt.h (at least). I dont think we need to go into detail about each option here. That should be in the BLE stack documentation>


 
### Building the application
Now that we have created the application and the target we can build it and test it out. The command you need to run is the newt build command with the target we created (ble_tgt). The output will show the files being compiled and linked. You should see this when all is done (except for the ... of course):

```no-highlight
wes@~/dev/larva$ newt build ble_tgt
...
Archiving os.a
Compiling cons_fmt.c
Compiling cons_tty.c
Archiving full.a
Linking ble_app.elf
App successfully built: /Users/wes/dev/larva/bin/ble_tgt/apps/ble_app/ble_app.elf
```

<NEED MORE CONTENT HERE. We should download the target we built and show it doing something. I am not sure what to put here since I dont know what we will show for dealing with the host.>