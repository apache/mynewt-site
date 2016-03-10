# Hardware Abstraction Layer

###Description

The Hardware Abstraction Layer (HAL) includes a set of APIs 
(Application Programmer Interface) to connect to 
the underlying hardware components including MCU components and peripheral
components.

The goal is to allow libraries, modules and applications written for Mynewt to 
be shared within the Mynewt community and used across the variety of supported
Mynewt platforms. A secondary goal is to provide a simple consistent API 
to commonly used MCU components and peripherals to make development easier.
Nothing in the HAL precludes the user of the underlying physical devices,
it only limits the portability of the end application.

###Example

A Mynewt contributor might write a light-switch 
module (`libs/light`) that provides the functionality of an intelligent light 
switch.  This might involve using a timer, a General Purpose Output (GPO) 
to set the light to the on or off state, and flash memory to log the times the 
lights were turned on or off.  The contributor would like this module to 
work with as many different hardware platforms as possible, but can't 
possibly test across the complete set of hardware supported by Mynewt.

**Solution**:  The contributor uses the HAL APIs to control the peripherals.
The Mynewt team ensures that the underlying HAL devices all work equivalently
through the HAL APIs. The contributors library is independent of the specifics
of the hardware.  

###Dependency

To include the HAL within your project,  simply add it to your package
dependencies as follows:

```no-highlight
pkg.deps: 
    . . .
    hw/hal
```

###Platform Support

Not all platforms (MCU and BSP) support all HAL devices. Consult your MCU
or BSP documentation to find out if you have hardware support for the 
peripherals you are interested in using.  Once you verify support, then
consult the MCU implementation and see if the specific HAL interface you are
using is in the `mcu/xxx/src/hal_xxxx.c` implementation.  Finally, you 
can build your project and ensure that there are no unresolved hal_xxx 
externals.

###Implementing HAL Interfaces

It might be that a specific HAL interface is not supported on your MCU or
platform.  See the specific HAL documentation for that interface for tips
on implementing this for your MCU.
