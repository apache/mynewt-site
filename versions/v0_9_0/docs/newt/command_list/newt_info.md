## <font color="#F2853F" style="font-size:24pt">newt info </font>

Shows information about the current project.

#### Usage: 

```no-highlight
    newt info [flags]
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
info         | Displays the repositories in the current project (the local as well as all the external repositories fetched). Also displays the packages in the local repository.

