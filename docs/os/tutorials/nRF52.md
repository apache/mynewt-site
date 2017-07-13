## Blinky, your "Hello World!", on nRF52

<br>

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) on a target board. Once built using the *newt* tool, this application will blink the LED lights on the target board.

Create a project with a simple app that blinks an LED on the nRF52 board from Nordic Semiconductors.  Download the application to the target and watch it blink!

Note that there are several versions of the nRF52 in the market. The boards tested with this tutorial are listed under "Hardware needed" below.

<br>

### Hardware needed

* nRF52 Development Kit (one of the following)
    * Preview Kit from Nordic - PCA 10036
    * Dev Kit from Nordic - PCA 10040
    * Eval Kit from Rigado - BMD-300-EVAL-ES
* Laptop running Mac OS
* It is assumed you have already installed newt tool. 
* It is assumed you already installed native tools as described [here](../get_started/native_tools.md)

<br>

### Install jlinkEXE

In order to be able to communicate with the SEGGER J-Link debugger on the dev board, you have to download and install the J-Link GDB Server software on to your laptop. You may download the "Software and documentation pack for Mac OS X" from [https://www.segger.com/jlink-software.html](https://www.segger.com/jlink-software.html). 

<br>

### Create a project.  

Create a new project to hold your work.  For a deeper understanding, you can read about project creation in 
[Get Started -- Creating Your First Project](../get_started/project_create.md)
or just follow the commands below.

```
    $ mkdir ~/dev
    $ cd ~/dev
    $ newt new myproj
    Downloading project skeleton from apache/incubator-mynewt-blinky...
    Installing skeleton in myproj...
    Project myproj successfully created.
    
    $ cd myproj
    
    $ newt install -v 
    apache-mynewt-core
    Downloading repository description for apache-mynewt-core... success!
    ...
    apache-mynewt-core successfully installed version 0.7.9-none
``` 

<br>

### Create the targets

Create two targets - one for the bootloader and one for the nrf52 board.  

<font color="#F2853F">
Note: The correct bsp must be chosen for the board you are using. </font>

* For the Nordic Preview Dev Kit choose @apache-mynewt-core/hw/bsp/nrf52840pdk (as shown below)
* For the Nordic Dev Kit choose @apache-mynewt-core/hw/bsp/nrf52dk instead (in the highlighted lines)
* For the Rigado Eval Kit choose @apache-mynewt-core/hw/bsp/bmd300eval instead (in the highlighted lines)


```hl_lines="3 8"
$ newt target create blink_nordic
$ newt target set blink_nordic app=apps/blinky
$ newt target set blink_nordic bsp=@apache-mynewt-core/hw/bsp/nrf52840pdk
$ newt target set blink_nordic build_profile=debug

$ newt target create nrf52_boot
$ newt target set nrf52_boot app=@apache-mynewt-core/apps/boot
$ newt target set nrf52_boot bsp=@apache-mynewt-core/hw/bsp/nrf52840pdk
$ newt target set nrf52_boot build_profile=optimized

$ newt target show 
targets/blink_nordic
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/nrf52840pdk
    build_profile=debug
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52840pdk
    build_profile=optimized
```

<br>

### Build the target executables 

```
$ newt build nrf52_boot
...
Compiling log_shell.c
Archiving log.a
Linking boot.elf
App successfully built: ~/dev/myproj/bin/nrf52_boot/apps/boot/boot.elf
```
```
$ newt build blink_nordic
...
Compiling main.c
Archiving blinky.a
Linking blinky.elf
App successfully built: ~/dev/myproj/bin/blink_nordic/apps/blinky/blinky.elf
```

<br>

### Sign and create the blinky application image 

You must sign and version your application image to download it using newt to the board. Use the newt create-image command to perform this action. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```
$ newt create-image blink_nordic 1.0.0
App image successfully generated: ~/dev/myproj/bin/blink_nordic/apps/blinky/blinky.img
Build manifest: ~/dev/myproj/bin/blink_nordic/apps/blinky/manifest.json
```

<br>

### Connect the board

Connect the evaluation board via micro-USB to your PC via USB cable.
        
<br>

### Download to the target

Download the bootloader first and then the blinky executable to the target platform. Don't forget to reset the board if you don't see the LED blinking right away!

```
$ newt -v load nrf52_boot
$ newt -v load blink_nordic
```

<br>

**Note:** If you want to erase the flash and load the image again, you can use JLinkExe to issue an `erase` command.

```
$ JLinkExe -device nRF52 -speed 4000 -if SWD
SEGGER J-Link Commander V5.12c (Compiled Apr 21 2016 16:05:51)
DLL version V5.12c, compiled Apr 21 2016 16:05:45

Connecting to J-Link via USB...O.K.
Firmware: J-Link OB-SAM3U128-V2-NordicSemi compiled Mar 15 2016 18:03:17
Hardware version: V1.00
S/N: 682863966
VTref = 3.300V


Type "connect" to establish a target connection, '?' for help
J-Link>erase
Cortex-M4 identified.
Erasing device (0;?i?)...
Comparing flash   [100%] Done.
Erasing flash     [100%] Done.
Verifying flash   [100%] Done.
J-Link: Flash download: Total time needed: 0.363s (Prepare: 0.093s, Compare: 0.000s, Erase: 0.262s, Program: 0.000s, Verify: 0.000s, Restore: 0.008s)
Erasing done.
J-Link>exit
$
```


### Conclusion

You have created, setup, compiled, loaded, and ran your first mynewt application
for an nrf52 board.

We have more fun tutorials for you to get your hands dirty. Be bold and work on the OS with tutorials on [writing a test suite](unit_test.md) or try enabling additional functionality such as [remote comms](project-target-slinky.md) or [Bluetooth Low Energy](bletiny_project.md) on your current board.

If you see anything missing or want to send us feedback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and blinking!





