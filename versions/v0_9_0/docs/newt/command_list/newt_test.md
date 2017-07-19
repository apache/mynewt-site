## <font color="#F2853F" style="font-size:24pt">newt test </font>

Executes unit tests for one or more packages 

#### Usage: 

```no-highlight
    newt test [flags] input1 [input2] ...
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
test   | Test a pkg named `input1`. You may specify multiple packages separated by space in the same command. 


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
test | newt test targets/myble2 | Tests the pkg named 'targets/myble2' 
    | newt test @apache-mynewt-core/libs/os | Tests the libs/os pkg in the repo named apache-mynewt-core
    | newt test libs/os libs/json | Tests the `libs/os` and `libs/json packages` in the current repo. Should indicate at the end of the output: <br> `Passed tests: [libs/os libs/json]` <br>  `All tests passed`


    


