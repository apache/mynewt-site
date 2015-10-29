
## Newt tool Reference

### Available high-level commands

```
version     Display the Newt version number
help        Help about any command
nest        Commands to manage nests & clutches (remote egg repositories)
egg         Commands to list and inspect eggs on a nest
target      Set and view target information
```

### *version*

#### Usage:

    newt version [flags]
    
Flags:

    -h, --help=false: help for version

Global Flags:

    -h, --help=false: help for newt
    
    
Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
version       | newt version | Displays the version of newt tool installed


### *help*

#### Usage:

    newt help [input1]
    
Flags:

```

-h, --help=false: help for newt
-l, --loglevel="WARN": Log level, defaults to WARN.
-q, --quiet=false: Be quiet; only display error output.
-s, --silent=false: Be silent; don't output anything.
-v, --verbose=false: Enable verbose output when executing commands.
```
    
Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
help       | newt help target | Displays the help text for the newt command 'target'
help       | newt help   | Displays the help text for newt tool
    
    

### *nest*

#### Usage: 

    newt nest [command][flags] input1 input2...

Available commands: 

    create          Create a new nest
    generate-clutch Generate a clutch file from the eggs in the current directory
    add-clutch      Add a remote clutch, and put it in the current nest
    list-clutches   List the clutches installed in the current nest
    show-clutch     Show an individual clutch in the current nest


Flags:

    -h, --help=false: help for nest

Global Flags:

    -h, --help=false: help for newt
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.

Description

Sub-command  | Explanation
-------------| ------------------------
create       | Downloads the skeleton of a nest on your local machine from the optional `input2` nest url, if specified, and creates a new nest directory by the name of `input1`. If `input2` is not specified, then a default skeleton from the `tadpole` nest on Mynewt is downloaded. The command lays out a generic directory structure for the nest you are going to build under it and includes some default eggs in it.
generate-clutch | Takes a snapshot of the eggs in the current local directory and combines them into a clutch by the name of `input1` and with the url of `input2` and generates a standard output of the clutch details that can be redirected to a `.yml` clutch file. Typically the clutch file name is chosen to match the clutch name which means the standard output should be directed to a clutch file named `input1.yml`
add-clutch   | Downloads the clutch of the name `input1` from the master branch of the github repository `input2` into the current nest. A file named `input1.yml` file is added in the `.nest/clutches` subdirectory inside the current local nest. The `.nest/` directory structure is created automatically if it does not exist.
list-clutches | Lists all the clutches present in the current nest, including clutches that may have been added from other nests on github. The output shows all the remote clutch names and the total eggshells in each of the clutches.
show-clutch | Shows information about the clutch that has the name given in the `input1` argument. Output includes the clutch name, url, and all the constituent eggs with their version numbers.

Command-specific flags

Sub-command  | Available flags | Explanation
-------------| ----------------|------------
add-clutch   | -b, --branch="<branch-name>" | Fetches the clutch file with name `input1` from the specified branch at `input1` url of the github repository. All subsequent egg installations will be done from that branch.

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
create       | newt nest create test_project | Creates a new nest named "test_project " using the default skeleton0
create       | newt nest create mynest <nest-url> | Creates a new nest named "mynest" using the skeleton at the <nest-url> specified
generate-clutch | newt nest generate-clutch myclutch https://www.github.com/mynewt/larva > myclutch.yml| Takes a snapshot of the eggs in the current nest to form a clutch named myclutch with the url https://www.github.com/mynewt/larva. The output is written to a file named `myclutch.yml` and describes the properties and contents of the clutch (name, url, eggs).
add-clutch   | newt nest add-clutch larva https://www.github.com/mynewt/larva | Adds the remote clutch named larva at www.github.com/mynewt/larva to the local nest. 
list-clutches | newt nest list-clutches | Shows all the remote clutch description files that been downloaded into the current nest
show-clutch   | newt nest show-clutch larva | Outputs the details of the clutch named larva such as the github url where the remote sits, the constituent eggs and their versions


### *egg*

#### Usage: 

    newt egg [command][flag] input1 input2
    
    
Available Commands: 
 
    list        List eggs in the current nest
    checkdeps   Check egg dependencies
    hunt        Search for egg from clutches
    show        Show the contents of an egg.
    install     Install an egg
    remove      Remove an egg

Flags:
 
    -h, --help=false: help for egg

Global Flags:

    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.

Description

Sub-command  | Explanation
-------------| ------------------------
list         | List all the eggs in the current nest. The output shows the name, version, path, and any additional attributes of each egg in the nest such as dependencies, capabilities, and linker scripts. The newt command gets the attributes of each egg from the corresponsing egg.yml description file.
checkdeps    | Resolve all dependencies in the local nest. This command goes through all eggs currently installed, checks their dependencies, and prints any unresolved dependencies between eggs.
hunt         | Hunts for an egg, specified by `input1`. The local nest, along with all remote nests (clutches) are searched. All matched eggs are shown along with the clutch informaton. Installed eggs are called out as such. The command can be invoked from anywhere in the nest.
show     |  Show the contents of the egg named `input2` found in the clutch named `input1`. The clutch name is optional; if only the egg name is given as the argument it is resolved using all the clutches installed in the current nest. If the egg is present in multiple clutches it will list all of them along with the clutch information for each.
install  |  Install the egg specified by `input2` from the clutch named `input1`. The command downloads the egg from the github repository using the URL in the clutch description file (typically donwloaded as 'input1@<branch-name>.yml' in .nest/clutches). It also downloads all the dependencies (constituent eggs) as decribed in the egg's description file ('egg.yml') and installs all of them. The clutch name is optional. If only the egg name is given as the argument, the command looks for the egg name in all the clutches in the local nest and installs accordingly. An egg is installed by this command only if it has not already been installed. 
remove   |  Remove an egg named `input2` from clutch `input1`, if clutch is specified. Otherwise only one input required - that of the name of the egg to be removed from the local nest.




Command-specific flags

Sub-command  | Available flags | Explanation
-------------| ----------------|------------
install   | -b, --branch="<branch-name>" | Installs the eggs from the branch name or tag of the clutch specified

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
list       | newt egg list | CList all of the eggs in the current nest and the details of the eggs.
checkdeps       | newt egg checkdeps | Checks all the dependencies between eggs in the nest. Lists any unresolved dependencies.
hunt | newt egg hunt blinky| Hunts for the egg named 'blinky'. The command can be invoked from anywhere in the nest. Results show if the egg is installed and which clutch, if any, has the egg.
show   | newt egg show larva libs/os | Show the contents of the egg named 'libs/os' in the clutch named larva. The contents are essentially derived from the egg's 'egg.yml' file. 
install | newt egg install hw/bsp/stm32f3discovery | Downloads and installs the egg named "stm32f3discovery" (specified with its full path name inside the remote nest) along with all its dependencies from the remote nest on github. Since no clutch is specified, the URL for the remote nest in the clutch description file found in the local nest (in .nest/clutches for the project) is used. 
remove   | newt egg remove larva blinky| Removes the egg named blinky only from the clutch named larva
remove   | newt egg remove blinky| Removes the egg named blinky from the local nest


### *target*

#### Usage: 

Usage: 

    newt target [command] input1 [flag1] [flag2]

Available Commands: 

    set         Set target configuration variable
    unset       Unset target configuration variable
    delete      Delete target
    create      Create a target
    show        View target configuration variables
    build       Build target
    test        Test target
    export      Export target
    import      Import target

Flags:

    -h, --help=false: help for target

Global Flags:

    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.

Description

Sub-command  | Explanation
-------------| ------------------------
set         | Set attributes of the target. Currently the list of possible attributes are:``` arch, compiler, compiler_def, project, bsp, egg, identities, capabilities, dependencies, cflags, lflags```. Typically only the first 5 need to be set for a hardware target. For a simulated target, e.g. for software testing purposes, `arch=sim`, `compiler=sim`, and `egg=<egg name to be tested>`. You cannot set both the project and egg for a target. 
unset    | Unset attributes of the target in its configuration.
delete         | Deletes only the description for the target. Does not delete the target directory with associated binaries. If you want to clean out the binaries, list files, and executables use`newt target build <target-name> clean` **before** deleting the target!
create    |  Creates a target description or build definition by the name `input1`. By default it assigns the sim (simulator) architecture to it which allows you to build new projects and software on your native OS and try it out.
show  |  Display the configuration defined for the target named `input1`. If no `input1` is specified then show the details for all the targets in the nest.
build   |  Build the source code into an image that can be loaded on the hardware associated with the target named `input1` to do the application enabled by the 'project' associated with that target (via the target definition). It creates 'bin/' and 'bin/<input1>/' subdirectories inside the base directory for the project, compiles and generates binaries and executables, and places them in 'bin/<input1>/. 
test   | Test an egg on the target named `input1`. The egg is either supplied as an argument to the command line invocation of `newt target test` or added as part of the target definition. If only the target is specified as `input1`, then the egg in the target's definition is automatically chosen to be tested. You currently cannot test an entire project on a hardware target. The test command is envisioned for use if one or two eggs gets updated and each needs to be tested against a target. Alternatively, a script may be written for a series of tests on several eggs.
export |  Exports the configurations of the specified target `input1`. If -a or -export-all flag is used, then all targets are exported and printed out to standard out. You may redirect the output to a file. 
import | Import one or more target configuration from standard input or a file. Each target starts with `@target=<target-name>` followed by the attributes. The list of targets should end with `@endtargets`.
size   | Outputs the RAM and flash consumption by the components of the specified target `input1`.




Command-specific flags

Sub-command  | Available flags | Explanation
-------------| ----------------|------------
build   | clean | All the binaries and object files for the specified target will be removed. The subdirectory named after the specified target within that project is removed.
build clean | all | All the binaries and object files for all targets are removed, and subdirectories of all targets for the project are removed. However, the entire repository is not emptied since any eggs or projects that the specified target doesn't reference are not touched.
export  | -a, -export-all  | Export all targets. `input1` is not necessary when this flag is used.
import  | -a, -import-all  | Import all targets typed into standard input or redirected from a file. 

Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
set       | newt target set myblinky compiler=arm-none-eabi-m4 | Set the compiler for the 'myblinky' target to the gcc compiler for embedded ARM chips.
unset       | newt target unset myblinky compiler | Remove the setting for the compiler for the 'myblinky' target.
delete       | newt target delete myblinky | Delete the target description for the target named 'myblinky'. Note that it does not remove any binaries or clean out the directory for this target. 
create       | newt target create blink_f3disc | Create a new target description by the name 'blink_f3disc'. The architecture is 'sim' by default and can be changed using subcommand 'set' above.
show      | newt target show myblinky | Show the target attributes set for 'myblinky'
build       | newt target build blink_f3disc | Compile the source code for the target named blink_f3disc and generate binaries that can be loaded into the target hardware.
test | newt target test test_target egg=libs/os | Tests the egg named 'libs/os' against the target named 'test_target'
export   | newt target export -a > my_exports.txt | Export all build targets from the current nest, and redirect output to a file named 'my_exports.txt'.
export  | newt target export -export-all  | Export all build targets from the current nest, and print them to standard output on the screen.
export  | newt target export my_target | Export only target named 'my_target' and print it to standard output on the screen.
import | newt target import ex_tgt_1 < exported_targets.txt | Imports the target configuration for 'ex_tgt_1' in 'exported_targets.txt'.
import | newt target import -a < in_targets.txt | Imports all the targets specified in the file named `in_targets.txt`. A sample file is shown after this table.
size   | newt target size blink_nordic | Inspects and lists the RAM and Flash memory use by each component (object files and libraries) of the target.

Example content for `in_targets.txt` file used for importing targets `test3` and `test4`.  

> @target=test3  
project=blinked  
arch=sim  
compiler_def=debug  
compiler=arm-none-eabi-m4  
@target=test4  
project=super_blinky  
arch=sim  
compiler_def=debug  
compiler=arm-none-eabi-m4  
@endtargets
