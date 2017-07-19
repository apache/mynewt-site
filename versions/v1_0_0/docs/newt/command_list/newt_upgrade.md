## <font color="#F2853F" style="font-size:24pt">newt upgrade </font>

Upgrade project dependencies.

#### Usage: 
```no-highlight
    newt upgrade [flags] 
```    
    
#### Flags:
```no-highlight 
    -f, --force   Force upgrade of the repositories to latest state in project.yml
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
#### Description
Upagrades your project and package dependencies. If you have changed the project.yml description for the project, you need to run this command to update all the package dependencies.  
