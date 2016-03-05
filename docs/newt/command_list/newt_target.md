## <font color="#F2853F" style="font-size:24pt">newt target </font>

Provides commands to create, build, delete, and query targets. 

#### Usage: 

```no-highlight
    newt target [command] input1 [flag1] [flag2]
```
#### Available Commands: 
```no-highlight
    set         Set target configuration variable
    unset       Unset target configuration variable
    delete      Delete target
    create      Create a target
    show        View target configuration variables
    build       Build target
    test        Test target
    size        Size of the target
    label       Add image header to target binary
    download    Download project to target
    debug       Open debugger session to target
    export      Export target
    import      Import target
```
#### Flags:
```no-highlight
    -h, --help=false: help for target
```
#### Global Flags:
```no-highlight
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```
#### Description

Sub-command  | Explanation
-------------| ------------------------
set         | Set attributes (variables) of the target. Currently the list of possible attributes (variables) are:``` arch, compiler, compiler_def, project, bsp, pkg, identities, capabilities, dependencies, cflags, lflags```. Typically only the first 5 need to be set for a hardware target. For a simulated target, e.g. for software testing purposes, `arch=sim`, `compiler=sim`, and `pkg=<pkg name to be tested>`. You cannot set both the project and pkg for a target. 
         | To display all the existing values for any target attribute (variable), you can simply hit return after that variable. For example, `newt target set target1 arch` displays the valid values available for the attribute `arch` for a target named `target1`. 
unset    | Unset attributes of the target in its configuration.
delete         | Deletes only the description for the target. Does not delete the target directory with associated binaries. If you want to clean out the binaries, list files, and executables use`newt target build <target-name> clean` **before** deleting the target!
create    |  Creates a target description or build definition by the name `input1`. By default it assigns the sim (simulator) architecture to it which allows you to build new projects and software on your native OS and try it out.
show  |  Display the configuration defined for the target named `input1`. If no `input1` is specified then show the details for all the targets in the app.
build   |  Build the source code into an image that can be loaded on the hardware associated with the target named `input1` to do the application enabled by the 'project' associated with that target (via the target definition). It creates 'bin/' and 'bin/<input1>/' subdirectories inside the base directory for the project, compiles and generates binaries and executables, and places them in 'bin/<input1>/. 
test   | Test a pkg on the target named `input1`. The pkg is either supplied as an argument to the command line invocation of `newt target test` or added as part of the target definition. If only the target is specified as `input1`, then the pkg in the target's definition is automatically chosen to be tested. You currently cannot test an entire project on a hardware target. The test command is envisioned for use if one or two pkgs gets updated and each needs to be tested against a target. Alternatively, a script may be written for a series of tests on several pkgs.
size   | Displays the memory used (in bytes) by the component libraries that have been compiled and linked to form the executable for the specified target build (input1). The memory usage of the different components is shown by each memory type available in the bsp (board support package) used in the target e.g. RAM, flash, CCM etc.
label  | Appends an image header to the created binary file for the target named `input1`. Version number in the header is set to the value given as `[flag1]`. The manifest.json file in the directory with the binaries (project/<project-name>/bin/<target-name>) reflects the version number. A manifest.json file is created if none exists for the target. 
export |  Exports the configurations of the specified target `input1`. If -a or -export-all flag is used, then all targets are exported and printed out to standard out. You may redirect the output to a file. 
import | Import one or more target configuration from standard input or a file. Each target starts with `@target=<target-name>` followed by the attributes. The list of targets should end with `@endtargets`.
download | Downloads the binary executable `<target-name>.elf.bin` to the board.
debug    | Downloads the binary executable `<target-name>.elf.bin` to the board and starts up the openocd/gdb combination session. gdb takes over the terminal.


#### Command-specific flags

Sub-command  | Available flags | Explanation
-------------| ----------------|------------
build   | clean | All the binaries and object files for the specified target will be removed. The subdirectory named after the specified target within that project is removed.
build clean | all | All the binaries and object files for all targets are removed, and subdirectories of all targets for the project are removed. However, the entire repository is not emptied since any pkgs or projects that the specified target doesn't reference are not touched.
export  | -a, -export-all  | Export all targets. `input1` is not necessary when this flag is used.
import  | -a, -import-all  | Import all targets typed into standard input or redirected from a file. 

#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
set       | newt target set myblinky compiler=arm-none-eabi-m4 | Set the compiler for the 'myblinky' target to the gcc compiler for embedded ARM chips.
set       | newt target set myblinky compiler | Lists the valid values currently available to be assigned for target attribute (variable) 'compiler'. For example, arm-none-eabi-m0, arm-none-eabi-m4, sim. As Mynewt grows, the number of possible values will grow.
unset       | newt target unset myblinky compiler | Remove the setting for the compiler for the 'myblinky' target.
delete       | newt target delete myblinky | Delete the target description for the target named 'myblinky'. Note that it does not remove any binaries or clean out the directory for this target. 
create       | newt target create blink_f3disc | Create a new target description by the name 'blink_f3disc'. The architecture is 'sim' by default and can be changed using subcommand 'set' above.
show      | newt target show myblinky | Show the target attributes set for 'myblinky'
build       | newt target build blink_f3disc | Compile the source code for the target named blink_f3disc and generate binaries that can be loaded into the target hardware.
test | newt target test test_target pkg=libs/os | Tests the pkg named 'libs/os' against the target named 'test_target'
size     | newt target size -v boot_olimex | Displays the memory footprint in bytes for all object and linked files for the target named boot_olimex. The -v option shows all the steps of loading and inspecting the different pkgs required for the project on this target as well as the different memory locations available. The memory usage for each component is broken up into the different memory types used. An example output is shown for `newt target size boot_olimex` below.
label   | newt target label boot_olimex 2.0.1 | Appends an image header specifying the version number as 2.0.1 to the binary image file for target named boot_olimex. The version number in the manifest.json file for this target is also updated to 2.0.1.
export   | newt target export -a > my_exports.txt | Export all build targets from the current app, and redirect output to a file named 'my_exports.txt'.
export  | newt target export -export-all  | Export all build targets from the current app, and print them to standard output on the screen.
export  | newt target export my_target | Export only target named 'my_target' and print it to standard output on the screen.
import | newt target import ex_tgt_1 < exported_targets.txt | Imports the target configuration for 'ex_tgt_1' in 'exported_targets.txt'.
import | newt target import -a < in_targets.txt | Imports all the targets specified in the file named `in_targets.txt`. A sample file is shown after this table.
import | newt target import test3 | Awaits all the configuration variables for a target named 'test3'. This allows you to define all the attributes in one shot e.g. by cutting and pasting the contents of `in_targets.txt` file shown at the bottom of this page.  
size   | newt target size blink_nordic | Inspects and lists the RAM and Flash memory use by each component (object files and libraries) of the target.
download  | newt target -v -lVERBOSE download blinky | Downloads `blinky.elf.bin` to the hardware in verbose mode with logging turned on at VERBOSE level.
debug | newt target debug blinky  | Downloads `blinky.elf.bin` to the hardware, opens up a gdb session with `blinky.elf` in the terminal, and halts for further input in gdb.


#### Example output for `newt target size boot_olimex`:

```no-highlight

$ newt target size boot_olimex
Inspecting target boot_olimex (project = boot)
  FLASH     CCM     RAM 
     13       0       3 *fill*
    239       0       0 boot.o
    124       0       0 crt0.o
     84       0      40 crtbegin.o
      4       0       4 crtend.o
      8       0       0 crti.o
     16       0       0 crtn.o
   1396       0      50 libbaselibc.a
   2054       0    1104 libbootutil.a
     84       0       0 libcmsis-core.a
    266       0       4 libfs.a
     80       0       0 libg.a
   1452       0       0 libgcc.a
    940       0       8 libhal.a
  12130       0     538 libnffs.a
   1172    3072      68 libolimex_stm32-e407_devboard.a
   3654       0     645 libos.a
   1504       0      32 libstm32f4xx.a
```

#### Example content for `in_targets.txt` file used for importing targets `test3` and `test4`.  

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
