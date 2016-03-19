# Mynewt Logging

Mynewt has a logging package (`apache-mynewt-core/sys/log`) to support
logging of information within a mynewt application.

#Description

Logging API is provided in `apache-mynewt-core/sys/log/include/log/log.h`.

It allows packages to define their own log streams with separate 
names.  It also allows application to control the output destinations
of logs. 

## Compile Time Settings

To save space at compile time, there is a compile time log level that
includes/excludes certain logs at compile time, saving image space.  For 
example, during debug, you can have significant logs present, but disable
these at compile time to ensure the code size limits are met.

A compiler flag `LOG_LEVEL` can be set  in your `target.cflags` or within
your app `pkg.cflags` files to set the compile time log level.   The 
log level are defined in `apache-mynewt-core/sys/log/include/log/log.h`
but must be added by number to your `yml` file.

For example:

```no-highlight
    pkg.cflags -DLOG_LEVEL=8
```

or 

```no-highlight
    newt target set my_target cflags=-DLOG_LEVEL=8
```

would both set the compile-time log level to `LOG_LEVEL_ERROR`.  All logs
of less than `LOG_LEVEL_ERROR` severity would be disabled at compile 
time and take no space within the mynewt application image.

These compile time settings are applicable to all logs registered with the
system.

## Log

Each log stream requires a log structure to define its  logging properties.
Its typical for modules to extern this structure.

## Log Handler

To use logs, a log-handler is required, which is responsible for handling
the I/O from the log.  The log package comes with two pre-build log handlers

* console -- streams log events directly to the console port.  Does
not support walking and reading.
* cbmem -- writes/reads log events to a circular buffer.  Supports walking 
and reading for access by newtmgr and shell commands.

In addition, its possible to create custom log handlers for other methods.
Example may include

* Flash file system
* Flat flash buffer
* streamed over some other interface

To use logging, you will not typically need to create your own log handler.
You can use one of the two supplied above. 

In Mynewt today, each module will register its logs with a default log handler.
Its up to the application to use or override this log handler for its 
specific purposes.  See below for an example.

## Typical use of logging when writing an application 

When writing an application that is using others log modules, you 
may want to override their log handlers and log levels.

Add the logging to your package file.

```no-highlight
    pkg.deps:
        - "@apache-mynewt-core/sys/log"
```

Initialize the logs in your startup code. It may look like this 

```no-highlight
#include <module1/module1.h>
#include <module3/module2.h>
#include <module3/module3.h>
#include <log/log.h>

/* log to console */
static struct log_handler app_log_handler;

/* this has to be after all the modules are 
 * initialized and have registered
 * their log modules */
void app_log_init(void)
{

    /* create a log handler for all logs . FOr this application
    ** send them directly to the console port */
    log_console_handler_init(&app_log_handler);
    ...
    /* set up logging for the modules appropriately */
    module1_log.log_level = LOG_LEVEL_WARN;
    module2_log.log_level = LOG_LEVEL_INFO;
    module3_log.log_level = LOG_LEVEL_DEBUG;

    /* set up a single handler for all modules */
    module1_log.log_handler = &app_log_handler;
    module2_log.log_handler = &app_log_handler;
    module3_log.log_handler = &app_log_handler;
}
```


## Typical use of Logging when writing a module 

When creating a package using its own logging, you can have this type of
structure.  

```no-highlight
/* my_package.h*/

/* pick a unique name here */
extern struct log my_log;
```

with an implementation in your module that looks like this 

```no-highlight

/* my_package.c */

struct log_handler log_console_handler;
struct log my_log;

{
    ...
    /* create a default handler for this log stream */
    log_console_handler_init(&log_console_handler);

    /* register my log with a name to the system */
    log_register("log", &my_log, &log_console_handler);

    /* set up default log level for my package */
    my_log.log_level = LOG_LEVEL_DEBUG;

    LOG_DEBUG(&my_log, LOG_MODULE_DEFAULT, "bla");
    LOG_DEBUG(&my_log, LOG_MODULE_DEFAULT, "bab");
}
```


