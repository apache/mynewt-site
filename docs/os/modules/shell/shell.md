# Shell

The shell runs above the console and provides two functionalities:

* Processes console input. See the [Enabling the Console and Shell Tutorial](/os/tutorials/add_shell.md) for an example of the shell.
* Implements the [newtmgr](../../../newtmgr/overview.md) line protocol over serial transport. 

The `sys/shell` package implements the shell.  The shell uses the OS default event queue 
for shell events and runs in the context of the main task. An application can, optionally, 
specify a dedicated event queue for the shell to use.

###Description

* The shell's first job is to direct incoming commands to other subsystems. It parses the incoming character string 
into tokens and uses the first token to determine the subsystem command handler to call to process the command.

    * Subsystems register their command handlers using the `shell_cmd_register()` 
      function.  When shell calls the command handler, it passes the other tokens as arguments.

    * A few commands are currently available in the shell - `tasks`, `log`, `echo`, `date` and `prompt`.

* The shell's second job is to handle packet framing, encoding, and decoding of newtmgr protocol messages that are
sent over the console.  The Newtmgr serial transport package (`mgmt/newtmgr/transport/newtmgr_shell`) 
calls the `shell_nlip_input_register()` function to register a handler that the shell calls when it 
receives newtmgr request messages.

<br>

###Data structures

This data structure is used in holding information about registered command handlers.

```c
struct shell_cmd {
    char *sc_cmd;
    shell_cmd_func_t sc_cmd_func;
    STAILQ_ENTRY(shell_cmd) sc_next;
};
```

| Element | Description |
|---------|-------------|
| `sc_cmd` | Character string of the command |
| `sc_cmd_func` | Pointer to the command handler |
| `sc_next` | Bookkeeping linkage internal for shell |

###List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in this OS feature are:

| Function | Description |
|---------|-------------|
| [shell_cmd_register](shell_cmd_register.md) | Registers a handler for incoming console commands. |
| [shell_nlip_input_register](shell_nlip_input_register.md) | Registers a handler for incoming newtmgr messages. |
| [shell_nlip_output](shell_nlip_output.md) | Queue outgoing newtmgr message for transmission. |
| [shell_evq_set](shell_evq_set.md) | Specifies a dedicated event queue for shell events. |

