## Blinky, Your Hello World!

### Objective

Learn how to use packages from a default application repository of Mynewt to build your first *Hello World* application (Blinky) in the safe haven of a simulation. 

This tutorial will guide to achieve the following: 

1. Set up the environment on your computer to use Mynewt OS and newt tool. 
2. Download packages for building and testing the project [on a simulated target](#build-test-code-on-simulator).

** Time Requirement**: Allow yourself an hour for this project if you are relatively new to embedded systems and want to understand each step.


### What you need

1. Personal Computer with Mac OS (Mac: OS X Yosemite Version 10.10.5) or Linux box (Ubuntu 14.10: Utopic Unicorn)
2. An account on Github repository and *git* installed on your computer.
3. It assumed you already installed native tools described [here](native_tools.md)

Also, we assume that you're familiar with UNIX shells.

Let's gets started!

### Install Native and Cross Tools


See [Installing Native Tools](../get_started/native_tools.md)
 and [Installing Cross Tools](../get_started/cross_tools.md) for ARM to install
the tools needed by newt.


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

### Conclusion

In summation, you achieved and learned a fair amount in this hands-on tutorial, all in the simulation environment.  

Now you can turn to more fun tutorials where you can get your hands dirty with actual hardware. Be bold and try the Blinky [tutorials on Olimex board](../tutorials/olimex.md).

If you see anything missing or want to send us feeback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md)

Keep on hacking and blinking!