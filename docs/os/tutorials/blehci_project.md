## Use HCI access to NimBLE controller

<br>

This tutorial explains how to use the example application `blehci` included in the NimBLE stack to talk to the Mynewt NimBLE controller via the Host Controller Interface. You may build the Mynewt image using a laptop running any OS of your choice - Mac, Linux, or Windows.

The host used in this specific example is the BlueZ Bluetooth stack. Since BlueZ is a Bluetooth stack for Linux kernel-based family of operating system, the tutorial expects a computer running Linux OS and with BlueZ installed to talk to the board with the Mynewt image.

<br>

### Pre-Requisites

* Ensure you have installed [newt](../../newt/install/newt_mac.md) and that the 
newt command is in your system path. 
* You must have Internet connectivity to fetch remote Mynewt components.
* If you are not using the Docker container for newt and other tools, you must [install the compiler tools](../get_started/native_tools.md) to 
support native compiling to build the project this tutorial creates.  
* You have a board with BLE radio that is supported by Mynewt. We will use an nRF52 Dev board in this tutorial.
* USB TTL Serial Cable that supports hardware flow control such as ones found at [http://www.ftdichip.com/Products/Cables/USBTTLSerial.htm](http://www.ftdichip.com/Products/Cables/USBTTLSerial.htm) to establish a serial USB connection between the board and the laptop.
* You have installed a BLE host such as BlueZ on a Linux machine to talk to the nrf52 board running Mynewt. Use `sudo apt-get install bluez` to install it on your Linux machine. 

<br>

### Create a project

Use the Newt tool to create a new project directory containing a skeletal Mynewt framework. Change into the newly created directory. 

```
$ newt new blehciproj 
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in blehciproj ...
Project blehciproj  successfully created.
$ cd mblehciproj 

$ newt install
apache-mynewt-core
```

<br>

### Create targets 

You will create two targets - one for the bootloader, the other for the application. Then you will add the definitions for them. Note that you are using the example app `blehci` for the application target. Set the bsp correctly (nrf52pdk or nrf52dk depending on whether the board is the preview kit or the dev kit, respectively).

```
$ newt target create nrf52_boot
$ newt target set nrf52_boot app=@apache-mynewt-core/apps/boot
$ newt target set nrf52_boot bsp=@apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set nrf52_boot build_profile=optimized
```
```
$ newt target create myble2
$ newt target set myble2 bsp=@apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set myble2 app=@apache-mynewt-core/apps/blehci
$ newt target set myble2 build_profile=optimized
```

<br>

Check that the targets are defined correctly.


```
$ newt target show
   targets/my_blinky_sim
       app=apps/blinky
       bsp=@apache-mynewt-core/hw/bsp/native
       build_profile=debug
   targets/myble2
       app=@apache-mynewt-core/apps/blehci
       bsp=@apache-mynewt-core/hw/bsp/nrf52dk
       build_profile=optimized
   targets/nrf52_boot
       app=@apache-mynewt-core/apps/boot
       bsp=@apache-mynewt-core/hw/bsp/nrf52dk
       build_profile=optimized
```

<br>

### Build targets

Then build the two targets.

```no-highlight
$ newt build nrf52_boot
<snip>
Linking ~/dev/blehciproj/bin/targets/nrf52_boot/app/apps/boot/boot.elf
Target successfully built: targets/nrf52_boot

$ newt build myble2
<snip>
Linking ~/dev/blehciproj/bin/targets/myble2/app/apps/blehci/blehci.elf
Target successfully built: targets/myble2
$
```


<br>

### Create the app image

Generate a signed application image for the `myble2` target. The version number is arbitrary.

```no-highlight
$ newt create-image myble2 1.0.0
App image succesfully generated: ~/dev/blehciproj/bin/targets/myble2/app/apps/bletiny/bletiny.img
```

<br>

### Load the bootloader and the application image

Make sure the USB connector is in place and the power LED on the board is lit. Use the Power ON/OFF switch to reset the board after loading the image.

Load the bootloader:

```no-highlight
$ newt load nrf52_boot
Loading bootloader
$
```
<br>
Load the application image:
```no-highlight
$ newt load myble2
Loading app image into slot 1
$
```

<br>

### Establish serial connection

Attach a serial port to your board by connecting the USB TTL Serial Cable. This should create /dev/ttyUSB0 (or similar) on your machine. 

**Note** Certain Linux OS versions have been observed to detect the nrf52 board as a mass storage device and the console access doesn’t work properly. In that case try powering the nrf52 board from your monitor or something other than your Linux computer/laptop when you set up the serial port for HCI communication.

<br>

### Open Bluetooth monitor btmon

`btmon` is a BlueZ test tool to display all HCI commands and events in a human readable format. Start the btmon tool in a terminal window. 

```
$ sudo btmon
[sudo] password for admin: 
Bluetooth monitor ver 5.37
```

<br>

### Attach the blehci device to BlueZ

In a different terminal, attach the blehci device to the BlueZ daemon (substitute the correct /dev filename for ttyUSB0).

```
$ sudo btattach -B /dev/ttyUSB0 -S 1000000
Attaching BR/EDR controller to /dev/ttyUSB0
Switched line discipline from 0 to 15
Device index 1 attached
```

The baud rate used to connect to the controller may be changed by overriding the default value of 1000000 in the `net/nimble/transport/uart/syscfg.yml`. Settings in the serial transport `syscfg.yml` file can be overridden by a higher priority package such as the application. So, for example, you may set the `BLE_HCI_UART_BAUD` to a different value in `apps/blehci/syscfg.yml`.

If there is no CTS/RTS lines present in the test environment, flow control should be turned off. This can be done with
-N option for btattach. **Note:** -N option came with BlueZ ver 5.44.

<br>

### Start btmgmt to send commands

In a third terminal, start btmgmt.  This tool allows you to send commands to the blehci controller. Use the index number that shows up when you `btattach` in the previous step.

```
$ sudo btmgmt --index 1
[sudo] password for admin: 
```

Set your device address (you can substitute any static random address here).

```
[hci1]# static-addr cc:11:11:11:11:11
Static address successfully set
```

Initialize the controller.

```
[hci1]# power on
hci1 Set Powered complete, settings: powered le static-addr 
```

Begin scanning.

```
[hci1]# find -l
Discovery started
hci1 type 6 discovering on
hci1 dev_found: 58:EF:77:C8:8D:17 type LE Random rssi -78 flags 0x0000 
AD flags 0x06 
eir_len 23
<snip>
```

