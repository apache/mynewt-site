## <font color="#F2853F" style="font-size:24pt">newt load </font>

Load app image to specified target. 

#### Usage: 

```no-highlight
    newt load <target-name> [flags]
```

#### Flags:
```no-highlight
    -h, --help=false: help for target
```
#### Global Flags:
```no-highlight
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -o, --outfile string    Filename to tee output to
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```
#### Description

Sub-command  | Explanation
-------------| ------------------------
load         |  Uses download scripts to automatically load, onto the connected board, the image built for the app defined in the target specified by <target-name>. <br> <br> If the wrong board is connected, or the target definition is wrong (i.e. the wrong values are given for bsp or app), the command will fail with error messages such as `Can not connect to J-Link via USB` or `Unspecified error -1`. 