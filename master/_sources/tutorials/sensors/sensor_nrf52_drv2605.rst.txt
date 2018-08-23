Enabling and Calibrating Off-Board DRV2605 LRA Actuator
-------------------------------------------------------

This tutorial shows you how to run the **sensors\_test** application
on an nRF52-DK board to communicate, via the I2C interface, with the :doc:`Adafruit
DRV2605 <https://learn.adafruit.com/adafruit-drv2605-haptic-controller-breakout/overview>`
device. The DRV2605 driver includes the ``drv2605`` shell command that allows you
to quickly to view the status, calibrate and actuate your motor in
preperation for using it programmatically in your own app.

This tutorial shows you how to:

-  Create and build the application and bootloader targets.
-  Connect a DRV2605 actuator device to an nRF52-DK board.
-  Run ``drv2605`` shell commands to view the actuator data
   and control the drv2605 device.

.. contents::
  :local:
  :depth: 2

Prerequisites
~~~~~~~~~~~~~

-  Meet the prerequisites listed in :doc:`Sensor Tutorials <sensors>`
-  Understand how to :doc:`add an offboard sensor <sensor_nrf52_bno055>`,
   we wont be covering bootloader and application console connection here.
-  Have a Nordic nRF52-DK board.
-  Have an `Adafruit DRV2605 <https://learn.adafruit.com/adafruit-drv2605-haptic-controller-breakout/overview>`__
   actuator and LRA motor.


Step 1: Creating the Application Target
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In this step, you create a target for the sensors\_test application that enables the DRV2605
off-board device.

To add the DRV2605 device support, you create the application target with
the following syscfg settings enabled:

-  ``I2C_0``: Enables the I2C interface 0 in the nRF52 BSP HAL setting.
-  | ``DRV2605_OFB``: Enables support for the DRV2605 actuator in the sensor
     creator package (``hw/sensor/creator``).
   | When this setting is enabled, the creator package performs the
     following:

   -  Includes the DRV2605 driver package (``hw/drivers/drv2605``)
      as a package dependency.
   -  Creates an os device for the device in the Mynewt kernel.
   -  Configures the device with default values.

-  ``DRV2605_CLI``: Enables the ``drv2605`` shell command in the DRV2605
   device driver package. The sensors\_test application also uses this
   setting to conditionally include the call to the
   ``drv2605_shell_init()`` function to initialize the shell support in
   the driver.

-  ``DRV2605_EN_PIN``: The pin the driver needs to gpio in order to enable
    your DRV2605 device.

-  ``DRV2605_RATED_VOLTAGE``: I have no easy default for you here, it is 
   entirelay based on your purchased LRA motor. See 8.5.2.1 Rated Voltage
   Programming in the TI DRV2605 Datasheet or maybe talk to your motor supplier.
    
-  ``DRV2605_OD_CLAMP``: I have no easy default for you here, it is 
   entirelay based on your purchased LRA motor. See 8.5.2.2 Overdrive
   Voltage-Clamp Programming in the TI DRV2605 Datasheet or maybe talk
   to your motor supplier. NOTE: LRA and ERM (8) and (9) equations are
   swapped in the datasheet revision "SLOS854C REVISED SEPTEMBER 2014"

-  ``DRV2605_DRIVE_TIME``: I have no easy default for you here, it is 
   entirelay based on your purchased LRA motor. See 8.6.21, but generally
   it is computable with the equation 
   LRA DRIVE_TIME = (0.5 × (1/fLRA * 1000) - 0.5 ms) /  0.1 ms

1. Run the ``newt target create`` command, from your project base
directory, to create the target. We name the target
``nrf52_drv2605_test``:

.. code-block:: console


    $ newt target create nrf52_drv2605_test
    Target targets/nrf52_drv2605_test successfully created
    $

2. Run the ``newt target set`` command to set the app, bsp, and
build\_profile variables for the target:

.. code-block:: console


    $ newt target set nrf52_drv2605_test app=@apache-mynewt-core/apps/sensors_test bsp=@apache-mynewt-core/hw/bsp/nrf52dk build_profile=debug
    Target targets/nrf52_drv2605_test successfully set target.app to @apache-mynewt-core/apps/sensors_test
    Target targets/nrf52_drv2605_test successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52dk
    Target targets/nrf52_drv2605_test successfully set target.build_profile to debug

    $

3. Run the ``newt target set`` command to enable the ``I2C_0``,
``DRV2605_OFB``, ``DRV2605_CLI``, ``DRV2605_EN_PIN``, ``DRV2605_RATED_VOLTAGE``,
``DRV2605_OD_CLAMP``, and ``DRV2605_DRIVE_TIME`` syscfg settings:

.. code-block:: console


    $ newt target set nrf52_drv2605_test syscfg=DRV2605_OFB=1:I2C_0=1:DRV2605_CLI=1:DRV2605_EN_PIN=3:DRV2605_RATED_VOLTAGE=0x53:DRV2605_OD_CLAMP=0x69:DRV2605_DRIVE_TIME=20
    Target targets/nrf52_drv2605_test successfully set target.syscfg to DRV2605_OFB=1:I2C_0=1:DRV2605_CLI=1:DRV2605_EN_PIN=3:DRV2605_RATED_VOLTAGE=0x53:DRV2605_OD_CLAMP=0x69:DRV2605_DRIVE_TIME=20

    $

Step 2: Creating an Application Image and loading it
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This tutorial assumes you have a functioning bootloader as taught in
:doc:`add an offboard sensor <sensor_nrf52_bno055>`
Now run the ``newt create-image`` command to create an image file. You may
assign an arbitrary version (e.g. 1.0.0) to the image.

.. code-block:: console


    $ newt build nrf52_drv2605_test && newt create-image nrf52_drv2605_test 1.0.0
    App image succesfully generated: ~/dev/myproj/bin/targets/nrf52_drv2605_test/app/apps/sensors_test/sensors_test.img


Step 3: Communicating with and Calibrating the DRV2605 device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This tutorial assumes you have a functioning application console as
taught in :doc:`add an offboard sensor <sensor_nrf52_bno055>`
The DRV2605 device driver implements the ``drv2605`` shell command
that allows you to:

-  Query the chip id, content of registers, calibrations.
-  Reset the device.
-  Change the power mode.
-  Change the operation mode.
-  Load waveforms to actuate.
-  Actuate the device.

**Example 1:** Query the device chip id:

.. code-block:: console


    711273 compat> drv2605 chip_id
    769056 0x07

**Example 2:** Run Diagnostics on your motor setup numbers:

.. code-block:: console


    827472 compat> drv2605 op_mode diag
    drv2605 op_mode diag
    829717 op_mode succeeded

If that didn't work or you will have to compute different DRV2605_RATED_VOLTAGE,
DRV2605_OD_CLAMP, and DRV2605_DRIVE_TIME values and try again or maybe talk to your
motor manufacturer or TI for more help.

**Example 3:** Run Calibration on your motor:
Theres a lot more setup numbers you could enter here for the DRV2605 to figure out
how to actuate your motor, but some of them it can figure out itself through auto calibration.
Lets run autocalibration and then dump the fresh calibration numbers:

.. code-block:: console

    001407 compat> drv2605 op_mode cal
    drv2605 op_mode cal
    001931 op_mode succeeded
    drv2605 dump_cal
    DRV2605_CALIBRATED_COMP: 0x09
    DRV2605_CALIBRATED_BEMF: 0x79
    DRV2605_CALIBRATED_BEMF_GAIN: 1

You could programmatically run this on every startup, but more likely you'd want to save these
as in your syscfg.yml and restart. Presumably you'd never have to do these steps ever again.

Step 4: Actually Actuate
~~~~~~~~~~~~~~~~~~~~~~~~~

Now you're ready to (sigh) rumble. One way to use the DRV2605 device is to enable
the ROM mode to use its stored patterns. Technically you dont need to do this after
first configure as ROM mode is the default mode:

.. code-block:: console

    021773 compat> drv2605 op_mode rom
    drv2605 op_mode rom
    037245 op_mode succeeded

Now you can load up to 8 internal roms or delays. In this case we'll use four hard
clicks (1) with max delays (255) in between. You may only have to do this once per
boot if you wanted to use this same sequence every time you trigger the DRV2605 device.

.. code-block:: console

    120858 compat> drv2605 load_rom 1 255 1 255 1 255 1 255
    drv2605 load_rom 1 255 1 255 1 255 1 255
    122555 Load succeeded

The motor is in standby by default after a mode change, so enable it:

.. code-block:: console

    002111 compat> drv2605 power_mode active
    drv2605 power_mode active
    003263 power_mode succeeded

Now you can trigger those forms as many times as you want or load new forms and trigger again:

.. code-block:: console

    122555 compat> drv2605 trigger
    drv2605 trigger
    128806 Trigger succeeded

Conclusion
~~~~~~~~~~


You've successfully enabled a mynewt application to communicate with a drv2605 device,
calibrated it and actuated a motor! Next youll want to look at the code comments
on the drv2605.c file and how the drv2605_shell.c file is implemented so you can
setup and actuate your device programmatically within your application.


