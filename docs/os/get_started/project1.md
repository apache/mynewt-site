## Blinky, Your Hello World!

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) on a target board. Once built using *newt* tool, this application will blink the LED lights on the target board. Fun stuff!

This tutorial will guide to achieve the following: 

1. Set up the environment on your computer to use Mynewt OS and newt tool. 
2. Download packages for building and testing the project [on a simulated target](#build-test-code-on-simulator).
3. Download packages and use tools to create a runtime image for a board to make its LED blink. You have two choices here:
    * [Download an image to SRAM](#use-sram-to-make-led-blink), or 
    * [Download it to flash](#use-flash-to-make-led-blink).

** Time Requirement**: Allow yourself a couple of hours for this project if you are relatively new to embedded systems and playing with development boards. Those jumpers can be pesky!


### What you need

1. STM32-E407 development board from Olimex. You can order it from [http://www.mouser.com](http://www.mouser.com/ProductDetail/Olimex-Ltd/STM32-E407/?qs=UN6GZl1KCcit6Ye0xmPO4A%3D%3D), [http://www.digikey.com](http://www.digikey.com/product-detail/en/STM32-E407/1188-1093-ND/3726951), and other places.
2. ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
3. USB A-B type cable to connect the debugger to your personal computer
4. Personal Computer with Mac OS (Mac: OS X Yosemite Version 10.10.5) or Linux box (Ubuntu 14.10: Utopic Unicorn)
5. An account on Github repository and *git* installed on your computer.

Also, we assume that you're familiar with UNIX shells.

Let's gets started!

### Set up toolchain for Mac


* Install gcc/libc that will produce 32-bit executables, using *brew*. 
```
        $ brew install gcc
        ...
        ...
        ==> Summary
        🍺  /usr/local/Cellar/gcc/5.2.0: 1353 files, 248M
```

* Install the PX4 Toolchain and check the version installed. ARM maintains a pre-built GNU toolchain with a GCC source branch targeted at Embedded ARM Processors, namely Cortex-R/Cortex-M processor families. After installing, ensure that the symbolic link installed by Homebrew points to the correct version of the debugger. If not, you can either change the symbolic link using the "ln -f -s" command or just go ahead and try with the version it points to!
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
  Note: If no version is specified, brew will install the latest version available. Mynewt OS will eventually work with multiple versions available, including the latest releases. However, at present we have tested only with this version and recommend it for getting started. 
    
* Install OpenOCD (Open On-Chip Debugger), which is an open-source software that will allow you to interface with the JTAG debug connector/adaptor for the Olimex board, debug, and test embedded target devices, including the Olimex board. For more on OpenOCD go to [http://openocd.org](http://openocd.org).
```no-highlight
        $ brew install open-ocd
        $ which openocd
        /usr/local/bin/openocd
        $ ls -l $(which openocd)
        lrwxr-xr-x  1 <user>  admin  36 Sep 17 16:22 /usr/local/bin/openocd -> ../Cellar/open-ocd/0.9.0/bin/openocd
```

At this point you have installed all the necessary software to build and test code on a simluator for the Mac OS.
* Proceed to the [Build test code on simulator](#build-test-code-on-simulator) section.


### Set up toolchain for Linux 


* Install gcc/ ibc that will produce 32-bit executables: 
```no-highlight
        $ sudo apt-get install gcc-multilib libc6-i386
```        
* For the LED project on the Olimex hardware, you should install gcc for AM 4.9.3.  This package can be installed with apt-get as documented below. The steps are explained in depth at [https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded](https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded).
```no-highlight
        $ sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi 
        $ sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded 
        $ sudo apt-get update 
        $ sudo apt-get install gcc-arm-none-eabi
```
* And finally, install OpenOCD (Open On-Chip Debugger), which is an open-source software that will allow you to interface with the JTAG debug connector/adaptor for the Olimex board, debug your program and test embedded target devices which, including the Olimex board.

    If you are running Ubuntu 15.x, then you are in luck and you can simply run: 
```no-highlight
        $ sudo apt-get install openocd 
```
 For this project, you should download the openocd 0.8.0 package from [https://launchpad.net/ubuntu/vivid/+source/openocd](https://launchpad.net/ubuntu/vivid/+source/openocd). The direct link to the amd64 build is [http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb](http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb). 

* At this point you have installed all the necessary software to build and test code on a simluator for Linux. Proceed to the [Build test code on simulator](#build-test-code-on-simulator) section.

### Install newt tool

There are two ways to install the *newt* tool on your computer. The easy way (and the recommeded way for this project) is to download the respective *newt* binaries from the links below:
* Mac OS 
* Linux

Include the *newt* in your $PATH.

Or if you're an adventurer then you can set up the environment on your computer, install the Go language, and build the *newt* tool from source as explained in the tutorials in the Newt Tool Manual. See [Install newt from source on Mac](../../newt/newt_mac.md) and [Install newt from source on Linux](../../newt/newt_linux.md).

### Build test code on simulator 


1\. Clone the larva repository from the Apache git repository into a local directory named `larva`.

```no-highlight
        $ cd ~/dev 
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git larva
        $ ls

        go	larva
        $ ls larva
        DISCLAIMER	NOTICE		app.yml		compiler	hw		net		project		sys
        LICENSE		README.md	autotargets	fs  libs	pkg-list.yml	scripts
``` 
  
2\. Create a target using the newt tool. 

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

3\. Now continue to populate and build out the sim target. 
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
        
4\. Configure *newt* to use the gnu build tools native to OS X or Linux. In order for sim to work properly, it needs the 32-bit gcc (gcc-5). Replace *~/dev/larva/compiler/sim/compiler.yml* with the *compiler/sim/osx-compiler.yml* or *linux-compiler.yml* file, depending on the system. On a Windows machine, follow the instruction for the Linux machine as you are running commands in a Linux VM.

  For a Mac OS X environment:
```no-highlight
        $ cp compiler/sim/osx-compiler.yml compiler/sim/compiler.yml 
```        
  For a Linux machine:
```no-highlight        
        $ cp compiler/sim/linux-compiler.yml compiler/sim/compiler.yml
```

5\. Next, build the packages for the sim project using the *newt* tool. You should see lots of console output while *newt* is resolving dependencies and compiling the source code.  After a minute, it should complete with 
the `Successfully run!` text.

```no-highlight
        $ newt target build sim_test
        Building target sim_test (project = test)
        ...
        ...
        Successfully run!
```
For extra details, specify the VERBOSE option.

```no-highlight
        $newt -l VERBOSE target build sim_test
        2015/09/29 09:46:12 [INFO] Building project test
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//bootutil...
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//cmsis-core...
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//ffs..
        ...
        Successfully run!
```
6\. Run the test suite executable inside this project and enjoy your first successful test!
```no-highlight
        $ project/test/bin/sim_test/test.elf
        [pass] os_mempool_test_suite/os_mempool_test_case
        [pass] os_mutex_test_suite/os_mutex_test_basic
        [pass] os_mutex_test_suite/os_mutex_test_case_1
        ...
        ...
        [pass] cbmem_test_suite/cbmem_test_case_3
```

### Use SRAM to make LED blink

If you wish to build the image to run from the onboard SRAM on Olimex board, follow the steps below:
#### Preparing the Software

* Make sure the PATH environment variable includes the $HOME/dev/go/bin directory. 

* If you have cloned the larva repository for the simulator test in the previous section, you can skip this step. Otherwise, you have to create a repository for the project. Go to ~/dev and clone the larva repository from the apache git repository into a local directory named `larva`.

```no-highlight
        $ cd ~/dev 
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git larva
        $ ls

        go	larva
        $ ls larva
        DISCLAIMER	NOTICE		app.yml		compiler	hw		net		project		sys
        LICENSE		README.md	autotargets	fs  libs	pkg-list.yml	scripts
``` 
    
* Change directory to ~dev/larva directory and build the *blinky* project inside larva, using the *newt* tool. Starting with the target name, assign specific aspects of the project, as shown below, to pull the appropriate packages and build the right bundle or list for the board. For example, we set the architecture (arch), compiler, board support package (bsp), project, and compiler mode.

    (Remember to prefix each command with "newtvm" if you are executing the newt command in a Linux virtual machine on your Windows box!)

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

* Next, let's build the image with the above values assigned. By default, the linker script within the `hw/bsp/olimex_stm32-e407_devboard` package builds an image for flash memory, which we don't want; instead, we want an image for the SRAM, so you need to switch that script with `run_from_sram.ld`. 

<font color="red">
(We are working to simplify this scheme whereby an executable for a project will correctly elect the linker scripts and generate the relevant image. For example, the scheme will key on project identity such as bootloader, RAM, Flash (default) and build accordingly. </font>.)

    Afer you build the target, you can find the executable *blinky.elf* in the project directory *~/dev/larva/project/blinky/bin/blinky.* 
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

* Check if you have all the scripts needed to launch OpenOCD and interact with the project's specific hardware. Depending on your system (Ubuntu or Windows) you may already have the scripts in your */usr/share/openocd/scripts/* directory, as they may have been part of the openocd download. If they exist, you are all set and can proceed to prepare the hardware. Otherwise check the *~/dev/larva/hw/bsp/olimex_stm32-e407_devboard* directory for a file named *f407.cfg*. Used by OpenOCD, this config enables us to interact with this specific hardware. 

You are all set if you see the file.

```no-highlight
        $ ls ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        bin		include		olimex_stm32-e407_devboard_download.sh	run_from_loader.ld
        boot-olimex_stm32-e407_devboard.ld	olimex_stm32-e407_devboard.ld	pkg.yml		run_from_sram.ld
        f407.cfg		olimex_stm32-e407_devboard_debug.sh	run_from_flash.ld			src
```
 
#### Prepare the hardware to boot from embedded SRAM

* Locate the boot jumpers on the board.
![Alt Layout - Top View](pics/topview.png)
![Alt Layout - Bottom View](pics/bottomview.png)

* B1_1/B1_0 and B0_1/B0_0 are PTH jumpers. Note that because the markings on the board may not always be accurate, when in doubt, you should always refer to the manual for the correct positioning. Since the jumpers are a pair, they should move together, and as such, the pair is responsible for the boot mode when bootloader is present. 
To locate the bootloader, the board searches in three places: User Flash Memory, System Memory or the Embedded SRAM. For this Blinky project, we will configure it to boot from SRAM by jumpering **B0_1** and **B1_1**.

* Connect USB-OTG#2 in the picture above to a USB port on your computer (or a powered USB hub to make sure there is enough power available to the board). 

* The red PWR LED should be lit. 

* Connect the JTAG connector to the SWD/JTAG interface on the board. The other end of the cable should be connected to the USB port or hub of your computer.

#### Let's Go!

* Ensure that you are in the blinky project directory with the *blinky.elf* executable. Run the debug command in the *newt* tool. You'll see some status messages as shown below. In case you need to halt the debugging session, you can issue an `-c "reset halt"` command.
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

   Check the value of the msp (main service pointer) register. If it is not 0x10010000 as indicated above, you will have to manually set it after you open the gdp tool and load the image on it. For example, 
   
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
      
* Voilà! The board's LED should be blinking at 1 Hz. Success!

### Use flash to make LED blink

If you wish to build the image to run from the onboard flash memory on Olimex board, follow the steps below:

* Configure the board to boot from flash by moving the two jumpers together to **B0_0** and **B1_0**. Refer to the pictures of the board under the section titled ["Prepare the hardware to boot from embedded SRAM"](#prepare-the-hardware-to-boot-from-embedded-sram).

   You will have to reset the board once the image is uploaded to it.
        
* If you skipped the first option for the project [(downloading an image to SRAM)](#use-sram-to-make-led-blink), then skip this step. Otherwise, continue with this step. 

   By default, the linker script (`olimex_stm32-e407_devboard.ld`) is configured to run from bootloader and flash. However, if you first ran the image from SRAM you had changed `olimex_stm32-e407_devboard.ld` to match `run_from_sram.ld`. You will, therefore, return to defaults with `olimex_stm32-e407_devboard.ld` linker script matching the contents of 'run_from_loader.ld'. Return to the project directory.

```no-highlight
        $ cd ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        $ diff olimex_stm32-e407_devboard.ld run_from_sram.ld
        $ diff olimex_stm32-e407_devboard.ld run_from_loader.ld
        (some diff will be displayed)
        $ cp run_from_loader.ld olimex_stm32-e407_devboard.ld
        $ cd ~/dev/larva/project/blinky/bin/blinky
```

* In order to run the image from flash, you need to build the bootloader as well. The bootloader does the initial set up of the Olimex board and then transfers control to the image stored at a location in flash known to it. The bootloader in turn requires the *bin2image* tool to check the image header for version information, CRC checks etc. So, we will need to build these two additional targets (bootloader and bin2img).

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
* Now let's build all the three targets now.
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

* Voilà! The LED should be blinking! Success!

* But wait...not so fast. let's double check that it is indeed booting from flash and making the LED blink from the image in flash. Pull the USB cable off the Olimex JTAG adaptor, severing the debug connection to the JTAG port. Next power off the Olimex board by pulling out the USB cable from the board. Wait for a couple of seconds and plug the USB cable back to the board. 

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
    
   Note #2: If you want to erase the flash and load the image again you may use the following commands from within gdb. `flash erase_sector 0 0 x` tells it to erase sectors 0 through x. When you ask it to display (in hex notation) the contents of the sector starting at location 'lma,' you should see all f's. The memory location 0x8000000 is the start or origin of the flash memory contents and is specified in the olimex_stm32-e407_devboard.ld linker script. The flash memory locations is specific to the processor.
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

### Conclusion

In summation, you achieved and learned a fair amount in this hands-on tutorial. If this is your first time to embedded systems, this must feel like the best hands-on and low-level "Hello World" progam ever. 

Good, we have more fun tutorials for you to get your hands dirty. Be bold and try other Blinky-like [tutorials](../tutorials/nRF52.md).

If you see anything missing or want to send us feeback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md)

Keep on hacking and blinking!
