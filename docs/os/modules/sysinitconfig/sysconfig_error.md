##Validation and Error Messages 

With multiple packages defining and overriding system configuration settings, it 
is easy to introduce conflicts and violations that are difficult to find.  The 
`newt build <target-name>` command validates the setting definitions and value 
overrides for all the packages in the target to ensure a valid and consistent build.
It aborts the build when it detects violations or ambiguities between packages.  
The following sections describe the error conditions that newt detects and 
the error messages that it outputs. For most errors, newt also outputs 
the `Setting history` with the order of package overrides to help 
you resolve the errors.

**Note:** The `newt target config <target-name>` command also detects 
errors and outputs error messages at the top of the command output. 
The command outputs the package setting definitions and values after it 
outputs the error messages. It is easy to miss the error messages at the top. 


###Value Override Violations

The newt tool uses package priorities to resolve override conflicts. It uses 
the value override from the highest priority package when multiple 
packages override the same setting. Newt checks for the following 
override violations:

* Ambiguity Violation - Two packages of the same priority override a setting with 
different values. And no higher priority package overrides the setting.
* Lateral Violation - A Lib package overrides a setting that another Lib package defines.
* Priority Violation - A package overrides a setting defined by a package with higher or 
equal priority (TODO: Add error message examples)

####Example: Ambiguity Violation Error Message

The following example shows the error message that newt outputs for an ambiguity violation:

```no-highlight

Error: Syscfg ambiguities detected:
    Setting: LOG_NEWTMGR, Packages: [apps/slinky, apps/splitty]
Setting history (newest -> oldest):
    LOG_NEWTMGR: [apps/splitty:0, apps/slinky:1, sys/log:0]

```

The above error occurs because the `apps/slinky` and `apps/splitty` packages 
in the split image target both override the same setting with different 
values.  The `apps/slinky` package sets the `sys/log` package `LOG_NEWTMGR` 
setting to 1, and the `apps/splitty` package sets the setting to 0. The 
overrides are ambiguous because both are `app` packages and 
have the same priority.  The following are excerpts of the defintion 
and the two overrides from the `syscfg.yml` files that cause the error:


```no-highlight

#Package: sys/log/
syscfg.defs:
    LOG_NEWTMGR:
        description: 'Enables or disables newtmgr command tool logging'
        value: 0

#Package: apps/slinky
syscfg.vals:
    LOG_NEWTMGR: 1

#Package: apps/splitty
syscfg.vals:
    LOG_NEWTMGR: 0

```

####Example: Lateral Violation Error Message

The following example shows the error message that newt outputs for a lateral violation:

```no-highlight


Error: Lateral overrides detected (bottom-priority packages cannot override settings):
    Package: mgmt/newtmgr, Setting: LOG_NEWTMGR

Setting history (newest -> oldest):
    LOG_NEWTMGR: [sys/log:0]

```

The above error occurs because the `mgmt/newtmgr` lib package 
overrides the `LOG_NEWTMGR` setting that the `sys/log` lib package 
defines. The following are excerpts of the definition and the override from the 
`syscfg.yml` files that cause this error: 

```no-highlight

#Package: sys/log
syscfg.defs:
     LOG_NEWTMGR:
        description: 'Enables or disables newtmgr command tool logging'
        value: 0

#Package: mgmt/newtmgr
syscfg.vals:
    LOG_NEWTMGR: 1

```
<br>

###Flash Area Violations

For `flash_owner` type setting definitions, newt checks 
for the following violations:

* An undefined flash area is assigned to a setting.
* A flash area is assigned to multiple settings.

####Example: Undefined Flash Area Error Message

The following example shows the error message that newt outputs for an undefined flash area.

```no-highlight

Building target targets/sim_slinky
Error: Flash errors detected:
    Setting REBOOT_LOG_FLASH_AREA specifies unknown flash area: FLASH_AREA_NOEXIST

Setting history (newest -> oldest):
    REBOOT_LOG_FLASH_AREA: [hw/bsp/native:FLASH_AREA_NOEXIST, sys/reboot:]

```
The above error occurs because the `hw/bsp/native` package assigns the 
undefined `FLASH_AREA_NOEXIST` flash area to the `sys/reboot` package 
`REBOOT_LOG_FLASH_AREA` setting.  The following are excerpts of the definition 
and the override from the `syscfg.yml` files that cause the error:

```no-highlight

#Package: sys/reboot
syscfg.defs:
    REBOOT_LOG_FLASH_AREA:
        description: 'Flash Area to use for reboot log.'
        type: flash_owner
        value:

#Package: hw/bsp/native
syscfg.vals:
    REBOOT_LOG_FLASH_AREA: FLASH_AREA_NOEXIST

```

####Example: Multiple Flash Area Assignment Error Message

The following example shows the error message that newt outputs when multiple 
settings are assigned the same flash area:

```no-highlight

Error: Flash errors detected:
    Multiple flash_owner settings specify the same flash area
          settings: REBOOT_LOG_FLASH_AREA, CONFIG_FCB_FLASH_AREA
        flash area: FLASH_AREA_NFFS

Setting history (newest -> oldest):
    CONFIG_FCB_FLASH_AREA: [hw/bsp/native:FLASH_AREA_NFFS, sys/config:]
    REBOOT_LOG_FLASH_AREA: [apps/slinky:FLASH_AREA_NFFS, sys/reboot:]

```

The above error occurs because the `hw/bsp/native` package assigns 
the `FLASH_AREA_NFFS` flash area to the `sys/config/` package 
`CONFIG_FCB_FLASH_AREA` setting, and the `apps/slinky` package 
also assigns `FLASH_AREA_NFFS` to the `sys/reboot` package 
`REBOOT_LOG_FLASH_AREA` setting.  The following are excerpts of the 
two definitions and the two overrides from the `syscfg.yml` files 
that cause the error:

```no-highlight

# Package: sys/config
syscfg.defs.CONFIG_FCB:
    CONFIG_FCB_FLASH_AREA:
        description: 'The flash area for the Config Flash Circular Buffer'
        type: 'flash_owner'
        value:

# Package: sys/reboot
syscfg.defs:
    REBOOT_LOG_FLASH_AREA:
        description: 'The flash area for the reboot log'
        type: 'flash_owner' 
        value:

#Package: hw/bsp/native
syscfg.vals:
     CONFIG_FCB_FLASH_AREA: FLASH_AREA_NFFS

#Package: apps/slinky
syscfg.vals: 
    REBOOT_LOG_FLASH_AREA: FLASH_AREA_NFFS

```
<br>
###Restriction Violations
For setting definitions with `restrictions` specified, newt checks for 
the following violations:

* A setting with a `$notnull` restriction does not have a value. 
* For a setting with expression restrictions, some required setting 
values in the expressions evaluate to false. 

####Example: $notnull Restriction Violation Error Message

The following example shows the error message that newt outputs when
a setting with `$notnull` restriction does not have a value:

```no-highlight

Error: Syscfg restriction violations detected:
    NFFS_FLASH_AREA must not be null 

Setting history (newest -> oldest):
    NFFS_FLASH_AREA: [fs/nffs:]

```

The above error occurs because the `fs/nffs` package defines the `NFFS_FLASH_AREA` 
setting with a `$notnull` restriction and no packages override the setting.  The 
following is an excerpt of the definition in the `syscfg.yml` file that causes the error:

```no-highlight

#Package: fs/nffs
syscfg.defs:
    NFFS_FLASH_AREA:
        description: 'The flash area to use for the Newtron Flash File System'
        type: flash_owner
        value:
        restrictions:
            - $notnull
```
####Example: Expression Restriction Violation Error Message

The following example shows the error message that newt outputs for 
an expression restriction violation:

```no-highlight

Error: Syscfg restriction violations detected:
    CONFIG_FCB=1 requires CONFIG_FCB_FLASH_AREA be set, but CONFIG_FCB_FLASH_AREA=

Setting history (newest -> oldest):
    CONFIG_FCB: [targets/sim_slinky:1, sys/config:0]
    CONFIG_FCB_FLASH_AREA: [sys/config:]

```

The above error occurs because the `sys/config` package defines the `CONFIG_FCB` setting with 
a restriction that when set, requires that the `CONFIG_FCB_FLASH_AREA` setting must 
also be set.  The following are excerpts of the definition and the override from the `syscfg.yml` 
files that cause the error:

```no-highlight

# Package:  sys/config
syscfg.defs:
    CONFIG_FCB:
        description: 'Uses Config Flash Circular Buffer'
        value: 0
        restrictions:
            - '!CONFIG_NFFS'
            - 'CONFIG_FCB_FLASH_AREA'

# Package: targets/sim_slinky
syscfg.vals:
    CONFIG_FCB: 1
```
<br>
###Task Priority Violations

For `task_priority` type setting definitions, newt checks for the following violations:

* A task priority number is assigned to multiple settings.  
* The task priority number is greater than 239.

####Example: Duplicate Task Priority Assignment Error Message

The following example shows the error message that newt outputs when
a task priority number is assigned to multiple settings.

**Note:** The settings used in this example are not actual `apps/slinky` and `sys/shell` settings.
These settings are created for this example because currently only one Mynewt package 
defines a `task_priority` type setting. 

```no-highlight

Error: duplicate priority value: setting1=SHELL_TASK_PRIORITY setting2=SLINKY_TASK_PRIORITY pkg1=apps/slinky pkg2=sys/shell value=1

```

The above error occurs because the `apps/slinky` package defines a `SLINKY_TASK_PRIORITY` 
setting with a default task priority of 1 and the `sys/shell` package also defines a 
`SHELL_TASK_PRIORITY` setting with a default task priority of 1.

####Example: Invalid Task Priority Error Message

The following example shows the error message that newt outputs when
a setting is assigned an invalid task priority value:

```no-highlight

Error: invalid priority value: value too great (> 239); setting=SLINKY_TASK_PRIORITY value=240 pkg=apps/slinky

```

The above error occurs because the `apps/slinky` package defines the `SLINKY_TASK_PRIORITY` setting 
with 240 for the default task priority value. 

**Note:** Newt does not output the `Setting history` with task priority violation error messages.  


<br>
###Duplicate System Configuration Setting Definition

A setting definition must be unique.  Newt checks that only one package in the 
target defines a setting. The following example shows the error message that newt 
outputs when multiple packages define the `LOG_NEWTMGR` setting:

```no-highlight

Error: setting LOG_NEWTMGR redefined

```
**Note:** Newt does not output the `Setting history` with duplicate setting error messages. 
