
# Hal Interfaces

The HAL supports separate interfaces for many peripherals.  A brief
description of the interfaces are shown below.


| **Hal Name** | ** Interface File ** | **Description ** |
|--------------|----------------------|------------------|
| [cputime](hal_cpu_timer.md)      |  [hal_cputime.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_cputime.h)       | An interface for getting the CPU uptime, an interface to set arbitrary timers based on the CPU time, and an interface for a blocking delay if CPU time.
| [flash](hal_flash.md)        |  [hal_flash.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_flash.h)         | A blocking interface to access flash memory
| [flash_int](hal_flash_int.md)    |  [hal_flash_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_flash_int.h)     | The underlying API that the flash drivers implement.  If you are writing a new flash driver, this is how you hook it into the HAL.
| [flash map](hal_flash_map.md)    |  [flash_map.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/flash_map.h)         | An interface to query information about the flash map (regions and sectors) 
| [gpio](hal_gpio.md)         |  [hal_gpio.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_gpio.h)          |  An interface for manipulating General Purpose Inputs and Outputs
| [system](hal_system.md)       |  [hal_system.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_system.h)      | An interface for starting and resetting the system
| [uart](hal_uart.md)         |  [hal_uart.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_uart.h)         | An interface for communicating via asyncrhonous serial interface 


