## Command Structure

Just like verbs are actions in a sentence and adverdbs modifiy verbs, so in *newt* tool, commands are actions and flags modify actions. A command can have subcommands, too. Arguments to commands and subcommands, with appropriate flags, will dictate the execution and result of a command. 

For instance, in the example below, the *newt* command has the subcommand `target set` in which the argument 'my_target1' is the target whose attribute, *arch*, is set to 'cortex_md.' 

```no-highlight
    newt target set my_target1 arch=cortex_m4
```

Global flags work uniformly across *newt* commands. Consider the flag `-v, --verbose,` It works both for command and subcommands, to generate verbose output. Likewise, the help flag `-h` or  `--help,`  to print helpful messsages.

A command may additionally take flags specific to it. For example, the `-n ` flag instructs `newt debug` not to start GDB from command line.

```no-highlight
    newt debug <target-name> -n
```
In addition to the [Newt Tool Manual](newt_intro.md) in docs, command-line help is available for each command (and subcommand), through the `-h` or `--help` options. 

```no-highlight
    newt target  --help
    Command for manipulating targets
    
    Usage:
      newt target [flags]
      newt target [command]
    
    Available Commands:
      config      View target system configuration
      copy        Copy target
      create      Create a target
      delete      Delete target
      dep         View target's dependency graph
      revdep      View target's reverse-dependency graph
      set         Set target configuration variable
      show        View target configuration variables
    
    Global Flags:
      -l, --loglevel string   Log level (default "WARN")
      -o, --outfile string    Filename to tee output to
      -q, --quiet             Be quiet; only display error output
      -s, --silent            Be silent; don't output anything
      -v, --verbose           Enable verbose output when executing commands
    
    Use "newt target [command] --help" for more information about a command.

```
