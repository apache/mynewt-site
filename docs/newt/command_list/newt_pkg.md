## <font color="#F2853F" style="font-size:24pt">newt pkg </font>

Provides sub-commands to search, display and install packages in your current application or workspace.

#### Usage: 
```no-highlight
    newt pkg [command][flag] input1 input2
```    
    
#### Available Commands: 
```no-highlight 
    list        List pkgs in the current app
    checkdeps   Check pkg dependencies
    hunt        Search for pkg from pkg-lists
    show        Show the contents of a pkg.
    install     Install a pkg
    remove      Remove a pkg
```
#### Flags:
```no-highlight 
    -h, --help=false: help for pkg

#### Global Flags:

    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```
#### Description

Sub-command  | Explanation
-------------| ------------------------
list         | List all the pkgs in the current app. The output shows the name, version, path, and any additional attributes of each pkg in the app such as dependencies, capabilities, and linker scripts. The newt command gets the attributes of each pkg from the corresponsing pkg.yml description file.
checkdeps    | Resolve all dependencies in the local app. This command goes through all pkgs currently installed, checks their dependencies, and prints any unresolved dependencies between pkgs.
search       | Searches for a pkg, specified by `input1`. The local app, along with all remote apps (pkg-lists) are searched. All matched pkgs are shown along with the pkg-list informaton. Installed pkgs are called out as such. The command can be invoked from anywhere in the app.
show     |  Show the contents of the pkg named `input2` found in the pkg-list named `input1`. The pkg-list name is optional; if only the pkg name is given as the argument it is resolved using all the pkg-lists installed in the current app. If the pkg is present in multiple pkg-lists it will list all of them along with the pkg-list information for each.
install  |  Install the pkg specified by `input2` from the pkg-list named `input1`. The command downloads the pkg from the github repository using the URL in the pkg-list description file (typically donwloaded as 'input1@<branch-name>.yml' in .app/pkg-lists). It also downloads all the dependencies (constituent pkgs) as decribed in the pkg's description file ('pkg.yml') and installs all of them. The pkg-list name is optional. If only the pkg name is given as the argument, the command looks for the pkg name in all the pkg-lists in the local app and installs accordingly. A pkg is installed by this command only if it has not already been installed. 
remove   |  Remove a pkg named `input2` from pkg-list `input1`, if pkg-list is specified. Otherwise only one input required - that of the name of the pkg to be removed from the local app.




#### Command-specific flags

Sub-command  | Available flags | Explanation
-------------| ----------------|------------
install   | -b, --branch="<branch-name>" | Installs the pkgs from the branch name or tag of the pkg-list specified

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
list       | newt pkg list | CList all of the pkgs in the current app and the details of the pkgs.
checkdeps       | newt pkg checkdeps | Checks all the dependencies between pkgs in the app. Lists any unresolved dependencies.
hunt | newt pkg hunt blinky| Hunts for the pkg named 'blinky'. The command can be invoked from anywhere in the app. Results show if the pkg is installed and which pkg-list, if any, has the pkg.
show   | newt pkg show larva libs/os | Show the contents of the pkg named 'libs/os' in the pkg-list named larva. The contents are essentially derived from the pkg's 'pkg.yml' file. 
install | newt pkg install hw/bsp/stm32f3discovery | Downloads and installs the pkg named "stm32f3discovery" (specified with its full path name inside the remote app) along with all its dependencies from the remote app on github. Since no pkg-list is specified, the URL for the remote app in the pkg-list description file found in the local app (in .app/pkg-lists for the project) is used. 
remove   | newt pkg remove larva blinky| Removes the pkg named blinky only from the pkg-list named larva
remove   | newt pkg remove blinky| Removes the pkg named blinky from the local app

