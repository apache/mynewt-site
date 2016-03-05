# hal_cputime


The hardware independent interface to system time.

## Description

Contains several different interface.

* An interface to get the current CPU time 
* Interfaces to convert between CPU time and clock time (microseconds etc.)
* An Interface to set up a software timer based on CPU time.

## Definition

[hal_cputime.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_cputime.h)

## CPU Time

The CPU time is not the same as the [os_time](TBD).  Typically,
the os_time is set to a much slower tick rate than the CPU time.  The CPU
time should be used for timing real-time events at exact times.  The os_time
should be used for system level timeout etc that are not in fine time 
resolutions.  In fact, cputime is not part of the os at all, but a hardware
layer abstraction to high resolution timers. 

There are methods to get the cputime as 32-bit and 64-bit values.  Both 
values may eventually wrap, but for timing short events a 32-bit value
may be sufficient and would 

 
