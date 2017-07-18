## <font color="#F2853F" style="font-size:24pt">newt upgrade </font>

Upgrade project dependencies

#### Usage: 
```no-highlight
    newt pkg [command][flag] input1 input2
```    
    
#### Flags:
```no-highlight 
    -f, --force   Force upgrade of the repositories to latest state in project.yml

#### Global Flags:

    -l, --loglevel="WARN": Log level, defaults to WARN.
    -o, --outfile string    Filename to tee log output to
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```
#### Description

Sub-command  | Explanation
-------------| ------------------------
upgrade      | If you have changed the project.yml description for the project, you need to run this command to update all the package dependencies.  