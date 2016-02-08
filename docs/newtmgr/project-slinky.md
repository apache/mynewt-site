## Project Slinky 


### Objective

The goal of the project is to enable and demonstate remote communications with a device or target via newt manager (newtmgr). We will first build the project image for a simulated device and then build an image for a hardware target. Next, the tool newtmgr has to be installed and a connection established with the target. Finally, various available commands in newtmgr will be used to query the target, upgrade image, and collect data from the endpoint.


### What you need

1. STM32-E407 development board from Olimex. You can order it from [http://www.mouser.com](http://www.mouser.com/ProductDetail/Olimex-Ltd/STM32-E407/?qs=UN6GZl1KCcit6Ye0xmPO4A%3D%3D), [http://www.digikey.com](http://www.digikey.com/product-detail/en/STM32-E407/1188-1093-ND/3726951), and other places.
2. ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
3. USB A-B type cable to connect the debugger to your personal computer
4. A USB to TTL Serial Cable with female wiring harness. An example is [http://www.amazon.com/JBtek®-WINDOWS-Supported-Raspberry-Programming/dp/B00QT7LQ88/ref=lp_464404_1_9?s=pc&ie=UTF8&qid=1454631303&sr=1-9](http://www.amazon.com/JBtek®-WINDOWS-Supported-Raspberry-Programming/dp/B00QT7LQ88/ref=lp_464404_1_9?s=pc&ie=UTF8&qid=1454631303&sr=1-9)
5. Personal Computer

The instructions assume the user is using a Bourne-compatible shell (e.g. bash or zsh) on your computer. The given instructions have been tested with the following releases of operating systems:

* Mac: OS X Yosemite Version 10.10.5

### Overview of steps

* Define targets using the newt tool
* Build executables for the targets using the newt tool
* Set up serial connection with the targets - both the physical connection with a hardware target and the connection profile using the newtmgr tool
* Use the newtmgr tool to communicate with the targets

The following instructions will walk you through the update of the larva nest and the installation of newtmgr as well.

### Creating local repository

Make sure Mynewt's default nest `larva` is up to date by downloading the latest from the Apache mynewt repository ([https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva](https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva)).

```no-highlight
        $ pwd
        /Users/<user>/dev/larva
        $ ls -al
        total 72
        drwxr-xr-x  18 <user>  staff    612 Feb  3 15:47 .
        drwxr-xr-x   5 <user>  staff    170 Feb  3 13:32 ..
        drwxr-xr-x  13 <user>  staff    442 Feb  3 13:32 .git
        -rw-r--r--   1 <user>  staff     66 Feb  3 13:32 .gitignore
        -rw-r--r--   1 <user>  staff      0 Feb  3 13:32 .gitmodules
        drwxr-xr-x   4 <user>  staff    136 Feb  3 16:13 .nest
        -rw-r--r--   1 <user>  staff  11358 Feb  3 13:32 LICENSE
        ...
        ...
        drwxr-xr-x   5 <user>  staff    170 Feb  3 13:32 sys
        $ git pull origin master
```

### Installing Newtmgr

You will first download the source code for newt. Currently, you need to create a symbolic link for all the directory references in the go scripts to work correctly.

```no-highlight
        $ cd ~/dev
        $ go get git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ ln -s ~/dev/go/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git ~/dev/go/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt

        $ pwd
       /Users/<user>/dev/go
        $ ls
         bin	pkg	   src
        $ cd src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt/newt
        $ ls
        newt	newtmgr	   newtvm	util
        $ cd newtmgr
        $ go build
        $ 
```

Note: If the `go build` command results in errors indicating some package cannot be found, do a `go get` to download all the third-party files needed from github.com and then run `go build` again. 

### Building Targets

You will create a total of 4 targets. The first one is a simulation target and the second a hardware target (for STM32-E407 Olimex development board). In order to run an image from the flash on the Olimex board, a bootloader is required. You will build two additional targets (bootloader and bin2img) as explained in Project Blinky under [Using flash to make LED blink](../get_started/project1/#using-flash-to-make-led-blink) and as shown below.

Here;'s how to create the target for simulation.

```no-highlight
        $ newt target create slinky_sim
        Creating target slinky_sim
        Target slinky_sim sucessfully created!
        $ newt target set slinky_sim arch=sim
        Target slinky_sim successfully set arch to sim
        $ newt target set slinky_sim compiler=sim
        Target slinky_sim successfully set compiler to sim
        $ newt target set slinky_sim project=slinky
        Target slinky_sim successfully set project to slinky
        $ newt target set slinky_sim compiler_def=debug
        Target slinky_sim successfully set compiler_def to debug
        $ newt target set slinky_sim bsp=hw/bsp/native
        Target slinky_sim successfully set bsp to hw/bsp/native
        $ newt target show slinky_sim
        slinky_sim
        	arch: sim
        	bsp: hw/bsp/native
        	compiler: sim
        	compiler_def: debug
        	name: slinky_sim
        	project: slinky     
```
Repeat the above steps using the attribute information for each target from the target output shown below to create the remaining three targets. The four target definitions are:

```no-highlight
        $ newt target show
        bin2img
        	arch: sim
        	bsp: hw/bsp/native
        	compiler: sim
        	compiler_def: debug
        	name: bin2img
        	project: bin2img
        boot_olimex
        	arch: cortex_m4
	        bsp: hw/bsp/olimex_stm32-e407_devboard
	        compiler: arm-none-eabi-m4
	        compiler_def: optimized
	        name: boot_olimex
	        project: boot
        slinky1
        	arch: cortex_m4
	        bsp: hw/bsp/olimex_stm32-e407_devboard
	        compiler: arm-none-eabi-m4
	        compiler_def: debug
	        name: slinky1
	        project: slinky
        slinky_sim
	        arch: sim
	        bsp: hw/bsp/native
	        compiler: sim
	        compiler_def: debug
	        name: slinky_sim
	        project: slinky
```
Go ahead and build all the targets. The build command for slinky_sim is shown below.
```no-highlight
        $ newt target build slinky_sim
        Building target slinky_sim (project = slinky)
        Compiling base64.c
        Compiling cbmem.c
        ...
        Archiving libnative.a
        Compiling main.c
        Building project slinky
        Linking slinky.elf
        Successfully run!
```
Now run the `newt target build` command for the remaining three targets.
     

### Using newtmgr with a sim target 

* Run the executable you have build for the simulated environment. The serial port name on which the simulated target is connected is shown in the output.

```no-highlight
        $ pwd
        /Users/<user>/dev/larva/project/slinky
        $ ./bin/slinky_sim/slinky.elf
        uart0 at /dev/ttys007
```
* You will now set up a connection profile using `newtmgr` for the serial port connection and start communicating with the simulated remote device.

```no-highlight
        $ newtmgr conn add sim1 type=serial connstring=/dev/ttys007
        Connection profile sim1 successfully added
        $ newtmgr conn show
        Connection profiles: 
          sim1: type=serial, connstring='/dev/ttys007'
        $ newtmgr -c sim1 taskstats
        Return Code = 0
          uart_poller (prio=0 tid=3 runtime=0 cswcnt=43810 stksize=1024 stkusage=325 last_checkin=0 next_checkin=0)
          newtmgr (prio=4 tid=4 runtime=0 cswcnt=6 stksize=1024 stkusage=585 last_checkin=0 next_checkin=0)
          task1 (prio=1 tid=5 runtime=0 cswcnt=551 stksize=1024 stkusage=83 last_checkin=0 next_checkin=0)
          task2 (prio=2 tid=6 runtime=0 cswcnt=551 stksize=1024 stkusage=85 last_checkin=0 next_checkin=0)
          idle (prio=255 tid=0 runtime=552525 cswcnt=44005 stksize=1024 stkusage=529 last_checkin=0 next_checkin=0)
          os_sanity (prio=254 tid=1 runtime=0 cswcnt=551 stksize=1024 stkusage=82 last_checkin=0 next_checkin=0)
          shell (prio=3 tid=2 runtime=0 cswcnt=20 stksize=1024 stkusage=142 last_checkin=0 next_checkin=0)
        $ newtmgr -c sim1 stat stat
        Return Code = 0
        Stats Name: stat
          s0: 1
```



### Using newtmgr with a remote target 

* First make sure the USB A-B type cable is connected to the ARM-USB-TINY-H debugger connector on the Olimex board. 

     Next go the to project directory and download the slinky project image to the flash of the Olimex board. You will see the executables in the `slinky1` directory created for the Olimex target to run the slinky project.

```no-highlight
        $ pwd
        /Users/<user>/dev/larva/project/slinky
        $ ls
        bin		egg.yml		slinky.yml	src
        $ ls bin
        slinky1		slinky_sim
        $ ls bin/slinky1
        slinky.elf	slinky.elf.bin	slinky.elf.cmd    slinky.elf.img    slinky.elf.lst    slinky.elf.map
        $ newt target download boot_olimex
        Downloading with /Users/<user>/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh
        $ newt target download slinky1
        Downloading with /Users/<user>/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh
```

   You can now disconnect the debugging cable from the board. You should see the green LED blinking. If not, try powercycling the board.
   
* Now you have to set up the serial connection from your computer to the Olimex board. Locate the PC6/USART6_TX (pin#3), PC7/USART6_RX (pin#4), and GND (pin#2) of the UEXT connector on the Olimex board. More information on the UEXT connector can be found at [https://www.olimex.com/Products/Modules/UEXT/](https://www.olimex.com/Products/Modules/UEXT/). The schematic of the board can be found at [https://www.olimex.com/Products/ARM/ST/STM32-E407/resources/STM32-E407_sch.pdf](https://www.olimex.com/Products/ARM/ST/STM32-E407/resources/STM32-E407_sch.pdf) for reference.

     ![Alt Layout - Serial Connection](pics/serial_conn.png)


	* Connect the female RX pin of the USB-TTL serial cable to the TX of the UEXT connector on the board. 
	* Connect the female TX pin of the USB-TTL serial cable to the RX of the UEXT connector on the board. 
	* Connect the GND pin of the USB-TTL serial cable to the GND of the UEXT connector on the board.


* Locate the serial connection established in the /dev directory of your computer. It should be of the type `tty.usbserial-<some identifier>`.

```no-highlight
        $ ls /dev/tty.usbserial-AJ03HAQQ 
        /dev/tty.usbserial-AJ03HAQQ
```

* You now have to define a connection profile using newtmgr. You can give it any name you want. The example below shows the connection profile being named as the very imaginative `olimex01`.

```no-highlight
        $ pwd
        /Users/<user>/dev/larva/project/slinky
        $ newtmgr conn add olimex01 type=serial connstring=/dev/tty.usbserial-AJ03HAQQ 
        Connection profile olimex01 successfully added
        $ newtmgr conn show
        Connection profiles: 
          sim1: type=serial, connstring='/dev/ttys007'
          olimex01: type=serial, connstring='/dev/tty.usbserial-AJ03HAQQ'
```

* Now go ahead and query the Olimex board to get responses back. The simplest command is the `echo` command to ask it to respond with the text you send it. 

```no-highlight
        $ newtmgr echo -c olimex01 hello
        {"r": "hello"}
        $ newtmgr image -c olimex01 list
        Images:
            0 : 11.22.33.44
        $ newtmgr -c olimex01 taskstats
        Return Code = 0
          shell (prio=3 tid=1 runtime=0 cswcnt=5 stksize=1024 stkusage=60 last_checkin=0 next_checkin=0)
          newtmgr (prio=4 tid=2 runtime=0 cswcnt=4 stksize=1024 stkusage=256 last_checkin=0 next_checkin=0)
          task1 (prio=1 tid=3 runtime=0 cswcnt=23 stksize=1024 stkusage=32 last_checkin=0 next_checkin=0)
          task2 (prio=2 tid=4 runtime=0 cswcnt=24 stksize=1024 stkusage=33 last_checkin=0 next_checkin=0)
          idle (prio=255 tid=0 runtime=23121 cswcnt=26 stksize=32 stkusage=16 last_checkin=0 next_checkin=0)
```










