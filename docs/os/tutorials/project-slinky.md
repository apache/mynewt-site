## Project Sim Slinky  


<br>

The goal of the project is to use a sample app called "Slinky" included in the Mynewt repository to enable remote communications with a device running the Mynewt OS. The protocol for remote communications is called newt manager (newtmgr). In this tutorial we will create a target for a simulated device and define it with the sample app "Slinky". 

If you have an existing project using a target that does not use the Slinky app and you wish to add newtmgt functonality to it, check out the tutorial titled [Enable newtmgr in any app](add_newtmgr.md). 

<br>

### What you need

1.Personal Computer

The instructions assume the user is using a Bourne-compatible shell (e.g. bash or zsh) on your computer. The given instructions have been tested with the following releases of operating systems:

* Mac: OS X Yosemite Version 10.10.5

### Overview of steps

* Install dependencies
* Define a target using the newt tool
* Build executables for the targets using the newt tool
* Set up serial connection with the targets 
* Create a connection profile using the newtmgr tool
* Use the newtmgr tool to communicate with the targets

### Installing newt

If you have not already installed `newt` see the 
[newt installation instructions](../get_started/get_started/) and ensure newt is installed an in your path.

### Installing newtmgr

If you have not already installed `newtmgr` see the 
[newtmgr installation instructions](../../newtmgr/installing/) and ensure newtmgr is installed an in your path.

### Creating a new project

Instructions for creating a project are located in the [Basic Setup](../get_started/project_create/) section of the [Mynewt Documentation](../introduction/)

We will list only the steps here for brevity.  We will name the project
`slinky`.

```no-highlight
    $ newt new slinky
    Downloading project skeleton from apache/incubator-mynewt-blinky...
    ...
    Installing skeleton in slink...
    Project slink successfully created
    $ cd slinky
    $ newt install -v
    Downloading repository description for apache-mynewt-core... success!
    ...
    Repos successfully installed
```

### Setting up your target build

Create a target for `slinky` using the native bsp. We will list only the steps and suppress the tool output here for brevity.

```no-highlight
    $ newt target create sim_slinky
    $ newt target set sim_slinky bsp=@apache-mynewt-core/hw/bsp/native
    $ newt target set sim_slinky build_profile=debug
    $ newt target set sim_slinky app=@apache-mynewt-core/apps/slinky
```

### Building Your target

To build your target, use `newt build`.  When complete, an executable file
is created.

```no-highlight
    $ newt build sim_slinky 
    Building target targets/sim_slinky
    Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec256.c
    Compiling repos/apache-mynewt-core/boot/bootutil/src/image_rsa.c
    Compiling repos/apache-mynewt-core/boot/bootutil/src/image_ec.c
    Compiling repos/apache-mynewt-core/boot/split/src/split.c
    Compiling repos/apache-mynewt-core/boot/bootutil/src/image_validate.c
    Compiling repos/apache-mynewt-core/boot/bootutil/src/loader.c
    Compiling repos/apache-mynewt-core/boot/bootutil/src/bootutil_misc.c
    Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aesni.c
    Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aes.c
    Compiling repos/apache-mynewt-core/boot/split/src/split_config.c
    Compiling repos/apache-mynewt-core/apps/slinky/src/main.c

              ...

    Archiving util_crc.a
    Archiving util_mem.a
    Linking ~/dev/slinky/bin/targets/sim_slinky/app/apps/slinky/slinky.elf
    Target successfully built: targets/sim_slinky

```

### Run the target

Run the executable you have build for the simulated environment. The serial port name on which the simulated target is connected is shown in the output
when mynewt slinky starts.

```no-highlight
    $ ~/dev/slinky/bin/targets/sim_slinky/app/apps/slinky/slinky.elf
    uart0 at /dev/ttys005
```

<br>

In this example, the slinky app opened up a com port `/dev/ttys005` for communications with newtmgr. 

**NOTE:** This application will block. You will need to open a new console (or execute this in another console) to continue the tutorial.*

<br>

### Setting up a connection profile

You will now set up a connection profile using `newtmgr` for the serial port connection and start communicating with the simulated remote device.

```no-highlight
    $ newtmgr conn add sim1 type=serial connstring=/dev/ttys005
    Connection profile sim1 successfully added
    $ newtmgr conn show
    Connection profiles: 
      sim1: type=serial, connstring='/dev/ttys005'
```

### Executing newtmgr commands with the target

You can now use connection profile `sim1` to talk to the running sim_slinky.
As an example, we will query the running mynewt OS for the usage of its 
memory pools.  

```no-highlight
    $ newtmgr -c sim1 mpstats
    Return Code = 0
                            name blksz  cnt free  min
                          msys_1   292   12   10   10

```

As a test command, you can send an arbitrary string to the target and it
will echo that string back in a response to newtmgr.

```no-highlight
    $ newtmgr -c sim1 echo "Hello Mynewt"
    Hello Mynewt
```

In addition to these, you can also examine running tasks, statistics, 
logs, image status (not on sim), and configuration.
