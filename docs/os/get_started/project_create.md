## Create Your First Mynewt Project

This page shows how to create a Mynewt Project using the `newt` command-line tool.

<br>

### Prerequisites

* Have Internet connectivity to fetch remote Mynewt components.
* Install Newt:
    * If you have taken the native install route,  see the installation instructions for [Mac OS](../../newt/install/newt_mac.md) or for [Linux](../../newt/install/newt_linux.md). 
    * If you have taken the Docker route, you have already installed Newt.
* Install the [native toolchain](native_tools.md) to compile and build a Mynewt native application. 

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

**Note**: If you do not have `tree`, run `brew install tree` to install on Mac OS or run `sudo apt-get install tree` to install on Linux.

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
    vers: 1-latest
    user: apache
    repo: incubator-mynewt-core
```
Changing to 0-dev will put you on the latest master branch. **This branch may not be stable and you may encounter bugs or other problems.**

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
│   ├── blesplit
│   ├── bletest
│   ├── bletiny
│   ├── bleuart
│   ├── boot
│   ├── fat2native
│   ├── ffs2native
│   ├── ocf_sample
│   ├── slinky
│   ├── slinky_oic
│   ├── spitest
│   ├── splitty
│   ├── test
│   ├── testbench
│   └── timtest
├── boot
│   ├── boot_serial
│   ├── bootutil
│   ├── split
│   └── split_app
├── compiler
│   ├── arm-none-eabi-m0
│   ├── arm-none-eabi-m4
│   ├── gdbmacros
│   ├── mips
│   ├── sim
│   └── sim-mips
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
│   ├── disk
│   ├── fatfs
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
│   └── testutil
├── time
│   └── datetime
└── util
    ├── cbmem
    ├── crc
    └── mem

94 directories, 9 files
```

As you can see, the core of the Apache Mynewt operating system has been brought 
into your local directory. 

<br>

### Test the project's packages

You have already built your first basic project. You can ask Newt to execute the unit tests in a package. For example, to test the `sys/config` package in the `apache-mynewt-core` repo, call newt as shown below.

```no-highlight
$ newt test @apache-mynewt-core/sys/config
Testing package @apache-mynewt-core/sys/config/test-fcb
Compiling bootutil_misc.c
Compiling image_ec.c
Compiling image_rsa.c
Compiling image_validate.c

    ...

Linking ~/dev/myproj/bin/targets/unittest/sys_config_test-fcb/app/sys/config/test-fcb/sys_config_test-fcb.elf
Executing test: ~/dev/myproj/bin/targets/unittest/sys_config_test-fcb/app/sys/config/test-fcb/sys_config_test-fcb.elf
Testing package @apache-mynewt-core/sys/config/test-nffs
Compiling repos/apache-mynewt-core/encoding/base64/src/hex.c
Compiling repos/apache-mynewt-core/fs/fs/src/fs_cli.c
Compiling repos/apache-mynewt-core/fs/fs/src/fs_dirent.c
Compiling repos/apache-mynewt-core/fs/fs/src/fs_mkdir.c
Compiling repos/apache-mynewt-core/fs/fs/src/fs_mount.c
Compiling repos/apache-mynewt-core/encoding/base64/src/base64.c
Compiling repos/apache-mynewt-core/fs/fs/src/fs_file.c
Compiling repos/apache-mynewt-core/fs/disk/src/disk.c
Compiling repos/apache-mynewt-core/fs/fs/src/fs_nmgr.c
Compiling repos/apache-mynewt-core/fs/fs/src/fsutil.c
Compiling repos/apache-mynewt-core/fs/nffs/src/nffs.c

     ...

Linking ~/dev/myproj/bin/targets/unittest/sys_config_test-nffs/app/sys/config/test-nffs/sys_config_test-nffs.elf
Executing test: ~/dev/myproj/bin/targets/unittest/sys_config_test-nffs/app/sys/config/test-nffs/sys_config_test-nffs.elf
Passed tests: [sys/config/test-fcb sys/config/test-nffs]
All tests passed
```

**NOTE:** If you've installed the latest gcc using homebrew on your Mac, you will likely be running gcc-6. Make sure you have adjusted the compiler.yml configuration to reflect that as noted in [Native Install Option](native_tools.md). You can choose to downgrade to gcc-5 in order to use the default gcc compiler configuration for MyNewt.

**NOTE:** If you are running the standard gcc for 64-bit machines, it does not support 32-bit. In that case you will see compilation errors. You need to install multiboot gcc (e.g. gcc-multilib if you running on a 64-bit Ubuntu).

```no-highlight
$ brew uninstall gcc-6
$ brew link gcc-5
```

<br>

To test all the packages in a project, specify `all` instead of the package name.

```no-highlight
$ newt test all
Testing package @apache-mynewt-core/boot/boot_serial/test
Compiling repos/apache-mynewt-core/boot/boot_serial/test/src/boot_test.c
Compiling repos/apache-mynewt-core/boot/boot_serial/test/src/testcases/boot_serial_setup.c

     ...

Linking ~/dev/myproj/bin/targets/unittest/boot_boot_serial_test/app/boot/boot_serial/test/boot_boot_serial_test.elf

...lots of compiling and testing...

Linking ~/dev/myproj/bin/targets/unittest/util_cbmem_test/app/util/cbmem/test/util_cbmem_test.elf
Executing test: ~/dev/myproj/bin/targets/unittest/util_cbmem_test/app/util/cbmem/test/util_cbmem_test.elf
Passed tests: [boot/boot_serial/test boot/bootutil/test crypto/mbedtls/test encoding/base64/test encoding/cborattr/test encoding/json/test fs/fcb/test fs/nffs/test kernel/os/test net/ip/mn_socket/test net/nimble/host/test net/oic/test sys/config/test-fcb sys/config/test-nffs sys/flash_map/test sys/log/full/test util/cbmem/test]
All tests passed

```

<br>

### Build the Project

To build and run your new application, simply issue the following command:

```no-highlight
$ newt build my_blinky_sim 
Building target targets/my_blinky_sim
Compiling repos/apache-mynewt-core/hw/hal/src/hal_common.c
Compiling repos/apache-mynewt-core/hw/drivers/uart/src/uart.c
Compiling repos/apache-mynewt-core/hw/hal/src/hal_flash.c
Compiling repos/apache-mynewt-core/hw/bsp/native/src/hal_bsp.c
Compiling repos/apache-mynewt-core/hw/drivers/uart/uart_hal/src/uart_hal.c
Compiling apps/blinky/src/main.c

    ...


Archiving sys_mfg.a
Archiving sys_sysinit.a
Archiving util_mem.a
Linking ~/dev/myproj/bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf
Target successfully built: targets/my_blinky_sim

```

<br>

### Run the Project

You can run the simulated version of your project and see the simulated LED
blink. If you are using newt docker, use `newt run` to run the simulated binary.

```no-highlight
$ newt run my_blinky_sim
Loading app image into slot 1
    ...
Debugging ~/dev/myproj/bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf
    ...
Reading symbols from /bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf...done.
(gdb)
```
Type `r` at the `(gdb)` prompt to run the project. You will see an output indicating that the hal_gpio pin is toggling between 1 and 0 in a simulated blink.

If you natively install the toolchain, you can either use `newt run` or call the binary directly. Generally, `newt run` is the expected way to call things.

```no-highlight
$ ./bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf
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
