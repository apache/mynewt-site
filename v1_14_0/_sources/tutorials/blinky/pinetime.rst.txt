Blinky, your "Hello World!", on a PineTime smartwatch
-------------------------------------------------------

This tutorial shows you how to create, build, and run the Blinky
application on a PineTime smartwatch.

.. contents::
  :local:
  :depth: 2

Prerequisites
~~~~~~~~~~~~~

-  Meet the prerequisites listed in :doc:`Project Blinky <blinky>`.
-  Have a `PineTime Dev Kit <https://store.pine64.org/?product=pinetime-dev-kit>`__
-  Have a `ST-LINK programmer <https://www.st.com/en/development-tools/st-link-v2.html>`__ or a cheap clone
-  Install a patched version of OpenOCD 0.10.0 described in :doc:`Install OpenOCD <../../get_started/native_install/cross_tools>`.

If you have not removed the flash protection yet, you should to that first. 
See `the PineTime wiki <https://wiki.pine64.org/index.php/Reprogramming_the_PineTime>`__ 
for instructions.

Create a Project
~~~~~~~~~~~~~~~~

Create a new project if you do not have an existing one. You can skip
this step and proceed to `Create the Targets`_ if you
already have a project created.

Run the following commands to create a new project:

.. code-block:: console

        $ mkdir ~/dev
        $ cd ~/dev
        $ newt new blinky-pinetime
        Downloading project skeleton from apache/mynewt-blinky...
        Downloading repository mynewt-blinky 
        Installing skeleton in blinky-pinetime...
        Project blinky-pinetime successfully created.
        $ cd blinky-pinetime
        $ newt upgrade
        newt upgrade
        Downloading repository mynewt-core (commit: master)
        Downloading repository mynewt-nimble (commit: master)
        Downloading repository mcuboot (commit: master)
        Making the following changes to the project:
            install apache-mynewt-core (1.7.0)
            install apache-mynewt-nimble (1.2.0)
            install mcuboot (1.3.1)
        $

Create the Targets
~~~~~~~~~~~~~~~~~~

Create two targets for the PineTime - one for the bootloader and
one for the Blinky application.

Run the following ``newt target`` commands, from your project directory,
to create a bootloader target. We name the target ``boot-pinetime``:

.. code-block:: console
    :emphasize-lines: 3

    $ newt target create boot-pinetime
    $ newt target set boot-pinetime app=@mcuboot/boot/mynewt
    $ newt target set boot-pinetime bsp=@apache-mynewt-core/hw/bsp/pinetime
    $ newt target set boot-pinetime build_profile=optimized

Run the following ``newt target`` commands to create a target for the
Blinky application. We name the target ``blinky-pinetime``.

.. code-block:: console
    :emphasize-lines: 3

    $ newt target create blinky-pinetime
    $ newt target set blinky-pinetime app=apps/blinky
    $ newt target set blinky-pinetime bsp=@apache-mynewt-core/hw/bsp/pinetime
    $ newt target set blinky-pinetime build_profile=debug

You can run the ``newt target show`` command to verify the target
settings:

.. code-block:: console

    $ newt target show
    targets/blinky-pinetime
        app=apps/blinky
        bsp=@apache-mynewt-core/hw/bsp/pinetime
        build_profile=debug
    targets/boot-pinetime
        app=@mcuboot/boot/mynewt
        bsp=@apache-mynewt-core/hw/bsp/pinetime
        build_profile=optimized

Build the Target Executables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Run the ``newt build boot-pinetime`` command to build the bootloader:

.. code-block:: console

    $ newt build boot-pinetime
    Building target targets/boot-pinetime
    Compiling bin/targets/boot-pinetime/generated/src/boot-pinetime-sysflash.c
    Compiling bin/targets/boot-pinetime/generated/src/boot-pinetime-sysinit-app.c
    Compiling bin/targets/boot-pinetime/generated/src/boot-pinetime-sysdown-app.c
    Compiling repos/mcuboot/boot/bootutil/src/boot_record.c
    Compiling repos/mcuboot/boot/bootutil/src/caps.c

        ...

    Archiving sys_sysinit.a
    Archiving util_mem.a
    Archiving util_rwlock.a
    Linking /tmp/blinky-pinetime/bin/targets/boot-pinetime/app/boot/mynewt/mynewt.elf
    Target successfully built: targets/boot-pinetime


Run the ``newt build blinky-pinetime`` command to build the Blinky
application:

.. code-block:: console

    $ newt build blinky-pinetime
    Building target targets/blinky-pinetime
    Compiling bin/targets/blinky-pinetime/generated/src/blinky-pinetime-sysinit-app.c
    Compiling bin/targets/blinky-pinetime/generated/src/blinky-pinetime-sysdown-app.c
    Compiling bin/targets/blinky-pinetime/generated/src/blinky-pinetime-sysflash.c
    Compiling repos/apache-mynewt-core/hw/bsp/pinetime/src/sbrk.c
    Compiling apps/blinky/src/main.c
    Assembling repos/apache-mynewt-core/hw/bsp/pinetime/src/arch/cortex_m4/gcc_startup_nrf52.s
    Compiling repos/apache-mynewt-core/hw/bsp/pinetime/src/hal_bsp.c

        ...

    Archiving sys_sysinit.a
    Archiving util_mem.a
    Archiving util_rwlock.a
    Linking /tmp/blinky-pinetime/bin/targets/blinky-pinetime/app/apps/blinky/blinky.elf
    Target successfully built: targets/blinky-pinetime

Sign and Create the Blinky Application Image
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Run the ``newt create-image blinky-pinetime 1.0.0`` command to create and
sign the application image. You may assign an arbitrary version (e.g.
1.0.0) to the image.

.. code-block:: console

    $ newt create-image blinky-pinetime 1.0.0
    App image succesfully generated: ~/dev/blinky-pinetime/bin/targets/blinky-pinetime/app/apps/blinky/blinky.img

Connect to the Board
~~~~~~~~~~~~~~~~~~~~

-  Connect a ST-LINK programmer via USB to your computer.
-  Connect the ST-LINK programmer to the SWD connectors of the PineTime. The 
   easiest way it to mount the PineTime on a cradle and let the programmer cable 
   rest on the contact pads. See `PineTime wiki <https://wiki.pine64.org/index.php/PineTime#SWD_Pinout>`__ 
   for the pinout.

Load the Bootloader and the Blinky Application Image
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Run the ``newt load boot-pinetime`` command to load the bootloader onto the
board:

.. code-block:: console

    $ newt load boot-pinetime
    Loading bootloader
    $

Run the ``newt load blinky-pinetime`` command to load the Blinky
application image onto the board.

.. code-block:: console

    $ newt load blinky-pinetime
    Loading app image into slot 1

You should see the backlight of the screen board blink!

Note: The screen itself will stay black, this could make the blinking difficult to see.
