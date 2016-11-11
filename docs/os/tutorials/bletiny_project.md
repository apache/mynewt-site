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

Define the targets further. Note that you are using the example app `bletiny` for the application target. Set the bsp correctly (nrf52pdk or nrf52dk depending on whether the board is the preview kit or the dev kit, respectively. Look on the top of your board, if you see PCA100040, use the nrf52dk version, otherwide use the nrf52pdk version). 

```
$ newt target set myble bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
Target targets/myble successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52pdk
$ newt target set myble app=@apache-mynewt-core/apps/bletiny
Target targets/myble successfully set target.app to @apache-mynewt-core/apps/bletiny
$ newt target set myble build_profile=optimized
Target targets/myble successfully set target.build_profile to optimized
$ newt target set myble cflags=-DSTATS_NAME_ENABLE
Target targets/myble successfully set pkg.cflags to DSTATS_NAME_ENABLE
```

Use the same `newt target set` command to set the following definition for the bootloader target -- again, make sure you use the correct value for the bsp based on which version of the board you have..

```
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
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
    bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
    build_profile=optimized
    cflags=-DSTATS_NAME_ENABLE 
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52pdk
    build_profile=optimized
```

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

You will now look for some BLE related stats over a serial connection and see the radio is actually working. The picture below shows a serial connector set up. Pin PA.08 is RX and pin PA.06 is TX. Make sure TX from the NRF52 goes to RX on your Serial board, and that RX on the NRF52 goes to TX on your Serial Board.

![nRF52](pics/nrf52.JPG "nRF52 Dev Board with a Serial Connection set up")

<br>

You may use any terminal emulation program to communicate with the board, but you should connect to the nRF52's serial port using a baudrate of 115200, 8N1, and hardware/software flow control both off. This tutorial shows a Minicom set up. You will have to find out what the usbserial port number is on your laptop, of course.

```
$ minicom -D /dev/tty.usbserial-AJ03HAQQ -b 115200
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
4828455:log     echo    ?       tasks   mempools        date 
4828457:stat    b 
```

<br>

Try the `stat` command. 

```hl_lines="1"
stat
4973017:Must specify a statistic name to dump, possible names are:
4973021:        stat
4973022:        ble_l2cap
4973024:        ble_att
4973026:        ble_gap
4973027:        ble_gattc
4973029:        ble_gatts
4973031:        ble_hs
4973032:        ble_ll_conn
4973034:        ble_ll
```

<br>

Try specifying a BLE related stat, for example `ble_ll`. You should see some HCI (Host Controller Interface) command counts. 

```hl_lines="1"
stat ble_ll
4986297:hci_cmds: 5
4986297:hci_cmd_errs: 0
4986299:hci_events_sent: 5
4986301:bad_ll_state: 0
4986303:bad_acl_hdr: 0
4986306:rx_adv_pdu_crc_ok: 0
4986308:rx_adv_pdu_crc_err: 0
4986311:rx_adv_bytes_crc_ok: 0
4986314:rx_adv_bytes_crc_err: 0
4986317:rx_data_pdu_crc_ok: 0
4986319:rx_data_pdu_crc_err: 0
4986322:rx_data_bytes_crc_ok: 0
<snip>
```

<br>

For a more exciting output, try scanning your surroundings for BLE adverstisements. The HCI command shown below specifies a scan duration in ms, sets discovery mode to general (as opposed to limited), the filter to no-whitelist, and type of scan to passive. You should see some scan data flying by!

```hl_lines="1"
b scan dur=10000 disc=gen filt=no_wl type=passive

5301227:[ts=5301227ssb, mod=4 level=1] host_hci_cmd_send: ogf=0x08 ocf=0x0b len=7
5301233:[ts=5301233ssb, mod=4 level=1] Command Complete: cmd_pkts=1 ogf=0x8 ocf=0xb status=0
5301241:[ts=5301241ssb, mod=4 level=1] host_hci_cmd_send: ogf=0x08 ocf=0x0c len=2
5301248:[ts=5301248ssb, mod=4 level=1] Command Complete: cmd_pkts=1 ogf=0x8 ocf=0xc status=0
GAP procedure initiated: discovery; disc_mode=2 filter_policyLE advertising report. len=38 num=1 evtype=3 addr9
5301270:[ts=5301270ssb, mod=4 level=1] 02 01 06 03 03 aa fe 12 
5301276:[ts=5301276ssb, mod=4 level=1] 16 aa fe 10 f6 02 67 2e 
5301281:[ts=5301281ssb, mod=4 level=1] 63 6f 2f 62 65 61 63 6f 
5301287:[ts=5301287ssb, mod=4 level=1] 6e 73 
5301291:[ts=5301291ssb, mod=64 level=2] received advertisement; event_type=3 addr_type=1 addr=0xa0:0x0d:0xec:0:
5301316:[ts=5301316ssb, mod=64 level=2]     flags=0x06
5301321:[ts=5301321ssb, mod=64 level=2]     uuids16(complete)=0xfeaa 
5301327:[ts=5301327ssb, mod=64 level=2]     svc_data_uuid16=
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
