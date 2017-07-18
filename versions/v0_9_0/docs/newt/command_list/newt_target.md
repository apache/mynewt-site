## <font color="#F2853F" style="font-size:24pt">newt target </font>

Provides commands to create, build, delete, and query targets. 

#### Usage: 

```no-highlight
    newt target [command] input1 [input2]
```
#### Available Commands: 
```no-highlight
    show        View target configuration variables
    set         Set target configuration variable
    create      Create a target
    delete      Delete target
    copy        Copy target
    vars        Show variable names possible for a target
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
show        | Shows what variables (attributes) are set on the specified target `input1`. If no `input1` is specified then show the configuration for all the targets defined so far.
set         | Set variables (attributes) of the target named via `input1`. Currently the list of possible attributes (variables) are:`app`, `bsp`, `build_profile`, `features`, `cflags`, `lflags`. For a simulated target, e.g. for software testing purposes, `bsp` is set to `@apache-mynewt-core/hw/bsp/native`. 
         | To display all the existing values for a target variable (attribute), you can simply hit return after that variable. For example, `newt target set input1 app` displays the valid values available for the variable `app` for a target named `input11`. 
         | Currently, the only two values available for `build_profile` are `optimized` and `debug`. 
create    |  Creates an empty target definition by the name of `input1`. 
delete    | Deletes only the description for the target. Does not delete the target directory with associated binaries. If you want to clean out the binaries, list files, and executables use`newt target clean <target-name>` **before** deleting the target!
copy | Creates a new target by the name of `input2` by cloning the definition of an existing target named `input1`. 
vars        | Shows what variables (attributes) are available to set on the target


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
show   | newt target show myble | Shows all variable settings for the target named "myble" i.e. what app, bsp, build_profile, features, cflags are set to. Note that all variables are not required to be set in order to successfully define a target.  
show   | newt target show | Shows all variable settings for all the targets defined. 
set       | newt target set myble app=@apache-mynewt-core/apps/bletiny | Assign `bletiny` to be the application to be included in the build for the target named `myble`.
copy  | newt target copy my_blinky_sim test1 | Creates a new target by the name `test1` by copying the attributes from `my_blinky_sim`
vars | newt target vars  | Shows all the variables newt recognizes - app, bsp, build_profile, features


