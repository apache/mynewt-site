## <font color="#F2853F" style="font-size:24pt">newt install </font>

Install project dependencies. 

#### Usage: 
```no-highlight
    newt install [flags]
```

#### Flags:
```no-highlight
    -f, --force   Force install of the repositories in project, regardless of what exists in repos directory
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
#### Description

Sub-command  | Explanation
-------------| ------------------------
install | Downloads description of all the repositories specified in the project.yml file of the current project directory. Installs all the correct versions of all the packages dictated by the project dependencies. <br> <br> Always run the command from within the project directory (i.e. remember to `cd` into the app directory after creating a new app using `newt new`) before running `newt install`.

