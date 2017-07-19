## Check stats for a BLE Application  the NRF52 Board

<br>

This tutorial explains how to run an example BLE app on a board and command it to scan and spew some stats. The stats will be seen over a serial port, not a BLE wireless connection.

<br>

### Prerequisites

Ensure that you have met the following prerequisites before continuing with this tutorial:

* Have Internet connectivity to fetch remote Mynewt components.
* Have a board with BLE radio that is supported by Mynewt. We will use an nRF52 Dev board in this tutorial.
* Have a cable to establish a serial USB connection between the board and the laptop
* Install the newt tool and toolchains (See [Basic Setup](/os/get_started/get_started.md)).
* Install the [Segger JLINK package]( https://www.segger.com/jlink-software.html) to load your project on the board.

<br>

### Create a project

Use the newt tool to create a new project directory containing a skeletal Mynewt framework. Change into the newly created directory.

```no-highlight
$ newt new myproj 
Downloading project skeleton from apache/mynewt-blinky...
Installing skeleton in myproj...
Project myproj successfully created.
$ cd myproj

$ newt install 
```

<br>

### Create targets 

You will create two targets - one for the bootloader, the other for the application.

```no-highlight
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

Define the targets further. Note that you are using the example app `bletiny` for the application target. Set the bsp correctly (nrf52pdk or nrf52dk depending on whether the board is the preview kit or the dev kit, respectively. Look on the top of your board, if you see PCA100040, use the nrf52dk version, otherwide use the nrf52pdk version). 

```no-highlight
$ newt target set myble bsp=@apache-mynewt-core/hw/bsp/nrf52dk
Target targets/myble successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set myble app=@apache-mynewt-core/apps/bletiny
Target targets/myble successfully set target.app to @apache-mynewt-core/apps/bletiny
$ newt target set myble build_profile=optimized
Target targets/myble successfully set target.build_profile to optimized
$ newt target set myble cflags=-DSTATS_NAME_ENABLE
Target targets/myble successfully set pkg.cflags to DSTATS_NAME_ENABLE
```

Use the same `newt target set` command to set the following definition for the bootloader target -- again, make sure you use the correct value for the bsp based on which version of the board you have..

```no-highlight
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
    build_profile=optimized
```

You should have the following targets by the end of this step.

```no-highlight
$ newt target show
targets/my_blinky_sim
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/native
    build_profile=debug
targets/myble
    app=@apache-mynewt-core/apps/bletiny
    bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
    build_profile=optimized
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
    build_profile=optimized
```

Since we're interested in seeing the stats, we'll need to enable the stats module for the target. By default, the stats module is not enabled, so we will have to override the default behavior.
To do this, you'll need to create a configuration file `syscfg.yml` in the app directory. from the target definition above, you can see that the app is in `apache-mynewt-core/apps/bletiny`
so that is where you'll put your configuration file. 

```no-highlight
# Package: apps/bletiny

syscfg.vals:
    SHELL_TASK: 1
    STATS_NAMES: 1
    STATS_CLI: 1
```

The first configuration value turns on the Shell Task, and we'll need this to get to the shell. The next 2 enable the names for the various stats, and then turns on the stats CLI option.

### Build targets

Then build the two targets.

Run the `newt build nrf52_boot` command to build the bootloader:

```no-highlight
Building target targets/nrf52_boot
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
Compiling repos/apache-mynewt-core/apps/boot/src/boot.c

Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/myproj/bin/targets/nrf52_boot/app/apps/boot/boot.elf
Target successfully built: targets/nrf52_boot
```
<br>
Run the `newt build myble` command to build the bletiny application:
```no-highlight
 newt build myble
Building target targets/myble
Compiling repos/apache-mynewt-core/encoding/base64/src/base64.c
Compiling repos/apache-mynewt-core/encoding/base64/src/hex.c
Compiling repos/apache-mynewt-core/hw/bsp/nrf52dk/src/hal_bsp.c
Compiling repos/apache-mynewt-core/apps/bletiny/src/parse.c
Compiling repos/apache-mynewt-core/apps/bletiny/src/misc.c
Compiling repos/apache-mynewt-core/apps/bletiny/src/gatt_svr.c
Compiling repos/apache-mynewt-core/apps/bletiny/src/cmd.c
Compiling repos/apache-mynewt-core/apps/bletiny/src/main.c

Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.elf
Target successfully built: targets/myble

```
<br>
### Create the app image

Run the `newt create-image myble 1.0.0` command to generate a signed application image for the `myble` target. The version number is arbitrary.

```no-highlight
$newt create-image myble 1.0.0
Compiling bin/targets/myble/generated/src/myble-sysinit-app.c
Archiving myble-sysinit-app.a
Linking ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.elf
App image succesfully generated: ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.img
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

Once you have a connection set up, you can connect to your device as follows:

* On Mac OS and Linux platforms, you can run ```minicom -D /dev/tty.usbserial-<port> -b 115200``` to connect to the console of your app. Note that on Linux, the format of the port name is `/dev/ttyUSB<N>`, where N is a number.

* On Windows, you can run ```PuTTY``` to connect to the device.
	
	If you located your port from a MinGW terminal, the port name format is `/dev/ttyS<N>`, where `N` is a number. You must map the port name to a Windows COM port: `/dev/ttyS<N>` maps to `COM<N+1>`. For example, `/dev/ttyS2` maps to  `COM3`.
	
	You can also use the Windows Device Manager to locate the COM port number.

<br>
This tutorial uses minicom.  When the Minicom screen comes up, type in `?`

```hl_lines="9"
Welcome to minicom 2.7

OPTIONS: 
Compiled on Mar 18 2016, 04:59:47.
Port /dev/tty.usbserial-1a12, 21:24:09

Press Meta-Z for help on special keys

?
7471:Commands:
7471:     stat      echo         ?    prompt     ticks     tasks 
7474: mempools      date         b 
```

<br>

Try the `stat` command. 

```hl_lines="1"
> tasks
Tasks: 
46682:    task pri tid  runtime      csw    stksz   stkuse   lcheck   ncheck fg
46684:    idle 255   0    46683       99       64       31        0        0  0
46686:    main 127   1        1       29      512      156        0        0  0
46688:  ble_ll   0   2        0       12       80       58        0        0  0
46691: > 
```

<br>

Try specifying a BLE related stat, for example `ble_ll`. You should see some HCI (Host Controller Interface) command counts. 

```hl_lines="1"
113136: > stat ble_ll
hci_cmds: 11
155545:hci_cmd_errs: 0
155545:hci_events_sent: 11
155547:bad_ll_state: 0
155547:bad_acl_hdr: 0
155548:no_bufs: 0
155548:rx_adv_pdu_crc_ok: 0
155549:rx_adv_pdu_crc_err: 0
155550:rx_adv_bytes_crc_ok: 0
155551:rx_adv_bytes_crc_err: 0
155552:rx_data_pdu_crc_ok: 0

    ...

155564:scan_req_txf: 0
155565:scan_req_txg: 0
155565:scan_rsp_txg: 0
155566: > 
```

<br>

For a more exciting output, try scanning your surroundings for BLE advertisements. The HCI command shown below specifies a scan duration in ms, scan to passive, and no duplicates.  You should see some scan data flying by!


```hl_lines="1"
b scan dur=10000 passive=1 nodups=1
37266:[ts=291140616ssb, mod=4 level=1] GAP procedure initiated: discovery; own_as

37641:
38256:received advertisement; event_type=0 rssi=-48 addr_type=1 addr=59:cc:3d:a3:
38261:    flags=0x1a:
38261:        General discoverable mode
38262:    uuids16(complete)=0x1802 
38263:    name(complete)=Find Me
38264:
38551:scanning finished
```

<br>

If you're still not seeing any output from the device, try running the debugger and see if you are seeing the program execute properly. 

<br>

```
$newt debug myble
[~/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52dk/nrf52dk_debug.sh ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52dk ~/dev/wanda/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny]
~/dev/myproj/repos/apache-mynewt-core/hw/scripts/common.sh: line 38: [: =: unary operator expected
Debugging ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.elf
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
Reading symbols from ~/dev/myproj/bin/targets/myble/app/apps/bletiny/bletiny.elf...done.
os_tick_idle (ticks=1920)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:200
200    if (ticks > 0) {
(gdb) monitor reset
Resetting target
(gdb) c
Continuing.
^C
Program received signal SIGTRAP, Trace/breakpoint trap.
os_tick_idle (ticks=1907)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:200
200    if (ticks > 0) {
(gdb) p g_os_time
$1 = 13
(gdb) c
Continuing.
^C
Program received signal SIGTRAP, Trace/breakpoint trap.
os_tick_idle (ticks=1920)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:200
200    if (ticks > 0) {
(gdb) p g_os_time
$2 = 6611
(gdb) 
```
<br>

You should see the g_os_time advancing as above, as each os time tick is 1ms. If the system ticks aren't advancing, then nothing's actually running.