Mynewt FAQ - Troubleshooting/Debugging
======================================

.. contents::
  :local:
  :depth: 1

Concurrent debug sessions with two boards
-----------------------------------------

**Q**: Can I run concurrent GDB connections to multiple devices? Is the GDB port hardcoded?

Yes, starting with release 1.5 Mynewt allows "newt debug" to have a session with JLink as well as openocd simultaneously open. And no, the GDB port is not hardcoded. You can specify it with the -port option. For example:

.. code-block:: console
 
    newt debug slinky_nrf52 --extrajtagcmd "-port 5431 -select usb=682148664"

Error: Unsatisfied APIs detected
--------------------------------

**Q**: I ran into the following error message: 

.. code-block:: console 

    Error: Unsatisfied APIs detected:
    * stats, required by: hw/drivers/sensors/bmp280, hw/drivers/sensors/ms5837, net/oic

How do I resolve this?

**A**: You may be missing some package dependencies in your ``pkg.yml`` file. In this case, you need to include 
``sys/stats`` (either ``sys/stats/full`` or ``sys/stats/stub``) to your ``pkg.yml`` file. You can add it to either 
your app’s or target’s pkg.yml file, but if you have a custom app it is recommended that you add it to your app’s 
``pkg.yml``. That way you can have multiple targets for the same app, without having to add it to every target. 
Moreover, if you share your app package, others won’t run into the same error when building it. 

Greyed out files on iOS 11
--------------------------
 
**Q**: I'm trying to use the Adafruit Mynewt Manager to upload a custom image over BLE. Uploading one of the provided 
``bleuartx000.img`` works fine and I can boot into them, confirm etc. However, when I try to upload a custom image I 
can't even seem to add it to the app. Images stored in the iCloud drive just appear as disabled icons. Anyone with a 
clue as to how to get that working?

**A**: The new iOS version no longer allows files with unrecognized extensions to be selected. Try renaming the file to 
something more compatible (e.g. ``.txt``). 

``arm-none-eabi-gcc`` Build Error for Project
---------------------------------------------

**Q**: I am having this error when I try to build my project:

.. code-block:: console

  Building target targets/stm32l072czy6tr_boot
  Error: exec: "arm-none-eabi-gcc": executable file not found in $PATH

How do I add it?

**A**: First, install the GNU Arm Embedded Toolchain if you haven’t already. Then, depending on your OS, add the link to 
your ``arm-none-eabi-gcc`` executable path to your PATH environment variable.

Issues Running Image on Boot
----------------------------

**Q**: I was able to successfully create a BSP for my custom board (using nRF52 MCU), then build and run that image in the 
debugger. However, it does not run on boot. Any ideas to fix the issue?

**A**: A good process in general is to do a full flash erase, then flash the bootloader and the running image. Make sure to 
dump the contents of flash and see that it actually gets written there as well. If you experience the issue again after a 
reboot, you will also want to set ``MCU_DCDC_ENABLED:0`` then redo the process of erase, rebuild, and reload. 

Enable Trace in Mynewt
----------------------

**Q**: I’m trying to use gdb with Trace, but do not know how to enable it. How do I do this in Mynewt?

**A**: To enable Trace, you can add ``cflags`` to ``pkg.yml`` in your target directory: 

.. code-block:: console

    ~/dev/mynewt $ cat targets/mytarget/pkg.yml
    ### Package: targets/mytarget
    pkg.name: “targets/mytarget”
    pkg.type: "target"
    pkg.description: 
    pkg.author: 
    pkg.homepage:
    pkg.cflags:
      - -DENABLE_TRACE

Bug With Older Versions of ``gcc``
----------------------------------

**Q**: I got the following error using ``newt build``. How do I fix it?

.. code-block:: console

  Error: repos/apache-mynewt-core/sys/log/modlog/src/modlog.c: In function 'modlog_alloc':
  repos/apache-mynewt-core/sys/log/modlog/src/modlog.c:61:23: error: missing braces around initializer [-Werror=missing-braces]
            *mm = (struct modlog_mapping) { 0 };
                             ^
  repos/apache-mynewt-core/sys/log/modlog/src/modlog.c:61:23: error: (near initialization for '(anonymous).next') [-Werror=missing-braces]
  cc1: all warnings being treated as errors

**A**: That is a bug in older versions of ``gcc`` (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=53119).  The recommended ``gcc`` version is 7.x.
