## Project 2 - Blinky on additional boards

### Objective

The goal of this tutorial is to download a generic firmware skeleton ("bootstrap image") that applies to any hardware and then throw in additional applicable eggs to generate a build for a specific board. In the process you will be exposed to more Mynewt terms and Newt tool commands.

The following target hardware chips are covered:

* [STM32F303VC MCU](#stm32f303vc-mcu) from STMicroelectronics
* [nRF52 Series](#nrf52-series) from Nordic Semiconductors 


### STM32F303VC MCU

#### Hardware needed

* Discovery kit with STM32F303VC MCU
* Laptop running Mac OS


#### Step by Step Instructions to build image

* The first step is to download the generic skeleton of the project. The eggs constituting the skeleton are not hardware architecture specific. The skeleton is maintained as a nest in a separate repository on Apache. You know it is a nest because there is a nest.yml file. 

```no-highlight
        [user:~/dev]$ newt nest create test_project
        Downloading nest skeleton from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-tadpole.git... ok!
        Nest test_project successfully created in ~/dev/go/test_project
    
        [user:~/dev]$ cd test_project/
        [user:~/dev/test_project]$ ls
        README.md	compiler	hw		libs	nest.yml
```

* Next, the clutch of eggs named larva is added from the nest (also named larva) from another repository on Apache. This step simply downloads the clutch description file and does not actually install the eggs that constitute the clutch. The clutch description file (`clutch.yml`) will be used to check dependencies during the egg install to ensure completeness. It serves as a reference for all the eggs in the clutch that one can choose from and install.
```no-highlight
        [user:~/dev/test_project]$ newt nest add-clutch larva https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git
        Downloading clutch.yml from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git/master... ok!
        Verifying clutch.yml format...
        ok!
        Clutch larva successfully installed to Nest.
```

* The next step is to install relevant eggs from the larva nest on github. The instructions assume that you know what application or project you are interested in (the blinky application, in this case), what hardware you are using (STM32F3DISCOVERY board, in this case) and hence, what board support package you need. 

```no-highlight

        [user:~/dev/test_project]$ newt egg install project/blinky          
        Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/master... ok!
        Installing project/blinky
        Installing libs/console/full
        Installing libs/shell
        Installation was a success!
    
        [user:~/dev/test_project]$ newt egg install hw/bsp/stm32f3discovery
        Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/master... ok!
        Installing hw/bsp/stm32f3discovery
        Installing hw/mcu/stm/stm32f3xx
        Installing libs/cmsis-core
        Installing compiler/arm-none-eabi-m4
        Installation was a success!
```

* It's time to create a target for the project and define the target attributes. 
```no-highlight
        [user:~/dev/test_project]$ newt target create blink_f3disc
        Creating target blink_f3disc
        Target blink_f3disc successfully created!

        [user:~/dev/test_project]$ newt target set blink_f3disc project=blinky
        Target blink_f3disc successfully set project to blinky

        [user:~/dev/test_project]$ newt target set blink_f3disc bsp=hw/bsp/stm32f3discovery
        Target blink_f3disc successfully set bsp to hw/bsp/stm32f3discovery

        [user:~/dev/test_project]$ newt target set blink_f3disc compiler_def=debug
        Target blink_f3disc successfully set compiler_def to debug

        [user:~/dev/test_project]$ newt target set blink_f3disc compiler=arm-none-eabi-m4
        Target blink_f3disc successfully set compiler to arm-none-eabi-m4
        
        [user:~/dev/test_project]$ newt target set blink_f3disc arch=cortex_m4
        Target blink_f3disc successfully set arch to cortex_m4
        
        [user:~/dev/test_project]$ newt target show blink_f3disc
        blink_f3disc
	        arch: cortex_m4
	        project: blinky
	        bsp: hw/bsp/stm32f3discovery
	        compiler_def: debug
	        compiler: arm-none-eabi-m4
	        name: blink_f3disc
```        
* Next, you get to build the target and generate an executable that can then be uploaded to the board. The STM32F3DISCOVERY board includes an ST-LINK/V2 embedded debug tool interface that will be used to program/debug the board. To program the MCU on the board, simply plug in the two jumpers on CN4, as shown in the picture in red. If you want to learn more about the board you will find the User Manual at [http://www.st.com/st-web-ui/static/active/jp/resource/technical/document/user_manual/DM00063382.pdf](http://www.st.com/st-web-ui/static/active/jp/resource/technical/document/user_manual/DM00063382.pdf)

* ![STMdiscovery](pics/STM32f3discovery_connector.png)

```no-highlight  
        [user:~/dev/test_project]$ newt target build blink_f3disc
        Building target blink_f3disc (project = blinky)
        Compiling case.c
        Compiling suite.c
        Compiling testutil.c
        Compiling testutil_arch_arm.c
        Archiving libtestutil.a
        Compiling os.c
        Compiling os_callout.c
        Compiling os_eventq.c
        Compiling os_heap.c
        Compiling os_mbuf.c
        Compiling os_mempool.c
        Compiling os_mutex.c
        Compiling os_sanity.c
        Compiling os_sched.c
        Compiling os_sem.c
        Compiling os_task.c
        Compiling os_time.c
        Compiling os_arch_arm.c
        Assembling HAL_CM4.s
        Assembling SVC_Table.s
        Archiving libos.a
        Compiling hal_gpio.c
        Compiling stm32f3xx_hal_gpio.c
        Archiving libstm32f3xx.a
        Compiling cmsis_nvic.c
        Compiling libc_stubs.c
        Compiling os_bsp.c
        Compiling sbrk.c
        Compiling system_stm32f3xx.c
        Assembling startup_stm32f303xc.s
        Archiving libstm32f3discovery.a
        Compiling main.c
        Building project blinky
        Linking blinky.elf
        Successfully run!
```

* Finally, you have to download the image on to the board. You will see a blue light start to blink.
```no-highlight
        [user:~/dev/test_project]$ newt target download blink_f3disc
        Downloading with /Users/user/dev/test_project/hw/bsp/stm32f3discovery/stm32f3discovery_download.sh
```


### nRF52 Series


#### Hardware needed

* nRF52 Development Kit
* Laptop running Mac OS


#### Step by Step Instructions to build image

* The first step is to download the generic skeleton of the project. The eggs installed are not hardware architecture specific.
```no-highlight
        []user@~/dev]$ newt nest create nordic_blinky
        Downloading nest skeleton from https://www.github.com/mynewt/tadpole... ok!
        Nest nordic_blinky successfully created in ~dev/nordic_blinky
        
        user@~/dev$ cd nordic_blinky/
```

* Then, the clutch of eggs named larva is added from the nest (also named larva) on the github. This step simply downloads the clutch description file and does not actually install the eggs that constitute the clutch. The clutch description file (`clutch.yml`) will be used to check dependencies during the egg install to ensure completeness. It serves as a reference for all the eggs in the clutch that one can choose from and install.
```no-highlight
        []user@~/dev/nordic_blinky]$ newt nest add-clutch larva https://github.com/mynewt/larva
        Downloading clutch.yml from https://github.com/mynewt/larva/master... ok!
        Verifying clutch.yml format...ok!
        Clutch larva successfully installed to Nest.
```
* The next step is to install relevant eggs from the larva nest on github. The instructions assume that you know what application or project you are interested in (the blinky application, in this case), what hardware you are using (STM32F3DISCOVERY board, in this case) and hence, what board support package you need. 
```no-highlight
        [user@~/dev/nordic_blinky]$ newt egg install project/blinky 
        Downloading larva from https://github.com/mynewt/larva//master... ok!
        Installing project/blinky
        Installation was a success!

    
        [user@~/dev/nordic_blinky]$ newt egg install hw/bsp/nrf52pdk
        Downloading larva from https://github.com/mynewt/larva//master... ok!
        Installing hw/bsp/nrf52pdk
        Installing hw/mcu/nordic/nrf52xxx
        Installing libs/cmsis-core
        Installing compiler/arm-none-eabi-m4
        Installation was a success!
```

* It's time to create a target for the project and define the target attributes. 
```no-highlight
        [user@~/dev/nordic_blinky]$ newt target create blink_nordic
        Creating target blink_nordic
        Target blink_nordic successfully created!
        [user@~/dev/nordic_blinky]$ newt target set blink_nordic project=blinky
        Target blink_nordic successfully set project to blinky
        [user@~/dev/nordic_blinky]$ newt target set blink_nordic bsp=hw/bsp/nrf52pdk
        Target blink_nordic successfully set bsp to hw/bsp/nrf52pdk
        [user@~/dev/nordic_blinky]$ newt target set blink_nordic compiler_def=debug
        Target blink_nordic successfully set compiler_def to debug
        [user@~/dev/nordic_blinky]$ newt target set blink_nordic compiler=arm-none-eabi-m4
        Target blink_nordic successfully set compiler to arm-none-eabi-m4
        [user@~/dev/nordic_blinky]$ newt target set blink_nordic arch=cortex_m4
        Target blink_nordic successfully set arch to cortex_m4
        [user@~/dev/nordic_blinky]$ newt target show
        blink_nordic
        	compiler: arm-none-eabi-m4
	    	name: blink_nordic
	    	arch: cortex_m4
	    	project: blinky
	    	bsp: hw/bsp/nrf52pdk
	    	compiler_def: debug
```
        
* Finally, you get to build the target and generate an executable that can now be uploaded to the board via the on-board SEGGER J-Link debugger. 
```no-highlight
        [user@~/dev/nordic_blinky]$ newt target build blink_nordic
        Building target blink_nordic (project = blinky)
        Compiling case.c
        Compiling suite.c
        Compiling testutil.c
        Compiling testutil_arch_arm.c
        Archiving libtestutil.a
        Compiling os.c
        Compiling os_callout.c
        Compiling os_eventq.c
        Compiling os_heap.c
        Compiling os_mbuf.c
        Compiling os_mempool.c
        Compiling os_mutex.c
        Compiling os_sanity.c
        Compiling os_sched.c
        Compiling os_sem.c
        Compiling os_task.c
        Compiling os_time.c
        Compiling os_arch_arm.c
        Assembling HAL_CM4.s
        Assembling SVC_Table.s
        Archiving libos.a
        Compiling hal_cputime.c
        Compiling hal_gpio.c
        Compiling hal_uart.c
        Archiving libnrf52xxx.a
        Compiling cmsis_nvic.c
        Compiling hal_bsp.c
        Compiling libc_stubs.c
        Compiling os_bsp.c
        Compiling sbrk.c
        Compiling system_nrf52.c
        Assembling gcc_startup_nrf52.s
        Archiving libnrf52pdk.a
        Compiling main.c
        Building project blinky
        Linking blinky.elf
        Successfully run!
```
* In order to be able to communicate with the SEGGER J-Link debugger on the dev board, you have to download and install the J-Link GDB Server software on to your laptop. You may download the "Software and documentation pack for Mac OS X" from [https://www.segger.com/jlink-software.html](https://www.segger.com/jlink-software.html). The command line version of the server is used in the steps below. 

* Open a new terminal and start a J-Link session.
```no-highlight
        [user@~/dev/nordic_blinky/project/blinky/bin]$ which JLinkGDBServer
        /usr/local/bin/JLinkGDBServer
        [user@~/dev/nordic_blinky/project/blinky/bin]$ JLinkGDBServer -if SWD
        SEGGER J-Link GDB Server V5.02f Command Line Version

        JLinkARM.dll V5.02f (DLL compiled Oct  2 2015 20:55:03)

        -----GDB Server start settings-----
        GDBInit file:                  none
        GDB Server Listening port:     2331
        SWO raw output listening port: 2332
        Terminal I/O port:             2333
        Accept remote connection:      yes
        Generate logfile:              off
        Verify download:               off
        Init regs on start:            off
        Silent mode:                   off
        Single run mode:               off
        Target connection timeout:     0 ms
        ------J-Link related settings------
        J-Link Host interface:         USB
        J-Link script:                 none
        J-Link settings file:          none
        ------Target related settings------
        Target device:                 unspecified
        Target interface:              SWD
        Target interface speed:        1000kHz
        Target endian:                 little

        Connecting to J-Link...
        J-Link is connected.
        Firmware: J-Link OB-SAM3U128-V2-NordicSemi compiled Aug 28 2015 19:26:24
        Hardware: V1.00
        S/N: 682371959
        Checking target voltage...
        Target voltage: 3.30 V
        Listening on TCP/IP port 2331
        Connecting to target...Connected to target
        Waiting for GDB connection...Connected to 127.0.0.1
```

* You need a configuration file for the GDB session to be opened correctly and the image ("blinky.elf") you built for this target downloaded to flash. A sample config script is given below. Alternatively, you could choose to type each command at the gdb prompt.
```no-highlight
         [user@~/dev/nordic_blinky/project/blinky/bin/blink_nordic]$ cat jlink-gdb.cfg 
         echo ***Setting up the environment for debugging gdb.***\n
         set complaints 1
         set prompt (gdb) 
         set endian little
         echo \n*** Set target charset ASCII\n
         set target-charset ASCII
         echo \n*** Connecting over port #2331 ***\n
         target remote localhost:2331
         echo \n*** Enable flash write and set device to nrf52 ***\n
         monitor flash download=1
         monitor flash device=nRF52
         echo \n*** loading blinky.elf ***\n
         load ~/dev/nordic_blinky/project/blinky/bin/blink_nordic/blinky.elf 
         symbol-file ~/dev/nordic_blinky/project/blinky/bin/blink_nordic/blinky.elf
         echo \n*** Resetting target ***\n
         monitor reset
         echo \n*** Halting target ***\n
         monitor halt
```
* Start the gdb session and monitor that it loads the image, resets the target, and halts for a command to continue. 
```no-highlight
        [user@~/dev/nordic_blinky/project/blinky/bin/blink_nordic]$ arm-none-eabi-gdb -x ~/dev/nordic_blinky/project/blinky/bin/blink_nordic/jlink-gdb.cfg
        
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
        Type "apropos word" to search for commands related to "word".
        
        ***Setting up the environment for debugging gdb.***
        The target is assumed to be little endian

        *** Set target charset ASCII

        *** Connecting over port #2331 ***
        0x00003c34 in ?? ()

        *** Enable flash write and set device to nrf52 ***
        Flash download enabled
        Selecting device: nRF52

        *** loading blinky.elf ***
        Loading section .text, size 0x5c84 lma 0x0
        Loading section .ARM.extab, size 0x24 lma 0x5c84
        Loading section .ARM.exidx, size 0xd8 lma 0x5ca8
        Loading section .data, size 0x8f8 lma 0x5d80
        Start address 0x48c, load size 26232
        Transfer rate: 12808 KB/sec, 2914 bytes/write.
        During symbol reading, unexpected overlap between:
         (A) section `.text' from `~/dev/nordic_blinky/project/blinky/bin/blink_nordic/blinky.elf' [0x0, 0x5c84)
         (B) section `*COM*' from `~/dev/nordic_blinky/project/blinky/bin/blink_nordic/blinky.elf' [0x0, 0x0).
        Will ignore section B.

        *** Resetting target ***
        Resetting target

        *** Halting target ***
```
* Type 'c' to continue. The LED on the board will start to blink. You will also see some activity in the terminal showing the open J-Link GDB server connection. The LED will continue to blink after you quit out of that connection.
```no-highlight
        (gdb) c
        Continuing.
```





