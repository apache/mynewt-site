Mynewt FAQ - Hardware-Specific Questions
========================================

.. contents::
  :local:
  :depth: 2

Nordic nRF52-DK
---------------

Inverted Pin Value on nRF52-DK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I’ve been experiencing what seems to be some oddities with ``hal_gpio_write``. It appears as though the LED 
pin value on the nRF52-DK is inverted (0 sets the pin high, 1 sets it low). I am checking the GPIO state by turning 
an LED on and off. Why is this the case?

**A**: LEDs on the nRF52-DK are connected to VDD and GPIO so you need to set GPIO to a low state in order to make it turn on. 

Time Precision on nRF52
~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Can ``OS_TICKS_PER_SEC`` be changed per app? I'm on the nRF52 and I need better time precision than 128Hz.

**A**: No, it isn't possible to change the ticks per second for a single app.  That constant is defined to be most efficient 
for the particular MCU. 

If you need precision, the OS tick timer is probably not the right thing to use.  Take a look at :doc:`OS CPU Time <../../../../os/core_os/cputime/os_cputime>` for timer documentation. ``os_cputime`` has 1MHz frequency by default, and is enabled by default. 
It is recommended to use this for higher precision applications. 

Size Limit on Transaction Length for nRF52
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: There appears to be a 256-byte size limit on the maximum transaction length that the nRF52xxx ``hal_i2c`` driver can support. When I try send transactions larger than this the transactions fail (even after playing with a larger timeout etc). Does anyone know if this limit is due to the way the driver is written or the nRF52's i2c peripheral itself?

**A**: There shouldn’t be any limit here since TWI works basically by transferring data byte after byte. Check your slave device to see if it has some limit.

Redbear BLE Nano 2
------------------

View Logs on the Redbear BLE Nano2
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is it possible to see debug statements / logs while using Mynewt on the Redbear BLE Nano2. If so, can someone please 
tell me how to do so?


**A**: The RedBear daplink board presents multiple USB devices, one is a serial port which you can connect to. The 
:doc:`Blinky example project <../../tutorials/blinky/rbnano2>` has debug log statements which you can look at for how to log.

