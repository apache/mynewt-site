## Blinky, your "Hello World!", on Olimex

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) on a target board. Once built using the *newt* tool, this application will blink the LED lights on the target board. Fun stuff!

This tutorial shows you how to create a runtime image for an Olimex board to make its LED blink. Download the image to its flash memory and see the LED blink!

<br>

### What you need

1. STM32-E407 development board from Olimex. You can order it from [http://www.mouser.com](http://www.mouser.com/ProductDetail/Olimex-Ltd/STM32-E407/?qs=UN6GZl1KCcit6Ye0xmPO4A%3D%3D), [http://www.digikey.com](http://www.digikey.com/product-detail/en/STM32-E407/1188-1093-ND/3726951), and other places.
2. ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
3. USB A-B type cable to connect the debugger to your personal computer
4. Personal Computer with Mac OS (Mac: OS X Yosemite Version 10.10.5) or Linux box (Ubuntu 14.10: Utopic Unicorn)
5. An account on Github repository and *git* installed on your computer.
6. It is assumed you have already installed newt tool. 
7. It is assumed you already installed native tools as described [here](../get_started/native_tools.md)

Also, we assume that you're familiar with UNIX shells. Let's gets started!

<br>


### Prepare the Software

* Make sure the PATH environment variable includes the $HOME/dev/go/bin directory. 
 
<br>

### Create a project.  

Create a new project to hold your work.  For a deeper understanding, you can read about project creation in 
[Get Started -- Creating Your First Project](../get_started/project_create.md)
or just follow the commands below.

```no-highlight
    $ mkdir ~/dev
    $ cd ~/dev
    $ newt new myproj
    Downloading project skeleton from apache/incubator-mynewt-blinky...
    Installing skeleton in myproj...
    Project myproj successfully created.

    $cd myproj

    $ newt install -v 
    apache-mynewt-core
    Downloading repository description for apache-mynewt-core... success!
    ...
    apache-mynewt-core successfully installed version 0.7.9-none
``` 

<br>
   
### Create targets

Change directory to ~/dev/myproj directory and define the *blinky* target inside myproj, using the *newt* tool. Starting with the target name, assign specific aspects of the project, as shown below, to pull the appropriate packages and build the right bundle or list for the board. For example, we set the build_profile, board support package (bsp), and app.


```no-highlight
    $ newt target create blinky
    $ newt target set blinky build_profile=debug
    $ newt target set blinky bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
    $ newt target set blinky app=apps/blinky
    
    $ newt target create boot_olimex
    $ newt target set boot_olimex app=@apache-mynewt-core/apps/boot
    $ newt target set boot_olimex bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
    $ newt target set boot_olimex build_profile=optimized
    
    $ newt target show 
    targets/blinky
        app=apps/blinky
        bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
        build_profile=debug
    targets/boot_olimex
        app=@apache-mynewt-core/apps/boot
        bsp=@apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
        build_profile=optimized
```

<br>

### Build the images

Next, let's build the images for the above targets. Afer you build the target, you can find the executable *blinky.elf* in the project directory *~/dev/myproj/bin/blinky/apps/blinky/.* 
    
    
```no-highlight
    $ newt build blinky
    Compiling case.c
    Compiling suite.c
    ...
    Linking blinky.elf
    App successfully built:~/dev/myproj/bin/blinky/apps/blinky/blinky.elf
    $ ls ~/dev/myproj/bin/blinky/apps/blinky/
        blinky.elf      blinky.elf.bin     blinky.elf.cmd  
        blinky.elf.lst  blinky.elf.map
        
    $ newt build boot_olimex
    Building target targets/boot_olimex
    App successfully built: ~/dev/myproj/bin/boot_olimex/apps/boot/boot.elf
```

<br>

### Sign and create the blinky application image 

You must sign and version your application image to download it using newt to the board. Use the newt create-image command to perform this action. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```
$ newt create-image blinky 1.0.0
App image succesfully generated: ~/dev/myproj/bin/blinky/apps/blinky/blinky.img
Build manifest: ~/dev/myproj/bin/blinky/apps/blinky/manifest.json
```

<br>

### Prepare the hardware to boot from flash

* Locate the boot jumpers on the board.

<br>

![Alt Layout - Top View](pics/topview.png)
![Alt Layout - Bottom View](pics/bottomview.png)

<br>

* B1_1/B1_0 and B0_1/B0_0 are PTH jumpers. Note that because the markings on the board may not always be accurate, when in doubt, you should always refer to the manual for the correct positioning. Since the jumpers are a pair, they should move together, and as such, the pair is responsible for the boot mode when bootloader is present. 
To locate the bootloader, the board searches in three places: User Flash Memory, System Memory or the Embedded SRAM. For this Blinky project, we will configure it to boot from flash by jumpering **B0_0** and **B1_0**.

* Connect USB-OTG#2 in the picture above to a USB port on your computer (or a powered USB hub to make sure there is enough power available to the board). 

* The red PWR LED should be lit. 

* Connect the JTAG connector to the SWD/JTAG interface on the board. The other end of the cable should be connected to the USB port or hub of your computer.

<br>

### Let's Go!

* Load the images
```no-highlight
$ newt -v load boot_olimex
Loading image with: ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/ ~/dev/myproj/bin/boot_olimex/apps/boot/boot BASELIBC FS LIBC NFFS bootloader
Successfully loaded image.

$ newt -v load blinky
Loading image with: ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard/ ~/dev/myproj/bin/blinky/apps/blinky/blinky BASELIBC LIBC
Successfully loaded image.
```
<br>

* Voilà! The LED should be blinking! Success!

<br>

**But wait...not so fast.** Let's double check that it is indeed booting from flash and making the LED blink from the image in flash. Pull the USB cable off the Olimex JTAG adaptor, severing the debug connection to the JTAG port. Next power off the Olimex board by pulling out the USB cable from the board. Wait for a couple of seconds and plug the USB cable back to the board. 

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
