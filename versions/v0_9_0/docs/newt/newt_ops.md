## Command Structure

Just like verbs are actions in a sentence and adverdbs modifiy verbs, so in *newt* tool, commands are actions and flags modify actions. A command can have subcommands, too. Arguments to commands and subcommands, with appropriate flags, will dictate the execution and result of a command. 

For instance, in the example below, the *newt* command has the subcommand `target set` in which the argument 'my_target1' is the target whose attribute, *arch*, is set to 'cortex_md.' 

```no-highlight
    newt target set my_target1 arch=cortex_m4
```

Global flags work uniformly across *newt* commands. Consider the flag `-v, --verbose,` It works both for command and subcommands, to generate verbose output. Likewise, the help flag `-h` or  `--help,`  to print helpful messsages.

A command may additionally take flags specific to it. For example, the `-b ` flag instructs `newt pkg install` to install the pkg from a git `branch.`

```no-highlight
    newt pkg install -b <branchname> <eggname>
```
In addition to the [Newt Tool Manual](newt_intro.md) in docs, command-line help is available for each command (and subcommand), through the `-h` or `--help` options. 

```no-highlight
    $ newt target export --help
    Export build targets from the current nest, and print them to 
    standard output. If the -a (or -export-all) option is specified, 
    then all targets will be exported. Otherwise, <target-name> 
    must be specified, and only that target will be exported.

    Usage: 
      newt target export [flags]

    Examples:
      newt target export [-a -export-all] [<target-name>]
      newt target export -a > my_exports.txt
      newt target export my_target > my_target_export.txt

    Flags:
      -a, --export-all=false: If present, export all targets
      -h, --help=false: help for export

    Global Flags:
      -l, --loglevel="WARN": Log level, defaults to WARN.
      -q, --quiet=false: Be quiet; only display error output.
      -s, --silent=false: Be silent; don't output anything.
      -v, --verbose=false: Enable verbose output when executing commands.
```
