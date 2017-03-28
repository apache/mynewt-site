## Blinky, your "Hello World!", on Olimex

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) on a target board. Once built using the *newt* tool, this application will blink the LED lights on the target board. Fun stuff!

This tutorial shows you how to create a blinky application for the Olimex board. It also shows you how to load the application onto the board's flash memory and run the application.

<br>

### Prerequisites
Ensure that you have met the following prerequisites before continuing with this tutorial:

* Have a STM32-E407 development board from Olimex. 
* Have a ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
* Have Internet connectivity to fetch remote Mynewt components.
* Have a computer to build a Mynewt application and connect to the board over USB.
* Have a USB A-B type cable to connect the debugger to your computer.
* Have a USB Micro-A cable to connect your computer to the board.
* Install the Newt tool and toolchains (See [Basic Setup](/os/get_started/get_started.md)).
* Create a project space (directory structure) and populated it with the core code repository (apache-mynewt-core) or know how to as explained in [Creating Your First Project](/os/get_started/project_create).
* Read the Mynewt OS [Concepts](/os/get_started/vocabulary.md) section.


<br>


### Create a Project
Create a new project if you do not have an existing one.  You can skip this step and proceed to [create the targets](#create_targets) if you already created a project.

Run the following commands to create a new project:

```no-highlight
    $ mkdir ~/dev
    $ cd ~/dev
    $ newt new myproj
    Downloading project skeleton from apache/incubator-mynewt-blinky...
    Installing skeleton in myproj...
    Project myproj successfully created.

    $cd myproj

    $ newt install
    apache-mynewt-core
    $
```

<br>

### <a name="create_targets"></a>Create the Targets

Create two targets for the Olimex board - one for the bootloader and one for the Blinky application.

Run the following `newt target` commands, from your project directory,  to create a bootloader target. We name the target `boot_olimex`.

```no-highlight
$ newt target create boot_olimex
$ newt target set boot_olimex build_profile=optimized
$ newt target set boot_olimex app=@apache-mynewt-core/apps/boot
$ newt target set boot_olimex bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
```

<br>
Run the following `newt target` commands to create a target for the Blinky application. We name the target `olimex_blinky`.

```no-highlight
$ newt target create olimex_blinky
$ newt target set olimex_blinky build_profile=debug
$ newt target set olimex_blinky bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
$ newt target set olimex_blinky app=apps/blinky

```

<br>

### Build the Bootloader 
Run the `newt build boot_olimex` command to build the bootloader:

```no-highlight
$ newt build boot_olimex
Building target targets/boot_olimex
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling bin/targets/boot_olimex/generated/src/boot_olimex-sysflash.c

     ...

Archiving libc_baselibc.a
Archiving sys_flash_map.a
Archiving sys_mfg.a
Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/boot_olimex/app/apps/boot/boot.elf
Target successfully built: targets/boot_olimex
```
<br>
### Build the Blinky Application
Run the `newt build olimex_blinky` command to build the blinky application:

```no-highlight
$ newt build olimex_blinky
Building target targets/olimex_blinky
Assembling repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/src/arch/cortex_m4/startup_STM32F40x.s
Compiling repos/apache-mynewt-core/hw/drivers/uart/src/uart.c
Compiling repos/apache-mynewt-core/hw/cmsis-core/src/cmsis_nvic.c
Compiling repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/src/sbrk.c
Compiling apps/blinky/src/main.c
Compiling repos/apache-mynewt-core/hw/drivers/uart/uart_hal/src/uart_hal.c
Compiling repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/src/hal_bsp.c
Compiling repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/src/system_stm32f4xx.c
Compiling repos/apache-mynewt-core/hw/hal/src/hal_common.c
Compiling repos/apache-mynewt-core/hw/hal/src/hal_flash.c

   ...

Archiving sys_mfg.a
Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/olimex_blinky/app/apps/blinky/blinky.elf
Target successfully built: targets/olimex_blinky

```

<br>

### Sign and Create the Blinky Application Image
Run the `newt create-image olimex_blinky 1.0.0` command to sign and create an image file for the blinky application. You may assign an arbitrary version (e.g. 1.0.0) number.


```no-highlight
$ newt create-image olimex_blinky 1.0.0
App image succesfully generated: ~/dev/myproj/bin/targets/olimex_blinky/app/apps/blinky/blinky.img
```
<br>

### Connect to the Board

Configure the board to bootload from flash memory and to use USB-OTG2 for the power source. Refer to the following diagrams to locate the boot jumpers and power input select jumpers on the board. 

**Note:** The labels for the **USB-OTG1** and **USB-OTG2** ports on the diagram are reversed. The port labeled USB-OTG1 on the diagram is the USB-OTG2 port and the port labeled USB-OTG2 on the diagram is the USB-OTG1 port.
<br>

<p align="center">
<img src="../pics/STM32-E407_top_small.jpg"></img>
<br>
<img src="../pics/STM32-E407_bot_small.jpg"></img>
</p>

<br>

* Locate the boot jumpers on the lower right corner of the board.  **B1_1/B1_0** and **B0_1/B0_0** are PTH jumpers to control the boot mode when a bootloader is present.  These two jumpers must be moved together.  The board searches for the bootloader in three places: User Flash Memory, System Memory or the Embedded SRAM. For this Blinky project, we configure the board to boot from flash by jumpering **B0_0** and **B1_0**.
**Note:** The markings on the board may not always be accurate, and you should always refer to the manual for the correct positioning. 

* Locate the **Power Input Select** jumpers on the lower left corner of the board.  Set the Power Select jumpers to position 5 and 6 to use the USB-OTG2 port for the power source. If you would like to use a different power source, refer to the [OLIMEX STM32-E407 user manual](https://www.olimex.com/Products/ARM/ST/STM32-E407/resources/STM32-E407.pdf) for pin specifications.

* Connect the USB Micro-A cable to the USB-OTG2 port on the board. 

* Connect the JTAG connector to the JTAG/SWD interface on the board. 

* Connect the USB A-B cable to the ARM-USB-TINY-H connector and your computer.

* Check that the red PWR LED lights up.
<br>

### Load the Bootloader and Blinky Application

Run the `newt load boot_olimex` command to load the bootloader image onto the board:
```no-highlight
$newt load -v boot_olimex
Loading bootloader
Load command: ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard ~/dev/myproj/bin/targets/boot_olimex/app/apps/boot/boot
Successfully loaded image.
```
Run the `newt load olimex_blinky` command to load the blinky application image onto the board:
```no-highlight
newt load -v olimex_blinky
Loading app image into slot 1
Load command: ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard ~/dev/myproj/bin/targets/olimex_blinky/app/apps/blinky/blinky
Successfully loaded image.

```
<br>
The LED should be blinking!

<br>
Let's double check that it is indeed booting from flash and making the LED blink from the image in flash. Pull the USB cable off the Olimex JTAG adaptor, severing the debug connection to the JTAG port. Next power off the Olimex board by pulling out the USB cable from the board. Wait for a couple of seconds and plug the USB cable back to the board.

   The LED light will start blinking again. Success!

   **Note #1:** If you want to download the image to flash and a gdb session opened up, use `newt debug blinky`. Type `c` to continue inside the gdb session.

```no-highlight     
    $ newt debug blinky
    Debugging with ~/dev/myproj/hw/bsp/olimex_stm32-e407_...
    Debugging ~/dev/myproj/project/blinky/bin/blinky/blinky.elf
    GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
    Copyright (C) 2014 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 <http://gnu.org/licenses/gpl.html>
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

<br>

   **Note #2:** If you want to erase the flash and load the image again you may use the following commands from within gdb. `flash erase_sector 0 0 x` tells it to erase sectors 0 through x. When you ask it to display (in hex notation) the contents of the sector starting at location 'lma,' you should see all f's. The memory location 0x8000000 is the start or origin of the flash memory contents and is specified in the olimex_stm32-e407_devboard.ld linker script. The flash memory locations is specific to the processor.
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

Congratulations! You have now tried out a project on actual hardware. If this is your first time to embedded systems, this must feel like the best hands-on and low-level "Hello World" program ever.

Good, we have more fun tutorials for you to get your hands dirty. Be bold and try other Blinky-like [tutorials](../tutorials/nRF52.md) or try enabling additional functionality such as [remote comms](project-target-slinky.md) on the current board.

If you see anything missing or want to send us feedback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and blinking!
