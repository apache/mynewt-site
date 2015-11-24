## Blinky, the First Project

### Objective

We will show you how you can use eggs from a nest on Mynewt to make an LED on a target board blink. We will call it ** Project Blinky**. The goals of this tutorial are threefold:
 
1. First, you will learn how to set up your environment to be ready to use Mynewt OS and newt tool. 
2. Second, we will walk you through a download of eggs for building and testing [on a simulated target](#building-test-code-on-simulator) on a non-Windows machine.
3. Third, you will download eggs and use tools to create a runtime image for a board to make its LED blink. You have two choices here - you can [download an image to SRAM](#making-an-led-blink-from-sram) or you can [download it to flash](#using-flash-to-make-led-blink).

** Time Requirement**: Allow yourself a couple of hours for this project if you are relatively new to embedded systems and playing with development boards. Those jumpers can be pesky!


### What you need

1. STM32-E407 development board from Olimex. You can order it from [http://www.mouser.com](http://www.mouser.com/ProductDetail/Olimex-Ltd/STM32-E407/?qs=UN6GZl1KCcit6Ye0xmPO4A%3D%3D), [http://www.digikey.com](http://www.digikey.com/product-detail/en/STM32-E407/1188-1093-ND/3726951), and other places.
2. ARM-USB-TINY-H connector with JTAG interface for debugging ARM microcontrollers (comes with the ribbon cable to hook up to the board)
3. USB A-B type cable to connect the debugger to your personal computer
4. Personal Computer

The instructions assume the user is using a Bourne-compatible shell (e.g. bash or zsh) on your computer. You may already have some of the required packages on your machine.  In that 
case, simply skip the corresponding installation step in the instructions under [Getting your Mac Ready](project1.md#getting-your-mac-ready) or [Getting your Ubuntu machine Ready](project1.md#getting-your-ubuntu-machine-ready) or [Getting your Windows machine Ready](#getting-your-windows-machine-ready). While the given instructions should work on other versions, they have been tested for the three specific releases of operating systems noted here:

* Mac: OS X Yosemite Version 10.10.5
* Linux: Ubuntu 14.10 (Utopic Unicorn)
* Windows: Windows 10


### Access to the Apache repo

* Get an account on Apache. 

* The latest codebase for the Mynewt OS is on the master branch at  https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git

* The latest codebase for the Newt tool is on the master branch at  https://git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git


### Getting your Mac Ready

#### Installing Homebrew to ease installs on OS X 

* Do you have Homebrew? If not, open a terminal on your Mac and paste the following at a Terminal prompt. It will ask you for your sudo password.

        $ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

    Alternatively, you can just extract (or `git clone`) Homebrew and install it to `/usr/local`.

#### Installing Go 

* The directory structure must be first readied for using Go. Go code must be kept inside a workspace. A workspace is a directory hierarchy with three directories at its root:

    * src contains Go source files organized into packages (one package per directory),

    * pkg contains package objects, and

    * bin contains executable commands.

    The GOPATH environment variable specifies the location of your workspace. First create a 'dev' directory and then a 'go' directory under it. Set the GOPATH environment variable to this directory and then proceed to create the directory for cloning the newt tool repository.

        $ cd $HOME
        $ mkdir -p dev/go  
        $ cd dev/go
        $ export GOPATH=`pwd`

    Note that you need to add export statements to ~/.bash_profile to export variables permanently. Don't forget to source the file for the change to go into effect.
    
        $ vi ~/.bash_profile
        $ source ~/.bash_profile

* Next you will use brew to install Go. The summary message at the end of the installation should indicate that it is installed in the /usr/local/Cellar/go/ directory. You will use the Go command 'install' to compile and install packages (called eggs in the Mynewt world) and dependencies. 
    
        $ brew install go
        ==> 
        ...
        ... 
        ==> *Summary*
        🍺  /usr/local/Cellar/go/1.5.1: 5330 files, 273M

    Alternatively, you can download the Go package directly from (https://golang.org/dl/) instead of brewing it. Install it in /usr/local directory.
    

#### Creating local repository

* You are ready to download the newt tool repository. You will use Go to copy the directory (currently the asf incubator directory). Be patient as it may take a minute or two. Check the directories installed.

        $ go get git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ ls
         bin	pkg	   src
        $ ls src
        git-wip-us.apache.org	github.com		gopkg.in


* Check that newt is installed.

        $ ls $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git  
        Godeps			README.md		coding_style.txt    newt.go
        LICENSE			cli			    design.txt


#### Building the Newt tool

* You will use Go to run the newt.go program to build the newt tool. The command used is  `go install` which compiles and writes the resulting executable to an output file named `newt`. It installs the results along with its dependencies in $GOPATH/bin.
   
        $ cd $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ go install
        $ ls "$GOPATH"/bin/
        godep		incubator-mynewt-newt.git	  newt

* Try running newt using the compiled binary. For example, check for the version number by typing 'newt version'. See all the possible commands available to a user of newt by typing 'newt -h'.

   Note: If you are going to be be modifying the newt tool itself often and wish to compile the program every time you call it, you may want to store the command in a variable in your .bash_profile. So type in `export newt="go run $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt/newt/go"` in your .bash_profile and execute it by calling `$newt` at the prompt instead of `newt`. Here, you use `go run` which runs the compiled binary directly without producing an executable. Don't forget to reload the updated bash profile by typing `source ~/.bash_profile` at the prompt! 

        $ newt version
        Newt version:  1.0
        $ newt -h
        Newt allows you to create your own embedded project based on the Mynewt
        operating system. Newt provides both build and package management in a
        single tool, which allows you to compose an embedded workspace, and set
        of projects, and then build the necessary artifacts from those projects.
        For more information on the Mynewt operating system, please visit
        https://www.github.com/mynewt/documentation.

        Please use the newt help command, and specify the name of the command
        you want help for, for help on how to use a specific command

        Usage:
         newt [flags]
         newt [command]

        Examples:
         newt
         newt help [<command-name>]
           For help on <command-name>.  If not specified, print this message.


        Available Commands:
         version     Display the Newt version number.
         target      Set and view target information
         egg         Commands to list and inspect eggs on a nest
         nest        Commands to manage nests & clutches (remote egg repositories)
         help        Help about any command

        Flags:
         -h, --help=false: help for newt
         -l, --loglevel="WARN": Log level, defaults to WARN.
         -q, --quiet=false: Be quiet; only display error output.
         -s, --silent=false: Be silent; don't output anything.
         -v, --verbose=false: Enable verbose output when executing commands.


        Use "newt help [command]" for more information about a command.
       
* Without creating a project repository you can't do a whole lot with the Newt tool. So you'll have to wait till you have downloaded a nest to try out the tool. 

#### Getting the debugger ready

* Before you start building nests and hatching eggs, you need to do one final step in the environment preparation - install gcc / libc that can produce 32-bit executables. So, first install gcc. You will see the brew steps and a final summary confirming install.

        $ brew install gcc
        ...
        ...
        ==> Summary
        🍺  /usr/local/Cellar/gcc/5.2.0: 1353 files, 248M


* ARM maintains a pre-built GNU toolchain with a GCC source branch targeted at Embedded ARM Processors namely Cortex-R/Cortex-M processor families. Install the PX4 Toolchain and check the version installed. Make sure that the symbolic link installed by Homebrew points to the correct version of the debugger. If not, you can either change the symbolic link using the "ln -f -s" command or just go ahead and try with the version it points to!

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

    Note: If no version is specified, brew will install the latest version available. MynewtOS will eventually work with multiple versions available including the latest releases. However, at present we have tested only with this version and recommend it for getting started. 
    
* You have to install OpenOCD (Open On-Chip Debugger) which is an open-source software that will allow you to interface with the JTAG debug connector/adaptor for the Olimex board. It lets you program, debug, and test embedded target devices which, in this case, is the Olimex board. Use brew to install it. Brew adds a simlink /usr/local/bin/openocd to the openocd directory in the Cellar. For more on OpenOCD go to [http://openocd.org](http://openocd.org).

        $ brew install open-ocd
        $ which openocd
        /usr/local/bin/openocd
        $ ls -l $(which openocd)
        lrwxr-xr-x  1 <user>  admin  36 Sep 17 16:22 /usr/local/bin/openocd -> ../Cellar/open-ocd/0.9.0/bin/openocd

* Proceed to the [Building test code on simulator](#building-test-code-on-simulator) section.


### Getting your Ubuntu machine Ready 

#### Getting an account on GitHub

* Get an account on GitHub. Make sure you have joined the "Newt Operating System" organization.

#### Installing some prerequisites

* Install git, libcurl, and the Go language if you do not have them already.

        $ sudo apt-get install git 
        $ sudo apt-get install libcurl4-gnutls-dev 
        $ sudo apt-get install golang 
        
#### Creating local repository 

* The directory structure must be first readied for using Go. Go code must be kept inside a workspace. A workspace is a directory hierarchy with three directories at its root:

    * src contains Go source files organized into packages (one package per directory),

    * pkg contains package objects, and

    * bin contains executable commands.

    The GOPATH environment variable specifies the location of your workspace. First create a 'dev' directory and then a 'go' directory under it. Set the GOPATH environment variable to this directory and then proceed to create the directory for cloning the newt tool repository.

        $ cd $HOME
        $ mkdir -p dev/go  
        $ cd dev/go
        $ export GOPATH=$PWD

    Note that you need to add export statements to ~/.bashrc (or equivalent) to export variables permanently.

* You are ready to download the newt tool repository. You will use Go to copy the directory (currently the asf incubator directory). Be patient as it may take a minute or two. Check the directories installed.

        $ go get git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ ls
         bin	pkg	   src
        $ ls src
        git-wip-us.apache.org	github.com		gopkg.in


* Check that newt is installed.

        $ ls $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git  
        Godeps			README.md		coding_style.txt    newt.go
        LICENSE			cli			    design.txt

#### Building the newt tool


* You will use Go to run the newt.go program to build the newt tool. The command used is  `go install` which compiles and writes the resulting executable to an output file named `newt`. It installs the results along with its dependencies in $GOPATH/bin.
   
        $ cd $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ go install
        $ ls "$GOPATH"/bin/
        godep		incubator-mynewt-newt.git	  newt

* Try running newt using the compiled binary. For example, check for the version number by typing 'newt version'. See all the possible commands available to a user of newt by typing 'newt -h'.

   Note: If you are going to be be modifying the newt tool itself often and wish to compile the program every time you call it, you may want to store the command in a variable in your .bash_profile. So type in `export newt="go run $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt/newt/go"` in your ~/.bashrc (or equivalent) and execute it by calling `$newt` at the prompt instead of `newt`. Here, you use `go run` which runs the compiled binary directly without producing an executable.   
  

        $ newt version
        Newt version:  1.0
        $ newt -h
        Newt allows you to create your own embedded project based on the Mynewt
        operating system. Newt provides both build and package management in a
        single tool, which allows you to compose an embedded workspace, and set
        of projects, and then build the necessary artifacts from those projects.
        For more information on the Mynewt operating system, please visit
        https://www.github.com/mynewt/documentation.

        Please use the newt help command, and specify the name of the command
        you want help for, for help on how to use a specific command

        Usage:
         newt [flags]
         newt [command]

        Examples:
         newt
         newt help [<command-name>]
           For help on <command-name>.  If not specified, print this message.


        Available Commands:
         version     Display the Newt version number.
         target      Set and view target information
         egg         Commands to list and inspect eggs on a nest
         nest        Commands to manage nests & clutches (remote egg repositories)
         help        Help about any command

        Flags:
         -h, --help=false: help for newt
         -l, --loglevel="WARN": Log level, defaults to WARN.
         -q, --quiet=false: Be quiet; only display error output.
         -s, --silent=false: Be silent; don't output anything.
         -v, --verbose=false: Enable verbose output when executing commands.


        Use "newt help [command]" for more information about a command.
        
* Without creating a project repository you can't do a whole lot with the Newt tool. So you'll have to wait till you have downloaded a nest to try out the tool. 

#### Getting the debugger ready

* Before you start building nests and hatching eggs, you need to do one final step in the environment preparation - install gcc / libc that can produce 32-bit executables. You can install these as follows: 

        $ sudo apt-get install gcc-multilib libc6-i386
        
* For the LED project on the Olimex hardware, you have to install gcc for AM 4.9.3.  This package can be installed with apt-get as documented [here](https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded).

        $ sudo apt-get remove binutils-arm-none-eabi gcc-arm-none-eabi 
        $ sudo add-apt-repository ppa:terry.guo/gcc-arm-embedded 
        $ sudo apt-get update 
        $ sudo apt-get install gcc-arm-none-eabi

* And finally, you have to install OpenOCD (Open On-Chip Debugger) which is an open-source software that will allow you to interface with the JTAG debug connector/adaptor for the Olimex board. It lets you program, debug, and test embedded target devices which, in this case, is the Olimex board. You have to acquire OpenOCD 0.8.0. 

    If you are running Ubuntu 15.x, then you are in luck and you can simply run: 

        $ sudo apt-get install openocd 

    Other versions of Ubuntu may not have the correct version of openocd available.  In this case, you should download the openocd 0.8.0 package from [https://launchpad.net/ubuntu/vivid/+source/openocd](https://launchpad.net/ubuntu/vivid/+source/openocd). The direct link to the amd64 build is [http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb](http://launchpadlibrarian.net/188260097/openocd_0.8.0-4_amd64.deb). 

* Proceed to the [Building test code on simulator](#building-test-code-on-simulator) section.

### Getting your Windows machine Ready


#### Getting an account on GitHub

* Get an account on GitHub. Make sure you have joined the "Newt Operating System" organization.

#### Installing some prerequisites

* You have to install the following if you do not have them already.  The steps below indicate specific folders where each of these programs should be installed. You can choose different locations, but the remainder of this
tutorial for a Windows machine assumes the specified folders.    

    * win-builds-i686
    * win-builds-x86_64
    * MSYS
    * gcc for ARM
    * openocd
    * zadig
    * git
    * go

        - *win-builds (mingw64) 1.5 for i686*
        
        Download from [http://win-builds.org/doku.php/download_and_installation_from_windows](http://win-builds.org/doku.php/download_and_installation_from_windows). Install at: "C:\win-builds-i686".
        
        Be sure to click the i686 option (not x86_64). The defaults for all other options are OK. The installer will want to download a bunch of additional packages. They are not all necessary, but it is simplest to just accept the defaults.

        - *win-builds (mingw64) 1.5 for x86_64*
        
        Download from [http://win-builds.org/doku.php/download_and_installation_from_windows](http://win-builds.org/doku.php/download_and_installation_from_windows). Install at "C:\win-builds-x86_64"
        
        Run the installer a second time, but this time click the x86_64 option, NOT i686.  The defaults for all other options are OK.
        
        - *MSYS*
        
        Start your download from [http://sourceforge.net/projects/mingw-w64/files/External%20binary%20packages%20%28Win64%20hosted%29/MSYS%20%2832-bit%29/MSYS-20111123.zip](http://sourceforge.net/projects/mingw-w64/files/External%20binary%20packages%20%28Win64%20hosted%29/MSYS%20%2832-bit%29/MSYS-20111123.zip)
        
        Unzip to "C:\msys"
        
        - *gcc for ARM, 4.9.3*
        
        Download the Windows installer from [https://launchpad.net/gcc-arm-embedded/+download](https://launchpad.net/gcc-arm-embedded/+download) and install at "C:\Program Files (x86)\GNU Tools ARM Embedded\4.9 2015q3".

        - OpenOCD 0.8.0
        
        Download OpenOCD 0.8.0 from [http://www.freddiechopin.info/en/download/category/4-openocd](http://www.freddiechopin.info/en/download/category/4-openocd). Unzip to "C:\openocd".
        
        - Zadig 2.1.2
        
        Download it from [http://zadig.akeo.ie](http://zadig.akeo.ie) and install it at "C:\zadig".
        
        - Git
        
        Click on [https://git-scm.com/download/win](https://git-scm.com/download/win) to start the download. Install at "C:\Program Files (x86)\Git". Specify the "Use Git from the Windows Command Prompt" option.  The defaults for all other options are OK.
        
        - Go
        
        Download the release for Microsoft Windows from [https://golang.org/dl/](https://golang.org/dl/) and install it "C:\Go".
    
        
#### Creating local repository 

* The directory structure must be first readied for using Go. Go code must be kept inside a workspace. A workspace is a directory hierarchy with three directories at its root:

    * src contains Go source files organized into packages (one package per directory),

    * pkg contains package objects, and

    * bin contains executable commands.

    The GOPATH environment variable specifies the location of your workspace. First create a 'dev' directory and then a 'go' directory under it. Set the GOPATH environment variable to this directory and then proceed to create the directory for cloning the newt tool repository.

        $ cd c:\
        $ mkdir dev\go
        $ cd dev\go

* Set the following user environment variables using the steps outlined here.

    * GOPATH: C:\dev\go
    * PATH: C:\Program Files (x86)\GNU Tools ARM Embedded\4.9 2015q3\bin;%GOPATH%\bin;C:\win-builds-x86_64\bin;C:\win-builds-i686\bin;C:\msys\bin
    
    Steps:
    
       1. Right-click the start button
       2. Click "Control panel"
       3. Click "System and Security"
       4. Click "System"
       5. Click "Advanced system settings" in the left panel
       6. Click the "Envoronment Variables..." button
       7. There will be two sets of environment variables: user variables
      in the upper half of the screen, and system variables in the lower
      half.  Configuring the user variables is recommended and tested 
      (though system variables will work as well).

 
* Next, install godep. Note that the following command produces no output.

        $ go get github.com/tools/godep 

* Set up the repository for the package building tool "newt" on your local machine. First create the appropriate directory for it and then clone the newt tool repository from the online apache repository (or its github.com mirror) into this newly created directory. Check the contents of the directory.

        $ mkdir %GOPATH%\src\github.com\mynewt
        $ cd %GOPATH%\src\github.com\mynewt
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git newt
        $ dir
        newt
        $ cd newt
        $ dir
        Godeps                  README.md               coding_style.txt        newt.go
        LICENSE                 cli                     design.txt

* Use the Go command 'install' to compile and install packages and dependencies. Add Go environment to path. Again, to make the export variable permanent, add it to your ~/.bashrc (or equivalent) file.

        $ %GOPATH%\bin\godep restore 
        $ go get 
        $ go install 

#### Building the newt tool

* * You will use Go to run the newt.go program to build the newt tool. The command used is  `go install` which compiles and writes the resulting executable to an output file named `newt`. It installs the results along with its dependencies in $GOPATH/bin.
   
        $ go install
        $ ls "$GOPATH"/bin/
        godep		incubator-mynewt-newt.git	  newt

* Try running newt using the compiled binary. For example, check for the version number by typing 'newt version'. See all the possible commands available to a user of newt by typing 'newt -h'.

    Note: If you are going to be be modifying the newt tool itself often and wish to compile the program every time you call it, you may want to define the newt environment variable that allows you to execute the command via `%newt%`. Use `set newt=go run %GOPATH%\src\github.com\mynewt\newt\newt.go` or set it from the GUI. Here, you use `go run` which runs the compiled binary directly without producing an executable.

        $ newt version
        Newt version:  1.0
        $ newt -h
        Newt allows you to create your own embedded project based on the Mynewt
        operating system. Newt provides both build and package management in a
        single tool, which allows you to compose an embedded workspace, and set
        of projects, and then build the necessary artifacts from those projects.
        For more information on the Mynewt operating system, please visit
        https://www.github.com/mynewt/documentation.

        Please use the newt help command, and specify the name of the command
        you want help for, for help on how to use a specific command

        Usage:
         newt [flags]
         newt [command]

        Examples:
         newt
         newt help [<command-name>]
           For help on <command-name>.  If not specified, print this message.


        Available Commands:
         version     Display the Newt version number.
         target      Set and view target information
         egg         Commands to list and inspect eggs on a nest
         nest        Commands to manage nests & clutches (remote egg repositories)
         help        Help about any command

        Flags:
         -h, --help=false: help for newt
         -l, --loglevel="WARN": Log level, defaults to WARN.
         -q, --quiet=false: Be quiet; only display error output.
         -s, --silent=false: Be silent; don't output anything.
         -v, --verbose=false: Enable verbose output when executing commands.


        Use "newt help [command]" for more information about a command.
        
* Without creating a project repository you can't do a whole lot with the Newt tool. So you'll have to wait till you have downloaded a nest to try out the tool. 

#### Getting the debugger ready

* Use Zadig to configure the USB driver for your Olimex debugger.  If your debugger is already set up, you can skip this step.

    1. Plug in your Olimex debugger.
    2. Start Zadig.
    3. Check the Options -> List All Devices checkbox.
    4. Select "Olimex OpenOCD JTAG ARM-USB-TINY-H" in the dropdown menu.
    5. Select the "WinUSB" driver.
    6. Click the "Install Driver" button.

#### Proceed to the [Building test code on simulator on Windows machine](#building-test-code-on-simulator) section.

Note: Currently, the simulator cannot be run in the Windows machine. We are still working on it. So you will go ahead and [make an LED blink](#making-an-led-blink-from-sram) on the Olimex hardware directly. 

However, before you skip to the hardware target, you still need to build your first nest as outlined in step 1 in the [Building test code on simulator](#building-test-code-on-simulator).


### Building test code on simulator 

Note: Currently, the simulator cannot be run in the Windows machine. We are working on it. If you are on a Windows machine, do step 1 below and then proceed to the [Making an LED blink](#making-an-led-blink) on the Olimex hardware directly.

1.  First, you have to create a repository for the project i.e. build your first nest! Go to ~/dev and clone the larva repository from the apache git repository into a local directory named `larva`.

    Substitute DOS commands for Unix commands as necessary in the following steps if your machine is running Windows. The newt tool commands do not change.

 
        $ cd ~/dev 
        $ git clone https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git larva
        $ ls
        go	larva
        $ cd larva
        $ ls
        LICENSE		clutch.yml	hw		nest.yml      project
        README.md	compiler	libs		net	      scripts

2. You will now create a new target using the newt tool. You can either use the compiled binary `newt` or run the newt.go program using `$newt` (assuming you have stored the command in a variable in your .bash_profile or .bashrc). When you do a `newt target show` or `$newt target show` it should list all the projects you have created so far. 

        $ newt target create sim_test
        Creating target sim_test
        Target sim_test sucessfully created!
        $ newt target show
        sim_test
	        name: sim_test
	        arch: sim

3. Now continue to populate and build out the sim project.

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
	        arch: sim
	        project: test
	        compiler_def: debug
	        bsp: hw/bsp/native
	        compiler: sim
	        name: sim_test

4. Configure newt to use the gnu build tools native to OS X or linux. In order for sim to work properly, it needs to be using 32-bit gcc (gcc-5). Replace 
~/dev/larva/compiler/sim/compiler.yml with the compiler/sim/osx-compiler.yml or linux-compiler.yml file, depending on the system. 

    For a Mac OS X environment:

        $ cp compiler/sim/osx-compiler.yml compiler/sim/compiler.yml 
        
    For a Linux machine:
        
        $ cp compiler/sim/linux-compiler.yml compiler/sim/compiler.yml

5. Next, create (hatch!) the eggs for this project using the newt tool - basically, build the packages for it. You can specify the VERBOSE option if you want to see the gory details. 

        $ $newt target build sim_test
        Successfully run!

    You can specify the VERBOSE option if you want to see the gory details.

        $newt -l VERBOSE target build sim_test
        2015/09/29 09:46:12 [INFO] Building project test
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//bootutil...
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//cmsis-core...
        2015/09/29 09:46:12 [INFO] Loading Package /Users/aditihilbert/dev/larva/libs//ffs..
        ...
        Successfully run!

6. Try running the test suite executable inside this project and enjoy your first successful hatch.

        $ ./project/test/bin/sim_test/test.elf
        [pass] os_mempool_test_suite/os_mempool_test_case
        [pass] os_mutex_test_suite/os_mutex_test_basic
        [pass] os_mutex_test_suite/os_mutex_test_case_1
        [pass] os_mutex_test_suite/os_mutex_test_case_2
        [pass] os_sem_test_suite/os_sem_test_basic
        [pass] os_sem_test_suite/os_sem_test_case_1
        [pass] os_sem_test_suite/os_sem_test_case_2
        [pass] os_sem_test_suite/os_sem_test_case_3
        [pass] os_sem_test_suite/os_sem_test_case_4
        [pass] os_mbuf_test_suite/os_mbuf_test_case_1
        [pass] os_mbuf_test_suite/os_mbuf_test_case_2
        [pass] os_mbuf_test_suite/os_mbuf_test_case_3
        [pass] gen_1_1/ffs_test_unlink
        [pass] gen_1_1/ffs_test_rename
        [pass] gen_1_1/ffs_test_truncate
        [pass] gen_1_1/ffs_test_append
        [pass] gen_1_1/ffs_test_read
        [pass] gen_1_1/ffs_test_overwrite_one
        [pass] gen_1_1/ffs_test_overwrite_two
        [pass] gen_1_1/ffs_test_overwrite_three
        ...
        ...
        [pass] boot_test_main/boot_test_vb_ns_11

### Building test code on simulator on Windows machine

Coming soon.

### Making an LED blink from SRAM

You are here because you want to build an image to be run from internal SRAM on the Olimex board.

#### Preparing the Software

1. Make sure the PATH environment variable includes the $HOME/dev/go/bin directory (or C:\%GOPATH%\bin on Windows machine). 

    Substitute DOS commands for Unix commands as necessary in the following steps if your machine is running Windows (e.g. `cd dev\go` instead of `cd dev/go`). The newt tool commands do not change.


2. You first have to create a repository for the project. Go to the ~dev/larva directory and build out a second project inside larva. The project name is "blinky", in keeping with the objective. Starting with the target name, you have to specify the different aspects of the project to pull the appropriate eggs and build the right package for the board. In this case that means setting the architecture (arch), compiler, board support package (bsp), project, and compiler mode.

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
	        compiler: arm-none-eabi-m4
	        project: blinky
	        compiler_def: debug
	        bsp: hw/bsp/olimex_stm32-e407_devboard
	        name: blinky
	        arch: cortex_m4

3. Now you have to build the image. The linker script within the `hw/bsp/olimex_stm32-e407_devboard` egg builds an image for flash memory by default. Since you want an image for the SRAM, you need to switch that script with `run_from_sram.ld` in order to get the egg to produce an image for SRAM. <font color="red"> We are working on making it easier to specify where the executable will be run from for a particular project and automatically choose the correct linker scripts and generate the appropriate image. It will be specified as a project identity e.g. bootloader, RAM, flash (default) and the target will build accordingly. </font>. 

    Once the target is built, you can find the executable "blinky.elf" in the project directory at ~/dev/larva/project/blinky/bin/blinky. It's a good idea to take a little time to understand the directory structure.

        $ cd ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        $ diff olimex_stm32-e407_devboard.ld run_from_sram.ld
        $ cp run_from_sram.ld olimex_stm32-e407_devboard.ld
        $ cd ~/dev/larva/project/blinky/bin/blinky
        $ newt target build blinky
        Building target blinky (project = blinky)
        Compiling case.c
        Compiling suite.c
        ...
        Successfully run!
        $ ls
        LICENSE		clutch.yml	hw		nest.yml	project
        README.md	compiler	libs		net		scripts
        $ cd project
        $ ls
        bin2img		bletest		blinky		boot		ffs2native	test
        $ cd blinky
        $ ls
        bin		blinky.yml	egg.yml		src
        $ cd bin
        $ ls
        blinky
        $ cd blinky
        $ ls
        blinky.elf	blinky.elf.bin	blinky.elf.cmd	blinky.elf.lst	blinky.elf.map


4. Check that you have all the scripts needed to get OpenOCD up and talking with the project's specific hardware. Depending on your system (Ubuntu, Windows) you may already have the scripts in your `/usr/share/openocd/scripts/ ` directory as they may have been part of the openocd download. If yes, you are all set and can proceed to preparing the hardware.

   Otherwise check the `~/dev/larva/hw/bsp/olimex_stm32-e407_devboard` directory for a file named `f407.cfg`. That is the config we will use to talk to this specific hardware using OpenOCD. You are all set if you see it.
   
        $ ls ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        bin					olimex_stm32-e407_devboard_debug.sh
        boot-olimex_stm32-e407_devboard.ld	olimex_stm32-e407_devboard_download.sh
        egg.yml					run_from_flash.ld
        f407.cfg				run_from_loader.ld
        include					run_from_sram.ld
        olimex_stm32-e407_devboard.ld		src

 
#### Preparing the hardware to boot from embedded SRAM

1. Locate the boot jumpers on the board.
![Alt Layout - Top View](pics/topview.png)
![Alt Layout - Bottom View](pics/bottomview.png)

2. B1_1/B1_0 and B0_1/B0_0 are PTH jumpers which can be moved relatively easy. Note that the markings on the board may not always be accurate. Always refer to the manual for the correct positioning of jumpers in case of doubt. The two jumpers must always be moved together – they are responsible for the boot mode if bootloader is present. The board can search for bootloader on three places – User Flash Memory, System Memory or the Embedded SRAM. We will configure it to boot from SRAM by jumpering B0_1 and B1_1.

3. Connect USB-OTG#2 in the picture above to a USB port on your computer (or a powered USB hub to make sure there is enough power available to the board). 

4. The red PWR LED should be lit. 

5. Connect the JTAG connector to the SWD/JTAG interface on the board. The other end of the cable should be connected to the USB port or hub of your computer.



#### Let's Go!

1. Make sure you are in the blinky project directory with the blinky.elf executable. Run the debug command in the newt tool. You should see some status messages are shown below. There is an inbuilt `-c "reset halt"` flag that tells it to halt after opening the session.
      
        $ cd dev/larva/project/blinky/bin/blinky
        $ newt target debug blinky
        Debugging with /Users/aditihilbert/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_debug.sh blinky
        Debugging /Users/aditihilbert/dev/larva/project/blinky/bin/blinky/blinky.elf
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
        Type "apropos word" to search for commands related to "word"...
        Reading symbols from /Users/aditihilbert/dev/larva/project/blinky/bin/        blinky/blinky.elf...done.
        Open On-Chip Debugger 0.8.0 (2015-09-22-18:21)
        Licensed under GNU GPL v2
        For bug reports, read
	        http://openocd.sourceforge.net/doc/doxygen/bugs.html
        Info : only one transport option; autoselect 'jtag'
        adapter speed: 1000 kHz
        adapter_nsrst_delay: 100
        jtag_ntrst_delay: 100
        Warn : target name is deprecated use: 'cortex_m'
        DEPRECATED! use 'cortex_m' not 'cortex_m3'
        cortex_m reset_config sysresetreq
        Info : clock speed 1000 kHz
        Info : JTAG tap: stm32f4x.cpu tap/device found: 0x4ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x4)
        Info : JTAG tap: stm32f4x.bs tap/device found: 0x06413041 (mfg: 0x020, part: 0x6413, ver: 0x0)
        Info : stm32f4x.cpu: hardware has 6 breakpoints, 4 watchpoints
        Info : JTAG tap: stm32f4x.cpu tap/device found: 0x4ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x4)
        Info : JTAG tap: stm32f4x.bs tap/device found: 0x06413041 (mfg: 0x020, part: 0x6413, ver: 0x0)
        target state: halted
        target halted due to debug-request, current mode: Thread 
        xPSR: 0x01000000 pc: 0x20000250 msp: 0x10010000
        Info : accepting 'gdb' connection from 3333
        Info : device id = 0x10036413
        Info : flash size = 1024kbytes
        Reset_Handler () at startup_STM32F40x.s:199
        199	    ldr    r1, =__etext


      Check the value of the msp (main service pointer) register. If it is not 0x10010000 as indicated above, you will have to manually set it after you open the gdp tool and load the image on it. 
      
        (gdb) set $msp=0x10010000
      
      Now load the image and type "c" or "continue" from the GNU debugger. 
              
        (gdb) load ~/dev/larva/project/blinky/bin/blinky/blinky.elf
        Loading section .text, size 0x4294 lma 0x20000000
        Loading section .ARM.extab, size 0x24 lma 0x20004294
        Loading section .ARM.exidx, size 0xd8 lma 0x200042b8
        Loading section .data, size 0x874 lma 0x20004390
        Start address 0x20000250, load size 19460
        Transfer rate: 81 KB/sec, 2432 bytes/write.
        (gdb) c
        Continuing.
         
2. Voilà! The board's LED should be blinking at 1 Hz.

### Using flash to make LED blink

You are here because you want to build an image to be run from flash memory on the Olimex board.

1. Configure the board to boot from flash by moving the two jumpers together to B0_0 and B1_0. 

   You will have to reset the board once the image is uploaded to it.
        
2. If you skipped the first option for the project [(downloading an image to SRAM)](#making-an-led-blink-from-sram), then skip this step. Otherwise, continue with this step. 

     By default, the linker script (`olimex_stm32-e407_devboard.ld`) is configured to run from bootloader and flash. However, if you first ran the image from SRAM you had changed `olimex_stm32-e407_devboard.ld` to match `run_from_sram.ld`. You will therefore return to defaults with `olimex_stm32-e407_devboard.ld` linker script matching the contents of 'run_from_loader.ld'. Return to the project directory.

        $ cd ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard
        $ diff olimex_stm32-e407_devboard.ld run_from_sram.ld
        $ diff olimex_stm32-e407_devboard.ld run_from_loader.ld
        $ cp run_from_loader.ld olimex_stm32-e407_devboard.ld
        $ cd ~/dev/larva/project/blinky/bin/blinky

3. In order to run the image from flash, you need to build the bootloader as well. The bootloader does the initial bring up of the Olimex board and then transfers control to the image stored at a location in flash known to it. The bootloader in turn requires the bin2image tool to check the image header for version information, CRC checks etc. So, we will need to build these two additional targets (bootloader and bin2img).

   Let's first create bin2img:
   
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
        $ newt target show bin2image
        $ newt target show bin2img
        bin2img
        	arch: sim
        	compiler: sim
        	project: bin2img
        	compiler_def: debug
        	bsp: hw/bsp/native
        	name: bin2img

   And then let's create boot_olimex:
  
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
        	project: boot
        	compiler_def: optimized
        	bsp: hw/bsp/olimex_stm32-e407_devboard
        	name: boot_olimex
        	arch: cortex_m4
        	compiler: arm-none-eabi-m4

4. Let's build all the three targets now.

        $ newt target build bin2img
        Building target bin2img (project = bin2img)
        Building project bin2img
        Successfully run!
        $ newt target build boot_olimex
        Building target boot_olimex (project = boot)
        Building project boot
        Successfully run!
        $ newt target build blinky
        Building target blinky (project = blinky)
        Building project blinky
        Successfully run!


5. Go to the project directory and download the bootloader and the image to flash ... in a flash! 

        $ cd ~/dev/larva/project/blinky/bin/blinky
        $ newt target download boot_olimex
        Downloading with ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh
        $ newt target download blinky
        Downloading with ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_download.sh

6. The LED should be blinking!

7. But wait...let's double check that it is indeed booting from flash and making the LED blink from the image in flash. Pull the USB cable off the Olimex JTAG adaptor. The debug connection to the JTAG port is now severed. Next power off the Olimex board by pulling out the USB cable from the board. Wait for a couple of seconds and plug the USB cable back to the board. 

    The LED light will start blinking again. Success!

    Note #1: If you want to download the image to flash and a gdb session opened up, use `newt target debug blinky` instead of `newt target download blinky`.
        
        $ newt target debug blinky
        Debugging with ~/dev/larva/hw/bsp/olimex_stm32-e407_devboard/olimex_stm32-e407_devboard_debug.sh blinky
        Debugging ~/dev/larva/project/blinky/bin/blinky/blinky.elf
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
        Type "apropos word" to search for commands related to "word"...
        Reading symbols from /Users/aditihilbert/dev/larva/project/blinky/bin/blinky/blinky.elf...done.
        Open On-Chip Debugger 0.8.0 (2015-09-22-18:21)
        Licensed under GNU GPL v2
        For bug reports, read
	        http://openocd.sourceforge.net/doc/doxygen/bugs.html
        Info : only one transport option; autoselect 'jtag'
        adapter speed: 1000 kHz
        adapter_nsrst_delay: 100
        jtag_ntrst_delay: 100
        Warn : target name is deprecated use: 'cortex_m'
        DEPRECATED! use 'cortex_m' not 'cortex_m3'
        cortex_m reset_config sysresetreq
        Info : clock speed 1000 kHz
        Info : JTAG tap: stm32f4x.cpu tap/device found: 0x4ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x4)
        Info : JTAG tap: stm32f4x.bs tap/device found: 0x06413041 (mfg: 0x020, part: 0x6413, ver: 0x0)
        Info : stm32f4x.cpu: hardware has 6 breakpoints, 4 watchpoints
        Info : JTAG tap: stm32f4x.cpu tap/device found: 0x4ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x4)
        Info : JTAG tap: stm32f4x.bs tap/device found: 0x06413041 (mfg: 0x020, part: 0x6413, ver: 0x0)
        target state: halted
        target halted due to debug-request, current mode: Thread 
        xPSR: 0x01000000 pc: 0x08000250 msp: 0x10010000
        Info : accepting 'gdb' connection from 3333
        Info : device id = 0x10036413
        Info : flash size = 1024kbytes
        Reset_Handler () at startup_STM32F40x.s:199
        199	    ldr    r1, =__etext
        (gdb)
    
    
    Note #2: If you want to erase the flash and load the image again you may use the following commands from within gdb. `flash erase_sector 0 0 x` tells it to erase sectors 0 through x. When you ask it to display (in hex notation) the contents of the sector starting at location 'lma' you should therefore see all f's. The memory location 0x8000000 is the start or origin of the flash memory contents and is specified in the olimex_stm32-e407_devboard.ld linker script. The flash memory locations is specific to the processor.
            
        (gdb) monitor flash erase_sector 0 0 4
        erased sectors 0 through 4 on flash bank 0 in 2.296712s
        (gdb) monitor mdw 0x08000000 16
        0x08000000: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff 
        (0x08000020: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff 
        (0x08000000: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff 
        (0x08000020: ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff ffffffff         
        (gdb) monitor flash info 0
        
        
        monitor flash erase_check 0

