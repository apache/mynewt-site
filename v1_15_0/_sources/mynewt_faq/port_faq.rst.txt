Mynewt FAQ - Porting Mynewt
===========================

.. contents::
  :local:
  :depth: 1

Porting Mynewt to Core-M3 MCU
-----------------------------

**Q**: I have a weird OS tick issue with a Core-M3 MCU port. The tick rate is set up identically to most ARM MCUs by 
setting up a hardware interrupt to trigger SysClock / ``os_tick_per_sec``. SysClock is correct and ``os_tick_per_sec`` 
is set to 1000, but the tick rate seems to be significantly higher. What am I doing wrong?

**A**: Check whether the LED is actually staying on or it is flickering really fast by debugging through the loop. If 
it is staying on, you may be getting into an ``assert()``. Otherwise, it is due to the fact that the OS timer wasn’t 
created, which is done by ``hal_bsp.c``. The OS timer needs a hardware timer to be running, so you will need to call 
``hal_timer_init`` for timer 0 at one point.