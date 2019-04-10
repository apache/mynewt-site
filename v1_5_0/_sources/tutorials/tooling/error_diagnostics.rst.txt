Diagnosing Errors
=================

Here we list some of the tools Mynewt has available. This is by no means
comprehensive. It does give an overview of some facilities more commonly
used.

To create output for this demo, I'm including the 'test/crash_test' package
while building the 'slinky' app.

Crash with Console
------------------
When system restarts due to an error, we always attempt to do it
in a way which allows us to dump the current system state. Calls to
assert(), error interrupts (regular faults, memory faults) both take
this path.

The basic facility is the printout of registers to console.

Here is an example of what it looks like with Cortex-M4:

.. code-block:: console

    041088 Unhandled interrupt (3), exception sp 0x20001d28
    041088  r0:0x00000000  r1:0x00017b61  r2:0x00000000  r3:0x0000002a
    041088  r4:0x20001dc8  r5:0x00000000  r6:0x200034e4  r7:0x20003464
    041088  r8:0x2000349c  r9:0x20001f08 r10:0x00017bd4 r11:0x00000000
    041088 r12:0x00000000  lr:0x00014e29  pc:0x00014e58 psr:0x61000000
    041088 ICSR:0x00421803 HFSR:0x40000000 CFSR:0x02000000
    041088 BFAR:0xe000ed38 MMFAR:0xe000ed34

Output includes the values of registers. The most interesting pieces
would be $pc (program counter), and $lr (link register), which show
the instruction where the fault happened, and the return address from
that function.

You would then take these values, and match them against the image
you're running on the target.

For example:

.. code-block:: console

    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ arm-elf-linux-gdb bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf
    GNU gdb (GDB) 7.8.1
      ...
    Reading symbols from bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf...done.
    (gdb) list *0x00014e58
    0x14e58 is in crash_device (repos/apache-mynewt-core/test/crash_test/src/crash_test.c:47).
    42	    if (!strcmp(how, "div0")) {
    43	
    44	        val1 = 42;
    45	        val2 = 0;
    46	
    47	        val3 = val1 / val2;
    48	        console_printf("42/0 = %d\n", val3);
    49	    } else if (!strcmp(how, "jump0")) {
    50	        ((void (*)(void))0)();
    51	    } else if (!strcmp(how, "ref0")) {

You can see that the system crashed due to divide-by-zero.

Crash with Verbose Location
~~~~~~~~~~~~~~~~~~~~~~~~~~~

We often call assert(), testing specific conditions which should be met
for program execution to continue. If the condition fails, we reset with a
message listing the instruction where assert() was called from.

.. code-block:: console

    829008 compat> Assert @ 0x14e9f
    831203 Unhandled interrupt (2), exception sp 0x20001d20

This address (here 0x14e9f) should then be used to find the line in
the program where it happened. Note that this address is specific to your
binary. So you have to do the search to locate the specific file/line using
your .elf file.

You can also enable more verbose report by setting syscfg variable
OS_CRASH_FILE_LINE to 1. The call to assert() from above would then look
like so:

.. code-block:: console

    000230 compat> Assert @ 0x1503b - repos/apache-mynewt-core/test/crash_test/src/crash_test.c:54
    001462 Unhandled interrupt (2), exception sp 0x20001d20

Note that this will increase the program text size, as we now need to
store the names for the files which call assert().

Crash with Console with Stacktrace
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Quite often you need a deeper view of the call chain to figure out
how the program got to place where it crashed. Especially if the routine
can be reached via multiple call chain routes.

You can enable a dump of possible call chain candidates by setting
syscfg variable OS_CRASH_STACKTRACE to 1.

When crash happens, the dumping routine walks backwards in the stack,
and prints any address which falls within text region. All these values
are candidates of being part of the call chain. However, you need to
filter it yourself to figure out which values are actually part of it, and
which addresses just happen to be in the stack at that time.

Here is a sample output:

.. code-block:: console
    
    004067 Unhandled interrupt (3), exception sp 0x20001d28
    004067  r0:0x00000000  r1:0x00017c55  r2:0x00000000  r3:0x0000002a
    004067  r4:0x20001dc8  r5:0x00000000  r6:0x200034e4  r7:0x20003464
    004067  r8:0x2000349c  r9:0x20001f08 r10:0x00017cc8 r11:0x00000000
    004067 r12:0x00000000  lr:0x00014ef9  pc:0x00014f28 psr:0x61000000
    004067 ICSR:0x00421803 HFSR:0x40000000 CFSR:0x02000000
    004067 BFAR:0xe000ed38 MMFAR:0xe000ed34
    004067 task:main
    004067  0x20001d64: 0x0001501b
    004067  0x20001d68: 0x00017338
    004067  0x20001dd0: 0x00017cc8
    004067  0x20001dd4: 0x00015c2b
    004067  0x20001dd8: 0x00015c1d
    004067  0x20001de4: 0x0001161d
    004067  0x20001df4: 0x00011841
    004067  0x20001e04: 0x000117c9
    004067  0x20001e0c: 0x00013d8f
    004067  0x20001e20: 0x00014375
    004067  0x20001e4c: 0x00013dfd
    004067  0x20001e54: 0x00013e09
    004067  0x20001e58: 0x00013e01
    004067  0x20001e5c: 0x0000925d
    004067  0x20001e64: 0x00008933
    004067  0x20001e7c: 0x00008cc3
    004067  0x20001e98: 0x000169e0
    004067  0x20001e9c: 0x00008cb9
    004067  0x20001ea0: 0x000088a9

You can see that it contains the usual dump of registers in the beginning,
followed by addresses to stack, and the value at that location. Note that
we skip the area of memory within stack which contains the stashed register
values. This means that $pc and $lr values will not show up in the array
of addresses. Depending on your CPU architecture, different stuff gets
pushed to stack. Given where Mynewt is ported to, there's always function
return address pushed there.

You would then take these values, and see if they seem legit. Here we'll
show what to do with the output above.

.. code-block:: console
    
    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ arm-elf-linux-gdb bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf
    GNU gdb (GDB) 7.8.1
    Copyright (C) 2014 Free Software Foundation, Inc.
    ...
    No symbol table is loaded.  Use the "file" command.
    Reading symbols from bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf...done.
    (gdb) list *0x0001501b
    0x1501b is in crash_test_nmgr_write (repos/apache-mynewt-core/test/crash_test/src/crash_nmgr.c:68).
    63	    if (rc != 0) {
    64	        return MGMT_ERR_EINVAL;
    65	    }
    66	
    67	    rc = crash_device(tmp_str);  <--- That is likely part of it
    68	    if (rc != 0) {
    69	        return MGMT_ERR_EINVAL;
    70	    }
    71	
    72	    rc = mgmt_cbuf_setoerr(cb, 0);
    (gdb) list *0x00017338  <--- not relevant
    (gdb) list *0x00017cc8  <--- neither is this
    (gdb) list *0x00015c2b
    0x15c2b is in cbor_mbuf_writer (repos/apache-mynewt-core/encoding/tinycbor/src/cbor_mbuf_writer.c:32).
    27	{
    28	    int rc;
    29	    struct cbor_mbuf_writer *cb = (struct cbor_mbuf_writer *) arg;
    30	
    31	    rc = os_mbuf_append(cb->m, data, len);  <-- Does not seem likely. This probably ended here due to an earlier work that this task was doing.
    32	    if (rc) {
    33	        return CborErrorOutOfMemory;
    34	    }
    35	    cb->enc.bytes_written += len;
    36	    return CborNoError;
    (gdb) list *0x00015c1d
    0x15c1d is in cbor_mbuf_writer (repos/apache-mynewt-core/encoding/tinycbor/src/cbor_mbuf_writer.c:27).
    22	#include <tinycbor/cbor.h>
    23	#include <tinycbor/cbor_mbuf_writer.h>
    24	
    25	int
    26	cbor_mbuf_writer(struct cbor_encoder_writer *arg, const char *data, int len)
    27	{
    28	    int rc;      <---- Nope. Not relevant.
    29	    struct cbor_mbuf_writer *cb = (struct cbor_mbuf_writer *) arg;
    30	
    31	    rc = os_mbuf_append(cb->m, data, len);
    (gdb) list *0x0001161d
    0x1161d is in create_container (repos/apache-mynewt-core/encoding/tinycbor/src/cborencoder.c:244).
    239	    memcpy(where, &v, sizeof(v));
    240	}
    241	
    242	static inline CborError append_to_buffer(CborEncoder *encoder, const void *data, size_t len)
    243	{
    244	    return encoder->writer->write(encoder->writer, data, len);  <--- Hmmm, unlikely
    245	}
    246	
    247	static inline CborError append_byte_to_buffer(CborEncoder *encoder, uint8_t byte)
    248	{
    (gdb) list *0x00011841
    0x11841 is in preparse_value (repos/apache-mynewt-core/encoding/tinycbor/src/cborparser.c:182).
    177	    /* are we at the end? */
    178	    if (it->offset == parser->end)
    179	        return CborErrorUnexpectedEOF;
    180	
    181	    uint8_t descriptor = parser->d->get8(parser->d, it->offset); <--- Probably not relevant.
    182	    uint8_t type = descriptor & MajorTypeMask;
    183	    it->type = type;
    184	    it->flags = 0;
    185	    it->extra = (descriptor &= SmallValueMask);
    186	
    (gdb) list *0x000117c9
    0x117c9 is in cbor_encoder_create_map (repos/apache-mynewt-core/encoding/tinycbor/src/cborencoder.c:521).
    516	 */
    517	CborError cbor_encoder_create_map(CborEncoder *encoder, CborEncoder *mapEncoder, size_t length)
    518	{
    519	    if (length != CborIndefiniteLength && length > SIZE_MAX / 2)
    520	        return CborErrorDataTooLarge;
    521	    return create_container(encoder, mapEncoder, length, MapType << MajorTypeShift);     <-- I don't think this is relevant either.
    522	}
    523	
    524	/**
    525	 * Creates a indefinite-length byte string in the CBOR stream provided by
    (gdb) list *0x00013d8f
    0x13d8f is in nmgr_handle_req (repos/apache-mynewt-core/mgmt/newtmgr/src/newtmgr.c:261).
    256	        } else {
    257	            rc = MGMT_ERR_ENOENT;
    258	        }
    259	    } else if (hdr.nh_op == NMGR_OP_WRITE) {
    260	        if (handler->mh_write) {
    261	            rc = handler->mh_write(&nmgr_task_cbuf.n_b); <-- This is part of it.
    262	        } else {
    263	            rc = MGMT_ERR_ENOENT;
    264	        }
    265	    } else {

I was sending a newtmgr command which crashed the system. As you can see from this this example, little less than 50% of the addresses were part of the call chain. So read this output with care.


Coredump
--------

Coredump contains a full dump of system memory, and CPU registers. You can inspect the system state, including stack of the failing task, or any of the global state.

You can enable coredumps by setting syscfg variable OS_COREDUMP to 1. When crash happens, dumper will write the contents to flash_map region COREDUMP_FLASH_AREA.
After the crash, you can use imgmgr to download the coredump for offline analysis. To enable download/erase commands, you need to set syscfg variable IMGMGR_COREDUMP to 1.

Coredump package does not overwrite a previous coredump, if it exists in the flash. To get a new one, you first need to erase the area.

You can either use a dedicated area of flash, or use image slot 1 as the target.
If image slot1 and coredump areas are co-located, coredump will overwrite the image, unless image upgrade is in progress (slot1 marked as pending, or slot0 is not confirmed).

Fetching Coredump with newtmgr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

newtmgr coredump management commands are handled by imgmgr. You can query whether corefile is present, download one if it exists, and then erase the area afterwards.

.. code-block:: console
    
    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ newtmgr -c ttys005 image corelist
    Corefile present
    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ newtmgr -c ttys005 image coredownload -e core.elf
    0
    512
    1024
    1536
     ...
    65676
    Done writing core file to core.elf; hash=7e20dcdd136c6796fcb2a51e7384e90800d2ec045f2ee088af32529e929e2130
    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ newtmgr -c ttys005 image coreerase
    Done

I specified option '-e' to coredownload command. This converts the internal data representation to ELF file; a format that gdb understands.

Coredump Analysis Offline
~~~~~~~~~~~~~~~~~~~~~~~~~

Not all GDB configurations support corefiles. Specifically for the
architecture we're showing here, 'arm-none-eabi-gdb' does not have it
built in. However, 'arm-elf-linux-gdb' does.

Here's how I built it with MacOS:

.. code-block:: console
    
    tar xvzf gdb-7.8.1.tar.gz
    cd gdb-7.8.1
    ./configure --target=arm-elf-linux --without-lzma --without-guile --without-libunwind-ia64 --with-zlib
    make
    gdb/gdb -v

And this is how I built it for Linux:


.. code-block:: console
    
    sudo apt-get install zlibc zlib1g zlib1g-dev libexpat-dev libncurses5-dev liblzma-dev
    tar xvzf gdb-7.8.1.tar.gz
    cd gdb-7.8.1
    ./configure --target=arm-elf-linux --with-lzma --with-expat --without-libunwind-ia64 --with-zlib --without-babeltrace
    make
    gdb/gdb -v

Now that I have a suitable version of gdb at hand, I can use it to analyze
the corefile.


.. code-block:: console
    
    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ arm-elf-linux-gdb bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf core.elf 
    GNU gdb (GDB) 7.8.1
    Copyright (C) 2014 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "--host=x86_64-apple-darwin14.5.0 --target=arm-elf-linux".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>.
    Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
    For help, type "help".
    Type "apropos word" to search for commands related to "word"...
    No symbol table is loaded.  Use the "file" command.
    Reading symbols from bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf...done.
    [New process 1]
    #0  0x00014f28 in crash_device (
         how=how@entry=0x20001dc8 <os_main_stack+3904> "div0")
         at repos/apache-mynewt-core/test/crash_test/src/crash_test.c:47
    47	        val3 = val1 / val2;
    (gdb) bt
    #0  0x00014f28 in crash_device (
        how=how@entry=0x20001dc8 <os_main_stack+3904> "div0")
        at repos/apache-mynewt-core/test/crash_test/src/crash_test.c:47
    #1  0x0001501a in crash_test_nmgr_write (cb=0x20003464 <nmgr_task_cbuf>)
        at repos/apache-mynewt-core/test/crash_test/src/crash_nmgr.c:67
    #2  0x00013d8e in nmgr_handle_req (
        nt=nt@entry=0x200034e4 <nmgr_shell_transport>, 
        req=0x20002014 <os_msys_init_1_data+292>)
        at repos/apache-mynewt-core/mgmt/newtmgr/src/newtmgr.c:261
    #3  0x00013dfc in nmgr_process (nt=0x200034e4 <nmgr_shell_transport>)
        at repos/apache-mynewt-core/mgmt/newtmgr/src/newtmgr.c:325
    #4  0x00013e08 in nmgr_event_data_in (ev=<optimized out>)
        at repos/apache-mynewt-core/mgmt/newtmgr/src/newtmgr.c:332
    #5  0x0000925c in os_eventq_run (evq=<optimized out>)
        at repos/apache-mynewt-core/kernel/os/src/os_eventq.c:162
    #6  0x00008932 in main (argc=<optimized out>, argv=<optimized out>)
        at repos/apache-mynewt-core/apps/slinky/src/main.c:289
    (gdb) p g_current_task 
    $1 = (struct os_task *) 0x20001e88 <os_main_task>

Setting up coredumps, setting up a mechanism to download them, managing
them on the device and building gdb is certainly more work, but you'll
have much more data available when you start analyzing problems.
I don't think I can emphasize too much how valuable having all this data
is, when you're stuck with a difficult-to-solve crash.


Task Stack Use
--------------

One of the common problems is stack overflow within a task. Mynewt OS fills
the stack of a task with a pattern at the time task gets created. If you're
suspecting that stack might be blown, check the start of the stack (and
memory right before it).

There are also APIs to check the stack use. Task statistics, accessible
with console CLI or newtmgr, attempt to report the stack use by the tasks.
They do it by inspecting the presence of this pattern, so it is possible
to fool them also.

Here is what that data looks like at console. 'stksz' is the amount of
stack, and 'stkuse' is how much of it we think the task used it.

.. code-block:: console

    7109237 compat> tasks
    7109387 Tasks: 
    7109387     task pri tid  runtime      csw    stksz   stkuse   lcheck   ncheck flg
    7109390     idle 255   0  7109375    72810       64       26        0        0
    7109392     main 127   1       15     6645     1024      388        0        0
    7109394    task1   8   2        0    55543      192      116        0        0
    7109396    task2   9   3        0    55543       64       28        0        0

There are some helper macros for this when using gdb also. You'll need
to eyeball the stack manually, but at least it will tell you where to
find the stacks.

.. code-block:: console

    [marko@IsMyLaptop:~/src2/incubator-mynewt-blinky]$ newt debug slinky_nrf52
    Debugging bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf
     ...
    Reading symbols from bin/targets/slinky_nrf52/app/apps/slinky/slinky.elf...done.
    os_tick_idle (ticks=128)
         at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:164
    164	    if (ticks > 0) {
    (gdb) os_tasks
    Undefined command: "os_tasks".  Try "help".
    (gdb) source repos/apache-mynewt-core/compiler/gdbmacros/os.gdb 
    (gdb) os_tasks
     prio state      stack  stksz       task name
    * 255   0x1 0x20000e88     64 0x200035fc idle
      127   0x2 0x20001e88   1024 0x20001e88 main
        8   0x2 0x20003ab0    192 0x20000cbc task1
        9   0x2 0x20003bc0     64 0x20000d0c task2


Stack Check during Context Switch
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can ask OS to check the top of the stack on every context switch.
It'll walk over X number of os_stack_t elements, checking if our pattern
is still there for the task which is about to be switched out.

You can enable this by setting syscfg variable OS_CTX_SW_STACK_CHECK to 1.
Another syscfg variable, OS_CTX_SW_STACK_GUARD, controls how far into
the stack we peek.

Memory Corruption
-----------------

The recommended way of allocating blocks of memory is by using the
OS memory pools. As with all dynamically allocated memory, there can
issues with using after it gets freed, or it does not get freed at
all, code tries to free the same element multiple times, or you end up
overwriting the data within the next element.

There are syscfg variables you can set to get OS to do some of
sanity checks for you.

Sanity Check on Free
~~~~~~~~~~~~~~~~~~~~

By setting syscfg variable OS_MEMPOOL_CHECK to 1, OS will act when
an element is freed. It will walk through the list of already freed
entries, and check that the entry being freed does not already appear
in the free list. It will also check that the pool entry the code is
trying to free is within the memory range belonging to that pool.


Poisoning Pool
~~~~~~~~~~~~~~

If you set syscfg variable OS_MEMPOOL_POISON, the OS fills pool
entry memory with a data pattern whenever that entry is being freed.
It then checks that this pattern has not been disturbed when that
pool entry is allocated again. This would help to detect the scenarios
when code is still using a freed pool entry. Of course, the detection
will only be triggered if the code tries to modify the data belonging
tot that entry.

Pool Guard Areas
~~~~~~~~~~~~~~~~

Normally OS takes the memory region allocated for pool use and
splits it into chunks which are exactly the size of the pool entry (taking
into account the alignment restriction). By setting syscfg variable
OS_MEMPOOL_GUARD to 1, it creates a 'guard area' between pool elements,
and writes a specific data pattern to it. This is then checked whenever
the pool entry is freed, or allocated. If code writes past the data area
belonging to pool entry, the pattern would likely be disturbed, and would
cause an assert.

Exhausting Memory
~~~~~~~~~~~~~~~~~

Memory pool usage can be monitored through the mempool API. The data
collected there can be seen via the console CLI and/or using newtmgr.

Here is that data as seen from console:

.. code-block:: console

    7375292 compat> mpool
    7375581 Mempools: 
    7375581                             name blksz  cnt free  min
    7375584                           msys_1   292   12   12    8
    7375585              modlog_mapping_pool    12   16   12   12


We list the memory pools OS knows about. 'cnt' tells how many
elements the pool has in total. 'free' tells how many elements are
currently in the free pool, and 'min' tells what's the low point
for the number of elements within the pool.

What you should check is the 'min' number. If it gets to 0, it means
that the pool has been exhausted at one point. Depending on what
the pool is used for, you might want to take action.

There's some gdb helper macros to inspect the data belonging to
the default networking memory pool, msys_1.

.. code-block:: console

    (gdb) source repos/apache-mynewt-core/compiler/gdbmacros/mbuf.gdb 
    (gdb) mn_msys1_print 
    Mbuf addr: 0x20001ef0
    Mbuf header: $1 = {om_data = 0x20002380 <os_msys_init_1_data+1168> "\244$", 
      om_flags = 0 '\000', om_pkthdr_len = 8 '\b', om_len = 14, 
      om_omp = 0x20002ca0 <os_msys_init_1_mbuf_pool>, om_next = {sle_next = 0x0}, 
      om_databuf = 0x20001f00 <os_msys_init_1_data+16> "\016"}
    Packet header: $2 = {omp_len = 14, omp_flags = 0, omp_next = {stqe_next = 0x0}}
      ....
    ---Type <return> to continue, or q <return> to quit---q
    Quit
    (gdb) help mn_msys1_print
    usage: mn_msys1_print
    
    Prints all mbufs in the first msys pool.  Both allocated and unallocated mbufs
    are printed.
    (gdb) mn_msys1_free_print
    Mbuf addr: 0x20002138
     ....
    Mbuf addr: 0x20002b7c


Crash in Log
------------

System restarts can also be recorded in reboot log. Assuming reboot log
has been set up, it'll write a record either when system is asked
to reset (managed reset), or when system is coming back after an
unexpected reset.

To facilitate the latter, you should include a call from main()
to reboot package, reporting what HAL is telling you.

.. code-block:: c

    int
    main(int argc, char **argv)
    {

        sysinit();

	/* .... */
        reboot_start(hal_reset_cause());

This will then show if the system was restarted due to POR, brownout,
or hardware watchdog (the cause determination is MCU specific, so YMMV).
As you remember, exit via assert() and unhandled interrupt is going
via the dumper. So these kind of reboots will show up as 'SOFT' reset.

Restarts due to hardware watchdog will show up here, however. You can also
add a printout to beginning of main(), outputting what hal_reset_cause_str()
returns. That will generate a report on the console.
