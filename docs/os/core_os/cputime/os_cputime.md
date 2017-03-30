# CPU Time

The MyNewt `cputime` module provides high resolution time and timer support. This module is intended for use by BSPs, drivers, and network controllers. 

## Description

The `cputime` API provides high resolution time and timer support.  The module must be initialized, using the `os_cputime_init()` function, with the clock frequency to use. The module uses the `hal_timer` API, defined in hal/hal_timer.h, to access the hardware timers. It uses the hardware timer number specified by the `OS_CPUTIME_TIMER_NUM` system configuration setting.

## Data Structures

The module uses the following data structures:

* `uint32_t` to represent `cputime`. Only the lower 32 bits of a 64 timer are used. 
* `struct hal_timer` to represent a cputime timer.

## List of Functions

The functions available in cputime are:

| **Function** | **Description** |
|-----------|-----------|
| [os_cputime_delay_nsecs](os_cputime_delay_nsecs.md) | Delays for a specified number of nanoseconds. |
| [os_cputime_delay_ticks](os_cputime_delay_ticks.md) | Delays for a specified number of ticks. |
| [os_cputime_delay_usecs](os_cputime_delay_usecs.md) | Delays for a specified number of microseconds. |
| [os_cputime_get32](os_cputime_get32.md) | Gets the current value of the cpu time.|
| [os_cputime_init](os_cputime_init.md) | Initializes the cputime module. |
| [os_cputime_nsecs_to_ticks](os_cputime_nsecs_to_ticks.md) | Converts the specified number of nanoseconds to number of ticks. |
| [os_cputime_ticks_to_nsecs](os_cputime_ticks_to_nsecs.md) | Converts the specified number of ticks to number of nanoseconds. | 
| [os_cputime_ticks_to_usecs](os_cputime_ticks_to_usecs.md) | Converts the specified number of ticks to number of microseconds. |
| [os_cputime_timer_init](os_cputime_timer_init.md) | Initializes a timer. |
| [os_cputime_timer_relative](os_cputime_timer_relative.md) | Sets a timer to expire in the specified number of microseconds from the current time. | 
| [os_cputime_timer_start](os_cputime_timer_start.md) | Sets a timer to expire at the specified cputime. |
| [os_cputime_timer_stop](os_cputime_timer_stop.md) | Stops a timer from running. |
| [os_cputime_usecs_to_ticks](os_cputime_usecs_to_ticks.md) | Converts the specified number of microseconds to number of ticks. |

## List of Macros

These macros should be used to evaluate the time with respect to each other.

* `CPUIME_LT(t1,t2)` -- evaluates to true if t1 is before t2 in time.
* `CPUTIME_GT(t1,t2)` -- evaluates to true if t1 is after t2 in time 
* `CPUTIME_LEQ(t1,t2)` -- evaluates to true if t1 is on or before t2 in time.
* `CPUTIME_GEQ(t1,t2)` -- evaluates to true if t1 is on or after t2 in time.
