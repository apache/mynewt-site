## Using the OIC framework

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

### Customize Newt Manager usage with mgmt

The **mgmt** package enables you to customize Newt Manager (in either the newtmgr or oicmgr framerwork) to only process the
commands that your application uses. The newtmgr commands are divided into management groups.
A manager package implements the commands for a group.  It implements the handlers that 
process the commands for the group and registers the handlers with mgmt. 
When newtmgr or oicmgr receives a newtmgr command, 
it looks up the handler for the command (by management group id and command id) from mgmt and calls the 
handler to process the command.   

The system level management groups are listed in following table:
<table style="width:90%" align="center">
<tt>
<td>Management Group</td>
<td>newtmgr Commands</td>
<td>Package</td>
</tt>
<tr>
<td>MGMT_GROUP_ID_DEFAULT</td>
<td>```echo``` ```taskstats``` ```mpstats``` ```datetime``` ```reset```</td>
<td>mgmt/newtmgr/nmgr_os</td>
</tr>
<tr>
<td>MGMT_GROUP_ID_IMAGE</td>
<td>```image``` </td>
<td>mgmt/imgmgr</td>
</tr>
<tr>
<td>MGMT_GROUP_ID_STATS</td>
<td>```stat``` </td>
<td>sys/stats</td>
</tr>
<tr>
<td>MGMT_GROUP_ID_CONFIG</td>
<td>```config```</td>
<td>sys/config</td>
</tr>
<tr>
<td>MGMT_GROUP_ID_LOGS</td>
<td>```log```</td>
<td>sys/log</td>
</tr>
<tr>
<td>MGMT_GROUP_ID_CRASH</td>
<td>```crash```</td>
<td>test/crash_test</td>
</tr>
<tr>
<td>MGMT_GROUP_ID_RUNTEST</td>
<td>```runtest```</td>
<td>test/runtest</td>
</tr>
</table>
Both newtmgr and ocimgr process the MGMT_GROUP_ID_DEFAULT commands by default.  You can also
use mgmt to add user defined management group commands. 
