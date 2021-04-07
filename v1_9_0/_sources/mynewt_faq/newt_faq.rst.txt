Mynewt FAQ - Newt
=================

.. contents::
  :local:
  :depth: 1

``newt size`` Command vs. Elf File Size
---------------------------------------

**Q**: I did a test build of blinky for nrf52 and got an elf-file of size 295424 bytes. If I use the newt size command for 
the application it says something like: 18764 bytes. What does this mean?

**A**: Elfs have a lot of extra information. newt size will show the are in flash that is used which better matches the 
``blinky.elf.bin`` file. Try ``running newt -ldebug build -v <your-target>`` and you will see something like this: 

.. code-block:: console 

  arm-none-eabi-objcopy -R .bss -R .bss.core -R .bss.core.nz -O binary ...
