.. _mynewt_faq:


Mynewt OS related FAQ
=====================

Here are some lists, grouped by categories, of frequently asked
questions when working with Mynewt OS and tools.

.. contents::
  :local:
  :depth: 2
  
Bluetooth
---------

NimBLE on nRF52840
~~~~~~~~~~~~~~~~~~

**Q**: Is the nRF52840 supported by NimBLE?

**A**: The nRF52840 is supported, including Bluetooth 5 features.

Trigger Exactly One BLE Advertisement Immediately
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is there a way to trigger exactly one BLE advertisement immediately? I basically want to use BLE as a means to advertise to a whole group of devices and it needs to be relatively time-precise. Hoping for about 1ms precision, but it's okay if there's a delay as long as it's deterministic. 

**A**: With extended advertising you can enable an advertising instance for exactly 1 advertising event but there will be some delay before controller starts advertising which depends on the level of precision. The NimBLE controller always schedules the 1st advertising event with a constant 5ms delay. However, if there are other things scheduled in the controller it may need to schedule it later so it’s not guaranteed to be deterministic. Periodic advertising is currently not supported.


Supported Bluetooth Radio Transceivers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Are there any other Bluetooth radio transceivers that are supported already or anyone working on? If there is a Bluetooth radio that can be integrated using the HCI, we can use the NimBLE host? If so, I suppose we don't need detailed specs of the Bluetooth radio?

**A**: You should be able to run the NimBLE host against pretty much any controller using HCI. We have a BLE controller implementation for Nordic only, but host (in theory) should work with all. More likely, it will work with 5.0 controller. For 4.x controllers it may fail on initialization since we do not check controller features - but this can be fixed as for other radio transceivers. For example, there's NXP KW41Z which has BLE-compatible radio documented. However, NXP documentation is more or less a description of zillions of different registers so not as friendly as the one from Nordic which explains how to actually use it.

NimBLE Operational Questions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Can I update firmware via BLE for multiple devices simultaneously using a single device/phone supporting Bluetooth?

**A**: Yes, it is possible to update several Nimble devices simultaneously from a single phone (e.g., central) as long as the central can handle all the simultaneous Bluetooth connections. You can also do it using your computer as a central with newtmgr.  Just open two terminals and initiate a newtmgr image upload command in each, each to a different device.  You will, however, get better overall throughput if you limit yourself to one upgrade at a time.

**Q**: I have the following doubts on NimBLE: The document says 32+ concurrent connections, multiple connections in simultaneous central and peripheral roles. Does that mean the “device running NimBLE” can connect to 32 different other devices like phones?

**A**: Yes, with one caveat: each of the 32 centrals needs to be sufficiently cooperative in choosing connection partners (http://www.novelbits.io/ble-connection-intervals/). Your app might need to request different connection parameters from the centrals (using ``ble_gap_update_params``). 

Of course, you will also need to build the Mynewt image device with a configuration suitable for 32 concurrent connections (e.g., ``NIMBLE_MAX_CONNECTIONS=32``, etc.)

``blemesh`` Forgets All Keys on Restart
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
**Q**: Is it expected that the blemesh example forgets all the keys on restart and needs to be provisioned again? If so, how can I implement key persistence myself? Is there any API to obtain / provide mesh keys before the mesh node is started? I found bt_mesh_provision, but the comment there seems to indicate that this is not the right way to use it.
  
**A**: Mesh implementations do not persist keys at the moment. There is a plan to add it but not sure about timeline. It probably needs to be implemented inside mesh implementation so there's no API, but if you'd like to hack something I suggest taking a look at shell.c and testing.c - there are some testing functions to add/display keys. Another area to look if you actually want to persist keys to flash is ``net/nimble/host/store/config/src/ble_store_config.c``.  This is the code that persists and restores security material for (non-mesh) Bluetooth.

L2CAP Connection
~~~~~~~~~~~~~~~~

**Q**: I want to do an L2CAP connection, and am trying the auth-passkey command, but am not sure about the parameters ``psm``, ``action``, and ``oob``. What is ``psm``, and what is the value of that parameter in the btshell command ``l2cap-connect``? How do I set the parameters ``action`` and ``oob``?

**A**: ``psm`` stands for Protocol Service Multiplexer. You pass the ``psm`` value to either ``l2-cap-connect`` or ``l2cap-create-server``. The parameters ``action`` and ``oob`` are just passing constant values as defined in the API. 

Bitbang, BLE Mesh, BLE Advertising
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is it possible to run bitbanging and BLE mesh at the same time? How about running BLE Mesh and BLE advertising at the same time?
  
**A**: It is possible to run bitbanging and BLE mesh at the same time, but the bitbanging UART takes a lot of CPU on Nordic. We’ve run it at 9600 which would probably be okay for lower rate devices, but for reliability it is recommended to run at 4800. If this is just for the console and your UART port is tied up, ``rtt`` is recommended. Visit :doc:`Segger RTT Console <../tutorials/tooling/segger_rtt>` for more information. However, bitbanger can be handy given limited UARTs. 

You can certainly continue advertisements during connections, if you are using the GATT bearer for mesh. Mesh is also tied into the ext-adv bearer in Mynewt, which also allows for interleaving, even if you’re transmitting mesh data on advertising channels.

Extended Advertising with ``btshell``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I am using ``btshell`` for advertising with nRF52. When I use 31 bytes, ``mfg_data`` accepts the data with extended advertising. But when I use more bytes than that, ``mfg_data`` doesn’t accept it. Is 251 byte payload supported in extended advertising? How can I send more than a 251 byte payload on extended advertising? 

**A**: You need to set the ``BLE_EXT_ADV_MAX_SIZE`` syscfg to your required value. For example: 

.. code-block:: console

  newt target amend <your_target> syscfg=BLE_EXT_ADV=1:BLE_EXT_ADV_MAX_SIZE=1650

The default is 31 bytes, and the max is 1650. 

Keep in mind that with extended advertising, you cannot set advertising data for an instance configured as scannable (e.g. ``advertise-configure scannable=1``). Either set scan response data using ``advertise-set-scan-rsp`` command (parameters are the same as for ``advertise-set-adv-data``) or configure the instance as non-scannable. For example, ``advertise-configure`` alone will configure the instance as non-connectable and non-scannable which means you can set advertising data. Also note that if you continue to use a scannable instance you will need to perform active scanning in order to get scan response data. 

FYI, legacy advertising instances can accept both advertising and scan response data but since they use legacy PDUs the limit is still 31 bytes. 
  
Configuring Maximum Number of Connections for ``blehci``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: How do I set the maximum number of connections for the ``blehci`` :doc:`example <../tutorials/ble/blehci_project>`? I see there is a ``MYNEWT_VAL_BLE_MAX_CONNECTIONS``, but I don't know how to set it.

**A**:  You can to set it in target settings:

.. code-block:: console

  newt target amend <target> syscfg=BLE_MAX_CONNECTIONS=2

and then rebuild using ``newt build <target>``. ``MYNEWT_VAL_BLE_MAX_CONNECTIONS`` is just a symbol that is defined in ``syscfg.h`` which is autogenerated by ``newt`` tool and contains all the settings set at package/app/target level.

**Q**: What if I need to set 2 constants? What's the syntax?

**A**: You can set each setting in separate commands or separate ``key=value`` pairs with colon:

.. code-block:: console

  newt target amend <target> syscfg=FOO=1:BAR=2

**Q**: How do you know the constant is ``BLE_MAX_CONNECTIONS`` and not ``MYNEWT_VAL_BLE_MAX_CONNECTIONS``? Is there a place I can see those names?

**A**: This is actually one of NimBLE’s settings - you can find these settings available for different packages in the ``syscfg.yml`` files in the repository. You can also use ``newt target config show <target>`` to show all settings with their current values, and then change any of these settings accordingly. Each setting will get a symbol prefixed by ``MYNEWT_VAL_`` in the autogenerated ``syscfg.h`` file so you can get the actual setting name from this symbol. For more info on System Configuration and Initialization, please visit the :doc:`Compile-Time Configuration and Initialization <../../../os/modules/sysinitconfig/sysinitconfig.rst>` page in the OS User Guide.

Disconnect/Crash While Writing Analog Value From Central Module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**Q**: I’m trying to write analog sensor data from my central module to my peripheral module. I can receive the values from the ADC callback perfectly, but I’m not able to write them to the peripheral module. The peripheral module disconnects right when the ``ble_gattc_write_flat`` command is called. What could be causing the issue?

**A**: First, check the reason for the disconnect. The gap event callback should indicate the reason in ``disconnect.reason``. If the code never reaches the disconnect callback, then the code most likely crashed. If so, check whether ``ble_gattc_write_flat`` is called from an interrupt context. Calling into the BLE host from within an interrupt is a bad idea in general, and may cause a crash to occur because the Bluetooth host attempts to log to the console during the write procedure. Logging to the console uses quite a bit of stack space, so it is likely that the interrupt stack is overflowing. 

Instead, you should send an event to the event queue and handle this in a task context. You’ll need to associate the characteristic data with the event so that your event callback knows what payload to pass to the ``ble_gattc_write_flat()`` function. If you don’t need to perform multiple writes in rapid succession, then you can just use a single global event and single global buffer. However, you will still need to make sure your buffer doesn’t become corrupted by a subsequent ADC interrupt while you are in mid-write. 


Bootloader and Firmware Upgrade
-------------------------------

**Q**: I wanted to check if the stack provides firmware upgrade capability and if so, is there an example you can provide on how it is being done?
  
**A**: The newtmgr tool is used to upgrade Mynewt devices. Newtmgr is a command line tool, but there are other client libraries available. There is some information listed under the “Image Upgrade” header in the :doc:`Split Image documentation <../../../os/modules/split/split>`.
  
**Q**: Is there any documentation on using the bootloader? It sounds like it has baked-in support for serial loading, but I can’t find any details on serial protocol, or how to do a serial boot load. I assume we set a GPREGRET flag that tells the bootloader to expect to be flashed by serial, then it handles the rest. Is that true?
  
**A**: The serial bootloader would inspect a GPIO to see whether to wait for image upload commands or not. The protocol is the same newtmgr protocol we use for usual image uploads. For some the state reporting is simplified (omitted), and image upload goes to slot 0 instead of slot 1. The serial bootloading is built into newtmgr. For more information, refer to the documentation on the :doc:`Mynewt bootloader <../../../os/modules/bootloader/bootloader>`.

**Q**: Is there any major difference between MCUboot and the Mynewt bootloader?
  
**A**: They use different formats. The header is different as well, since you need to pass an extra flag (e.g. -2 to newt for ``create-image``).

**Q**: What is the difference between ``boot_serial`` and ``bootutil``?
  
**A**: ``boot_serial`` is used only for downloading images over the serial port. If you are using newtmgr to upload image over serial, it is handled in ``boot_serial``. All other bootloader code is in ``bootutil``.

File System
-----------

``nffs`` Setup
~~~~~~~~~~~~~~

**Q**: I'm struggling to find any examples for ``nffs``, especially how do I setup the ``nffs_area_desc`` correctly. Where do I set it up in the BSP especially?

**A**: It’s all taken care of in ``nffs_pkg_init``. As long as the ``nffs`` package is included in the project, it should initialize itself.  A few things you might find helpful:

1. The ``NFFS_FLASH_AREA`` syscfg setting specifies the flash area that contains the file system.
2. The BSP's ``bsp.yml`` file defines all the flash areas in the system, including the one specified in "1." above.

NFC 
---

The NFC stack is work in progress.

Newt
----

Difference Between ``newt`` Commands ``install``, ``upgrade``, and ``sync``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: What’s the difference between ``newt install``, ``newt upgrade``, and ``newt sync``?

**A**: 

- ``newt install``: downloads repos that aren't installed yet.  The downloaded version matches what ``project.yml`` specifies.
- ``newt upgrade``: performs an install, but also applies to repos that are already installed.
- ``newt sync``: fetches and pulls the latest for each repo, but does not change the branch (version).

``newt size`` Command vs. Elf File Size
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I did a test build of blinky for nrf52 and got an elf-file of size 295424 bytes. If I use the newt size command for the application it says something like: 18764 bytes. What does this mean?

**A**: Elfs have a lot of extra information. newt size will show the are in flash that is used which better matches the ``blinky.elf.bin`` file. Try ``running newt -ldebug build -v <your-target>`` and you will see something like this: 

.. code-block:: console 

  arm-none-eabi-objcopy -R .bss -R .bss.core -R .bss.core.nz -O binary ...

Newtmgr
-------

Connection Profile using newtmgr
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I’m trying to connect to an Adafruit nRF52 Feather Pro running Mynewt via the newtmgr tool on MacOS.  I have the device powered via micro USB to my Mac.  How do I find the “connection profile” of the device so I can connect to it? I want to communicate over BLE and not serial. 

**A**: A connection profile tells newtmgr how to communicate with your device. You can create one using the ``newtmgr conn add`` command. Try talking to your device without a connection profile first. If that works, you can create a profile to make it easier to communicate with the device going forward.

For BLE, you can send an echo command to your device with something like this:

.. code-block:: console 

  newtmgr --conntype ble --connstring peer_name=nimble-bleprph echo Hello

That ``peer_name string`` is correct if your device is running the ``bleprph`` app.  You'll need to adjust it if your device has a different BLE name. The ``--conntype ble --connstring peer_name=nimble-bleprph`` part is what would go in a connection profile. If you create one, then you can just specify the profile's name rather than typing that long string each time you send a command.

NMP
~~~

**Q**: What does NMP stand for?

**A**: Newtmgr Management Protocol

Newtmgr with the Adafruit nRF52DK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I'm having issues using Newt Manager with the Adafruit nRF52DK. What do I do?

You can specify the reduced MTU by adding ``mtu=128`` to your connection string. The reason for this change is that MTU is the serial boot loader used to have a smaller receive buffer (128 bytes). The newtmgr tool sends larger image chunks by default, so specifying the MTU will reduce the image size. 

**A**: There are two things you will need to do to fix any issues you encounter when working with the Adafruit nRF52DK and Newt Manager:

1. Specify a reduced MTU:
You can specify the reduced MTU by adding ``mtu=128`` to your connection string. The reason for this change is that MTU is the serial boot loader used to have a smaller receive buffer (128 bytes). The newtmgr tool sends larger image chunks by default, so specifying the MTU will reduce the image size. 

2. Indicate that the existing image should not be erased:
This is accomplished with the ``-e`` command line option. Your command line should look similar to the following:
   
.. code-block:: console

  $ newtmgr --conntype serial --connextra 'dev=/dev/ttyUSB0,mtu=128' image upload -e <image-path>
   
This change is needed because the serial boot loader doesn't support the standalone "erase image" command - as a result, it drops the request. The newtmgr image upload command starts by sending an erase command, then times out when it doesn't receive a response. The older version of newtmgr would use smaller chunk size for images, and it did not send the standalone erase command. When newtmgr was changed in versions 1.2 and 1.3, the serial boot loader changed along with it. The latest newtmgr is not compatible with an older version of the boot loader (which your board will probably ship with) without the above workarounds.

Porting Mynewt
--------------

Porting Mynewt to Core-M3 MCU
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I have a weird OS tick issue with a Core-M3 MCU port. The tick rate is set up identically to most ARM MCUs by setting up a hardware interrupt to trigger SysClock / ``os_tick_per_sec``. SysClock is correct and ``os_tick_per_sec`` is set to 1000, but the tick rate seems to be significantly higher. What am I doing wrong?

**A**: Check whether the LED is actually staying on or it is flickering really fast by debugging through the loop. If it is staying on, you may be getting into an ``assert()``. Otherwise, it is due to the fact that the OS timer wasn’t created, which is done by ``hal_bsp.c``. The OS timer needs a hardware timer to be running, so you will need to call ``hal_timer_init`` for timer 0 at one point.

Mynewt Syntax and Semantics
---------------------------

Ending the Delay of a Task Blocking a Call Early
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I have a task which is blocking on a call to ``os_time_delay()``. What is the recommended way to end the delay early in an ISR (e.g. button press)?

**A**: The best way would be to use a semaphore. Initialize the semaphore with a count of 0 (``os_sem_init()``), then block on the semaphore with the maximum delay you want to wait for (``os_sem_pend()``).  The button press event would wake the first task up early by calling ``os_sem_release()``.

Random Function / Device
~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Does Mynewt have a random function or random device?

**A**: ``baselibc`` has ``rand()``, and ``crypto/tinycrypt`` has ``hmac-prng``.

Setting ``serial`` and ``mfghash``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: What is ``mfghash``? How do I set ``serial`` and ``mfghash`` (currently blank in my app)?

**A**: ``mfghash`` is computed if you’re using ``newt mfg`` to construct your flash image, and it identifies the build of your bootloader. ``newt mfg`` bundles togetherthe bootloader, target image, and other data you’d want to bundle when creating an image to burn to flash. See the ``newt mfg`` :doc:`documentation<../../../command_list/newt_mfg>` for the construction side of things and ``apache-mynewt-core/sys/mfg/src/mfg.c`` for the firmware side. ``serial`` was intended to be used if you want to have your own naming scheme per device when building products; i.e. you want something other than the mcu serial number, or if you don’t have serial number available.

Leading Zeros Format in ``printf``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is there a way to make printf and console_printf honor the leading zeroes format? As in: 

``console_printf("%.2d", 5);`` 

outputting "05" instead of as for me now: "2d" ?

**A**: ``console_printf("%02d", 5);``
  
Mynewt Equivalent of UNIX ``sleep(3)``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is there an equivalent to the UNIX sleep(3)?
  
**A**: ``os_time_delay(OS_TICKS_PER_SEC * secs)``

Modules in Mynewt
-----------------

**Q**: Can you tell me what the purpose of the module argument is in the Mynewt logging library? It looks like it just takes an int. Is this just to assign an integer ID for each module that logs?

**A**: It is just an integer which accompanies each log entry.  It provides context for each log entry, and it allows a client to filter messages based on module (e.g. "give me all the file system log entries"). 

**Q**: So, what is the conceptual difference between a log name, and a module number? It seems like a log type would be assigned the same name as the module that is using it, and that the module number is just a numerical ID for the module. Basically, I don't understand what the purpose of storing the name into the log type is, and passing the module number in as part of ``LOG_<LEVEL>`` macro.

**A**: A log just represents a medium or region of storage (e.g., "console", or "flash circular buffer in 12kB of flash, starting at 0x0007d000").  Many parts of the system can write to the same log, so you may end up with Bluetooth, file system, and kernel scheduler entries all in the same log.  The module ID distinguishes these entries from one another. You can control level per module, so you can say, “give me all bluetooth warnings, but only give me system level errors”.

**Q**: Okay, so for something like console logging, we would likely register one log for the entire application, and give each module an ID?

**A**: I think the thought is that would be the debug log, and during development you could pipe that to console. In production, that might go in the spare image slot. I’m not sure if we support it yet, but we should make sure the log can write to multiple handlers at the same time.

Troubleshooting
---------------

Error: Unsatisfied APIs detected 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I ran into the following error message: 

.. code-block:: console 

    Error: Unsatisfied APIs detected:
    * stats, required by: hw/drivers/sensors/bmp280, hw/drivers/sensors/ms5837, net/oic

How do I resolve this?

**A**: You may be missing some package dependencies in your ``pkg.yml`` file. In this case, you need to include ``sys/stats`` (either ``sys/stats/full`` or ``sys/stats/stub``) to your ``pkg.yml`` file. You can add it to either your app’s or target’s pkg.yml file, but if you have a custom app it is recommended that you add it to your app’s ``pkg.yml``. That way you can have multiple targets for the same app, without having to add it to every target. Moreover, if you share your app package, others won’t run into the same error when building it. 

Greyed out files on iOS 11
~~~~~~~~~~~~~~~~~~~~~~~~~~
 
**Q**: I'm trying to use the Adafruit Mynewt Manager to upload a custom image over BLE. Uploading one of the provided ``bleuartx000.img`` works fine and I can boot into them, confirm etc. However, when I try to upload a custom image I can't even seem to add it to the app. Images stored in the iCloud drive just appear as disabled icons. Anyone with a clue as to how to get that working?

**A**: The new iOS version no longer allows files with unrecognized extensions to be selected. Try renaming the file to something more compatible (e.g. .txt). 

``arm-none-eabi-gcc`` Build Error for Project
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I am having this error when I try to build my project:

.. code-block:: console

  Building target targets/stm32l072czy6tr_boot
  Error: exec: "arm-none-eabi-gcc": executable file not found in $PATH

How do I add it?

**A**: First, install the GNU Arm Embedded Toolchain if you haven’t already. Then, depending on your OS, add the link to your ``arm-none-eabi-gcc`` executable path to your PATH environment variable.

Issues Running Image on Boot
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I was able to successfully create a BSP for my custom board (using nRF52 MCU), then build and run that image in the debugger. However, it does not run on boot. Any ideas to fix the issue?

**A**: A good process in general is to do a full flash erase, then flash the bootloader and the running image. Make sure to dump the contents of flash and see that it actually gets written there as well. If you experience the issue again after a reboot, you will also want to set ``MCU_DCDC_ENABLED:0`` then redo the process of erase, rebuild, and reload. 

Miscellaneous
-------------

Enable Trace in Mynewt
~~~~~~~~~~~~~~~~~~~~~~

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
    ​
    pkg.cflags:
      - -DENABLE_TRACE
      
Version Control Applications with Git 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: What's the recommended way to work with git when you want to version control your application? As ``apache-mynewt-core`` is already a repository, there is a repo in repo problem. Are there any good alternatives/tools to submodules, mirror, etc? Ideally, I want to version control everything from the top level project directory as well as upgrading apache-mynewt-core, pushing pull requests back to Mynewt if needed, etc.

**A**: You can simply have a separate git for your app. For example, if you followed the Blinky tutorial, your git would be in ``apps/foo``, while repos gits are in repos. You may also keep your app in the core repo, just have your own working branch for it. 

Another option is to have your git repository with local packages (including apps) and have ``repository.yml`` there so ``newt install`` can download all dependencies. Just make sure to put e.g. ``bin``, ``repos``, and ``project.state``, and others in ``.gitignore`` so they are not in version control. 


Alternatives to ``cmsis_nvic.c``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: What do I use instead of the full version of ``cmsis_nvic.c`` (i.e. for setting and getting irq priorities)?

**A**: Those functions are in the ``core_cmx.h`` files in ``hw/cmsis-core``.

Inverted Pin Value on nRF52-DK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: I’ve been experiencing what seems to be some oddities with ``hal_gpio_write``. It appears as though the LED pin value on the nRF52-DK is inverted (0 sets the pin high, 1 sets it low). I am checking the GPIO state by turning an LED on and off. Why is this the case?

**A**: LEDs on the nRF52-DK are connected to VDD and GPIO so you need to set GPIO to a low state in order to make it turn on. 

Documentation on Correct Values for ``ble_gap_disc_params``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is there documentation somewhere on correct values for ``ble_gap_disc_params``? I'm trying to do a passive discovery and getting ``BLE_HS_EINVAL``.

**A**: Unfortunately, not at the moment. Here is a brief description of the fields:

- ``itvl``: This is defined as the time interval from when the Controller started its last LE scan until it begins the subsequent LE scan. (units=0.625 msec)
- ``window``: The duration of the LE scan. ``LE_Scan_Window`` shall be less than or equal to ``LE_Scan_Interval`` (units=0.625 msec)
- ``filter_policy``: The only useful documentation is the table in the Bluetooth spec (section 2.E.7.8.10).  This field controls which types of devices to listen for.
- ``limited``: If set, only discover devices in limited discoverable mode.
- ``passive``: If set, don't send scan requests to advertisers (i.e., don't request additional advertising data).
- ``filter_duplicates``: If set, the controller ignores all but the first advertisement from each device.

Time Precision on nRF52
~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Can ``OS_TICKS_PER_SEC`` be changed per app? I'm on the nRF52 and I need better time precision than 128Hz.

**A**: No, it isn't possible to change the ticks per second for a single app.  That constant is defined to be most efficient for the particular MCU. 

If you need precision, the OS tick timer is probably not the right thing to use.  Take a look at :doc:`OS CPU Time <../../../os/core_os/cputime/os_cputime` for timer documentation. ``os_cputime`` has 1MHz frequency by default, and is enabled by default. It is recommended to use this for higher precision applications. 

Multicast Messaging and Group Messaging
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: Is it possible to send a broadcast message by one of the devices present in the mesh (e.g. broadcast an event which happened)? Something like a push notification instead of continuously polling for it by a client. 

**A**: It is possible to do so with a publish model. Group address or virtual address should help here, according to the Mesh spec. There is no real documentation on it but you can try it out on our ``btmesh_shell`` app. There is a ``shell.c`` file which exposes configuration client which you can use for testing (e.g. you can subscribe to virtual addresses). You can also trigger sending messages to devices. By playing with the ``dst`` command, you probably should be able to set destination to some group. However, since we do not support the provisioner role, there is a command provision which sets fixed keys so you can create a mesh network out of a couple of nodes without the actual provisioner. 

Difference between ``compiler.yml`` vs. ``pkg.yml``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``compiler.yml`` defines a compiler. ``pkg.yml`` contains metadata about the package. All packages have a ``pkg.yml`` file, even compiler packages.

Drivers in Mynewt
~~~~~~~~~~~~~~~~~

**Q**: Is this a correct assumption about Mynewt, that if there exists no driver implementation for a specific SoC, in ``hw/drivers/``, then it is not supported. For instance, there exists a flash driver for ``at45db``, this implies that the Nordic nRF52 SoC is not supported at the moment?

**A**: ``at45db`` is SPI, and any SPI would work. You send SPI configuration info when initializing. SPI drivers are below the ``hw/mcu/`` tree. ``hw/drivers/pwm`` and ``hw/drivers/adc`` are SoC specific. In general, drivers are for peripherals that aren't universally supported. Features that all (or nearly all) MCUs support are implemented in the HAL. For example, internal flash support is a HAL feature. Visit the :doc:`HAL Documentation <../../../os/modules/hal/hal>` for more information.

Reduce Code Size for Mynewt Image
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Q**: How do I reduce the code size for my Mynewt image?

**A**: Please refer to the tutorial documentation on :doc:`reducing application code size <../tutorials/other/codesize>`.
  
