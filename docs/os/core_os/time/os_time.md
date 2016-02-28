# OS_Time


The system time for ther Mynewt OS.

## Description

The Mynewt OS contains an incrementing time that drives the OS scheduler and time delays. The time is a fixed size (e.g. 32 bits) and will eventually wrap back to zero. The time to wrap from zero back to zero is called the **OS time epoch**. 

The frequency of the OS time tick is specified in the architecture-specific OS code `os_arch.h` and is named `OS_TICKS_PER_SEC`.

## Data Structures

Time is stored in Mynewt as an `os_time_t` value. 


## List of Functions

The functions available in time are:

* [os_time_delay](os_time_delay.md)
* [os_time_get](os_time_get.md)
* [os_time_tick](os_time_tick.md)

## List of Macros

Several macros help with the evalution of times with respect to each other.

* `OS_TIME_TICK_LT(t1,t2)` -- evaluates to true if t1 is before t2 in time.
* `OS_TIME_TICK_GT(t1,t2)` -- evaluates to true if t1 is after t2 in time 
* `OS_TIME_TICK_GEQ(t1,t2)` -- evaluates to true if t1 is on or after t2 in time.

NOTE:  For all of these macros the calculations are done modulo 'os_time_t'.  

Ensure that comparison of OS time always uses the macros above (to compensate for the possible wrap of OS time)

## Special Notes

Its important to understand how quickly the time wraps especially when doing time comparison using the macros above (or by any other means). 

For example, if a tick is 1 millisecond and `os_time_t` is 32-bits the OS time will wrap back to zero in about 49.7 days or stated another way, the OS time epoch is 49.7 days.

If two times are more than 1/2 the OS time epoch apart, any time comparison will be incorrect.  Ensure at design time that comparisons will not occur between times that are more than half the OS time epoch.

