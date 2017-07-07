## Sensor Tutorials Overview

This set of sensor tutorials allows you to explore the Mynewt Sensor Framework features and learn how to develop sensor-enabled Mynewt applications.

The Mynewt Sensor framework supports:

* Onboard and off-board sensors.
* Retrieving sensor data and controlling sensor devices via the Mynewt OS Shell.
* Retrieving sensor data over the OIC protocol and BLE transport.

### Available Tutorials

The tutorials are:

* [Enabling an Off-Board Sensor in an Existing Application](/os/tutorials/sensors/sensor_nrf52_bno055.md) -  This is a introductory tutorial that allows you to quickly bring up a sensor enabled application that retrieves data from a sensor device. We recommend that you work through this tutorial before trying one of the other tutorials.

* [Changing the Default Configuration for a Sensor](/os/tutorials/sensors/sensor_offboard_config.md) -  This tutorial shows you how to change the default configuration values for a sensor. 

* [Writing an Application for an Onboard Sensor](/os/tutorials/sensor_thingy_accelerator.md) -  This tutorial shows you how to develop a simple application for an device with an onboard sensor.

* [Enabling OIC Sensor Data Monitoring in an Existing Application](/os/tutorials/sensors/sensor_oic_nrf52_bno055.md) - This tutorial shows you how to enable support for sensor data monitoring via OIC in an existing sensor enabled application.


<br>
### Prerequisites
Ensure that you meet the following prerequisites before continuing with one of the tutorials. 

* Have Internet connectivity to fetch remote Mynewt components.
* Have a computer to build a Mynewt application and connect to the board over USB.
* Have a Micro-USB cable to connect the board and the computer.
* Install the newt tool and toolchains (See [Basic Setup](/os/get_started/get_started.md)).
* Read the Mynewt OS [Concepts](/os/get_started/vocabulary.md) section. 
* Create a project space (directory structure) and populate it with the core code repository (apache-mynewt-core) explained in [Creating Your First Project](/os/get_started/project_create).
* Work through one of the [Blinky Tutorials](/os/tutorials/blinky.md).
<br>

