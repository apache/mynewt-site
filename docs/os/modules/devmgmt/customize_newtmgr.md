## Customizing Newt Manager Usage with mgmt

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
<td>```echo``` ```taskstat``` ```mpstat``` ```datetime``` ```reset```</td>
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
<td>```run```</td>
<td>test/runtest</td>
</tr>
</table>
Both newtmgr and ocimgr process the MGMT_GROUP_ID_DEFAULT commands by default.  You can also
use mgmt to add user defined management group commands. 
