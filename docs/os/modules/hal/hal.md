# Hardware Abstraction Layer

## Description

The Hardware Abstraction Layer (Hal) includes a set of APIs 
(Application Programmer Interface) to connect to 
the underlying hardware components including MCU components and peripheral
components.

The goal is to allow libraries, modules and applications to be written and
shared within the Mynewt community and used across the variety of supported
Mynewt platforms. A secondary goal is to provide a simple consistent API 
to commonly used MCU components and peripherals to make development easier.
Nothing in the hal precludes the user of the underlying physical devices,
it only limits the portability of the end application.

## Example

For example, a Mynewt contributor might write an intelligent light-switch 
module (`libs/light`) that provides the functionality of an intelligent light 
switch.  This might involve using a timer, a General Purpose Output (GPIO) 
to set the light in the on or off state, and the flash to log the times the 
lights were turned on or off.  The contributor would  like this module to 
work with as many different hardware, but can't possible test across the 
complete set of hardware supported by Mynewt.

**Solution**:  The contributor uses the HAL APIs to control the peripherals.
The Mynewt team ensures that the underlying HAL devices all work equivalently
through the HAL APIs. The contributors library is independent of the specifics
of the hardware.  

## Dependency

To include the HAL within your project,  simply add it to your package
dependencies as follows:

```no-highlight
pkg.deps: 
    . . .
    hw/hal
```

## Platform Support

Not all platforms (MCU and BSP) support all HAL devices. Consult your MCU
or BSP documentation to find out if you have hardware support for the 
peripherals you are interested in using.  Once you verify support, then
consult the MCU implementation and see if the specific hal interface you are
using is in the `mcu/xxx/src/hal_xxxx.c` implementation.  Finally, you 
can build your project and ensure that there are no unresolved hal_xxx 
externals.

## Hal Interfaces

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


## Implementing HAL Interfaces

It might be that a specific HAL interface is not supported on your MCU or
platform.  See the specific HAL documentation for that interface for tips
on implementing this for your MCU.
