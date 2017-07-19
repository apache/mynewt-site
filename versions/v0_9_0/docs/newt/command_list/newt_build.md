## <font color="#F2853F" style="font-size:24pt">newt build </font>

Compiles, links, and builds one or more apps. 

#### Usage: 

```no-highlight
    newt build [flags] input1
```

where `input1` is the name of the target to build.

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


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
build       | newt build <br> `input1`  | Builds the source code into an image that can be loaded on the hardware (`bsp`) associated with the target named `input1` to run the application enabled by the `app` setting associated with that target. It creates 'bin/' directory and 'bin/<input1>/apps/<app>' subdirectory inside the base directory for the app, compiles and generates binaries and executables, and places them in that subdirectory. 
      | newt build <br> my_blinky_sim | For example, if `app` was set to `apps/blinky` for the target "my_blinky_sim", you will find the generated .elf, .a, and .lst files in bin/my_blinky_sim/apps/blinky directory created under the base directory for the app created using `newt new` at the start of the project. 
build       |  newt build my_blinky_sim myble | builds the apps defined for both the targets "my_blinky_sim" and "myble".
