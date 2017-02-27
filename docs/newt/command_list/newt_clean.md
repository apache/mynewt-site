## <font color="#F2853F" style="font-size:24pt">newt clean </font>

Delete build artifacts for one or more targets. 

#### Usage: 

```no-highlight
    newt clean <target-name> [target-name...] | all [flags]
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

Deletes all the build artifacts generated for  the `target-name` target. It does not delete the target definition.  You can specify a list of targets, separated by a space, to delete the artifacts for multiple targets, or specify `all` to delete the artifacts for all targets.

#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
             | newt clean myble | Deletes the 'bin/targets/myble' directory where all the build artifacts generated from the `myble` target build are stored.
             | newt clean my_blinky_sim myble | Deletes the 'bin/targets/my_blinky_sim' and the 'bin/targets/myble' directories where all the artifacts generated from the `my_blinky_sim` and `myble` target builds are stored.
             | newt clean all | Removes the artifacts for all target builds. Deletes the top level 'bin' directory. 
