# Shell

The shell runs above the console and provides two functionalities:

* Processes console input. 
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

Create a sim target to check out these commands available in shell.

```no-highlight
user@~/dev$ newt target create blinky_sim
Creating target blinky_sim
Target blinky_sim successfully created!
user@~/dev$ newt target set blinky_sim name=blinky_sim
Target blinky_sim successfully set name to blinky_sim
user@~/dev$ newt target set blinky_sim arch=sim
Target blinky_sim successfully set arch to sim
user@~/dev$ newt target set blinky_sim project=blinky
Target blinky_sim successfully set project to blinky
user@~/dev$ newt target set blinky_sim bsp=hw/bsp/native
Target blinky_sim successfully set bsp to hw/bsp/native
user@~/dev$ newt target set blinky_sim compiler_def=debug
Target blinky_sim successfully set compiler_def to debug
user@~/dev$ newt target set blinky_sim compiler=sim
Target blinky_sim successfully set compiler to sim
user@~/dev$ newt target show
blinky_sim
	arch: sim
	bsp: hw/bsp/native
	compiler: sim
	compiler_def: debug
	name: blinky_sim
	project: blinky
user@~/dev$ newt target build blinky_sim
Building target blinky_sim (project = blinky)
Compiling case.c
Compiling suite.c
Compiling testutil.c
..
..
Building project blinky
Linking blinky.elf
Successfully run!

user@~/dev$ ./project/blinky/bin/blinky_sim/blinky.elf
uart0 at /dev/ttys005

```

Open up a new terminal to run minicom, a text-based serial port control and terminal emulation program. Set device name to the serial port of the target. 

```no-highlight
user@~$ minicom -D /dev/ttys005
Welcome to minicom 2.7

OPTIONS: 
Compiled on Nov 24 2015, 16:14:21.
Port /dev/ttys005, 11:32:17

Press Meta-Z for help on special keys

log 
174578:[0] bla
174578:[0] bab

tasks
217809:6 tasks: 
217809:  shell (prio: 3, nw: 0, flags: 0x0, ssize: 0, cswcnt: 59, tot_run_time: 0ms)
217840:  idle (prio: 255, nw: 0, flags: 0x0, ssize: 0, cswcnt: 18763, tot_run_time: 217809ms)
217878:  uart_poller (prio: 0, nw: 217819, flags: 0x0, ssize: 0, cswcnt: 18667, tot_run_time: 0ms)
217923:  task1 (prio: 1, nw: 218710, flags: 0x0, ssize: 0, cswcnt: 218, tot_run_time: 0ms)
217953:  os_sanity (prio: 254, nw: 218710, flags: 0x0, ssize: 0, cswcnt: 218, tot_run_time: 0ms)
218010:  task2 (prio: 2, nw: 217709, flags: 0x3, ssize: 0, cswcnt: 218, tot_run_time: 0ms)


prompt
Usage: prompt [set|show] [prompt_char]
prompt set >
Prompt set to: >
229370: >

```


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

