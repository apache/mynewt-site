Creating Your First Mynewt Project
----------------------------------

This page shows you how to create a Mynewt project using the ``newt``
command-line tool. The project is a blinky application that toggles a
pin. The application uses the Mynewt's simulated hardware and runs as a
native application on Linux, FreeBSD and older versions of Mac OS.

**Note:** The Mynewt simulator is not yet supported natively on Windows or
newer Mac OS versions.

If you are using the native install option (not the Docker option), you will
need to create the blinky application for a target board. We recommend that
you read the section on creating a new project and fetching the source
repository to understand the Mynewt repository structure, create a new
project, and fetch the source dependencies before proceeding to
one of the :ref:`blinky_tutorials`.

This guide shows you how to:

1. Create a new project and fetch the source repository and
   dependencies.
2. Test the project packages. (Using Docker image for Windows and MacOS.)
3. Build and run the simulated blinky application.

.. contents::
 :local:
 :depth: 2

Prerequisites
~~~~~~~~~~~~~

-  Have Internet connectivity to fetch remote Mynewt components.
-  Install the newt tool:

   -  If you have taken the native install option, see the installation
      instructions for :doc:`Mac OS <../../newt/install/newt_mac>`,
      :doc:`Linux <../../newt/install/newt_linux>`, or
      :doc:`Windows <../../newt/install/newt_windows>`.
   -  If you have taken the Docker option, you have already installed
      Newt.

-  Install the :doc:`native toolchain <native_install/native_tools>` to compile and
   build a Mynewt native application.

Creating a New Project and Fetching the Source Repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section describes how to use the newt tool to create a new project
and fetch the core mynewt source repository.

Creating a New Project
^^^^^^^^^^^^^^^^^^^^^^^^^

Choose a name for your project. We name the project ``myproj``.

Run the ``newt new myproj`` command, from your **dev** directory, to
create a new project:

**Note:** This tutorial assumes you created a **dev** directory under
your home directory.

.. code-block:: console

    $ cd ~/dev
    $ newt new myproj
    Downloading project skeleton from apache/mynewt-blinky...
    Downloading repository mynewt-blinky (commit: master) ...
    Installing skeleton in myproj...
    Project myproj successfully created.

The newt tool creates a project base directory name **myproj**. All newt
tool commands are run from the project base directory. The newt tool
populates this new project with a base skeleton of a new Apache Mynewt
project in the project base directory. It has the following structure:

**Note**: If you do not have ``tree``, run ``brew install tree`` to
install on Mac OS, ``sudo apt-get install tree`` to install on Linux,
``pacman -Su tree`` from a MinGW terminal to install on Windows, and
``pkg install tree`` on FreeBSD.

.. code-block:: console

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

The newt tool installs the following files for a project in the project
base directory:

1. The file ``project.yml`` contains the repository list that the
   project uses to fetch its packages. Your project is a collection of
   repositories. In this case, the project only comprises the core
   mynewt repository. Later, you will add more repositories to include
   other mynewt components.
2. The file ``apps/blinky/pkg.yml`` contains the description of your
   application and its package dependencies.
3. A ``target`` directory that contains the ``my_blinky_sim`` directory.
   The ``my_blinky_sim`` directory a target information to build a
   version of myproj. Use ``newt target show`` to see available build
   targets.
4. A non-buildable target called ``unittest``. This is used internally
   by ``newt`` and is not a formal build target.

**Note:** The actual code and package files are not installed (except
the template for ``main.c``). See the next step to install the packages.

Fetching the Mynewt Source Repository and Dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

By default, Mynewt projects rely on a single repository:
**apache-mynewt-core** and uses the source in the master branch. If you
need to use a different branch, you need to change the ``vers`` value in
the project.yml file:

.. code-block:: yaml
    :emphasize-lines: 3

    repository.apache-mynewt-core:
        type: github
        vers: 1-latest
        user: apache
        repo: mynewt-core

Changing vers to 0-dev will put you on the latest master branch. **This
branch may not be stable and you may encounter bugs or other problems.**

Run the ``newt upgrade`` command, from your project base directory
(myproj), to fetch the source repository and dependencies.

**Note:** It may take a while to download the apache-mynewt-core
repository. Use the *-v* (verbose) option to see the installation
progress.

.. code-block:: console

    $ newt upgrade
    Downloading repository mynewt-core (commit: master) ...
    Downloading repository mynewt-mcumgr (commit: master) ...
    Downloading repository mynewt-nimble (commit: master) ...
    Downloading repository mcuboot (commit: master) from ...
    Making the following changes to the project:
    apache-mynewt-core successfully upgraded to version 1.7.0
    apache-mynewt-nimble successfully upgraded to version 1.2.0
    mcuboot successfully upgraded to version 1.3.1

View the core of the Apache Mynewt OS that is downloaded into your local
directory.

(The actual output will depend on what is in the latest 'master' branch)

.. code-block:: console

    $ repos/apache-mynewt-core/
    ├── apps
    │   ├── bleprph_oic
    │   ├── blesplit
    │   ├── bleuart
    │   ├── bsncent
    │   ├── bsnprph
    │   ├── bus_test
    │   ├── coremark
    │   ├── crypto_test
    │   ├── ffs2native
    │   ├── flash_loader
    │   ├── iptest
    │   ├── lora_app_shell
    │   ├── loraping
    │   ├── lorashell
    │   ├── metrics
    │   ├── ocf_sample
    │   ├── pwm_test
    │   ├── sensors_test
    │   ├── slinky
    │   ├── slinky_oic
    │   ├── spitest
    │   ├── splitty
    │   ├── testbench
    │   ├── timtest
    │   └── trng_test
    ├── boot
    │   ├── split
    │   └── split_app
    ├── CODING_STANDARDS.md
    ├── compiler
    │   ├── arc
    │   ├── arm-none-eabi-m0
    │   ├── arm-none-eabi-m3
    │   ├── arm-none-eabi-m33
    │   ├── arm-none-eabi-m4
    │   ├── arm-none-eabi-m7
    │   ├── gdbmacros
    │   ├── mips
    │   ├── riscv64
    │   ├── sim
    │   ├── sim-armv7
    │   ├── sim-mips
    │   └── xc32
    ├── crypto
    │   ├── mbedtls
    │   └── tinycrypt
    ├── docs
    │   ├── conf.py
    │   ├── doxygen.xml
    │   ├── index.rst
    │   ├── Makefile
    │   ├── os
    │   └── README.rst
    ├── encoding
    │   ├── base64
    │   ├── cborattr
    │   ├── json
    │   └── tinycbor
    ├── fs
    │   ├── disk
    │   ├── fatfs
    │   ├── fcb
    │   ├── fcb2
    │   ├── fs
    │   └── nffs
    ├── hw
    │   ├── battery
    │   ├── bsp
    │   ├── bus
    │   ├── charge-control
    │   ├── cmsis-core
    │   ├── drivers
    │   ├── hal
    │   ├── mcu
    │   ├── mips-hal
    │   ├── scripts
    │   ├── sensor
    │   └── util
    ├── kernel
    │   ├── os
    │   └── sim
    ├── libc
    │   └── baselibc
    ├── LICENSE
    ├── mgmt
    │   ├── imgmgr
    │   ├── mgmt
    │   ├── newtmgr
    │   └── oicmgr
    ├── net
    │   ├── ip
    │   ├── lora
    │   ├── mqtt
    │   ├── oic
    │   └── wifi
    ├── NOTICE
    ├── project.yml
    ├── README.md
    ├── RELEASE_NOTES.md
    ├── repository.yml
    ├── sys
    │   ├── config
    │   ├── console
    │   ├── coredump
    │   ├── defs
    │   ├── fault
    │   ├── flash_map
    │   ├── id
    │   ├── log
    │   ├── metrics
    │   ├── mfg
    │   ├── reboot
    │   ├── shell
    │   ├── stats
    │   ├── sys
    │   ├── sysdown
    │   ├── sysinit
    │   └── sysview
    ├── targets
    │   └── unittest
    ├── test
    │   ├── crash_test
    │   ├── flash_test
    │   ├── i2c_scan
    │   ├── runtest
    │   ├── spiflash_stress_test
    │   └── testutil
    ├── time
    │   ├── datetime
    │   ├── timepersist
    │   └── timesched
    ├── uncrustify.cfg
    ├── util
    │   ├── cbmem
    │   ├── cmdarg
    │   ├── crc
    │   ├── debounce
    │   ├── easing
    │   ├── mem
    │   ├── parse
    │   ├── rwlock
    │   ├── streamer
    │   └── taskpool
    └── version.yml

    131 directories, 14 files

Testing the Project Packages
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Note:** If you're running this with Docker, use ``newt`` wrapper
script as described in :doc:`Docker Container <docker>`. Unit tests
depend on Mynewt simulator.

You can use the newt tool to execute the unit tests in a package. For
example, run the following command to test the ``sys/config`` package in
the ``apache-mynewt-core`` repo:

.. code-block:: console

    $ newt test @apache-mynewt-core/sys/config
    Testing package @apache-mynewt-core/sys/config/selftest-fcb
    Compiling repos/apache-mynewt-core/crypto/tinycrypt/src/aes_decrypt.c
    Compiling repos/apache-mynewt-core/crypto/tinycrypt/src/aes_encrypt.c
    Compiling repos/apache-mynewt-core/crypto/tinycrypt/src/cbc_mode.c
    Compiling repos/apache-mynewt-core/crypto/tinycrypt/src/ccm_mode.c
    Compiling repos/apache-mynewt-core/crypto/tinycrypt/src/cmac_mode.c
    ...

    Linking ~/dev/myproj/bin/targets/unittest/sys_config_selftest-fcb/app/sys/config/selftest-fcb/sys_config_selftest-fcb.elf
    Executing test: ~/dev/myproj/bin/targets/unittest/sys_config_selftest-fcb/app/sys/config/selftest-fcb/sys_config_selftest-fcb.elf
    Testing package @apache-mynewt-core/sys/config/selftest-nffs
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

    Linking ~/dev/myproj/bin/targets/unittest/sys_config_selftest-nffs/app/sys/config/selftest-nffs/sys_config_selftest-nffs.elf
    Executing test: ~/dev/myproj/bin/targets/unittest/sys_config_selftest-nffs/app/sys/config/selftest-nffs/sys_config_selftest-nffs.elf
    Passed tests: [sys/config/selftest-fcb sys/config/selftest-nffs]
    All tests passed

**Note:** If you installed the latest gcc using homebrew on your Mac,
you are probably running gcc-6. Make sure you change the compiler.yml
configuration to specify that you are using gcc-6 (See :doc:`native_install/native_tools`). You can also
downgrade your installation to gcc-5 and use the default gcc compiler configuration for MyNewt:

.. code-block:: console

    $ brew uninstall gcc-6
    $ brew link gcc-5

**Note:** If you are running the standard gcc for 64-bit machines, it
does not support 32-bit. In that case you will see compilation errors.
You need to install multilib gcc (e.g. gcc-multilib if you running on a
64-bit Ubuntu).
**Note:** Running ``newt test all`` within Docker Container can take
a long time.

To test all the packages in a project, specify ``all`` instead of the
package name.

.. code-block:: console

    $ newt test all
    Testing package @apache-mynewt-core/crypto/mbedtls/selftest
    Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aesni.c
    Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aria.c
    Compiling repos/apache-mynewt-core/crypto/mbedtls/src/arc4.c
    Compiling repos/apache-mynewt-core/crypto/mbedtls/src/aes.c

    ...

    Linking ~/dev/myproj/bin/targets/unittest/crypto_mbedtls_selftest/app/@apache-mynewt-core/crypto/mbedtls/selftest/@apache-mynewt-core_crypto_mbedtls_selftest.elf
    Executing test: ~/dev/myproj/bin/targets/unittest/crypto_mbedtls_selftest/app/@apache-mynewt-core/crypto/mbedtls/selftest/@apache-mynewt-core_crypto_mbedtls_selftest.elf

    ...lots of compiling and testing...

    Linking ~/dev/myproj/bin/targets/unittest/boot_boot_serial_test/app/@mcuboot/boot/boot_serial/test/@mcuboot_boot_boot_serial_test.elf
    Executing test: ~/dev/myproj/bin/targets/unittest/boot_boot_serial_test/app/@mcuboot/boot/boot_serial/test/@mcuboot_boot_boot_serial_test.elf
    Passed tests: [crypto/mbedtls/selftest encoding/base64/selftest encoding/cborattr/selftest encoding/json/selftest fs/fcb/selftest fs/fcb2/selftest fs/nffs/selftest hw/drivers/flash/enc_flash/selftest hw/drivers/trng/trng_sw/selftest hw/sensor/selftest kernel/os/selftest net/ip/mn_socket/selftest net/oic/selftest sys/config/selftest-fcb sys/config/selftest-nffs sys/flash_map/selftest sys/log/full/selftest/align1 sys/log/full/selftest/align2 sys/log/full/selftest/align4 sys/log/full/selftest/align8 sys/log/full/selftest/fcb_bookmarks sys/log/modlog/selftest util/cbmem/selftest util/debounce/selftest util/rwlock/selftest cborattr/test nimble/controller/test nimble/host/test boot/boot_serial/test]
    All tests passed

Building and Running the Simulated Blinky Application
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The section shows you how to build and run the blinky application to run
on Mynewt's simulated hardware.

**Note**: This is not yet supported on Windows or newer versions of MacOS. Refer to the :ref:`blinky_tutorials` to create a blinky application for a target board, or run the the application within Docker Container.

Building the Application
^^^^^^^^^^^^^^^^^^^^^^^^^

To build the simulated blinky application, run ``newt build my_blinky_sim``:

.. code-block:: console

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

Running the Blinky Application
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can run the simulated version of your project and see the simulated
LED blink.

If you natively install the toolchain execute the binary directly:

.. code-block:: console

    $ ./bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf
    hal_gpio set pin  1 to 0

If you are using newt docker, use ``newt run`` to run the simulated binary.
Remember to use the ``newt`` wrapper script when doing that.

.. code-block:: console

    $ newt run my_blinky_sim
    Loading app image into slot 1
        ...
    Debugging ~/dev/myproj/bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf
        ...
    Reading symbols from /bin/targets/my_blinky_sim/app/apps/blinky/blinky.elf...done.
    (gdb)


Type ``r`` at the ``(gdb)`` prompt to run the project. You will see an
output indicating that the ``hal_gpio`` pin is toggling between 1 and 0
in a simulated blink.

Exploring other Mynewt OS Features
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Congratulations, you have created your first project! The blinky
application is not terribly exciting when it is run in the simulator, as
there is no LED to blink. Apache Mynewt has a lot more functionality
than just running simulated applications. It provides all the features
you'll need to cross-compile your application, run it on real hardware
and develop a full featured application.

If you're interested in learning more, a good next step is to dig in to
one of the :ref:`tutorials` and get a Mynewt
project running on real hardware.

Happy Hacking!
