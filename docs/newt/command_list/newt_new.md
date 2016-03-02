## <font color="#F2853F" style="font-size:24pt">newt new </font>

Create a new application, specified by <app-name>, from a given skeleton. If the optional <app-url> parameter is specified, then download the skeleton of the application from 
that URL instead of using the default, and create a new app directory by the name of <app-name>. Currently, the default skeleton is the [tadpole repository](https://git-wip-us.apache.org/repos/asf/incubator-mynewt-tadpole.git) in Apache Mynewt. 


#### Usage: 
```no-highlight
    newt new [flags] <app-name> [, <app-url>]
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

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
newt new       | newt new test_project | Creates a new app named "test_project " using the default skeleton
       | newt new myapp <app-url> | Creates a new app named "myapp" using the skeleton at the <app-url> specified


