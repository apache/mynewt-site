## Blinky, the First Project

### Objective

To use available packages from the default application repository for Mynewt to make an LED on a target board blink. We call it *Project Blinky*. The goals of this tutorial are threefold:
 
1. Set up the environment on your computer to use Mynewt OS and newt tool. 
2. Download packages for building and testing the project [on a simulated target](#building-test-code-on-simulator).
3. Download packages and use tools to create a runtime image for a board to make its LED blink. You have two choices here:
    * [Download an image to SRAM](#using-sram-to-make-led-blink), or 
    * [Download it to flash](#using-flash-to-make-led-blink).

** Time Requirement**: Allow yourself a couple of hours for this project if you are relatively new to embedded systems and playing with development boards. Those jumpers can be pesky!


### What you need

1. STM32-E407 development board from Olimex. You can order it from [http://www.mouser.com](http://www.mouser.com/ProductDetail/Olimex-Ltd/STM32-E407/?qs=UN6GZl1KCcit6Ye0xmPO4A%3D%3D), [http://www.digikey.com](http://www.digikey.com/product-detail/en/STM32-E407/1188-1093-ND/3726951), and other places.
2. ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
3. USB A-B type cable to connect the debugger to your personal computer
4. Personal Computer

The instructions assume the user is using a Bourne-compatible shell (e.g. bash or zsh) on your computer. The given instructions have been tested with the following releases of operating systems:

* Mac: OS X Yosemite Version 10.10.5
* Linux: Ubuntu 14.10 (Utopic Unicorn)


### Access to the Apache repo

* Get an account on Apache. You do not need a committer account to view the website or clone the repository. You only need a committer account to push changes to it.

* The latest codebase for the Mynewt OS is on the master branch at https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git

* The latest codebase for the Newt tool is on the master branch at https://git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git . You do not need to download source code and build the newt tool for this project. You will simply use the available executable instead.


The following shows how to clone a Mynewt OS code repository:

* Non Committers
```no-highlight
        $ git clone http://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git
```
* Committers
```no-highlight
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git
```


### Setting up toolchain if you have a Mac


* You have to install gcc/libc that can produce 32-bit executables. Use homebrew to install gcc.
```no-highlight
        $ brew install gcc
        ...
        ...
        ==> Summary
        🍺  /usr/local/Cellar/gcc/5.2.0: 1353 files, 248M
```

* ARM maintains a pre-built GNU toolchain with a GCC source branch targeted at Embedded ARM Processors namely Cortex-R/Cortex-M processor families. Install the PX4 Toolchain and check the version installed. Make sure that the symbolic link installed by Homebrew points to the correct version of the debugger. If not, you can either change the symbolic link using the "ln -f -s" command or just go ahead and try with the version it points to!
```no-highlight
        $ brew tap PX4/homebrew-px4
        $ brew update
        $ brew install gcc-arm-none-eabi-49
        $ arm-none-eabi-gcc --version  
        arm-none-eabi-gcc (GNU Tools for ARM Embedded Processors) 4.9.3 20150529 (release) [ARM/embedded-4_9-branch revision 224288]
        Copyright (C) 2014 Free Software Foundation, Inc.
        This is free software; see the source for copying conditions.  There is NO
        warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
        $ ls -al /usr/local/bin/arm-none-eabi-gdb
        lrwxr-xr-x  1 aditihilbert  admin  69 Sep 22 17:16 /usr/local/bin/arm-none-eabi-gdb -> /usr/local/Cellar/gcc-arm-none-eabi-49/20150609/bin/arm-none-eabi-gdb
```
  Note: If no version is specified, brew will install the latest version available. MynewtOS will eventually work with multiple versions available including the latest releases. However, at present we have tested only with this version and recommend it for getting started. 
    
* You have to install OpenOCD (Open On-Chip Debugger) which is an open-source software that will allow you to interface with the JTAG debug connector/adaptor for the Olimex board. It lets you program, debug, and test embedded target devices which, in this case, is the Olimex board. Use brew to install it. Brew adds a simlink /usr/local/bin/openocd to the openocd directory in the Cellar. For more on OpenOCD go to [http://openocd.org](http://openocd.org).
```no-highlight
        $ brew install open-ocd
        $ which openocd
        /usr/local/bin/openocd
        $ ls -l $(which openocd)
        lrwxr-xr-x  1 <user>  admin  36 Sep 17 16:22 /usr/local/bin/openocd -> ../Cellar/open-ocd/0.9.0/bin/openocd
```
* Proceed to the [Building test code on simulator](#building-test-code-on-simulator) section.


### Setting up toolchain if you have Linux 


* You have to install gcc / libc that can produce 32-bit executables. You can install these as follows: 
```no-highlight
        $ sudo apt-get install gcc-multilib libc6-i386
```        
* For the LED project on the Olimex hardware, you have to install gcc for AM 4.9.3.  This package can be installed with apt-get as documented below. The steps are explained in depth at [https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded](https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded).
```no-highlight
        $ sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi 
        $ sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded 
        $ sudo apt-get update 
        $ sudo apt-get install gcc-arm-none-eabi
```
* And finally, you have to install OpenOCD (Open On-Chip Debugger) which is an open-source software that will allow you to interface with the JTAG debug connector/adaptor for the Olimex board. It lets you program, debug, and test embedded target devices which, in this case, is the Olimex board. You have to acquire OpenOCD 0.8.0. 

    If you are running Ubuntu 15.x, then you are in luck and you can simply run: 
```no-highlight
        $ sudo apt-get install openocd 
```
  Other versions of Ubuntu may not have the correct version of openocd available.  In this case, you should download the openocd 0.8.0 package from [https://launchpad.net/ubuntu/vivid/+source/openocd](https://launchpad.net/ubuntu/vivid/+source/openocd). The direct link to the amd64 build is [http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb](http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb). 

* Proceed to the [Building test code on simulator](#building-test-code-on-simulator) section.

### Download newt tool

Insert the loaction of the newt tool executable.

### Try building test code on simulator 


1.  Clone the larva repository from the Apache git repository into a local directory named `larva`.

```no-highlight
        $ cd ~/dev 
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git larva
        $ ls
        go	larva
        $ ls larva
        DISCLAIMER	NOTICE		app.yml		compiler	hw		net		project		sys
        LICENSE		README.md	autotargets	fs  libs	pkg-list.yml	scripts
``` 
  
2\.  Create a target using the newt tool. 

```no-highlight
        $ cd larva
        $ newt target create sim_test
        Creating target sim_test
        Target sim_test sucessfully created!
        $ newt target show
        sim_test
	        name: sim_test
	        arch: sim
```

3\. Now continue to populate and build out the sim project.
```no-highlight
        $ newt target set sim_test project=test
        Target sim_test successfully set project to test
        $ newt target set sim_test compiler_def=debug
        Target sim_test successfully set compiler_def to debug
        $ newt target set sim_test bsp=hw/bsp/native
        Target sim_test successfully set bsp to hw/bsp/native
        $ newt target set sim_test compiler=sim
        Target sim_test successfully set compiler to sim
        $ newt target show sim_test
        sim_test
			arch=sim
	     	bsp=hw/bsp/native
	     	compiler=sim
	     	compiler_def=debug
	     	name=sim_test
	     	project=test
```
        
4\. Configure newt to use the gnu build tools native to OS X or linux. In order for sim to work properly, it needs to be using 32-bit gcc (gcc-5). Replace 
~/dev/larva/compiler/sim/compiler.yml with the compiler/sim/osx-compiler.yml or linux-compiler.yml file, depending on the system. On a Windows machine follow the instruction for the Linux machine as you are running commands in a Linux VM.

  For a Mac OS X environment:
```no-highlight
        $ cp compiler/sim/osx-compiler.yml compiler/sim/compiler.yml 
```        
  For a Linux machine:
```no-highlight        
        $ cp compiler/sim/linux-compiler.yml compiler/sim/compiler.yml
```

5\. Next, build the packages for the sim project using the newt tool. You can specify the VERBOSE option if you want to see the gory details. 

```no-highlight
        $ newt target build sim_test
        Building target sim_test (project = test)
        ...
        ...
        Successfully run!
```
 You can specify the VERBOSE option if you want to see the gory details.
```no-highlight
        $newt -l VERBOSE target build sim_test
        2015/09/29 09:46:12 [INFO] Building project test
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//bootutil...
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//cmsis-core...
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//ffs..
        ...
        Successfully run!
```
6\. Try running the test suite executable inside this project and enjoy your first successful test!
```no-highlight
        $ project/test/bin/sim_test/test.elf
        [pass] os_mempool_test_suite/os_mempool_test_case
        [pass] os_mutex_test_suite/os_mutex_test_basic
        [pass] os_mutex_test_suite/os_mutex_test_case_1
        ...
        ...
        [pass] cbmem_test_suite/cbmem_test_case_3
```

### Using SRAM to make LED blink

You are here because you want to build an image to be run from internal SRAM on the Olimex board.

#### Preparing the Software

* Make sure the PATH environment variable includes the $HOME/dev/go/bin directory. 

* If you have cloned the larva repository for the simulator test in the previous section you can skip this step. Otherwise, you have to create a repository for the project. Go to ~/dev and clone the larva repository from the apache git repository into a local directory named `larva`.

```no-highlight
        $ cd ~/dev 
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git larva
        $ ls
        go	larva
        $ ls larva
        DISCLAIMER	NOTICE		app.yml		compiler	hw		net		project		sys
        LICENSE		README.md	autotargets	fs  libs	pkg-list.yml	scripts
``` 
    
* You now have to go to the ~dev/larva directory and build out a second project inside larva (the first one being the sim project). The project name is "blinky", in keeping with the objective. Starting with the target name, you have to specify the different aspects of the project to pull the appropriate packages and build the right bundle or list for the board. In this case that means setting the architecture (arch), compiler, board support package (bsp), project, and compiler mode.

    Remember to prefix each command with "newtvm" if you are executing the newt command in a Linux virtual machine on your Windows box!

```no-highlight
        $ newt target create blinky
        Creating target blinky
        Target blinky sucessfully created!
        $ newt target set blinky arch=cortex_m4
        Target blinky successfully set arch to arm
        $ newt target set blinky compiler=arm-none-eabi-m4
        Target blinky successfully set compiler to arm-none-eabi-m4
        $ newt target set blinky project=blinky
        Target blinky successfully set project to blinky
        $ newt target set blinky compiler_def=debug
        Target blinky successfully set compiler_def to debug
        $ newt target set blinky bsp=hw/bsp/olimex_stm32-e407_devboard
        Target blinky successfully set bsp to hw/bsp/olimex_stm32-e407_devboard
        $ newt target show blinky
        blinky
	    	arch=cortex_m4
	    	bsp=hw/bsp/olimex_stm32-e407_devboard
	    	compiler=arm-none-eabi-m4
	    	compiler_def=debug
	    	name=blinky
	    	project=blinky
```

* Now you have to build the image. The linker script within the `hw/bsp/olimex_stm32-e407_devboard` package builds an image for flash memory by default. Since you want an image for the SRAM, you need to switch that script with `run_from_sram.ld` in order to get the package to produce an image for SRAM. <font color="red"> We are working on making it easier to specify where the executable will be run from for a particular project and automatically choose the correct linker scripts and generate the appropriate image. It will be specified as a project identity e.g. bootloader, RAM, flash (default) and the target will build accordingly. </font>. 

    Once the target is built, you can find the executable "blinky.elf" in the project directory at ~/dev/larva/project/blinky/bin/blinky. It's a good idea to take a little time to understand the directory structure.
```no-highlight
        $ cd ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        $ diff olimex_stm32-e407_devboard.ld run_from_sram.ld
        (some diff will be displayed)
        $ cp run_from_sram.ld olimex_stm32-e407_devboard.ld
        $ cd ~/dev/larva/project/blinky/
        $ newt target build blinky
        Building target blinky (project = blinky)
        Compiling case.c
        Compiling suite.c
        ...
        Successfully run!
        $ ls bin/blinky
        blinky.elf	blinky.elf.bin	blinky.elf.cmd  blinky.elf.lst  blinky.elf.map
```

* Check that you have all the scripts needed to get OpenOCD up and talking with the project's specific hardware. Depending on your system (Ubuntu, Windows) you may already have the scripts in your `/usr/share/openocd/scripts/ ` directory as they may have been part of the openocd download. If yes, you are all set and can proceed to preparing the hardware.

    Otherwise check the `~/dev/larva/hw/bsp/olimex_stm32-e407_devboard` directory for a file named `f407.cfg`. That is the config we will use to talk to this specific hardware using OpenOCD. You are all set if you see it.
```no-highlight
        $ ls ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        bin		include		olimex_stm32-e407_devboard_download.sh	run_from_loader.ld
        boot-olimex_stm32-e407_devboard.ld	olimex_stm32-e407_devboard.ld	pkg.yml		run_from_sram.ld
        f407.cfg		olimex_stm32-e407_devboard_debug.sh	run_from_flash.ld			src
```
 
#### Preparing the hardware to boot from embedded SRAM

* Locate the boot jumpers on the board.
![Alt Layout - Top View](pics/topview.png)
![Alt Layout - Bottom View](pics/bottomview.png)

* B1_1/B1_0 and B0_1/B0_0 are PTH jumpers which can be moved relatively easy. Note that the markings on the board may not always be accurate. Always refer to the manual for the correct positioning of jumpers in case of doubt. The two jumpers must always be moved together – they are responsible for the boot mode if bootloader is present. The board can search for bootloader on three places – User Flash Memory, System Memory or the Embedded SRAM. We will configure it to boot from SRAM by jumpering B0_1 and B1_1.

* Connect USB-OTG#2 in the picture above to a USB port on your computer (or a powered USB hub to make sure there is enough power available to the board). 

* The red PWR LED should be lit. 

* Connect the JTAG connector to the SWD/JTAG interface on the board. The other end of the cable should be connected to the USB port or hub of your computer.



#### Let's Go!

* Make sure you are in the blinky project directory with the blinky.elf executable. Run the debug command in the newt tool. You should see some status messages are shown below. There is an inbuilt `-c "reset halt"` flag that tells it to halt after opening the session.
```no-highlight
        $ cd ~/dev/larva/project/blinky/bin/blinky
        $ newt target debug blinky
        Debugging with /Users/aditihilbert/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_debug.sh blinky
        Debugging /Users/aditihilbert/dev/larva/project/blinky/bin/blinky/blinky.elf
        GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
        Copyright (C) 2014 Free Software Foundation, Inc.
        License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
        ...
        (info)
        ...
        target state: halted
        target halted due to debug-request, current mode: Thread 
        xPSR: 0x01000000 pc: 0x20000250 msp: 0x10010000
        Info : accepting 'gdb' connection from 3333
        Info : device id = 0x10036413
        Info : flash size = 1024kbytes
        Reset_Handler () at startup_STM32F40x.s:199
        199	    ldr    r1, =__etext
```

   Check the value of the msp (main service pointer) register. If it is not 0x10010000 as indicated above, you will have to manually set it after you open the gdp tool and load the image on it. 
   
```no-highlight
        (gdb) set $msp=0x10010000
```
   Now load the image and type "c" or "continue" from the GNU debugger. 

```no-highlight           
        (gdb) load ~/dev/larva/project/blinky/bin/blinky/blinky.elf         
        Loading section .text, size 0x4294 lma 0x20000000
        Loading section .ARM.extab, size 0x24 lma 0x20004294
        Loading section .ARM.exidx, size 0xd8 lma 0x200042b8
        Loading section .data, size 0x874 lma 0x20004390
        Start address 0x20000250, load size 19460
        Transfer rate: 81 KB/sec, 2432 bytes/write.
        (gdb) c
        Continuing.
```   
      
* Voilà! The board's LED should be blinking at 1 Hz.

### Using flash to make LED blink

You are here because you want to build an image to be run from flash memory on the Olimex board.

* Configure the board to boot from flash by moving the two jumpers together to B0_0 and B1_0. Refer to the pictures of the board under the section titled ["Preparing the hardware to boot from embedded SRAM"](#preparing-the-hardware-to-boot-from-embedded-sram).

   You will have to reset the board once the image is uploaded to it.
        
* If you skipped the first option for the project [(downloading an image to SRAM)](#using-sram-to-make-led-blink), then skip this step. Otherwise, continue with this step. 

   By default, the linker script (`olimex_stm32-e407_devboard.ld`) is configured to run from bootloader and flash. However, if you first ran the image from SRAM you had changed `olimex_stm32-e407_devboard.ld` to match `run_from_sram.ld`. You will therefore return to defaults with `olimex_stm32-e407_devboard.ld` linker script matching the contents of 'run_from_loader.ld'. Return to the project directory.
```no-highlight
        $ cd ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        $ diff olimex_stm32-e407_devboard.ld run_from_sram.ld
        $ diff olimex_stm32-e407_devboard.ld run_from_loader.ld
        (some diff will be displayed)
        $ cp run_from_loader.ld olimex_stm32-e407_devboard.ld
        $ cd ~/dev/larva/project/blinky/bin/blinky
```

* In order to run the image from flash, you need to build the bootloader as well. The bootloader does the initial bring up of the Olimex board and then transfers control to the image stored at a location in flash known to it. The bootloader in turn requires the bin2image tool to check the image header for version information, CRC checks etc. So, we will need to build these two additional targets (bootloader and bin2img).

   Let's first create bin2img:
```no-highlight
        $ newt target create bin2img
        Creating target bin2img
        Target bin2img successfully created!
        $ newt target set bin2img arch=sim
        Target bin2img successfully set arch to sim
        $ newt target set bin2img compiler=sim
        Target bin2img successfully set compiler to sim
        $ newt target set bin2img project=bin2img
        Target bin2img successfully set project to bin2img
        $ newt target set bin2img compiler_def=debug
        Target bin2img successfully set compiler_def to debug
        $ newt target set bin2img bsp=hw/bsp/native
        Target bin2img successfully set bsp to hw/bsp/native
        $ newt target show bin2img
        bin2img
        		arch=sim
	    		bsp=hw/bsp/native
	    		compiler=sim
	    		compiler_def=debug
	    		name=bin2img
	    		project=bin2img
```
   And then let's create boot_olimex:
```no-highlight
        $ newt target create boot_olimex
        Creating target boot_olimex
        Target boot_olimex successfully created!
        $ newt target set boot_olimex arch=cortex_m4
        Target boot_olimex successfully set arch to cortex_m4
        $ newt target set boot_olimex compiler=arm-none-eabi-m4
        Target boot_olimex successfully set compiler to arm-none-eabi-m4
        $ newt target set boot_olimex project=boot
        Target boot_olimex successfully set project to boot
        $ newt target set boot_olimex compiler_def=optimized
        Target boot_olimex successfully set compiler_def to optimized
        $ newt target set boot_olimex bsp=hw/bsp/olimex_stm32-e407_devboard
        Target boot_olimex successfully set bsp to hw/bsp/olimex_stm32-e407_devboard
        $ newt target show boot_olimex
        boot_olimex
        		arch=cortex_m4
	    		bsp=hw/bsp/olimex_stm32-e407_devboard
	    		compiler=arm-none-eabi-m4
	    		compiler_def=optimized
	    		name=boot_olimex
	    		project=boot
```
* Let's build all the three targets now.
```no-highlight
        $ newt target build bin2img
        Building target bin2img (project = bin2img)
        Building project bin2img
        ...
        Successfully run!
        $ newt target build boot_olimex
        Building target boot_olimex (project = boot)
        Building project boot
        ...
        Successfully run!
        $ newt target build blinky
        Building target blinky (project = blinky)
        Building project blinky
        Successfully run!
```

* Go to the project directory and download the bootloader and the image to flash ... in a flash! 
```no-highlight
        $ cd ~/dev/larva/project/blinky/bin/blinky
        $ newt target download boot_olimex
        Downloading with ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh
        $ newt target download blinky
        Downloading with ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh
```

* The LED should be blinking!

* But wait...let's double check that it is indeed booting from flash and making the LED blink from the image in flash. Pull the USB cable off the Olimex JTAG adaptor. The debug connection to the JTAG port is now severed. Next power off the Olimex board by pulling out the USB cable from the board. Wait for a couple of seconds and plug the USB cable back to the board. 

   The LED light will start blinking again. Success!
  
   Note #1: If you want to download the image to flash and a gdb session opened up, use `newt target debug blinky` instead of `newt target download blinky`.
```no-highlight     
        $ newt target debug blinky
        Debugging with ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_debug.sh blinky
        Debugging ~/dev/larva/project/blinky/bin/blinky/blinky.elf
        GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
        Copyright (C) 2014 Free Software Foundation, Inc.
        License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
        ...
        (info)
        ...
        target state: halted
        target halted due to debug-request, current mode: Thread 
        xPSR: 0x01000000 pc: 0x08000250 msp: 0x10010000
        Info : accepting 'gdb' connection from 3333
        Info : device id = 0x10036413
        Info : flash size = 1024kbytes
        Reset_Handler () at startup_STM32F40x.s:199
        199	    ldr    r1, =__etext
        (gdb)
```
    
   Note #2: If you want to erase the flash and load the image again you may use the following commands from within gdb. `flash erase_sector 0 0 x` tells it to erase sectors 0 through x. When you ask it to display (in hex notation) the contents of the sector starting at location 'lma' you should therefore see all f's. The memory location 0x8000000 is the start or origin of the flash memory contents and is specified in the olimex_stm32-e407_devboard.ld linker script. The flash memory locations is specific to the processor.
```no-highlight         
        (gdb) monitor flash erase_sector 0 0 4
        erased sectors 0 through 4 on flash bank 0 in 2.296712s
        (gdb) monitor mdw 0x08000000 16
        0x08000000: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff 
        (0x08000020: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff 
        (0x08000000: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff 
        (0x08000020: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff         
        (gdb) monitor flash info 0
```
