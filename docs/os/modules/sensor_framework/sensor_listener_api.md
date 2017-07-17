## Sensor Listener API

The sensor listener API allows an application to register listeners for sensors and get notified whenever sensor data are read from the sensor devices. An application calls the `sensor_register_listener()` function to register a listener and specifies callback function and  the types of sensor data to listen for from a sensor device.

When the `sensor_read()` function defined in the [sensor API](/os/modules/sensor_framework/sensor_api.md) is called to read the sensor data for the specified sensor types from a sensor, the `sensor_read()` function calls the listener callback, passing it the sensor data that is read from the sensor. 

An application calls the `sensor_unregister_listner()` function to unregister a listener if it no longer needs notifications when data is read from a sensor.

An application can use listeners in conjunction with the sensor manager poller.  An application can configure a polling interval for a sensor and register a listener for the sensor types it wants to listen for from the sensor.  When the sensor manager poller reads the sensor data from the sensor at each polling interval, the listener callback is called with the sensor data passed to it.

An application can also use listeners for other purposes. For example, an application that uses the OIC sensor server may want to register listeners.  The OIC sensor server handles all the OIC requests for the sensor resources and an application does not know about the OIC requests. An application can install a listener if it wants to know about a request for a sensor resource or use the sensor data that the OIC sensor server reads from the sensor.

