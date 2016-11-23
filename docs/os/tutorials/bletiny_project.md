## Check stats on a BLE device

<br>

This tutorial explains how to run an example BLE app on a board and command it to scan and spew some stats. The stats will be seen over a serial port, not a BLE wireless connection.

<br>

### Pre-Requisites

* Ensure you have installed [newt](../../newt/install/newt_mac.md) and that the 
newt command is in your system path. 
* You must have Internet connectivity to fetch remote Mynewt components.
* You must [install the compiler tools](../get_started/native_tools.md) to 
support native compiling to build the project this tutorial creates.  
* You must install the [Segger JLINK package]( https://www.segger.com/jlink-software.html) to load your project on the board.
* You have a board with BLE radio that is supported by Mynewt. We will use an nRF52 Dev board in this tutorial.
* Cable to establish a serial USB connection between the board and the laptop

<br>

### Create a project

Use the Newt tool to create a new project directory containing a skeletal Mynewt framework. Change into the newly created directory.

```
$ newt new myapp1
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in myapp1...
Project myapp1 successfully created.
$ cd myapp1

$ newt install -v 
apache-mynewt-core
Downloading repository description for apache-mynewt-core... success!
...
apache-mynewt-core successfully installed version 0.7.9-none
```

<br>

### Create targets 

You will create two targets - one for the bootloader, the other for the application.

```
$ newt target create myble
Target targets/myble successfully created
$ newt target create nrf52_boot
Target targets/myble successfully created
$ newt target show
targets/my_blinky_sim
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/native
    build_profile=debug
targets/myble
targets/nrf52_boot
```

<br>

Define the targets further. Note that you are using the example app `bletiny` for the application target. Set the bsp 

**NOTE:** The preview version, nrf52pdk, is no longer supported. If you do not see PCA100040 on the top of your board, you have a preview version of the board and will need to upgrade your developer board before continuing.

<br>

```
$ newt target set myble bsp=@apache-mynewt-core/hw/bsp/nrf52dk
Target targets/myble successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set myble app=@apache-mynewt-core/apps/bletiny
Target targets/myble successfully set target.app to @apache-mynewt-core/apps/bletiny
$ newt target set myble build_profile=optimized
Target targets/myble successfully set target.build_profile to optimized
```

Use the same `newt target set` command to set the following definition for the bootloader target -- again, make sure you use the correct value for the bsp based on which version of the board you have..

```
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    build_profile=optimized
```

You should have the following targets by the end of this step.

```
$ newt target show
targets/my_blinky_sim
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/native
    build_profile=debug
targets/myble
    app=@apache-mynewt-core/apps/bletiny
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    build_profile=optimized
    cflags=-DSTATS_NAME_ENABLE 
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    build_profile=optimized
```

Since we're interested in seeing the stats, we'll need to enable the stats module for the target. By default, the stats module is not enabled, so we will have to override the default behavior.
To do this, you'll need to create a configuration file `syscfg.yml` in the app directory. from the target definition above, you can see that the app is in `apache-mynewt-core/apps/bletiny`
so that is where you'll put your configuration file. 

```
# Package: apps/bletiny

syscfg.vals:
    SHELL_TASK: 1
    STATS_NAMES: 1
    STATS_CLI: 1
```

The first configuration value turns on the Shell Task, and we'll need this to get to the shell. The next 2 enable the names for the various stats, and then turns on the stats CLI option.

### Build targets

Then build the two targets.

```
$ newt build nrf52_boot
<snip>
App successfully built: ./bin/nrf52_boot/apps/boot/boot.elf
$ newt build myble
Compiling hci_common.c
Compiling util.c
Archiving nimble.a
Compiling os.c
<snip>
```

<br>

### Create the app image

Generate a signed application image for the `myble` target. The version number is arbitrary.

```
$ newt create-image myble 1.0.0
App image succesfully generated: ./bin/makerbeacon/apps/bletiny/bletiny.img
Build manifest: ./bin/makerbeacon/apps/bletiny/manifest.json
```

<br>

### Load the image

Make sure the USB connector is in place and the power LED on the board is lit. Use the Power ON/OFF switch to reset the board after loading the image.

```
$ newt load nrf52_boot
$ newt load myble
```

<br>

### Establish serial connection

You will now look for some BLE related stats over a serial connection and see the radio is actually working. 
If you haven't done so already, make sure you're familiar with the [Serial Port Setup and Configuration](../get_started/serial_access.md)
section. 

<br>

You may use any terminal emulation program to communicate with the board. This tutorial shows a Minicom set up. 


```
$ minicom -D /dev/tty.usbserial-AJ03HAQQ
```

<br>

When the Minicom screen comes up, type in `?`

```hl_lines="9"
Welcome to minicom 2.7

OPTIONS: 
Compiled on Nov 24 2015, 16:14:21.
Port /dev/tty.usbserial-AJ03HAQQ, 09:57:17

Press Meta-Z for help on special keys

?
4754:Commands:
4754:     echo         ?    prompt     tasks  mempools      date
4756:        b
```

<br>

If you'd like a shell prompt, try the `prompt` command.
```hl_lines="1"
prompt
14025:Usage: prompt [set|show] [prompt_char]
prompt set >
15086:Prompt set to: >
15086:Usage: prompt [set|show] [prompt_char]
15087: >
```

You'll notice that there is an ever-increasing counter before the prompt (and before any output to the terminal).
This is just a counter kept by the MCU.

**Note**: If you want to have a shell prompt by default, simply add the line: `CONSOLE_PROMPT: 1` to your `syscfg.yml` file and it will be turned on by default.

<br>

Try the `tasks` command. 

```hl_lines="1"
27365: > tasks
Tasks:
28330:  idle (prio: 255, tid: 0, lcheck: 0, ncheck: 0, flags: 0x0, ssize: 64, susage: 34, cswcnt: 233, tot_run_time: 28330ms)
28333:  ble_ll (prio: 0, tid: 1, lcheck: 0, ncheck: 0, flags: 0x0, ssize: 80, susage: 60, cswcnt: 11, tot_run_time: 0ms)
28336:  shell (prio: 1, tid: 2, lcheck: 0, ncheck: 0, flags: 0x0, ssize: 512, susage: 115, cswcnt: 18, tot_run_time: 0ms)
28339:  bletiny (prio: 1, tid: 3, lcheck: 0, ncheck: 0, flags: 0x0, ssize: 512, susage: 138, cswcnt: 456, tot_run_time: 0ms)
28342: >
```

<br>

Try specifying a BLE related stat, for example `ble_ll`. You should see some HCI (Host Controller Interface) command counts. 

```hl_lines="1"
241133: > stat ble_ll
hci_cmds: 11
241888:hci_cmd_errs: 0
241888:hci_events_sent: 11
241890:bad_ll_state: 0
241890:bad_acl_hdr: 0
241891:no_bufs: 0
241891:rx_adv_pdu_crc_ok: 0
241892:rx_adv_pdu_crc_err: 0
241893:rx_adv_bytes_crc_ok: 0
241894:rx_adv_bytes_crc_err: 0
241895:rx_data_pdu_crc_ok: 0
241895:rx_data_pdu_crc_err: 0
<snip>
```

<br>

For a more exciting output, try scanning your surroundings for BLE adverstisements. The HCI command shown below specifies a scan duration in ms, sets discovery mode to general (as opposed to limited), the filter to no-whitelist, and type of scan to passive. You should see some scan data flying by!

```hl_lines="1"
139088: > b scan dur=10000 disc=gen filt=no_wl type=passive
...
146055:received advertisement; event_type=0 addr_type=1 addr=6b:aa:49:b7:46:e6 length_data=24 rssi=-42 data=0x02:0x01:0x1a:0x14:0xff:0x4c:0x00:0x01:0x00:0x00:0x00:0x00:0x04:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00 fields:
146061:    flags=0x1a
146062:    mfg_data=0x4c:0x00:0x01:0x00:0x00:0x00:0x00:0x04:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00:0x00
146065:
146065:received advertisement; event_type=0 addr_type=0 addr=ac:bc:32:ac:4f:e4 length_data=11 rssi=-36 data=0x02:0x01:0x06:0x07:0xff:0x4c:0x00:0x10:0x02:0x0b:0x00 fields:
146069:    flags=0x06
146070:    mfg_data=0x4c:0x00:0x10:0x02:0x0b:0x00
146071:
146072:scanning finished
...
<snip>
```

<br>

If you're still not seeing any output from the device, try running the debugger and see if you are seeing the program execute properly. 

<br>

```
$ newt debug myble
Debugging ./bin/myble/apps/bletiny/bletiny.elf
GNU gdb (GNU Tools for ARM Embedded Processors) 7.6.0.20140731-cvs
Copyright (C) 2013 Free Software Foundation, Inc.

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from ./bin/myble/apps/bletiny/bletiny.elf...done.
0x00002f08 in ?? ()
(gdb) monitor reset
Resetting target
(gdb) c
Continuing.
^C
Program received signal SIGTRAP, Trace/breakpoint trap.
os_tick_idle (ticks=1000) at hal_os_tick.c:117
117	    if (ticks > 0) {
(gdb) p g_os_time
$1 = 37991
(gdb) c
Continuing.
^C
Program received signal SIGTRAP, Trace/breakpoint trap.
os_tick_idle (ticks=1000) at hal_os_tick.c:117
117	    if (ticks > 0) {
(gdb) p g_os_time
$2 = 51888
(gdb) c
Continuing.
```

<br>

You should see the g_os_time advancing as above, as each os time tick is 1ms. If the system ticks aren't advancing, then nothing's actually running.