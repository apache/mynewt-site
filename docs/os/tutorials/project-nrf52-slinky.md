## Project Slinky using the Nordic nRF52 Board
This tutorial shows you how to create, build and run the Slinky application and communicate with newtmgr for a Nordic nRF52 board.

### Prerequisites
* Meet the prerequisites listed in [Project Slinky](/os/tutorials/project-slinky.md).  
* Have a Nordic nRF52-DK board.  
* Install the [Segger JLINK Software and documentation pack](https://www.segger.com/jlink-software.html).

### Create a New Project
Create a new project if you do not have an existing one.  You can skip this step and proceed to [create the targets](#create_targets) if you already have a project created or completed the [Sim Slinky](project-slinky.md) tutorial. 

Run the following commands to create a new project. We name the project `slinky`.	

```no-highlight
$ newt new slinky
Downloading project skeleton from apache/mynewt-blinky...
...
Installing skeleton in slink...
Project slinky successfully created
$ cd slinky
$newt install 
apache-mynewt-core
```

<br>

### <a name="create_targets"></a> Create the Targets

Create two targets for the nRF52-DK board - one for the bootloader and one for the Slinky application.

Run the following `newt target` commands, from your project directory, to create a bootloader target. We name the target `nrf52_boot`.

```no-highlight
$ newt target create nrf52_boot
$ newt target set nrf52_boot bsp=@apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set nrf52_boot build_profile=optimized
$ newt target set nrf52_boot app=@apache-mynewt-core/apps/boot
```
<br>
Run the following `newt target` commands to create a target for the Slinky application. We name the target `nrf52_slinky`.

```no-highlight
$ newt target create nrf52_slinky
$ newt target set nrf52_slinky bsp=@apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set nrf52_slinky build_profile=debug
$ newt target set nrf52_slinky app=@apache-mynewt-core/apps/slinky
```

<br>

### Build the Targets

Run the `newt build nrf52_boot` command to build the bootloader:

```no-highlight
$ newt build nrf52-boot
Building target targets/nrf52_boot
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aes.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_validate.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
Compiling repos/apache-mynewt-core/apps/boot/src/boot.c
    ...

Archiving sys_mfg.a
Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/slinky/bin/targets/nrf52_boot/app/apps/boot/boot.elf
Target successfully built: targets/nrf52_boot
```
<br>

Run the `newt build nrf52_slinky` command to build the Slinky application:

```no-highlight
$newt build nrf52_slinky
Building target targets/nrf52_slinky
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/boot/split/src/split.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
Compiling repos/apache-mynewt-core/boot/split/src/split_config.c
Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aesni.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_validate.c
Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aes.c
Compiling repos/apache-mynewt-core/apps/slinky/src/main.c

       ...

Archiving util_mem.a
Linking ~/dev/slinky/bin/targets/nrf52_slinky/app/apps/slinky/slinky.elf
Target successfully built: targets/nrf52_slinky
```

<br>

### Sign and Create the Slinky Application Image

Run the `newt create-image nrf52_slinky 1.0.0` command to create and sign the application image. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```no-highlight
$ newt create-image nrf52_slinky 1.0.0
App image succesfully generated: ~/dev/slinky/bin/targets/nrf52_slinky/app/apps/slinky/slinky.img
$
```
<br>

### Connect to the Board

* Connect a micro-USB cable from your computer to the micro-USB port on the nRF52-DK board.
* Turn the power on the board to ON. You should see the green LED light up on the board.

<br>
### Load the Bootloader and the Slinky Application Image

Run the `newt load nrf52_boot` command to load the bootloader onto the board:

```no-highlight
$ newt load nrf52_boot
Loading bootloader
$
```
<br>
Run the `newt load nrf52_slinky` command to load the Slinky application image onto the board:
```no-highlight
$ newt load nrf52_slinky
Loading app image into slot 1
$
```
<br>


### Connect Newtmgr with the Board using a Serial Connection

Set up a serial connection from your computer to the nRF52-DK board (See [Serial Port Setup](/os/get_started/serial_access.md)).  

Locate the port, in the /dev directory on your computer, that the serial connection uses. The format of the port name is platform dependent:

* Mac OS uses the format `tty.usbserial-<some identifier>`.
* Linux uses the format `TTYUSB<N>`, where `N` is a number.  For example, TTYUSB2.
* MinGW on Windows uses the format `ttyS<N>`, where `N` is a number. You must map the port name to a Windows COM port: `/dev/ttyS<N>` maps to `COM<N+1>`. For example, `/dev/ttyS2` maps to  `COM3`.  
	
	You can also use the Windows Device Manager to find the COM port number.

<br>
```no-highlight
$ ls /dev/tty*usbserial*
/dev/tty.usbserial-1d11
$
```
<br>

Setup a newtmgr connection profile for the serial port. For our example, the port is  `/dev/tty.usbserial-1d11`. 

Run the `newtmgr conn add` command to define a newtmgr connection profile for the serial port.  We name the connection profile `nrf52serial`.  

**Note**: 

* You will need to replace the `connstring` with the specific port for your serial connection. 
* On Windows, you must specify `COM<N+1>` for the connstring if `/dev/ttyS<N>` is the serial port.

<br>
```no-highlight
$ newtmgr conn add nrf52serial type=serial connstring=/dev/tty.usbserial-1d11
Connection profile nrf52serial successfully added
$
```

<br>
You can run the `newt conn show` command to see all the newtmgr connection profiles:

```no-highlight
$ newtmgr conn show
Connection profiles:
  nrf52serial: type=serial, connstring='/dev/tty.usbserial-1d11'
  sim1: type=serial, connstring='/dev/ttys012'
$
```

<br>
### Use Newtmgr to Query the Board
Run some newtmgr commands to query and receive responses back from the board (See the [Newt Manager Guide](../../newtmgr/overview) for more information on the newtmgr commands). 


Run the `newtmgr echo hello -c nrf52serial` command. This is the simplest command that requests the board to echo back the text. 

```no-highlight
$ newtmgr echo hello -c nrf52serial 
hello
$
```
<br>
Run the `newtmgr image list -c nrf52serial` command to list the images on the board:

```no-highlight
$ newtmgr image list -c nrf52serial 
Images:
 slot=0
    version: 1.0.0
    bootable: true
    flags: active confirmed
    hash: f411a55d7a5f54eb8880d380bf47521d8c41ed77fd0a7bd5373b0ae87ddabd42
Split status: N/A
$
```

<br>
Run the `newtmgr taskstat -c nrf52serial` command to display the task statistics on the board:

```no-highlight
$ newtmgr taskstat -c nrf52serial
Return Code = 0
      task pri tid  runtime      csw    stksz   stkuse last_checkin next_checkin
     task1   8   2        0     1751      192      110        0        0
     task2   9   3        0     1751       64       31        0        0
      idle 255   0   224081     2068       64       32        0        0
      main 127   1        3       29     1024      365        0        0
$
```
