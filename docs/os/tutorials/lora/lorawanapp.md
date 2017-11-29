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
$ newt build telee02_boot
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
SWD connector. Connect the UART pins (RX, TX and GND) to the board. Terminal settings 115200, N, 8, 1.
        
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


```
$ newt load telee02_boot
Loading bootloader
$ newt load lora_app_shell_telee02
Loading app image into slot 1
```

Assuming you attached the serial port and have a terminal up you should set the following output on the terminal:
```
000002 lora_app_shell
```
<br>
### Shell Commands

There are a number of shell commands that will allow you to join and send both unconfirmed and confirmed data. If you type 'help' in your terminal you will see the various commands displayed. Here is a screen shot of the output of help

```
000002 lora_app_shell
help

032766 help
032766 stat                          
032767 tasks                         
032768 mpool                         
032769 date                          
032770 las_wr_mib                    
032771 las_rd_mib                    
032772 las_rd_dev_eui                
032773 las_wr_dev_eui                
032774 las_rd_app_eui                
032775 las_wr_app_eui                
032776 las_rd_app_key                
032777 las_wr_app_key                
032778 las_app_port                  
032779 las_app_tx                    
032780 las_join                      
032781 las_link_chk                  
032782 compat> 
```

The following table lists the commands and gives a brief description of the commands. The lora commands are described in more detail later in the tutorial as well as their syntax (syntax not shown in the table).

|Command|Description|
|---|---|
| help | Display list of available shell commands |
| stat | Display statistics. Syntax: stat \<statistics group\>. 'stat' with no group displays avaialable groups |
| tasks | Display OS tasks |
| mpool | Displays OS memory pools and memory pool statistics |
| date | Displays current date/time |
| las_wr_mib | Write lora MIB |
| las_rd_mib | Read lora MIB |
| las_rd_dev_eui | Read lora device EUI |
| las_wr_dev_eui | Write lora device EUI |
| las_rd_app_eui | Read lora application EUI |
| las_wr_app_eui | Write lora application EUI |
| las_rd_app_key | Read lora application key |
| las_wr_app_key | Write lora application key |
| las_app_port | Open/close lora application port |
| las_app_tx | Transmit on lora application port |
| las_join | Perform a lora OTA join |
| las_link_chk | Perform a lora link check |

### OTA Join

Before sending any application data a lora end device must be joined to its lora network. To perform a lora OTA (over-the-air) join there are some commands that must be issued prior to attempting to join. The reason for these commands is that a lora end device must be configured with a device EUI, application EUI and application key prior to performing an OTA join.

```
598763 compat> las_wr_app_eui 0x00:0x11:0x22:0x01:0x01:0x00:0x10:10

623106 compat> las_wr_app_key 03:03:03:03:03:03:03:03:03:03:03:03:03:03:03:03

623758 compat> las_wr_dev_eui 0x00:0x11:0x22:0x02:0x02:0x00:0x00:0x00

630333 compat> las_join 1

630634 Attempting to join...
019802 compat> Join cb. status=0 attempts=1
```
If the join is successful the status returned should be 0. If it fails the status will be a non-zero lora status code (lora status error codes are described later in this tutorial).

A note about "endianness" in the device EUI commands. The first three bytes of the EUI are the OUI and the last 5 bytes are unique (for that OUI). The above example assumes an OUI of 001122. This is not the same order as the address over the air as device addresses are sent "least significant byte" first (little endian). The same convention also applies to keys: they are in big-endian order in the command but sent little endian over the air.
<br>

### Opening/closing an application port

Another step that must be performed prior to sending application data is to open an application port. All data frames containing application data are sent to a specific port. Port numbers are in the range 1 - 223 as port 0 is reserved for MLME-related activities. Ports 224-255 are reserved for future standardized application extensions.

The lora app shell does not open any application ports by default.

To open and/or close an application port the following commands are used. Note that the application port which you are using to send data must be open if you want to send data (or receive it).

```
115647 compat> las_app_port open 1

150958 Opened app port 1
150958 compat> las_app_port close 1

151882 Closed app port 1
```
<br>

### Sending data

The lora app shell allows the user to send both unconfirmed and confirmed data. The command to send data is *las_app_tx \<port\> \<len\> \<type\>*

NOTE: the current usage for this command shows an optional data rate and retries for this command. That feature has not been implemented and the command will not be accepted if they are separated.

Where:
	port = port number on which to send
 	len = size n bytes of app data
 	type = 0 for unconfirmed, 1 for confirmed
    
 To send a confirmed data transmission of size 5 bytes on port 10 the command would be: las_app_tx 10 20 1
 
Once the end device has sent the frame requested there should be a message which contains some additional information. Here is a screen shot using the above example. Note that there will be some delay between seeing the "Packet sent on port 10" message and the additional information as the additional information is the "confirmation" that the lora stack provides and the confirmation will not be returned until the lora stack is finished transmitting the frame and has received an acknowledgement or has finished waiting for all the receive windows.

```
449751 compat> las_app_tx 10 5 1

452144 Packet sent on port 10
452144 compat> Txd on port 10 type=conf status=0 len=5
452325 	dr:0
452325 	txpower:5
452325 	tries:1
452326 	ack_rxd:1
452326 	tx_time_on_air:330
452327 	uplink_cntr:0
452327 	uplink_freq:903500000
```
The information contained in the confirmation is the following:

dr: The data rate on which the frame was sent.  
txpower: Transmit power level of the device.  
tries: # of attempts made to transmit the frame successfully.  
ack_rxd: Was an acknowledgement received (0 no 1 yes).  
tx_time_on_air: The on-air length of the frame (in milliseconds).  
uplink_cntr: The frame uplink counter that this frame used.  
uplink_freq: The frequency (logical) on which the frame was sent (in Hz).  

<br>


<br>




