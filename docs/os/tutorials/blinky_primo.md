## Blinky, your "Hello World!", on Arduino Primo

<br>

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) on a target board. Once built using the *newt* tool, this application will blink the LED lights on the target board.

Create a project with a simple app that blinks an LED on the Arduino Primo board.  Download the application to the target and watch it blink!

Note that the Mynewt OS will run on the nRF52 chip in the Arduino Primo board. However, the board support package for the Arduino Primo is different from the nRF52 dev kit board support package.

<br>

### Hardware needed

* Arduino Primo
* Laptop running Mac OS
* [Segger J-Link Debug Probe](https://www.segger.com/jlink-debug-probes.html) - any model (this tutorial has been tested with J-Link EDU and J-Link Pro)
* [J-Link 9 pin Cortex-M Adapter](https://www.segger.com/jlink-adapters.html#CM_9pin) that allows JTAG, SWD and SWO connections between J-Link and Cortex M based target hardware systems
* A micro USB 2.0 cable to power the Arduino primo board
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
    apache-mynewt-core successfully installed version 0.9.0
``` 

<br>

If you are working with 0.9.0 release (and not any subsequent releases), you will have to instruct newt to download code for the Arduino Primo Board Support Package (bsp) from the `develop` branch. You first edit the `project.yml` file in your project directory to change `vers:0-latest` to `0-dev`:

```hl_lines="5"
<snip>
#
repository.apache-mynewt-core:
    type: github
    vers: 0-dev
    user: apache
    repo: incubator-mynewt-core
```

Then you run `newt upgrade`:

```
$ newt upgrade
apache-mynewt-core
Would you like to upgrade repository apache-mynewt-core from 0.9.0-none to 0.0.0-none ? [Yn] Y
```


**Note**: With the next release, the Arduino Primo bsp will be included in the main release package. The above edit and `newt upgrade` step will not be required.

<br>

### Create the targets

Create two targets - one for the bootloader and one for the Primo board.  


```
$ newt target create primoblinky
$ newt target set primoblinky app=@apache-mynewt-core/apps/blinky bsp=@apache-mynewt-core/hw/bsp/arduino_primo_nrf52 build_profile=debug

$ newt target create primo_boot
$ newt target set primo_boot app=@apache-mynewt-core/apps/boot bsp=@apache-mynewt-core/hw/bsp/arduino_primo_nrf52 build_profile=optimized

$ newt target show
targets/my_blinky_sim
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/native
    build_profile=debug
targets/primo_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/arduino_primo_nrf52
    build_profile=optimized
targets/primoblinky
    app=@apache-mynewt-core/apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/arduino_primo_nrf52
    build_profile=optimized
```

<br>

### Build the target executables 

```
$ newt build primo_boot
<snip>
Compiling log_shell.c
Archiving log.a
Linking boot.elf
App successfully built: ~/dev/myproj/bin/primo_boot/apps/boot/boot.elf
```
```
$ newt build primoblinky
<snip>
Compiling stats_shell.c
Archiving stats.a
Linking blinky.elf
App successfully built: ~/dev/myproj/bin/primoblinky/apps/blinky/blinky.elf
```

<br>

### Sign and create the blinky application image 

You must sign and version your application image to download it using newt to the board. Use the newt create-image command to perform this action. You may assign an arbitrary version (e.g. 1.0.0) to the image.

```
$ newt create-image primoblinky 1.0.0
```

<br>

### Connect the board

Connect the Segger J-Link debug probe to the JTAG port on the Primo board using the Jlink 9-pin adapter and cable. Note that there are two JTAG ports on the board. Use the one nearest to the reset button as shown in the picture. Also use a micro USB 2.0 cable to connect the Primo board to one of your laptop's USB host ports.

![J-Link debug probe to Arduino](pics/primo-jlink.jpg "Connecting J-Link debug probe to Arduino Primo")
        
<br>

### Download to the target

Download the bootloader first and then the blinky executable to the target platform. Don't forget to reset the board if you don't see the LED blinking right away. If the reset button doesn't work, powercycle the board!

```
$ newt -v load primo_boot
$ newt -v load primoblinky
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

<br>


### Conclusion

You have created, setup, compiled, loaded, and ran your first mynewt application
for an Arduino Primo board.

We have more fun tutorials for you to get your hands dirty. Be bold and work on the OS with tutorials on [writing a test suite](unit_test.md) or try enabling additional functionality such as [remote comms](project-target-slinky.md) or [Bluetooth Low Energy](bletiny_project.md) on your current board.

If you see anything missing or want to send us feedback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and blinking!





