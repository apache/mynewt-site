
# HAL Interfaces

The HAL supports separate interfaces for many peripherals.  A brief
description of the interfaces are shown below.


| **Hal Name** | ** Interface File ** | **Description ** |
|--------------|----------------------|------------------|
| [adc](hal_adc/hal_adc.md)      |  [hal_adc.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_adc.h)       | An interface for controlling Analog To Digital Converters.
| [cputime](hal_cputime/hal_cpu_timer.md)      |  [hal_cputime.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_cputime.h)       | An interface for getting the CPU uptime, an interface to set arbitrary timers based on the CPU time, and an interface for a blocking delay if CPU time.
| [dac](hal_dac/hal_dac.md)      |  [hal_dac.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_dac.h)       | An interface for controlling Digital to Analog Converters.
| [flash](hal_flash/hal_flash.md)        |  [hal_flash.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_flash.h)         | A blocking interface to access flash memory.
| [flash map](hal_flash/hal_flash_map.md)    |  [flash_map.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/flash_map.h)         | An interface to query information about the flash map (regions and sectors) 
| [gpio](hal_gpio/hal_gpio.md)         |  [hal_gpio.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_gpio.h)          |  An interface for manipulating General Purpose Inputs and Outputs.
| [i2c](hal_i2c/hal_i2c.md)      |  [hal_i2c.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_i2c.h)       | An interface for controlling Inter-Integrated-Circuit (i2c) devices.
| [pwm](hal_pwm/hal_pwm.md)      |  [hal_pwm.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_pwm.h)       | An interface for controlling Pulse Width Modulator Devices.
| [spi](hal_spi/hal_spi.md)      |  [hal_spi.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_spi.h)       | An interface for controlling Serial Peripheral Interface (SPI) devices.
| [system](hal_system/hal_sys.md)       |  [hal_system.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_system.h)      | An interface for starting and resetting the system
| [uart](hal_uart/hal_uart.md)         |  [hal_uart.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_uart.h)         | An interface for communicating via asynchronous serial interface .


