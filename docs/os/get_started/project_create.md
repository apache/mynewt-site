## Create Your First Mynewt Project

This page shows how to create a Mynewt Project using the `newt` command-line tool.

<br>

### Pre-Requisites

* Newt:
    * If you have taken the Docker route, you have already installed Newt.
    * If you have taken the native install route, you have to ensure that you have installed the Newt tool following the instructions for [Mac](../../newt/install/newt_mac.md) or [Linux](../../newt/install/newt_linux.md) as appropriate, and that the `newt` command is in your system path. 
* You must have Internet connectivity to fetch remote Mynewt components.
* You must [install the compiler tools](native_tools.md) to 
support native compiling to build the project this tutorial creates.  

<br>

### Newt New

Choose a project name. For this tutorial we will call this project `myproj`.
Enter the `newt new myproj` command. 

``` no-highlight
$ newt new myproj
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in myproj...
Project myproj successfully created.
```

<br>

Newt populates this new project with a base skeleton of a new Apache Mynewt 
project.  It has the following structure. 

**Note**: If you do not have `tree`, install it by running `brew install tree`.

```no-highlight 
$ cd myproj
$ tree 
.
├── DISCLAIMER
├── LICENSE
├── NOTICE
├── README.md
├── apps
│   └── blinky
│       ├── pkg.yml
│       └── src
│           └── main.c
├── project.yml
└── targets
    ├── my_blinky_sim
    │   ├── pkg.yml
    │   └── target.yml
    └── unittest
        ├── pkg.yml
        └── target.yml

6 directories, 11 files
```

<br>


The Newt tool has installed the base files for a project comprising the following:

1. The file `project.yml` contains the repository list that the project uses to fetch
its packages. Your project is a collection of repositories.  In this case, the project just
comprises the core mynewt repository.  Later you will add more repositories
to include other mynewt components.
2. The file `apps/blinky/pkg.yml` contains the description of your application
and its package dependencies.
3. A `target` directory containing `my_blinky_sim`, a target descriptor used to
build a version of myproj.  Use `newt target show` to see available build 
targets.
4. A non-buildable target called `unittest`.  This is used internally by `newt` and is not a formal build target.

**NOTE:** The actual code and package files are not installed 
(except the template for `main.c`).  See the next step for installing the packages.

**NOTE:** By default newt uses the code in the master branch. This is the latest stable
code for newt. If you need to use a different branch, you can set this in the project.yml
file. 

```no-highlight
repository.apache-mynewt-core:
    type: github
    vers: 0-latest
    user: apache
    repo: incubator-mynewt-core
```
Changing to 0-dev will put you on the develop branch. **The Develop Branch may not be stable and 
you may encounter bugs or other problems.**

<br>

### Newt Install

Once you've switched into your new project's directory, the next step is to fetch
any dependencies this project has.  By default, all Newt projects rely on a
single remote repository, apache-mynewt-core.  The _newt install_ command will
fetch this repository.

```no-highlight
$ newt install
apache-mynewt-core
```

**NOTE:** _apache-mynewt-core_ may take a while to download.  To see progress,
use the _-v_ (verbose) option to install. 

<br>

Once _newt install_ has successfully finished, the contents of _apache-mynewt-core_ will have been downloaded into your local directory.  You can view them by issuing the following commands in the base directory of the new project. The actual output will depend on what is in the latest 'master' branch you have pulled from.

```no-highlight
$ tree -L 2 repos/apache-mynewt-core/
repos/apache-mynewt-core/
repos/apache-mynewt-core/
├── CODING_STANDARDS.md
├── DISCLAIMER
├── LICENSE
├── NOTICE
├── README.md
├── RELEASE_NOTES.md
├── apps
│   ├── blecent
│   ├── blehci
│   ├── bleprph
│   ├── bleprph_oic
│   ├── bletest
│   ├── bletiny
│   ├── bleuart
│   ├── boot
│   ├── ffs2native
│   ├── ocf_sample
│   ├── slinky
│   ├── slinky_oic
│   ├── spitest
│   ├── splitty
│   ├── test
│   └── timtest
├── boot
│   ├── boot_serial
│   ├── bootutil
│   └── split
├── compiler
│   ├── arm-none-eabi-m0
│   ├── arm-none-eabi-m4
│   ├── gdbmacros
│   └── sim
├── crypto
│   ├── mbedtls
│   └── tinycrypt
├── docs
│   └── doxygen.xml
├── encoding
│   ├── base64
│   ├── cborattr
│   ├── json
│   └── tinycbor
├── fs
│   ├── fcb
│   ├── fs
│   └── nffs
├── hw
│   ├── bsp
│   ├── cmsis-core
│   ├── drivers
│   ├── hal
│   ├── mcu
│   └── scripts
├── kernel
│   └── os
├── libc
│   └── baselibc
├── mgmt
│   ├── imgmgr
│   ├── mgmt
│   ├── newtmgr
│   └── oicmgr
├── net
│   ├── ip
│   ├── nimble
│   ├── oic
│   └── wifi
├── project.yml
├── repository.yml
├── sys
│   ├── config
│   ├── console
│   ├── coredump
│   ├── defs
│   ├── flash_map
│   ├── id
│   ├── log
│   ├── mfg
│   ├── reboot
│   ├── shell
│   ├── stats
│   └── sysinit
├── targets
│   └── unittest
├── test
│   ├── crash_test
│   ├── flash_test
│   ├── runtest
│   ├── testreport
│   └── testutil
├── time
│   └── datetime
└── util
    ├── cbmem
    ├── crc
    └── mem

87 directories, 9 files
```

As you can see, the core of the Apache Mynewt operating system has been brought 
into your local directory. 

<br>

### Test the project's packages

You have already built your first basic project. You can ask Newt to execute the unit tests in a package. For example, to test the `libs/os` package in the `apache-mynewt-core` repo, call newt as shown below.

```
$ newt test @apache-mynewt-core/sys/config
Testing package @apache-mynewt-core/sys/config/test-fcb
Compiling bootutil_misc.c
Compiling image_ec.c
Compiling image_rsa.c
Compiling image_validate.c
<snip>
```

**NOTE:** If you've installed the latest gcc using homebrew on your Mac, you will likely be running gcc-6. Make sure you have adjusted the compiler.yml configuration to reflect that as noted in [Native Install Option](native_tools.md). You can choose to downgrade to gcc-5 in order to use the default gcc compiler configuration for MyNewt.

**NOTE:** If you are running the standard gcc for 64-bit machines, it does not support 32-bit. In that case you will see compilation errors. You need to install multiboot gcc (e.g. gcc-multilib if you running on a 64-bit Ubuntu).

```
$ brew uninstall gcc-6
$ brew link gcc-5
```

<br>

To test all the packages in a project, specify `all` instead of the package name.

```no-highlight
$ newt test all
...lots of compiling and testing...
...about 2 minutes later ...
Compiling mn_sock_test.c
Archiving mn_socket.a
Linking test_mn_socket
Executing test: /Users/dsimmons/myproj/bin/unittest/sys/mn_socket/test_mn_socket
Passed tests: [libs/json libs/util libs/mbedtls net/nimble/host hw/hal libs/bootutil sys/log sys/config sys/fcb fs/nffs libs/os libs/boot_serial sys/mn_socket]
All tests passed
```

<br>

### Build the Project

To build and run your new application, simply issue the following command:

```
$ newt build my_blinky_sim 
Building target targets/my_blinky_sim
Compiling main.c
Archiving blinky.a
Compiling hal_bsp.c
Compiling os_bsp.c
Compiling sbrk.c
Archiving native.a
Compiling flash_map.c
<snip>
Linking blinky.elf
App successfully built: /Users/dsimmons/myproj/bin/my_blinky_sim/apps/blinky/blinky.elf
```

<br>

### Run the Project

You can run the simulated version of your project and see the simulated LED
blink.

```
$ ./bin/my_blinky_sim/apps/blinky/blinky.elf
hal_gpio set pin  1 to 0
```

<br>

### Complete

Congratulations, you have created your first project!  The blinky application
is not terribly exciting when it is run in the simulator, as there is no LED to
blink.  Apache Mynewt has a lot more functionality than just running simulated
applications.  It provides all the features you'll need to cross-compile your
application, run it on real hardware and develop a full featured application.

If you're interested in learning more, a good next step is to dig in to one of
the [tutorials](../tutorials/tutorials) and get a Mynewt project running on real hardware.

Happy Hacking!
