Mynewt FAQ - Drivers and Modules
================================

.. contents::
  :local:
  :depth: 1

Drivers in Mynewt
-----------------

**Q**: Is this a correct assumption about Mynewt, that if there exists no driver implementation for a specific SoC, 
in ``hw/drivers/``, then it is not supported. For instance, there exists a flash driver for ``at45db``, this implies 
that the Nordic nRF52 SoC is not supported at the moment?

**A**: ``at45db`` is SPI, and any SPI would work. You send SPI configuration info when initializing. SPI drivers are below 
the ``hw/mcu/`` tree. ``hw/drivers/pwm`` and ``hw/drivers/adc`` are SoC specific. In general, drivers are for peripherals 
that aren't universally supported. Features that all (or nearly all) MCUs support are implemented in the HAL. For example, 
internal flash support is a HAL feature. Visit the :doc:`HAL Documentation <../../../../os/modules/hal/hal>` for more information.

Module Argument in Mynewt Logging Library
-----------------------------------------

**Q**: Can you tell me what the purpose of the module argument is in the Mynewt logging library? It looks like it just 
takes an ``int``. Is this just to assign an integer ID for each module that logs?

**A**: It is just an integer which accompanies each log entry.  It provides context for each log entry, and it allows a 
client to filter messages based on module (e.g. "give me all the file system log entries"). 

Log Name vs. Module Number
--------------------------

**Q**: So, what is the conceptual difference between a log name, and a module number? It seems like a log type would be 
assigned the same name as the module that is using it, and that the module number is just a numerical ID for the module. 
Basically, I don't understand what the purpose of storing the name into the log type is, and passing the module number 
in as part of ``LOG_<LEVEL>`` macro.

**A**: A log just represents a medium or region of storage (e.g., "console", or "flash circular buffer in 12kB of flash, 
starting at 0x0007d000").  Many parts of the system can write to the same log, so you may end up with Bluetooth, file 
system, and kernel scheduler entries all in the same log.  The module ID distinguishes these entries from one another. 
You can control level per module, so you can say, “give me all bluetooth warnings, but only give me system level errors”.

**Q**: Okay, so for something like console logging, we would likely register one log for the entire application, and give 
each module an ID?

**A**: I think the thought is that would be the debug log, and during development you could pipe that to console. In production, 
that might go in the spare image slot. I’m not sure if we support it yet, but we should make sure the log can write to multiple 
handlers at the same time.