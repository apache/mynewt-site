Enabling OIC Sensor Data Monitoring
-----------------------------------

.. toctree::
   :hidden:

   Enable OIC Sensor Support in the sensors_test Application <sensor_nrf52_bno055_oic>
   Add OIC Sensor Support to the bleprph_oic Application <sensor_bleprph_oic>
   
This tutorial shows you how to enable sensor data monitoring via the OIC
protocol over BLE transport in an application. It extends the example
application in the :doc:`Enabling an Off-Board Sensor in an Existing
Application Tutorial <sensor_nrf52_bno055>` and assumes that you have
worked through that tutorial.

This tutorial has two parts:

-  :doc:`Part 1 <sensor_nrf52_bno055_oic>` shows you how to enable 
   OIC sensor support in the sensors\_test application. The procedure 
   only requires setting the appropriate syscfg setting values for the 
   application target. The objective is to show you to quickly bring up
   the sensors\_test application and view the sensor data with the Mynewt
   Smart Device Controller app that is available for iOS and Android devices.

-  :doc:`Part 2 <sensor_bleprph_oic>` shows you how to modify the bleprph\_oic
   application code to add OIC sensor support. The objective is to show you 
   how to use the Sensor Framework API and OIC server API to develop an OIC
   over BLE sensor server application. 

.. contents::
  :local:
  :depth: 2  

Prerequisites 
~~~~~~~~~~~~~
Ensure that you meet the following prerequisites before continuing with the tutorials:

-  Complete the :doc:`Enabling an Off-Board Sensor in an Existing Application
   Tutorial <sensor_nrf52_bno055>`
-  Install the Mynewt Smart Device Controller on an iOS or Android
   Device. See the :doc:`Sensor Tutorials Overview <sensors>` on how to install
   the Mynewt Smart Device Controller app.

Overview of OIC Support in the Sensor Framework
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The sensor framework provides support for a sensor enabled application
to host the sensor devices as OIC resources. The sensor framework
provides the following OIC support:

-  Creates OIC resources for each sensor device that is enabled in the
   application. It creates an OIC discoverable and observable resource
   for each sensor type that the sensor device is configured for.
-  Processes CoAP GET requests for the sensor OIC resources. It reads
   the sensor data samples, encodes the data, and sends back a response.

The sensor package (``hw/sensor``) defines the following syscfg settings
for OIC support:

-  ``SENSOR_OIC``: This setting specifies whether to enable sensor OIC
   server support. The setting is enabled by default. The sensor package
   includes the ``net/oic`` package for the OIC support when this
   setting is enabled. The ``OC_SERVER`` syscfg setting that specifies
   whether to enable OIC server support in the ``net/oic`` package must
   also be enabled.
-  ``SENSOR_OIC_OBS_RATE``: Sets the OIC server observation rate.
