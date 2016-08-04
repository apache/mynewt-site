## Start Wi-Fi on Arduino Zero

This tutorial walks you through the steps to get your Arduino board on a Wi-Fi network. 

**Note:** Wi-Fi support is currently available in the `develop` branch of Mynewt only. It will be merged into `master` branch when version 0.10 is released.


### Prerequisites

Before tackling this tutorial, it's best to read about Mynewt in the [Introduction](../get_started/introduction) section of this documentation.

### Equipment

You will need the following equipment

* An Arduino Zero, Zero Pro or M0 Pro.  
**Note:** Mynewt has not been tested on Arduino M0 which has no internal debugger support.
* An Arduino Wi-Fi Shield 101
* A computer that can connect to the Arduino board over USB
* A local Wi-Fi network that the computer is connected to and which the Arduino board can join.
* A USB cable (Type A to micro B) that can connect the computer to the Arduino (or a USB hub between the computer and the Arduino board)
* The Mynewt Release


### Install Mynewt and Newt

* If you have not already done so, install Newt as shown in the [Newt install tutorial](../../newt/install/newt_mac.md). 
* If you installed Newt previously but need to update it, go to the newt git repo directory, pull the latest code from `develop` branch, and install the updated code.

```
   user@~/dev$ cd $GOPATH/src/mynewt.apache.org/newt
   user@~/dev/go/src/mynewt.apache.org/newt$ git remote -v
   origin	https://git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git (fetch)
   origin	https://git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git (push)
   user@~/dev/go/src/mynewt.apache.org/newt$ git pull origin develop
   remote: Counting objects: 59, done.
   <snip>
   user@~/dev/go/src/mynewt.apache.org/newt$ cd newt
   user@~/dev/go/src/mynewt.apache.org/newt/newt$ go install
   user@~/dev$ cd ~/dev
```

* If you have not already done so, create a project as shown in the Quick Start guide on how to [Create Your First Project](../get_started/project_create.md). Skip the testing and building the project steps in that tutorial since you will be defining a target for your Arduino board in this tutorial.

Let's say your new project is named `arduinowifi`. You will henceforth be working in that project directory.


<br>

### Fetch External Packages, Set correct version to download

Mynewt uses source code provided directly from the chip manufacturer for 
low level operations. Sometimes this code is licensed only for the specific manufacturer of the chipset and cannot live in the Apache Mynewt repository. That happens to be the case for the Arduino Zero board which uses Atmel SAMD21. Runtime's github repository hosts such external third-party packages and the Newt tool can fetch them.

To fetch the package with MCU support for Atmel SAMD21 for Arduino Zero from the Runtime git repository, you need to add 
the repository to the `project.yml` file in your base project directory (`arduinowifi`).

```
user@~/dev/arduinowifi$ vi project.yml
```

Here is an example ```project.yml``` file with the Arduino Zero repository
added. The sections with ```mynewt_arduino_zero``` that need to be added to 
your project file are highlighted. 

Also highlighted is the `0-dev` version for both the repositories to ensure code is downloaded from the `develop` branch.

```hl_lines="6 10 14 15 16 17 18"
$ more project.yml 
project.name: "my_project"

project.repositories:
    - apache-mynewt-core
    - mynewt_arduino_zero

repository.apache-mynewt-core:
    type: github
    vers: 0-dev
    user: apache
    repo: incubator-mynewt-core

repository.mynewt_arduino_zero:
    type: github
    vers: 0-dev
    user: runtimeinc
    repo: mynewt_arduino_zero
$ 
```

<br>

Once you've edited your ```project.yml``` file, the next step is to install the 
project dependencies, this can be done with the ```newt install``` command 
(to see more output, provide the ```-v``` verbose option.): 

```no-highlight
$ newt install 
apache-mynewt-core
mynewt_arduino_zero
$
```

<br>

### Create your bootloader target

Next, you need to tell Newt what to build.  For the Arduino Zero, we are going to 
generate both a bootloader, and an image target.

To generate the bootloader target, you need to specify the following options. The output of the commands (indicating success) have been suppressed for easier readability. 

```no-highlight
$ newt target create arduino_boot 
$ newt target set arduino_boot bsp=@mynewt_arduino_zero/hw/bsp/arduino_zero 
$ newt target set arduino_boot app=@apache-mynewt-core/apps/boot 
$ newt target set arduino_boot build_profile=optimized
```

<br>

If you have an Arduino Zero Pro or M0 Pro, you have to set the following next:

```
$ newt target set arduino_boot features=arduino_zero_pro 
```

If you have an Arduino Zero, you have to set the following instead:

```
$ newt target set arduino_boot features=arduino_zero 
```

<br>


### Build your bootloader

Once you've configured the bootloader target, the next step is to build the bootloader for your Arduino. You can do this by using the ```newt build``` command:

```no-highlight
$ newt build arduino_boot 
Compiling boot.c
Archiving boot.a
Compiling fs_cli.c
Compiling fs_dirent.c
Compiling fs_file.c
Compiling fs_mkdir.c
<snip>
App successfully built: ~/dev/arduinowifi/bin/arduino_boot/apps/boot/boot.elf
```

If this command finishes successfully, you have successfully built the Arduino 
bootloader, and the next step is to build your application for the Arduino 
board.

<br>

### Build your blinky app 

To create and download your application, you create another target, this one pointing to the application you want to download to the Arduino board.  In this tutorial,  we will use the Wi-Fi application that comes in the arduino repository, `apps/winc1500_wifi`:

**Note**: Remember to set features to `arduino_zero` if your board is Arduino Zero and not a Pro!

```hl_lines="5"
$ newt target create arduino_wifi 
$ newt target set arduino_wifi app=@mynewt_arduino_zero/apps/winc1500_wifi
$ newt target set arduino_wifi bsp=@mynewt_arduino_zero/hw/bsp/arduino_zero
$ newt target set arduino_wifi build_profile=debug 
$ newt target set arduino_wifi features=arduino_zero_pro 
```

<br>

You can now build the target, with ```newt build```: 

```no-highlight
$ newt build arduino_wifi 
Building target targets/arduino_wifi
Compiling main.c
Archiving winc1500_wifi.a
Compiling fs_cli.c
Compiling fs_dirent.c
Compiling fs_file.c
Compiling fs_mkdir.c
<snip>
Linking winc1500_wifi.elf
App successfully built: ~/dev/arduinowifi/bin/arduino_wifi/apps/winc1500_wifi/winc1500_wifi.elf
```
<font color="#FF0000"> Congratulations! </font> You have successfully built your Wi-Fi application. Now it's time to load both the bootloader and application onto the target.

<br>

### Connect the Target

Place the Wi-Fi shield on top of the Arduino board and push it in place, making sure the pins and pinholes are properly aligned. Connect your computer to the Arduino board with the Micro-USB cable through the Programming Port as shown below. Mynewt will download and debug the target through this port. You should see a little green LED come on. That means the board has power.

No external debugger is required.  The Arduino boards listed in this tutorial come with an internal debugger that can be accessed by Mynewt.

The picture below shows the setup.

![Arduino with Wi-Fi shield](pics/arduino_wifi.png "WifiShield")

<br>

### Download the Bootloader

Execute the command to download the bootloader. 

```c
    $ newt load arduino_boot
```

If the newt tool finishes without error, that means the bootloader has been 
successfully loaded onto the target.

<br>

<font color="#FF0000"> Reminder if you are using Docker: </font> When working with actual hardware, remember that each board has an ID. If you swap boards and do not refresh the USB Device Filter on the VirtualBox UI, the ID might be stale and the Docker instance may not be able to see the board correctly. For example, you may see an error message like `Error: unable to find CMSIS-DAP device` when you try to load or run an image on the board. In that case, you need to click on the USB link in VirtualBox UI, remove the existing USB Device Filter (e.g. "Atmel Corp. EDBG CMSIS-DAP[0101]") by clicking on the "Removes selected USB filter" button, and add a new filter by clicking on the "Adds new USB filter" button.

<br>

### Load the Application Image 

Now that the bootloader is downloaded to the target, the next steps are to create an image and load it onto the target device.


```no-highlight
$ newt create-image arduino_wifi 1.0.0
App image succesfully generated: ~/dev/arduinowifi/bin/arduino_wifi/apps/winc1500_wifi/winc1500_wifi.img
Build manifest: ~/dev/arduinowifi/bin/arduino_wifi/apps/winc1500_wifi/manifest.json
$ newt load arduino_wifi
Loading image
$
```

<br>


### Start Wi-Fi via console

Use a terminal emulation program to communicate with the board over the serial port. This tutorial shows a Minicom set up. You will have to find out what the usbserial port number is on your computer/laptop (`ls /dev`) and specify it as the -D flag value. Type `wifi start` to start Wi-Fi.

```hl_lines="12"
$ minicom -D /dev/tty.usbmodem141122 -b 115200


Welcome to minicom 2.7

OPTIONS: 
Compiled on Nov 24 2015, 16:14:21.
Port /dev/tty.usbmodem141122, 10:11:40

Press Meta-Z for help on special keys

wifi start
119470:(APP)(INFO)Chip ID 1502b1
(APP)(INFO)Firmware ver   : 19.4.4
(APP)(INFO)Min driver ver : 19.3.0
(APP)(INFO)Curr driver ver: 19.3.0                                              
wifi_init : 0                        
```

Connect to the local Wi-Fi network. Then start network services. The commands to be issued are highlighted below. In the example below, the network interface on the Arduino board gets an IP address of `192.168.0.117`.

```hl_lines="1 8"
wifi connect <Wi-Fi network name> <password> 
16906:wifi_request_scan : 0
17805:scan_results 16: 0
17816:wifi_connect : 0
18813:connect_done : 0
18821:dhcp done 192.168.0.117
18932:get sys time response 2016.8.2-18.4.43
net service
```

### Establish TCP connection and talk!

From a terminal on your computer/laptop, try telneting to ports 7, 9, or 19 using the IP address your board has been assigned. Type something on this terminal and see the console output (on minicom). Can you see the difference in the behaviors?

```
$ telnet 192.168.0.117 7
Trying 192.168.0.117...
Connected to 192.168.0.117.
Escape character is '^]'.
hello
hello
^]
telnet> q
$
```

One port echoes whatever is typed, one discards everything it gets, and the third spews out bits constantly. Type `wifi stop` to disable WiFi on the Arduino board.

Hope you had fun!