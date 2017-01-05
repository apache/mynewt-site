
##System Configuration and Initialization
This guide describes how Mynewt manages system configuration and initialization and shows you how to 
configure Mynewt to use specific system initialization functions and system configuration setting values 
for packages that you develop or use to build a target. This guide:

* Assumes you have read the [Concepts](/os/get_started/vocabulary.md) section that describes the Mynewt 
package hierarchy and its use of the `pkg.yml` and `syscfg.yml` files.   
* Assumes you have read the [Newt Tool Theory of Operation](/newt/newt_operation.md) and are familiar with how newt determines 
package dependencies for your target build.
* Covers only the system initialization for hardware independent packages. It does not cover the Board Support Package (BSP) and other hardware dependent system initialization.  

Mynewt defines several configuration parameters in the `pkg.yml` and `syscfg.yml` files that let you 
specify package initialization functions and define system configuration settings and values.
The newt tool uses this information from the `pkg.yml` and `syscfg.yml` files to: 

* Generate a system initialization function that calls all the package-specific system initialization functions. 
* Generate a system configuration header file that contains all the package configuration settings and values.
* Display the system configuration settings and values in the `newt target config` command.

The benefits with this approach include:

* Allows Mynewt developers to reuse other packages and easily change their configuration settings without updating source or header files when implementing new packages.
* Allows application developers to easily view the system configuration settings and values and determine the values to override for a target build.

###System Configuration Setting Definitions and Values 
A package can optionally:

* Define and expose the system configuration settings to allow other packages to override 
the default setting values. 
* Override the system configuration setting values defined by the packages that it depends on. 

You define package system configuration settings and override other package system configuration setting values 
in the `syscfg.yml` file for a given package. 

####Defining System Configuration Settings
You use the `defs` parameter in a package `syscfg.yml` file to define the system configuration settings 
for the package. `defs` is a mapping (or associative array) of system configuration setting definitions. It 
has the following syntax:  
 
```no-highlight
syscfg.defs:
    PKGA_SYSCFG_NAME1:
       description:
       value:
       type:
       restrictions:
    PKGA_SYSCFG_NAME2:
       description:
       value:
       type:
       restrictions:
```
Each system configuration setting definition consists of the following key-value mapping:  

* A system configuration setting name for the key, such as `PKGA_SYSCFG_NAME1` in the syntax example above.
Note: A system configuration setting name must be unique.  newt aborts the build 
when multiple packages define the same system configuration setting. 
* A mapping of system configuration setting fields for the value.  Each field is a key-value pair of attributes for
the setting.  The field keys are `description`, `value`, `type`, and `restrictions`. They are described in 
following table:

<table style="width:90%", align="center">
<tr>
<th>Field</th>
<th>Description</th>
</tr>
<tr>
<td><code>description</code></td>
<td>Describes the usage for the setting. This field is optional.</td>
<tr>
<td><code>value<code></td>
<td>Specifies the default value for the setting. This field is required. The value depends on the <code>type</code> that you specify. 
<tr>
<td><code>type</code></td>
<td>Specifies the data type for the <code>value</code> field. This field is optional. You can specify one of three types:
<ul>
<li><code>raw</code> - The <code>value</code> data is uninterpreted. This is the default <code>type</code>.</li>
<li><code>task_priority</code> - Specifies a Mynewt task priority number.  The task priority number assigned to each setting must be unique and between 0 and 239.  <code>value</code> can be one of the following: 
<ul>
<li>A number between 0 and 239 - The task priority number to use for the setting.</li>
<li><code>any</code> - Specify <code>any</code> to have newt automatically assign a priority for the setting.  
newt alphabetically orders all system configuration settings of this type and assigns the next highest available 
task priority number to each setting. </li>
</ul>
</li>
<li><code>flash_owner</code> - Specifies a flash area. 
<br>
<b>CHRIS - what is the format for this? The syscfg.yml files that use this type do not specify a value.</b> 
</li>
</ul>
</td>
</tr>
<tr>
<td><code>restrictions</code></td>
<td>Specifies restrictions on the setting value. This is an optional field. You can specify two formats:
<ul>
<li><code>$notnull</code> - Specifies that <code>value</code> cannot be the empty string.
<br>
<b>CHRIS: Do we still need this since we are now requiring a default value? </b> 
</li>
<li><code>expression</code> - Specifies a boolean expression of the form <code>[!]&ltrequired-setting>[if &ltbase-value>]</code>
<br>Examples:
<ul>
<li><code>restrictions: !LOG_FCB</code> - Can only enable this setting when <code>LOG_FCB</code> is false.
<li><code>restrictions: LOG_FCB if 0 </code> - Can only disable this setting when <code>LOG_FCB</code> is true.
</ul>
</li>
</ul>
</td>
</tr>
</table>
**Examples**

This is an example excerpt from the `sys/log` package `syscfg.yml` file:

```no-highlight

syscfg.defs:
    LOG_LEVEL:
        description: 'Log Level'
        value: 0
        type: raw

       ...       

    LOG_NEWTMGR: 
        description: 'Enables or disables newtmgr command tool logging'
        value: 0

```

The following example excerpt from the `net/nimble/controller` package `syscfg.yml` file uses the `task_priority` type:

```no-highlight

syscfg.defs:
    BLE_LL_PRIO:
        description: 'BLE link layer task priority'
        type: 'task_priority'
        value: 0

```

####Overriding System Configuration Setting Values
You use the `vals` parameter in `syscfg.yml` files to override the system configuration setting default values defined
by other packages.  This mechanism allows:

* Mynewt developers to implement a package and easily override the system configuration setting values 
   that are defined by the packages it depends on. 
* Application developers to easily override the system configuration setting values and build a customized target.
   You can use the `newt target config <target-name>` command to check all the system configuration setting definitions and
   values in your target to determine the setting values to override. See [newt target](/newt/command_list/newt_target.md). 

`vals` specifies the mappings of system configuration setting name-value pairs as follows: 

```no-highlight
syscfg.vals:
    PKGA_SYSCFG_NAME1: VALUE1
    PKGA_SYSCFG_NAME2: VALUE2
              ...
    PKGN_SYSCFG_NAME1: VALUEN
```
newt ignores overrides of undefined system configuration settings.  

**Resolving Override Conflicts**

newt uses package priorities to determine whether a package can override a value and 
to resolve conflicts when multiple packages override the same system configuration setting. 
The following rules apply:

* A package can only override the system configuration settings values that 
  are defined by packages with the same or lower priority. 
   ** CHRIS - Can LIB packages override the setting values of other LIB packages? The sysconfig email said yes but it looks like the current code does not allow it.**
* When packages with different priorities override the same system configuration setting value, newt uses 
   the value from the highest priority package.
* Packages of equal priority cannot override the same system configuration setting with different values. 
   newt aborts the build unless a higher priority package also overrides the value.

The following package types are listed from highest to lowest priority:

* Target
* App
* unittest - A target can include either an app or unit test package, but not both.
* BSP
* Lib - Includes all other system level packages such as os, lib, sdk, and compiler.

It is recommended that you override defaults at the target level instead of updating individual 
package `syscfg.yml` files.

**Example** 

This example is an excerpt from the `apps/slinky` package `syscfg.yml` file.  The package overrides, 
in addition to other packages, the `sys/log` package system configuration settings defined in the 
previous example. It changes the LOG_NEWTMGR system configuration setting value from `0` to `1`.

```no-highlight
syscfg.vals:
    # Enable the shell task.
    SHELL_TASK: 1

       ...

    # Enable newtmgr commands.
    STATS_NEWTMGR: 1
    LOG_NEWTMGR: 1
```


####Generated syscfg.h

**CHRIS - Please confirm that newt no longer generates #define for packages that are part of the 
build and #define for exported APIs in syscfg.h**
 
newt processes all the package `syscfg.yml` files and generates the
`<target-path>/generated/include/syscfg/syscfg.h` include file with `#define` statements for each system configuration 
setting definition.  newt creates a `#define` for a system configuration setting name as follows: 

* Adds the prefix `MYNEWT_VAL_`.
* Replaces all occurrences of "/", "-", and " " in the setting name with "_".
* Converts all characters to upper case.

For example, the #define for `my-config-name` setting name  is `MYNEWT_VAL_MY_CONFIG_NAME`.

newt groups the settings in `syscfg.h` by the packages that defined them. It also indicates the 
package that changed a system configuration setting value.  

Note: You only need to include `syscfg/syscfg.h` in your source files to access the `syscfg.h` file.  newt sets the correct include path to build your target. 

**syscfg.h Example**

This example is an excerpt from the `syscfg.h` file generated for an app/slinky target.  It lists 
the `sys/log` package definitions and also indicates that `app/slinky` changed the value 
for the `LOG_NEWTMGR` settings.  

```no-highlight
#ifndef H_MYNEWT_SYSCFG_
#define H_MYNEWT_SYSCFG_

     ...

/*** kernel/os */
#ifndef MYNEWT_VAL_MSYS_1_BLOCK_COUNT
#define MYNEWT_VAL_MSYS_1_BLOCK_COUNT (12)
#endif

#ifndef MYNEWT_VAL_MSYS_1_BLOCK_SIZE
#define MYNEWT_VAL_MSYS_1_BLOCK_SIZE (292)
#endif

     ...

/*** sys/log */

#ifndef MYNEWT_VAL_LOG_LEVEL
#define MYNEWT_VAL_LOG_LEVEL (0)
#endif

     ...

/* Overridden by apps/slinky (defined by sys/log) */
#ifndef MYNEWT_VAL_LOG_NEWTMGR
#define MYNEWT_VAL_LOG_NEWTMGR (1)
#endif

#endif
```

### System Initialization
**CHRIS do we need to document sysinit_loader() for split images.**

An application's `main()` function must first call the Mynewt `sysinit()` function to 
initialize the software before it performs any other processing.
`sysinit()` calls the `sysinit_app()` function to perform system 
initialization for the packages in the target.  You can, optionally, specify an 
initialization function that `sysinit_app()` calls to initialize a package. 
A package init function must have the following prototype:

```no-highlight
void init_func_name(void)
```
Package init functions are called in stages to ensure that lower priority packages 
are initialized before higher priority packages.

You specify an init function in the `pkg.yml` file for a package as follows:

* Use the `init_function` parameter to specify an init function name. 

           pkg.init_function: pkg_init_func_name

      `pkg_init_func_name` is the C function name of package init function. 

* Use the `init_stage` parameter to specify when to call the package init function.

           pkg.init_stage: stage_number

       `stage_number` is a number that indicates when this init function is called relative to the other 
       package init functions.  Mynewt calls the package init functions in increasing stage number order
       and in alphabetic order of init function names for functions in the same stage.
       Note: The init function will be called at stage 0 if `pkg.init_stage` is not specified.

       ** CHRIS - Are there guidelines on how to select the stage number? Are there specific stage numbers assigned
        to packages? **
 
#### Generated sysinit_app() Function
newt processes the `init_function` and `init_stage` parameters in all the pkg.yml files for a target,
generates the `sysinit_app()` function in the `<target-path>/generated/src/<target-name>-sysinit_app.c` file, and 
includes the file in the build. Here is an example `sysinit_app()` function:

```no-highlight
/**
 * This file was generated by Apache Newt (incubating) version: 1.0.0-dev
 */

#if !SPLIT_LOADER

void os_init(void);
void split_app_init(void);
void os_pkg_init(void);
void imgmgr_module_init(void);
void nmgr_pkg_init(void);

      ...

void console_pkg_init(void);
void log_init(void);

      ...

void
sysinit_app(void)
{
    os_init();

    /*** Stage 0 */
    /* 0.0: kernel/os */
    os_pkg_init();
    /* 0.1: sys/console/full */
    console_pkg_init();

        ...

    /*** Stage 1 */
    /* 1.0: sys/log */
    log_init();

        ...

    /*** Stage 5 */
    /* 5.0: boot/split */
    split_app_init();
    /* 5.1: mgmt/imgmgr */
    imgmgr_module_init();
    /* 5.2: mgmt/newtmgr */
    nmgr_pkg_init();
        ...
}

#endif

```

###Conditional Configurations
You can use the system configuration settings values to conditionally specify parameter values
in `pkg.yml` and `syscfg.yml` files. The syntax is:

```no-highlight
parameter_name.PKGA_SYSCFG_NAME:
     parameter_value
```
This specifies that `parameter_value` is only set for `parameter_name` if the `PKGA_SYSCFG_NAME` configuration setting value 
is non-zero. Here is an example from the `libs/os` package `pkg.yml` file:
```
pkg.deps:
    - sys/sysinit
    - util/mem

pkg.deps.OS_CLI
    - sys/shell

```
This example specfies that the `os` package depends on the `sysinit` and `mem` packages, and also depends on the 
`shell` package when `OS_CLI` is enabled. 

newt aborts the build when it detects circular conditional dependencies. 
