## <font color="#F2853F" style="font-size:24pt">newt new </font>

Create a new application, specified by <app-name>, from a given skeleton. Currently, the default skeleton is the [blinky repository](https://git-wip-us.apache.org/repos/asf/incubator-mynewt-blinky.git) in Apache Mynewt (or [https://github.com/apache/incubator-mynewt-blinky](https://github.com/apache/incubator-mynewt-blinky) on its github mirror.)


#### Usage: 
```no-highlight
    newt new [flags] <app-name>
```

#### Flags:
```no-highlight
    -h, --help=false: help for new
```
#### Global Flags:
```no-highlight
    -h, --help=false: help for newt
    -o, --outfile string    Filename to tee output to
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
newt new       | newt new test_project | Creates a new app named "test_project " using the default skeleton from the `apache/incubator-mynewt-blinky` repo.


