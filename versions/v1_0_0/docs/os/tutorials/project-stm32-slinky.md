## Project Slinky Using Olimex Board

This tutorial shows you how to create, build and run the Slinky application and communicate with newtmgr for an Olimex STM-E407 board.
<br>
###Prerequisites
* Meet the prerequisites listed in [Project Slinky](/os/tutorials/project-slinky.md).
* Have a STM32-E407 development board from Olimex. 
* Have a ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
* Have a USB A-B type cable to connect the debugger to your computer. 
* Have a USB to TTL Serial Cable with female wiring harness.
* Install the [OpenOCD debugger](/os/get_started/cross_tools/).

### Create a New Project
Create a new project if you do not have an existing one.  You can skip this step and proceed to [create the targets](#create_targets) if you already have a project created or completed the [Sim Slinky](project-slinky.md) tutorial.

```no-highlight
$ newt new slinky
Downloading project skeleton from apache/incubator-mynewt-blinky...
...
Installing skeleton in slink...
Project slink successfully created
$ cd slinky
$newt install
apache-mynewt-core
```

<br>

###<a name="create_targets"></a> Create the Targets
Create two targets for the STM32-E407 board - one for the bootloader and one for the Slinky application.

Run the following `newt target` commands, from your project directory, to create a bootloader target. We name the target `
stm32_boot`.

```no-highlight
$ newt target create stm32_boot
$ newt target set stm32_bootr bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
$ newt target set stm32_boot build_profile=optimized
$ newt target set stm32_boot target.app=@apache-mynewt-core/apps/boot
```
<br>
Run the following `newt target` commands to create a target for the Slinky application. We name the target `stm32_slinky`.

```no-highlight
$ newt target create stm32_slinky
$ newt target set stm32_slinky bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
$ newt target set stm32_slinky build_profile=debug
$ newt target set stm32_slinky app=@apache-mynewt-core/apps/slinky
```
<br>

### Build the Targets
Run the `newt build stm32_boot` command to build the bootloader:

```no-highlight
$ newt build stm32_boot
Building target targets/stm32_boot
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_validate.c
Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aes.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
Compiling repos/apache-mynewt-core/apps/boot/src/boot.c

      ...

Archiving sys_mfg.a
Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/slinky/bin/targets/stm32_boot/app/apps/boot/boot.elf
Target successfully built: targets/stm32_boot
$
```
<br>
Run the `newt build stm32_slinky` command to build the Slinky application:

```no-highlight
$newt build stm32_slinky
Building target targets/stm32_slinky
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_validate.c
Compiling repos/apache-mynewt-core/boot/split/src/split.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
Compiling repos/apache-mynewt-core/apps/slinky/src/main.c

       ...

Archiving util_crc.a
Archiving util_mem.a
Linking ~/dev/slinky/bin/targets/stm32_slinky/app/apps/slinky/slinky.elf
Target successfully built: targets/stm32_slinky
$
```
<br>
### Sign and Create the Slinky Application Image

Run the `newt create-image stm32_slinky 1.0.0` command to create and sign the application image. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```no-highlight
create-image stm32_slinky 1.0.0
App image succesfully generated: ~/dev/slinky/bin/targets/stm32_slinky/app/apps/slinky/slinky.img
$
```
<br>


###Connect to the Board

* Connect the USB A-B type cable to the ARM-USB-TINY-H debugger connector. 
* Connect the ARM-USB-Tiny-H debugger connector to your computer and the board.
* Connect the USB Micro-A cable to the USB-OTG2 port on the board.
* Set the Power Sel jumper on the board to pins 5 and 6 to select USB-OTG2 as the power source.  If you would like to use a different power source, refer to the [OLIMEX STM32-E407 user manual](https://www.olimex.com/Products/ARM/ST/STM32-E407/resources/STM32-E407.pdf) for pin specifications.

You should see a red LED light up on the board. 

<br>
### Load the Bootloader and the Slinky Application Image

Run the `newt load stm32_boot` command to load the bootloader onto the board:

```no-highlight
$ newt load stm32_boot
Loading bootloader
$
```
<br>
Note: If you are using Windows and get a `no device found` error, you will need to install the usb driver. Download [Zadig](http://zadig.akeo.ie) and run it:

* Select Options > List All Devices.
* Select `Olimex OpenOCD JTAG ARM-USB-TINY-H` from the drop down menu.
* Select the `WinUSB` driver.
* Click Install Driver.
* Run the `newt load stm32_boot` command again.

<br>
Run the `newt load stm32_slinky` command to load the Slinky application image onto the board:
```no-highlight
$ newt load stm32_slinky
Loading app image into slot 1
$
```
<br>

### Connect Newtmgr with the Board using a Serial Connection

Locate the PC6/USART6_TX (pin 3), PC7/USART6_RX (pin 4), and GND (pin 2) of the UEXT connector on the Olimex board. More information on the UEXT connector can be found at [https://www.olimex.com/Products/Modules/UEXT/](https://www.olimex.com/Products/Modules/UEXT/). The schematic of the board can be found at [https://www.olimex.com/Products/ARM/ST/STM32-E407/resources/STM32-E407_sch.pdf](https://www.olimex.com/Products/ARM/ST/STM32-E407/resources/STM32-E407_sch.pdf) for reference.


![Alt Layout - Serial Connection](pics/serial_conn.png)

* Connect the female RX pin of the USB-TTL serial cable to the TX (Pin 3) of the UEXT connector on the board.
* Connect the female TX pin of the USB-TTL serial cable to the RX (Pin 4) of the UEXT connector on the board.
* Connect the GND pin of the USB-TTL serial cable to the GND (Pin 2) of the UEXT connector on the board.

<br>
Locate the port, in the /dev directory on your computer, that the serial connection uses. The format of the port name is platform dependent:


* Mac OS uses the format `tty.usbserial-<some identifier>`.
* Linux uses the format `TTYUSB<N>`, where `N` is a number.  For example, TTYUSB2.
* MinGW on Windows uses the format `ttyS<N>`, where `N` is a number. You must map the port name to a Windows COM port: `/dev/ttyS<N>` maps to `COM<N+1>`. For example, `/dev/ttyS2` maps to  `COM3`.
	
	You can also use the Windows Device Manager to find the COM port number.

<br>
```no-highlight
$ ls /dev/tty*usbserial*
/dev/tty.usbserial-1d13
$
```

<br>
Setup a newtmgr connection profile for the serial port. For our example, the port is  `/dev/tty.usbserial-1d13`.

Run the `newtmgr conn add` command to define a newtmgr connection profile for the serial port.  We name the connection profile `stm32serial`.  
 
**Note**:

* You will need to replace the `connstring` with the specific port for your serial connection.
* On Windows, you must specify `COM<N+1>` for the connstring if `/dev/ttyS<N>` is the serial port.

<br>
```no-highlight
$ newtmgr conn add stm32serial type=serial connstring=/dev/tty.usbserial-1d13
Connection profile stm32serial successfully added
$
```
<br>
You can run the `newt conn show` command to see all the newtmgr connection profiles:

```no-highlight
$ newtmgr conn show
Connection profiles:
  stm32serial: type=serial, connstring='/dev/tty.usbserial-1d13'
  sim1: type=serial, connstring='/dev/ttys012'
$
```

<br>
### Use Newtmgr to Query the Board
Run some newtmgr commands to query and receive responses back from the board (See the [Newt Manager Guide](newtmgr/overview) for more information on the newtmgr commands).

Run the `newtmgr echo hello -c stm32serial` command. This is the simplest command that requests the board to echo back the
 text.

```no-highlight
$ newtmgr echo hello -c stm32serial
hello
$
```
<br>
Run the `newtmgr image list -c stm32serial` command to list the images on the board:

```no-highlight
$ newtmgr image list -c stm32serial
Images:
 slot=0
    version: 1.0.0
    bootable: true
    flags: active confirmed
    hash: 9cf8af22b1b573909a8290a90c066d4e190407e97680b7a32243960ec2bf3a7f
Split status: N/A
$
```


<br>
Run the `newtmgr taskstats -c stm32serial` command to display the task statistics on the board:

```no-highlight
$ newtmgr taskstats -c stm32serial
Return Code = 0
      task pri tid  runtime      csw    stksz   stkuse last_checkin next_checkin
     task1   8   2        0       90      192      110        0        0
     task2   9   3        0       90       64       31        0        0
      idle 255   0    89460    89463       64       26        0        0
      main 127   1        4       26     1024      368        0        0
$
```


