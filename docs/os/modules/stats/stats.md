
# Statistics Module

The statistics module allows application, libraries, or drivers to
record statistics that can be shown via the Newtmgr tool and console.

This allows easy integration of statistics for troubleshooting,
maintenance, and usage monitoring.

By creating and registering your statistics, they are automatically
included in the Newtmgr shell and console APIs.

### Implementation Details

A statistic is an unsigned integer that can be set by the 
code. When building stats, the implementer chooses the size of the 
statistic depending on the frequency of the statistic and the 
resolution required before the counter wraps.    

Typically the stats are incremented upon code events; however, they are 
not limted to that purpose.  

Stats are organized into sections. Each section of stats has its own
name and can be queried separately through the API.  Each section of stats
also has its own statistic size, allowing the user to separate large (64-bit)
statistics from small (16 bit statistics).  NOTE:  It is not currently possible
to group different size stats into the same section.  Please ensure all stats
in a section have the same size.

Stats sections are currently stored in a single global stats group.  

Statistics are stored in a simple structure which contains a small
stats header followed by a list of stats.  The stats header contains:

```c
struct stats_hdr {
     char *s_name;
     uint8_t s_size;
     uint8_t s_cnt;
     uint16_t s_pad1;
 #ifdef STATS_NAME_ENABLE
     struct stats_name_map *s_map;
     int s_map_cnt;
 #endif
     STAILQ_ENTRY(stats_hdr) s_next;
 };
 ```
 
 <br>
 
#### Compile Time Options

When building your app, there is a single compile time option for
statistics.  When querying statistics, they are always queried by number,
but if you want to see the results by name, you need to define 
`STATS_NAME_ENABLE`.  This is defined using 

```
pkg.clfags: -DSTATS_NAME_ENABLE
```
in your apps pkg.yml file or 

```
target.clfags: -DSTATS_NAME_ENABLE
```
in your target definition.

Enabling stat names provides better descriptions in the reported stats,
but takes code space to store the strings within the image.

<br>

### Adding Stats to your code.

Creating new stats table requires the following steps.

* Include the stats header file 
* Define a stats section
* Declare an instance of the section 
* Define the stat sections names table
* Implement stat in your code
* Initialize the stats
* Register the stats

<br>

#### Include the stats header file

Add the stats library to your pkg.yml file for your package or app by adding
this line to your package dependencies.

```
pkg.deps:
    - "@apache-mynewt-core/sys/stats"
```

<br>

Add this include directive to code files using the stats library.

```
#include <stats/stats.h>
```

<br>

#### Define a stats section

You must use the `stats.h` macros to define your stats table.  A 
stats section definition looks like this.  

```
STATS_SECT_START(my_stat_section)
    STATS_SECT_ENTRY(attempt_stat)
    STATS_SECT_ENTRY(error_stat)
STATS_SECT_END
```

<br>

In this case we chose to make the stats 32-bits each.  `stats.h` supports three
different stats sizes through the following macros:

* `STATS_SIZE_16` -- stats are 16 bits (wraps at 65536)
* `STATS_SIZE_32` -- stats are 32 bits (wraps at 4294967296)
* `STATS_SIZE_64` -- stats are 64-bits

When this compiles/pre-processes, it produces a structure definition like this

```
struct stats_my_stat_section { 
    struct stats_hdr s_hdr;
    uint32_t sattempt_stat;
    uint32_t serror_stat;
};
```

<br>

You can see that the defined structure has a small stats structure
header and the two stats we have defined.

Depending on whether these stats are used in multiple modules, you may need
to include this definition in a header file.

<br>

#### Declaring a variable to hold the stats

Declare the global variable to hold your statistics. Since it is possible to
have multiple copies of the same section (for example a stat section for
each of 5 identical peripherals), the variable name of the stats section 
must be unique.

```
STATS_SECT_DECL(my_stat_section) g_mystat;
```

<br>

Again, if your stats section is used in multiple C files you will need to 
include the above definition in one of the C files and 'extern' this declaration 
in your header file.

```
extern STATS_SECT_DECL(my_stat_section) g_mystat;
```

<br>

#### Define the stats section name table

Whether or not you are using `STATS_NAME_ENABLE`, you must define 
a stats name table.  If `STATS_NAME_ENABLE` is not enabled, this will 
not take any code space or image size.  

```
/* define a few stats for querying */
STATS_NAME_START(my_stat_section)
    STATS_NAME(my_stat_section, attempt_stat)
    STATS_NAME(my_stat_section, error_stat)
STATS_NAME_END(my_stat_section)
```

<br>

When compiled by the preprocessor, it creates a structure that looks like this.

```
struct stats_name_map g_stats_map_my_stat_section[] = {
    { __builtin_offsetof (struct stats_my_stat_section, sattempt_stat), "attempt_stat" },
    { __builtin_offsetof (struct stats_my_stat_section, serror_stat), "error_stat" },
};
```

<br>

This table will allow the UI components to find a nice string name for the 
stat.

<br>

#### Implement stats in your code.

You can use the `STATS_INC` or `STATS_INCN` macros to increment your statistics
within your C-code.  For example, your code may do this:

```
    STATS_INC(g_mystat, attempt_stat);
    rc = do_task();
    if(rc == ERR) { 
        STATS_INC(g_mystat, error_stat);        
    }
```

<br>

#### Initialize the statistics

You must initialize the stats so they can be operated on by the stats
library.  As per our example above, it would look like the following.

This tells the system how large each statistic is and the number of 
statistics in the section.  It also initialize the name information for
the statistics if enabled as shown above.

```
    rc = stats_init(
        STATS_HDR(g_mystat), 
        STATS_SIZE_INIT_PARMS(g_mystat, STATS_SIZE_32), 
        STATS_NAME_INIT_PARMS(my_stat_section));
    assert(rc == 0);
```

<br>

#### Register the statistic section

If you want the system to know about your stats,  you must register them.

```
    rc = stats_register("my_stats", STATS_HDR(g_mystat));
    assert(rc == 0);
```

<br>

There is also a method that does initialization and registration at the 
same time,  called `stats_init_and_reg`.

<br>

### Retrieving stats through console or Newtmgr

If you enable console in your project you can see stats through the 
serial port defined.

This is the stats as shown from the example above with names enabled.
```
stat my_stats
12274:attempt_stat: 3
12275:error_stat: 0
```

<br>

This is the stats as shown from the example without names enabled.
```
stat my_stats
29149:s0: 3
29150:s1: 0
```

<br>

### A note on multiple stats sections

If you are implementing a device with multiple instances, you may
want multiple stats sections with the exact same format.

For example, suppose I write a driver for an external distance sensor.  My
driver supports up to 5 sensors and I want to record the stats of 
each device separately.

This works identically to the example above, except you would need to 
register each one separately with a unique name.  The stats system will
not let two sections be entered with the same name.

