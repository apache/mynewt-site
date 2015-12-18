## Command Structure

In the newt tool, commands represent actions and flags are modifiers for those actions. A command can have children commands which are also simply referred to as commands. One or more arguments may need to be provided to a command to execute it correctly. 

In the example below, the `newt` command has the child command `target set`. The first argument 'my_target1' is the name of the target whose attributes are being set. The second argument 'arch=cortex_m4' specifies the value to set the attribute (variable) 'arch' to, which in this case is 'cortex_m4'. 

    newt target set my_target1 arch=cortex_m4

Global flags work on all newt commands in the same way. An example is the flag `-v, --verbose` to ask for a verbose output while executing a command. The help flag `-h` or  `--help` is available on all commands but provides command specific output, of course. These flags may be specified in either a long or a short form. 

A command may additionally take flags specific to it. For example, the `-b ` flag may be used with `newt egg install` to tell it which branch to install the egg from. 

    newt egg install -b <branchname> <eggname>

In addition to the newt tool [reference](../newt/newt_tool_reference.md) in this documentation set, command-line help is available for each command (and child command). Simply use the flag `-h` or `--help` as shown below:

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

