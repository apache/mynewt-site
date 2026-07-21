Mynewt FAQ - Bootloader and Firmware Upgrade
============================================

.. contents::
  :local:
  :depth: 1

Firmware Upgrade Capability
---------------------------

**Q**: I wanted to check if the stack provides firmware upgrade capability and if so, is there an example you can
provide on how it is being done?

**A**: The ``newtmgr`` tool is used to upgrade Mynewt devices. ``newtmgr`` is a command line tool, but there are
other client libraries available. There is some information listed under the "Image Upgrade" header in the
:doc:`Split Image documentation <../../../../os/modules/split/split>`.

Bootloader Documentation
------------------------

**Q**: Is there any documentation on using the bootloader? It sounds like it has baked-in support for serial loading,
but I can't find any details on serial protocol, or how to do a serial boot load. I assume we set a ``GPREGRET``
flag that tells the bootloader to expect to be flashed by serial, then it handles the rest. Is that true?

**A**: The serial bootloader would inspect a GPIO to see whether to wait for image upload commands or not. The protocol 
is the same newtmgr protocol we use for usual image uploads. For some the state reporting is simplified (omitted), and 
image upload goes to slot 0 instead of slot 1. The serial bootloading is built into newtmgr. For more information, refer 
to the documentation on the :doc:`Mynewt bootloader <../../../../os/modules/bootloader/bootloader>`.

MCUboot vs. Mynewt Bootloader
-----------------------------

**Q**: Is there any major difference between MCUboot and the Mynewt bootloader?
  
**A**: They use different formats. The header is different as well, since you need to pass an extra flag 
(e.g. -2 to newt for ``create-image`` for MCUboot). Visit the MCUboot page for more documentation. 

``boot_serial`` vs. ``bootutil``
--------------------------------

**Q**: What is the difference between ``boot_serial`` and ``bootutil``?
  
**A**: ``boot_serial`` is used only for downloading images over the serial port. If you are using newtmgr to upload 
image over serial, it is handled in ``boot_serial``. All other bootloader code is in ``bootutil``.