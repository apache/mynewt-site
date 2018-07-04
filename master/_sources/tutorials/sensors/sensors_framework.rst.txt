Sensor Tutorials Overview
=========================

.. toctree::
   :hidden:
   
   Enable an Off-Board Sensor in an Existing Application <sensor_nrf52_bno055>
   Change the Default Configuration For a Sensor <sensor_offboard_config>
   Develope an Application for an Onboard Sensor <sensor_thingy_lis2dh12_onb>
   Enable OIC Sensor Data Monitoring <sensor_oic_overview>
   

This set of sensor tutorials allows you to explore the Mynewt Sensor
Framework features and learn how to develop sensor-enabled Mynewt
applications.

The Mynewt Sensor framework supports:

-  Onboard and off-board sensors.
-  Retrieving sensor data and controlling sensor devices via the Mynewt
   OS Shell.
-  Retrieving sensor data over the OIC protocol and BLE transport.

.. contents::
  :local:
  :depth: 2

Available Tutorials
~~~~~~~~~~~~~~~~~~~

The tutorials are:

- :doc:`sensor_nrf52_bno055` - This is an introductory tutorial that 
  shows you to how to quickly bring up a sensor enabled application that 
  retrieves data from a sensor device. We recommend that you work through 
  this tutorial before trying one of the other tutorials.
- :doc:`sensor_offboard_config` - This tutorial shows you how to 
  change the default configuration values for a sensor.
- :doc:`sensor_thingy_lis2dh12_onb` - This tutorial shows you how to 
  develop a simple application for a device with an onboard sensor.
- :doc:`sensor_oic_overview` - This tutorial shows you how to enable
  support for sensor data monitoring via OIC in an existing application.

Mynewt Smart Device Controller OIC App
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We use the ``Mynewt Sensor Monitor`` App on iOS or Android to retrieve
and display sensor data from the Mynewt OS OIC sensor applications
described in the OIC Sensor Data Monitoring tutorials. You can download
the app from either the Apple Store or Google Play Store.

**Note:** At the time of writing this tutorial, the iOS app was still in
the queue waiting to be placed in the App Store. You can build the iOS
app from source as indicated below.

If you would like to contribute or modify the Mynewt Smart Device
Controller App, see the `Android Sensor
source <https://github.com/runtimeco/android_sensor>`__ and `iOS Sensor
source <https://github.com/runtimeco/iOS_oic>`__ on github.

Prerequisites
~~~~~~~~~~~~~

Ensure that you meet the following prerequisites
before continuing with one of the tutorials.

-  Have Internet connectivity to fetch remote Mynewt components.
-  Have a computer to build a Mynewt application and connect to the
   board over USB.
-  Have a Micro-USB cable to connect the board and the computer.
-  Install the newt tool and toolchains ( See :doc:`Basic Setup <../../../get_started/index>` ).
-  Read the Mynewt OS :doc:`Concepts <../../../concepts>` section.
-  Create a project space (directory structure) and populate it with the core
   code repository (apache-mynewt-core) explained in :doc:`Creating Your First
   Project <../../../get_started/project_create>`
-  Work through one of the :doc:`Blinky Tutorials <../blinky/blinky>`