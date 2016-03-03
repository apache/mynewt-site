# Shell

The shell is package sitting on top of console, handling 2 jobs; processing console input and implementing newtmgr line protocol over serial line. Shell runs on it's own task.

## Description

First job is directing incoming commands to other subsystems. It parses the incoming character string, and splits it into tokens. Then shell looks for the subsystem to handle this command based on the first token of input.

Subsystems register their command handlers using *shell_cmd_register()*. When shell calls the command handler, it passes the other tokens as arguments.

A few commands are currently available in the shell - `tasks`, `log`, and `stat stat`. A $ prompt sign will be coming soon!

Second job is doing framing, encoding and decoding newtmgr protocol when it's carried over the console. Protocol handler (libs/newtmgr) registers itself using *shell_nlip_input_register()*, and shell calls the registered handler for every frame. Outgoing frames for the protocol are sent using *shell_nlip_output()*.

Create a sim target to check out these commands available in shell.

```no-highlight
user@~/dev/larva$ newt target create blinky_sim
Creating target blinky_sim
Target blinky_sim successfully created!
user@~/dev/larva$ newt target set blinky_sim name=blinky_sim
Target blinky_sim successfully set name to blinky_sim
user@~/dev/larva$ newt target set blinky_sim arch=sim
Target blinky_sim successfully set arch to sim
user@~/dev/larva$ newt target set blinky_sim project=blinky
Target blinky_sim successfully set project to blinky
user@~/dev/larva$ newt target set blinky_sim bsp=hw/bsp/native
Target blinky_sim successfully set bsp to hw/bsp/native
user@~/dev/larva$ newt target set blinky_sim compiler_def=debug
Target blinky_sim successfully set compiler_def to debug
user@~/dev/larva$ newt target set blinky_sim compiler=sim
Target blinky_sim successfully set compiler to sim
user@~/dev/larva$ newt target show
blinky_sim
	arch: sim
	bsp: hw/bsp/native
	compiler: sim
	compiler_def: debug
	name: blinky_sim
	project: blinky
user@~/dev/larva$ newt target build blinky_sim
Building target blinky_sim (project = blinky)
Compiling case.c
Compiling suite.c
Compiling testutil.c
..
..
Building project blinky
Linking blinky.elf
Successfully run!

user@~/dev/larva$ ./project/blinky/bin/blinky_sim/blinky.elf
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

stat stat
229881:s0: 1

```


## Data structures

This data structure is used in holding information about registered command handlers.

```no-highlight
struct shell_cmd {
    char *sc_cmd;
    shell_cmd_func_t sc_cmd_func;
    STAILQ_ENTRY(shell_cmd) sc_next;
};
```

| Element | Description |
|---------|-------------|
| sc_cmd | Character string of the command |
| sc_cmd_func | Pointer to the command handler |
| sc_next | Bookkeeping linkage internal for shell |

## List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in this OS feature are:

* [shell_task_init](shell_task_init.md)
* [shell_cmd_register](shell_cmd_register.md)
* [shell_nlip_input_register](shell_nlip_input_register.md)
* [shell_nlip_output](shell_nlip_output.md)
