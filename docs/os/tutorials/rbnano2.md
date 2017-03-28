## Blinky, your "Hello World!", on RedBear Nano 2

<br>

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) on a target board. Once built using the *newt* tool, this application will blink the LED lights on the target board.

Create a project with a simple application that blinks an LED on a RedBear Nano 2 board.  Download the application to the target and watch it blink!

<br>

### Prerequisites

Ensure that you have met the following prerequisites before continuing with this tutorial:

* Have a RedBear Nano 2 board. 
* Have Internet connectivity to fetch remote Mynewt components.
* Have a computer to build a Mynewt application and connect to the board over USB.
* Install the Newt tool and toolchains (See [Basic Setup](/os/get_started/get_started.md)).
* Create a project space (directory structure) and populated it with the core code repository (apache-mynewt-core) or know how to as explained in [Creating Your First Project](/os/get_started/project_create).
* Read the Mynewt OS [Concepts](/os/get_started/vocabulary.md) section.

**Note:** You must install a patched version of OpenOCD .10.0 (See [Debugger Option 2 in the Arduino Primo Blinky Tutorial](/os/tutorials/blinky_primo)).

### Create a Project  
Create a new project if you do not have an existing one.  You can skip this step and proceed to [create the targets](#create_targets) if you already have a project created.  

Run the following commands to create a new project:

```no-highlight
    $ mkdir ~/dev
    $ cd ~/dev
    $ newt new myproj
    Downloading project skeleton from apache/incubator-mynewt-blinky...
    Installing skeleton in myproj...
    Project myproj successfully created.
    $ cd myproj
    $ newt install
    apache-mynewt-core
    $
``` 

<br>

### <a name="create_targets"></a>Create the Targets

Create two targets for the RedBear Nano 2 board - one for the bootloader and one for the Blinky application.

Run the following `newt target` commands, from your project directory, to create a bootloader target. We name the target `rbnano2_boot`:

```no-highlight
$ newt target create rbnano2_boot
$ newt target set rbnano2_boot app=@apache-mynewt-core/apps/boot
$ newt target set rbnano2_boot bsp=@apache-mynewt-core/hw/bsp/rb-nano2
$ newt target set rbnano2_boot build_profile=optimized
```

<br>
Run the following `newt target` commands to create a target for the Blinky application. We name the target `nrf52_blinky`.

```no-highlight
$ newt target create rbnano2_blinky
$ newt target set rbnano2_blinky app=apps/blinky
$ newt target set rbnano2_blinky bsp=@apache-mynewt-core/hw/bsp/rb-nano2
$ newt target set rbnano2_blinky build_profile=debug
```
<br>
You can run the `newt target show` command to verify the target settings:

```no-highlight
$ newt target show 
targets/rbnano2_blinky
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/rb-nano2
    build_profile=debug
targets/rbnano2_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/rb-nano2
    build_profile=optimized
```
<br>

### Build the Target Executables 

Run the `newt build rbnano2_boot` command to build the bootloader:

```no-highlight
$newt build rbnano2_boot
Building target targets/rbnano2_boot
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aes.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_validate.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
Compiling repos/apache-mynewt-core/apps/boot/src/boot.c

      ...

Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/rbnano2_boot/app/apps/boot/boot.elf
Target successfully built: targets/rbnano2_boot
```

<br>
Run the `newt build rbnano2_blinky` command to build the Blinky application:

```no-highlight
$newt build rbnano2_blinky
Building target targets/rbnano2_blinky
Assembling repos/apache-mynewt-core/hw/bsp/rb-nano2/src/arch/cortex_m4/gcc_startup_nrf52_split.s
Compiling repos/apache-mynewt-core/hw/drivers/uart/src/uart.c
Compiling repos/apache-mynewt-core/hw/cmsis-core/src/cmsis_nvic.c
Compiling repos/apache-mynewt-core/hw/bsp/rb-nano2/src/sbrk.c
Compiling apps/blinky/src/main.c

     ...

Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/rbnano2_blinky/app/apps/blinky/blinky.elf
Target successfully built: targets/rbnano2_blinky

```

<br>

### Sign and Create the Blinky Application Image 

Run the `newt create-image rbnano2_blinky 1.0.0` command to create and sign the application image. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```no-highlight
$newt create-image rbnano2_blinky 1.0.0
App image succesfully generated: ~/dev/myproj/bin/targets/rbnano2_blinky/app/apps/blinky/blinky.img
```

<br>

### Connect to the Board

Connect the RedBear Nano 2 USB to a USB port on your computer. You should see an orange LED light up on the board.

        
### Load the Bootloader and the Blinky Application Image

Run the `newt load rbnano2_boot` command to load the bootloader onto the board: 

```no-highlight
$ newt load rbnano2_boot
Loading bootloader
$
```
<br>
Note: The flash memory on the RedBear Nano 2 comes write protected from the factory. If you get an error loading the bootloader and you are using a brand new chip, you need to clear the write protection from the debugger and then load the bootloader again.  Run the `newt debug rbnano2_blinky` command and issue the following commands at the highlighted (gdb) prompts.  

```hl_lines="8 9 11 14"
$newt debug rbnano2_blinky
[~/dev/myproj/repos/apache-mynewt-core/hw/bsp/rb-nano2/rb-nano2_debug.sh  ~/dev/myproj/repos/apache-mynewt-core/hw/bsp/rb-nano2 ~/dev/myproj/bin/targets/rbnano2_blinky/app/apps/blinky/blinky]
Open On-Chip Debugger 0.10.0-dev-snapshot (2017-03-28-11:24)
Licensed under GNU GPL v2

     ...

(gdb) set {unsigned long}0x4001e504=2
(gdb) x/1wx 0x4001e504
0x4001e504:0x00000002
(gdb) set {unsigned long}0x4001e50c=1
Info : SWD DPIDR 0x2ba01477
Error: Failed to read memory at 0x00009ef4
(gdb) x/32wx 0x00
0x0:0xffffffff0xffffffff0xffffffff0xffffffff
0x10:0xffffffff0xffffffff0xffffffff0xffffffff
0x20:0xffffffff0xffffffff0xffffffff0xffffffff
0x30:0xffffffff0xffffffff0xffffffff0xffffffff
0x40:0xffffffff0xffffffff0xffffffff0xffffffff
0x50:0xffffffff0xffffffff0xffffffff0xffffffff
0x60:0xffffffff0xffffffff0xffffffff0xffffffff
0x70:0xffffffff0xffffffff0xffffffff0xffffffff
(gdb)
```

<br>
Run the `newt load rbnano2_blinky` command to load the Blinky application image onto the board.
```no-highlight
$ newt load rbnano2_blinky
Loading app image into slot 1
```

You should see a blue LED on the board blink!

Note: If the LED does not blink, try resetting your board.


### Conclusion

You have created, setup, compiled, loaded, and ran your first mynewt application for a RedBear Nano 2 board.

We have more fun tutorials for you to get your hands dirty. Be bold and work on the OS with tutorials on [writing a test suite](unit_test.md) or try enabling additional functionality such as [remote comms](project-target-slinky.md) or [Bluetooth Low Energy](bletiny_project.md) on your current board.

If you see anything missing or want to send us feedback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and blinking!

