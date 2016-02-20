# Shell

The shell is the program which puts up a prompt for a command, processes commands, and returns output. Interacting with the console of a device is done using a shell program.


## Description

Shell processes console input one line at a time. Eggs can register handlers for their commands. Shell parses the input, matches it against the set of registered commands, and then calls the handler it finds.

A few commands are currently available in the shell - `tasks`, `log`, and `stat stat`. A $ prompt sign will be coming soon!

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

Replace this with the list of data structures used, why, any neat features

## List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in this OS feature are:

* [shell_cmd](shell_cmd.md)
* [shell_cmd_list_lock](shell_cmd_list_lock.md)
* [shell_cmd_list_unlock](shell_cmd_list_unlock.md)
* [shell_cmd_register](shell_cmd_register.md)
* [shell_console_rx_cb](shell_console_rx_cb.md)
* [shell_echo_cmd](shell_echo_cmd.md)
* [shell_help_cmd](shell_help_cmd.md)
* [shell_nlip_input_register](shell_nlip_input_register.md)
* [shell_nlip_mqueue_process](shell_nlip_mqueue_process.md)
* [shell_nlip_mtx](shell_nlip_mtx.md)
* [shell_nlip_output](shell_nlip_output.md)
* [shell_nlip_process](shell_nlip_process.md)
* [shell_os_mpool_display_cmd](shell_os_mpool_display_cmd.md)
* [shell_os_tasks_display_cmd](shell_os_tasks_display_cmd.md)
* [shell_process_command](shell_process_command.md)
* [shell_read_console](shell_read_console.md)
* [shell_task_func](shell_task_func.md)
* [shell_task_init](shell_task_init.md)



