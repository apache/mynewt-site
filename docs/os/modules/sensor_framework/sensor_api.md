## Sensor API

The sensor API implements the sensor abstraction and the functions:

* For a sensor device driver package to initialize a sensor object with the device specific information. 

* For an application to read sensor data from a sensor and to configure a sensor for polling.  

A sensor is represented by the `struct sensor` object.

### Sensor API Functions Used by a Sensor Device Driver Package


A sensor device driver package must use the sensor API to initialize device specific information for a sensor object and to change sensor configuration types.  

#### Initializing a Sensor Object

When the BSP or the sensor creator package creates an OS device for a sensor named `SENSORNAME`, it specifies the `<sensorname>_init()` callback function, that the device driver exports, for the `os_dev_create()` function to call to initialize the device.  The `<sensorname>_init()` function must use the following sensor API functions to set the driver and interface information in the sensor object: 

* The `sensor_init()` function to initialize the `struct sensor` object for the device.

* The `sensor_set_driver()` function to set the types that the sensor device supports and the sensor driver functions to read the sensor data from the device and to retrieve the value type for a given sensor type.

* The `sensor_set_interface()` function to set the interface to use to communicate with the sensor device.

**Notes**: 

* See the [Sensor Device Driver](/os/modules/sensor_framework/sensor_driver.md) page for the functions and data structures that a sensor driver package exports.

* The `<sensorname>_init()` function must also call the `sensor_mgr_register()` function to register the sensor with the sensor manager.  See the [Sensor Manager API](/os/modules/sensor_framework/sensor_manager_api.md) for details.

<br>
#### Setting the Configured Sensor Types 

The BSP, or the sensor creator package, also calls the `<sensorname>_config()` function to configure the sensor device with default values. The `<sensorname>_config()` function is exported by the sensor device driver and must call the sensor API `sensor_set_type_mask()` function to set the configured sensor types in the sensor object. The configured sensor types are a subset of the sensor types that the device supports. The sensor framework must know the sensor types that a sensor device is configured for because it only reads sensor data for the configured sensor types.

**Note:** An application may also call the `<sensorname>_config()` function to configure the sensor device. 

### Sensor API Functions Used By an Application

The sensor API provides the functions for an application to read sensor data from a sensor and to configure a sensor for polling.

#### Reading Sensor Data

An application calls the `sensor_read()` function to read sensor data from a sensor device. You specify a bit mask of the configured sensor types to read from a sensor device and a callback function to call when the sensor data is read. The callback is called for each specified configured type and the data read for that sensor type is passed to the callback.

#### Setting a Poll Rate for A Sensor 

The sensor manager implements a poller that reads sensor data from a sensor at specified poll intervals. An application must call the `sensor_set_poll_rate_ms()` functon to set the poll rate for a sensor in order for poller to poll the sensor. 

**Note:** An application needs to register a [sensor listener](/os/modules/sensor_framework/sensor_listener_api.md) to receive the sensor data that the sensor manager poller reads from a sensor.

