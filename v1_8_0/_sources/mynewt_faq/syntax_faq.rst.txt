Mynewt FAQ - Syntax, Semantics, Configuration
=============================================

.. contents::
  :local:
  :depth: 1

Floating Point in Mynewt
------------------------

**Q**: I am trying to print floating point in Mynewt using ``console_printf("%f", floating_var)`` but I am unable to do so. 
How do I resolve the issue? I'm aware Mynewt uses baselibc - does it even support floating point?

**A**: Baselibc does support floating point formatting, but it is not enabled
by default.  To enable it, set the following syscfg setting to 1 in your
target: ``FLOAT_USER``

However, baselibc's float printf support is a bit limited.  In particular, it
ignores precision specifiers and always prints three digits after the
decimal point.

Ending the Delay of a Task Blocking a Call Early
------------------------------------------------

**Q**: I have a task which is blocking on a call to ``os_time_delay()``. What is the recommended way to end the delay 
early in an ISR (e.g. button press)?

**A**: The best way would be to use a semaphore. Initialize the semaphore with a count of 0 (``os_sem_init()``), then 
block on the semaphore with the maximum delay you want to wait for (``os_sem_pend()``).  The button press event would 
wake the first task up early by calling ``os_sem_release()``.

Random Function / Device
------------------------

**Q**: Does Mynewt have a random function or random device?

**A**: ``baselibc`` has ``rand()``, and ``crypto/tinycrypt`` has ``hmac-prng``.

Setting ``serial`` and ``mfghash``
----------------------------------

**Q**: What is ``mfghash``? How do I set ``serial`` and ``mfghash`` (currently blank in my app)?

**A**: ``mfghash`` is computed if you’re using ``newt mfg`` to construct your flash image, and it identifies the build of 
your bootloader. ``newt mfg`` bundles togetherthe bootloader, target image, and other data you’d want to bundle when creating 
an image to burn to flash. See the ``newt mfg`` :doc:`documentation <../newt/command_list/newt_mfg>` for the construction
side of things and ``apache-mynewt-core/sys/mfg/src/mfg.c`` for the firmware side. ``serial`` was intended to be used if you 
want to have your own naming scheme per device when building products; i.e. you want something other than the mcu serial 
number, or if you don’t have serial number available.

Leading Zeros Format in ``printf``
----------------------------------

**Q**: Is there a way to make printf and console_printf honor the leading zeros format? As in: 

``console_printf("%.2d", 5);`` 

outputting "05" instead of as for me now: "2d" ?

**A**: ``console_printf("%02d", 5);``

Mynewt Equivalent of UNIX ``sleep(3)``
--------------------------------------

**Q**: Is there an equivalent to the UNIX sleep(3)?
  
**A**: ``os_time_delay(OS_TICKS_PER_SEC * secs)``

Alternatives to ``cmsis_nvic.c``
--------------------------------

**Q**: What do I use instead of the full version of ``cmsis_nvic.c`` (i.e. for setting and getting IRQ priorities)?

**A**: Those functions are in the ``core_cmx.h`` files in ``hw/cmsis-core``.
