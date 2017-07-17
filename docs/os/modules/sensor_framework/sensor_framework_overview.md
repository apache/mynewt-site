# Mynewt Sensor Framework Overview

The Mynewt sensor framework is an abstraction layer between an application and sensor devices. The sensor framework provides the following support: 

* A set of APIs that allows developers to develop sensor device drivers within a common framework and enables application developers to develop applications that can access sensor data from any Mynewt sensor device using a common interface. 
* Support for onboard and off-board sensors.

* An OIC sensor server that exposes sensors as OIC resources and handles OIC CoAP requests for the sensor resources. A developer can easily develop a MyNewt OIC sensor enabled application that serves sensor resource requests from OIC client applications.

* A sensor shell command and optional sensor device driver shell commands to view sensor data and manage sensor device settings for testing and debugging sensor enabled applications and sensor device drivers.

![Alt Layout - Sensor Framework](/os/modules/sensor_framework/sensor_framework.png)
<br>
## Overview of Sensor Support Packages

* `hw/sensor`: The sensor framework package. This package implements the [sensor framework APIs](/os/modules/sensor_framework/sensor_api.md), the [OIC sensor server](/os/modules/sensor_framework/sensor_oic.md), and the [sensor shell command](/os/modules/sensor_framework/sensor_shell.md). 

* `hw/sensor/creator`: The sensor creator package. This package supports off-board sensor devices . It creates the OS devices for the sensor devices that are enabled in an application and configures the sensor devices with default values. See the [Creating and Configuring a Sensor Device](/os/modules/sensor_framework/sensor_create.md) page for more information.

* `hw/bsp/`: The BSP for boards that support onboard sensors. The BSP creates the OS devices for the onboard sensors that the board supports and configures the sensors with default values.  See the [Creating and Configuring a Sensor Device](/os/modules/sensor_framework/sensor_create.md) page for more information.

* `hw/drivers/sensors/*`: These are the sensor device driver packages. The `hw/drivers/sensors/<sensorname>` package is the device driver for a sensor named `SENSORNAME`. See the [Sensor Device Driver](/os/modules/sensor_framework/sensor_driver.md) page for more information.
