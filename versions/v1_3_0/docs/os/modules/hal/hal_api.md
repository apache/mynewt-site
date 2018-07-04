
# HAL Interfaces

The HAL supports separate interfaces for many peripherals.  A brief
description of the interfaces are shown below.


| **Hal Name** | ** Interface File ** | **Description ** |
|--------------|----------------------|------------------|
| [bsp](hal_bsp/hal_bsp.md)         |  [hal_bsp.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_bsp.h)         | An hardware independent interface to identify and access underlying BSP.|
| [flash api for apps to use](hal_flash/hal_flash.md)        |  [hal_flash.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_flash.h)         | A blocking interface to access flash memory.|
| [flash api for drivers to implement](hal_flash/hal_flash_int.md)    |  [flash_map.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_flash_int.h)         | An interface to query information about the flash map (regions and sectors)| 
| [gpio](hal_gpio/hal_gpio.md)         |  [hal_gpio.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_gpio.h)          |  An interface for manipulating General Purpose Inputs and Outputs.|
| [i2c](hal_i2c/hal_i2c.md)      |  [hal_i2c.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_i2c.h)       | An interface for controlling Inter-Integrated-Circuit (i2c) devices.|
| [OS tick](hal_os_tick/hal_os_tick.md)         |  [hal_os_tick.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_os_tick.h)         | An interface to set up interrupt timers or halt CPU in terms of OS ticks.|
| [spi](hal_spi/hal_spi.md)      |  [hal_spi.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_spi.h)       | An interface for controlling Serial Peripheral Interface (SPI) devices.|
| [system](hal_system/hal_sys.md)       |  [hal_system.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_system.h)      | An interface for starting and resetting the system. |
| [timer](hal_timer/hal_timer.md)      |  [hal_cputime.h](https://github.com/apache/incubator-mynewt-core/tree/develop/hw/hal/include/hal/hal_timer.h)       | An interface for configuring and running HW timers|
| [uart](hal_uart/hal_uart.md)         |  [hal_uart.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_uart.h)         | An interface for communicating via asynchronous serial interface.|
| [watchdog](hal_watchdog/hal_watchdog.md)         |  [hal_watchdog.h](https://github.com/apache/incubator-mynewt-core/blob/develop/hw/hal/include/hal/hal_watchdog.h)         | An interface for enabling internal hardware watchdogs. |


