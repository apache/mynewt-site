## <font color="#F2853F" style="font-size:24pt">newt app </font>


#### Usage: 
```no-highlight
    newt app [command][flags] input1 input2...
```
#### Available commands: 
```no-highlight
    generate-pkg-list Generate a pkg-list file from the pkgs in the current directory
    add-pkg-list      Add a remote pkg-list, and put it in the current app
    list-pkg-listes   List the pkg-listes installed in the current app
    show-pkg-list     Show an individual pkg-list in the current app
```

#### Flags:
```no-highlight
    -h, --help=false: help for app
```
#### Global Flags:
```no-highlight
    -h, --help=false: help for newt
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```
#### Description

Sub-command  | Explanation
-------------| ------------------------
generate-pkg-list | Takes a snapshot of the pkgs in the current local directory and combines them into a pkg-list by the name of `input1` and with the url of `input2` and generates a standard output of the pkg-list details that can be redirected to a `.yml` pkg-list file. Typically the pkg-list file name is chosen to match the pkg-list name which means the standard output should be directed to a pkg-list file named `input1.yml`
add-pkg-list   | Downloads the pkg-list of the name `input1` from the master branch of the github repository `input2` into the current app. A file named `input1.yml` file is added in the `.app/pkg-lists` subdirectory inside the current local app. The `.app/` directory structure is created automatically if it does not exist.
list-pkg-lists | Lists all the pkg-lists present in the current app, including pkg-lists that may have been added from other apps on github. The output shows all the remote pkg-list names and the total pkgshells in each of the pkg-lists.
show-pkg-list | Shows information about the pkg-list that has the name given in the `input1` argument. Output includes the pkg-list name, url, and all the constituent pkgs with their version numbers.

#### Command-specific flags

Sub-command  | Available flags | Explanation
-------------| ----------------|------------
add-pkg-list   | -b, --branch="<branch-name>" | Fetches the pkg-list file with name `input1` from the specified branch at `input1` url of the github repository. All subsequent pkg installations will be done from that branch.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
generate-pkg-list | newt app generate-pkg-list mypkg-list https://github.com/apache/incubator-mynewt-larva > mypkg-list.yml| Takes a snapshot of the pkgs in the current app to form a pkg-list named mypkg-list with the url https://github.com/apache/incubator-mynewt-larva. The output is written to a file named `mypkg-list.yml` and describes the properties and contents of the pkg-list (name, url, pkgs).
add-pkg-list   | newt app add-pkg-list larva https://github.com/apache/incubator-mynewt-larva | Adds the remote pkg-list named larva at https://github.com/apache/incubator-mynewt-larva to the local app. 
list-pkg-lists | newt app list-pkg-lists | Shows all the remote pkg-list description files that been downloaded into the current app. Output includes each list with name and summary of included packages e.g. `Remote package list larva@master (num_pkgs: 44)`
show-pkg-list   | newt app show-pkg-list larva | Outputs the details of the pkg-list named larva such as the github url where the remote sits, the constituent pkgs and their versions


