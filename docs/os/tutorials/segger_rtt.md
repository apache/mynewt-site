## SEGGER RTT Console

<br>

### Objective

Sometimes you dont have UART on your board, or you want to use it for something else while still having newt logs/shell capability. With [SEGGER's RTT](https://www.segger.com/jlink-rtt.html) capability you can swap UART for RTT, which is a very high-speed memory-mapped I/O.

<br>

### Hardware needed

You'll need a SEGGER J-Link programmer in order to use this advanced functionality. You might have an external J-Link programmer you're already using, or maybe your board has a dedicated J-Link onboard as some development kits do. Another possibilty is J-Link OB firmware available for some devices like the micro:bit. 

### Setup the target

We'll assume you have an existing project with some kind of console/shell like [Check stats on a BLE device](bletiny_project.md) that we're switching over to RTT from UART. We can disable uart and enable rtt with the newt target command:
```
newt target amend myble syscfg=CONSOLE_UART=0
newt target amend myble syscfg=CONSOLE_RTT=1
```

<br>

### Run the target executables 
Now 'run' the newt target as you'll need an active debugger process to attach to:

```
$ newt run myble 0
App image succesfully generated: ~/Downloads/myapp1/bin/targets/myble/app/apps/bletiny/bletiny.img
Loading app image into slot 1
[~Downloads/myapp1/repos/apache-mynewt-core/hw/bsp/nrf52-thingy/nrf52-thingy_debug.sh ~/Downloads/myapp1/repos/apache-mynewt-core/hw/bsp/nrf52-thingy ~/Downloads/myapp1/bin/targets/myble/app/apps/bletiny/bletiny]
Debugging ~/Downloads/myapp1/bin/targets/myble/app/apps/bletiny/bletiny.elf
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ~/Downloads/myapp1/bin/targets/myble/app/apps/bletiny/bletiny.elf...done.
0x000000d8 in ?? ()
Resetting target
0x000000dc in ?? ()
(gdb) 
```

<br>

### Connect to console

In a seperate terminal window ```telnet localhost 19021``` and when you continue your gdb session you should see your output. If you're not familiar with telnet, when you're ready to exit you may by using the hotkey ctrl+] then typing quit

```
$ telnet localhost 19021
Trying ::1...
telnet: connect to address ::1: Connection refused
Trying fe80::1...
telnet: connect to address fe80::1: Connection refused
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
SEGGER J-Link V6.14e - Real time terminal output
SEGGER J-Link EDU V8.0, SN=268006294
Process: JLinkGDBServer
```

Then you can interact with the device:
```
stat
stat
000262 Must specify a statistic name to dump, possible names are:
000262 	stat
000262 	ble_l2cap
000262 	ble_att
000262 	ble_gap
000262 	ble_gattc
000262 	ble_gatts
000262 	ble_hs
000262 	ble_ll_conn
000262 	ble_ll
000262 	ble_phy
000262 compat> 
```
