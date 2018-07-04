## <font color="#F2853F" style="font-size:24pt">newt new </font>

Create a new project from a skeleton. Currently, the default skeleton is the [blinky repository](https://github.com/apache/mynewt-blinky).


#### Usage: 
```no-highlight
    newt new <project-name> [flags]
```

#### Global Flags:
```no-highlight
    -h, --help              Help for newt commands
    -j, --jobs int          Number of concurrent build jobs (default 8)
    -l, --loglevel string   Log level (default "WARN")
    -o, --outfile string    Filename to tee output to
    -q, --quiet             Be quiet; only display error output
    -s, --silent            Be silent; don't output anything
    -v, --verbose           Enable verbose output when executing commands
```
### Description
Creates a new project named `project-name` from the default skeleton [blinky repository](https://github.com/apache/mynewt-blinky).


#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newt new test_project | Creates a new project named `test_project` using the default skeleton from the `apache/mynewt-blinky` repository.

