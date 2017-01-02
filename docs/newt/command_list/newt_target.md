## <font color="#F2853F" style="font-size:24pt">newt target </font>

Provides commands to create, build, delete, and query targets. 

#### Usage: 

```no-highlight
    newt target [command] input1 [input2]
```
#### Available Commands: 
```no-highlight
    config      View target system configuration
    copy        Copy target
    create      Create a target
    delete      Delete target
    dep         View target's dependency graph
    revdep      View target's reverse-dependency graph
    set         Set target configuration variable
    show        View target configuration variables
```

#### Flags:

```no-highlight
    -h, --help=false: help for target
```

#### Global Flags:

```no-highlight
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -o, --outfile string    Filename to tee log output to
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```
#### Description

Sub-command  | Explanation
-------------| ------------------------
config        | Displays the specified target's system configuration. The configuration for any package is listed in its `syscfg.yml` file. A target build consists of several packages. The command lists the settings for the config variables from all the included packages. If the default values have not been changed then the default values will be seen. 
copy         | Set variables (attributes) of the target named via `input1`. Currently the list of possible attributes (variables) are:`app`, `bsp`, `build_profile`, `cflags`, `lflags`. For a simulated target, e.g. for software testing purposes, `bsp` is set to `@apache-mynewt-core/hw/bsp/native`. 
create    |  Creates an empty target definition by the name of `input1`. 
delete    | Deletes only the description for the target. Does not delete the target directory with associated binaries. If you want to clean out the binaries, list files, and executables use`newt clean <target-name>` **before** deleting the target!
dep | Creates dependency tree for packages in the code for a target. Display shows each package followed by the list of libraries or packages that it depends on. 
revdep        | Creates the reverse dependency tree for packages in the code for a target. Display shows each package followed by the list of libraries or packages that depend on it.
set         | Set variables (attributes) of the target named via `input1`. Currently the list of possible attributes (variables) are:`app`, `bsp`, `build_profile`, `features`, `cflags`, `lflags`. For a simulated target, e.g. for software testing purposes, `bsp` is set to `@apache-mynewt-core/hw/bsp/native`.
         | To display all the existing values for a target variable (attribute), you can issue a `newt vals <variable-name>` command. For example, `newt vals app` displays the valid values available for the variable `app` for any target.
         | Currently, the only two values available for `build_profile` are `optimized` and `debug`.
show        | Shows what variables (attributes) are set on the specified target `input1`. If no `input1` is specified then show the configuration for all the targets defined so far.


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
config  | newt target config rb_blinky | Shows all the system configuration settings for all the packages in the target named `rb_blinky`.
copy   | newt target copy rb_blinky rb_bletiny | Clones the target settings in `rb_blinky` to the destination target `rb_bletiny`
create | newt target create target1 | Creates an empty target by the name `target1`
show   | newt target show myble | Shows all variable settings for the target named "myble" i.e. what app, bsp, build_profile, features, cflags are set to. Note that all variables are not required to be set in order to successfully define a target.  
show   | newt target show | Shows all variable settings for all the targets defined. 
set       | newt target set myble app=@apache-mynewt-core/apps/bletiny | Assign `bletiny` to be the application to be included in the build for the target named `myble`.

