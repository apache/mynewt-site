## <font color="#F2853F" style="font-size:24pt">newt help </font>

Displays the help text for the newt command line tool:

```no-highlight

Newt allows you to create your own embedded application based on the Mynewt 
operating system. Newt provides both build and package management in a single 
tool, which allows you to compose an embedded application, and set of 
projects, and then build the necessary artifacts from those projects. For more 
information on the Mynewt operating system, please visit 
https://mynewt.apache.org/. 
```

#### Usage:
```no-highlight
    newt help [input1]
```    
#### Flags:

```no-highlight

    -h, --help=false: help for newt
    -o, --outfile string    Filename to tee output to
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```

#### Available Commands: 

```no-highlight
    version      Display the Newt version number.
    install      Install project dependencies
    upgrade      Upgrade project dependencies
    new          Create a new project
    info         Show project info
    target       Command for manipulating targets
    build        Builds one or more targets.
    clean        Deletes build artifacts for one or more targets.
    test         Executes unit tests for one or more packages
    load         Load built target to board
    debug        Open debugger session to target
    size         Size of target components
    create-image Add image header to target binary
    run          build/create-image/download/debug <target>
```

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
help       | newt help target | Displays the help text for the newt command 'target'
help       | newt help   | Displays the help text for newt tool
    
    

