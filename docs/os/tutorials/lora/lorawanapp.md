## LoRaWAN App

<br>

### Objective

The purpose of this tutorial is to demonstrate how to build the lora app shell application for either a class A or class C lora device and to perform basic functions such as joining and sending data packets to a lora gateway/server.

NOTE: This tutorial presumes that you have a running lora gateway and lora network server. No description of the gateway/server is provided. It is expected that the user understands how to configure and operate the gateway/server so that it can communicate with a class A or class C device.

<br>

### Hardware needed

* Telenor EE02 module
* Segger J-Link or similar debugger
* LORA gateway
* Laptop running Mac OS
* It is assumed you have already installed newt tool. 
* It is assumed you understand the basics of the mynewt OS
* 3-wire serial cable to connect telenor module to your laptop
* Some form of terminal emulation application running on your laptop.

<br>

### Create a project.  

Create a new project to hold your work.  For a deeper understanding, you can read about project creation in 
[Get Started -- Creating Your First Project](../get_started/project_create.md)
or just follow the commands below.

```
    $ mkdir ~/dev
    $ cd ~/dev
    $ newt new mylora
    Downloading project skeleton from apache/mynewt-blinky...
    Installing skeleton in mylora...
    Project mylora successfully created.
    $ cd mylora
    
``` 

<br>

### Install Everything

Now that you have defined the needed repositories, it's time to install everything so
that you can get started.

```
    $ newt install -v 
    apache-mynewt-core
    Downloading repository description for apache-mynewt-core... success!
    ...
    apache-mynewt-core successfully installed version 1.2.0-none
    ...
```

<br>

### Create the targets

Create two targets - one for the bootloader and one for the lora app shell application.  

```no-highlight
$ newt target create telee02_boot
$ newt target set telee02_boot bsp=@apache-mynewt-core/hw/bsp/telee02
$ newt target set telee02_boot app=@apache-mynewt-core/apps/boot
$ newt target set telee02_boot build_profile=optimized

$ newt target create lora_app_shell_telee02
$ newt target set lora_app_shell_telee02 bsp=@apache-mynewt-core/hw/bsp/telee02
$ newt target set lora_app_shell_telee02 app=@apache-mynewt-core/apps/lora_app_shell
$ newt target set lora_app_shell_telee02 build_profile=optimized
```
The lora app shell application requires a few additional system configuration variables. 
Create and edit a file called syscfg.yml in dev/mylora/targets/lora_app_shell. The file
contents should be the following:

```
### Package: targets/lora_app_shell_telee02

syscfg.vals:
    SHELL_CMD_ARGC_MAX: "20"
    LORA_MAC_TIMER_NUM: "4"
    TIMER_4: "1"
```

You can now "display" the targets you created to make sure they are correct:

```
$ newt target show telee02_boot
targets/telee02_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/telee02
    build_profile=optimized
    
$ newt target show lora_app_shell_telee02
targets/lora_app_shell_telee02
    app=@apache-mynewt-core/apps/lora_app_shell
    bsp=@apache-mynewt-core/hw/bsp/telee02
    build_profile=optimized
    syscfg=LORA_MAC_TIMER_NUM=4:SHELL_CMD_ARGC_MAX=20:TIMER_4=1

```

<font color="#F2853F">
Note: If you've already built and installed a bootloader for your ee02 module then you do
not need to create a target for it here, or build and load it as below. </font>
<br>

### Build the target executables 

```
$ newt clean telee02_boot
$ newt clean telee02_boot
Building target targets/telee02_boot
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c    

        . . .

Archiving telee02_boot-sysinit-app.a
Archiving util_mem.a
Linking /Users/wes/dev/wes/bin/targets/telee02_boot/app/apps/boot/boot.elf
Target successfully built: targets/telee02_boot

$ newt clean lora_app_shell_telee02
$ newt build lora_app_shell_telee02
Building target targets/lora_app_shell_telee02
Assembling repos/apache-mynewt-core/hw/bsp/telee02/src/arch/cortex_m4/gcc_startup_nrf52_split.s
Compiling repos/apache-mynewt-core/encoding/base64/src/hex.c
Compiling repos/apache-mynewt-core/encoding/base64/src/base64.c
        . . .


Archiving util_mem.a
Archiving util_parse.a
Linking /Users/wes/dev/wes/bin/targets/lora_app_shell_telee02/app/apps/lora_app_shell/lora_app_shell.elf
Target successfully built: targets/lora_app_shell_telee0
```
<font color="#F2853F">
Note: The newt clean step is not necessary but shown here for good measure. </font>
<br>

### Sign and create the application image 

You must sign and version your application image to download it using newt to the board. 
Use the newt create-image command to perform this action. You may assign an arbitrary 
version (e.g. 1.0.0) to the image.

```
$ newt create-image lora_app_shell_telee02 0.0.0
App image succesfully generated: /Users/wes/dev/wes/bin/targets/lora_app_shell_telee02/app/apps/lora_app_shell/lora_app_shell.img
```

<font color="#F2853F">
Note: Only the application image requires this step; the bootloader does not </font>
<br>

### Connect the board

Connect the evaluation board via micro-USB to your PC via USB cable. Connect the Segger J-link debugger to the 9-pin
SWD connector. Connect the UART pins (RX, TX and GND) to the board.
        
<br>

### Download bootloader and application


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
<br>


<br>




