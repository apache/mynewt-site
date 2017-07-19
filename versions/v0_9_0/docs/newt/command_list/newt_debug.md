## <font color="#F2853F" style="font-size:24pt">newt debug </font>

Opens debugger session for specified target. 

#### Usage: 

```no-highlight
    newt debug <target-name> [flag]
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
debug         | Opens the appropriate debugging session for the image built for the named target.


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
debug       | newt debug myble2  | Opens J-Link connection and starts a GNU gdb session to debug bin/myble2/apps/bletiny/bletiny.elf when the target is as follows: <br> <br> targets/myble2 <br> app=@apache-mynewt-core/apps/bletiny <br> bsp=@apache-mynewt-core/hw/bsp/nrf52pdk <br> build_profile=optimized <br> cflags=-DSTATS_NAME_ENABLE 