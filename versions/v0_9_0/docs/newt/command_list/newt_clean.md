## <font color="#F2853F" style="font-size:24pt">newt clean </font>

Deletes application build artifacts for a specified target

#### Usage: 

```no-highlight
    newt clean [flags] input1
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
clean        | Deletes all the build artifacts generated for target specified by `input1`. It does not delete the target definition.


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
clean       | newt clean myble2 | Removes all the files generated while building the target `myble2` and placed in the `bin/myble2` directory created during the build process.
