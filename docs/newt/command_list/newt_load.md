## <font color="#F2853F" style="font-size:24pt">newt load </font>

Load application image onto the board for a target. 

#### Usage: 

```no-highlight
    newt load <target-name> [flags]
```


#### Flags:

```no-highlight
    --extrajtagcmd string   Extra commands to send to JTAG software

```

### Global Flags:
```no-highlight
    -h, --help              Help for newt commands
    -j, --jobs int          Number of concurrent build jobs (default 8)
    -l, --loglevel string   Log level (default "WARN")
    -o, --outfile string    Filename to tee output to
    -q, --quiet             Be quiet; only display error output
    -s, --silent            Be silent; don't output anything
    -v, --verbose           Enable verbose output when executing commands
```
#### Description

Uses download scripts to automatically load, onto the connected board, the image built for the app defined by the `target-name` target If the wrong board is connected or the target definition is incorrect (i.e. the wrong values are given for bsp or app), the command will fail with error messages such as `Can not connect to J-Link via USB` or `Unspecified error -1`. 
