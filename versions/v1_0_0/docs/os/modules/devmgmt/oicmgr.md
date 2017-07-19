## Using the OIC Framework

Apache Mynewt includes support for the OIC interoperability standard through the `oicmgr` framework.  Mynewt defines and exposes oicmgr as an OIC Server resource with the following identity and properties: 
<br>
<table style="width:50%" align="center">
<tr> 
<td>**URI**</td> 
<td>/omgr</td>
</tr>
<tr>
<td>**Resource Type**(rt)</td>
<td>x.mynewt.nmgr</td> 
</tr>
<td>**Interface**(if)</td>
<td>oic.if_rw (default), oic.if.baseline</td>
</tr>
<td>**Discoverable**</td>
<td>Yes</td>
</tr>
</table>
The newtmgr application tool uses CoAP (Constrained Application Protocol) requests to send commands to oicmgr.  
It sends a CoAP request for **/omgr** as follows:

* Specifies the newtmgr command to execute in the URI query string. 
* Uses a GET method for newtmgr commands that retreive information 
from your application, for example, the ```taskstats``` and ```mpstats``` commands. 
* Uses a PUT method for newtmgr commands that send data to or modify the state of your application,
for example, the ```echo``` or ```datetime``` commands. 
* Sends the CBOR-encoded command request data in the CoAP message payload.

The `oicmgr` framework supports transport over BLE, serial, and IP connections to the device.
