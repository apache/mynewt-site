## <font color="#F2853F" style="font-size:24pt">newtmgr log </font>
Manage logs on a device.

#### Usage:

```no-highlight
    newtmgr log [command] -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
  -c, --conn string       connection profile to use
  -h, --help              help for newtmgr
  -l, --loglevel string   log level to use (default "info")
      --name string       name of target BLE device; overrides profile setting
  -t, --timeout float     timeout in seconds (partial seconds allowed) (default 10)
  -r, --tries int         total number of tries in case of timeout (default 1)
```

#### Description
The log command provides subcommands to manage logs on a device. Newtmgr uses the `conn_profile` connection profile to connect to the device.

Sub-command  | Explanation
-------------| ------------------------
clear      | The newtmgr log clear command clears the logs on a device. 
level_list | The newtmgr level_list command shows the log levels on a device.
list      | The newtmgr log list command shows the log names on a device. 
module_list | The newtmgr log module_list command shows the log module names on a device. 
show  | The newtmgr log show command displays logs on a device. The command format is: <br>newtmgr log show [log_name [min-index [min-timestamp]]] -c &lt;conn_profile&gt;<br><br>The following optional parameters can be used to filter the logs to display: <ul><li>**log_name**: Name of log to display. If log_name is not specified, all logs are displayed.</li><li>**min-index**: Minimum index of the log entries to display. This value is only valid when a log_name is specified. The value can be `last` or a number. If the value is `last`, only the last log entry is displayed. If the value is a number, log entries with an index equal to or higher than min-index are displayed.</li><li>**min-timestamp**: Minimum timestamp of log entries to display. The value is only valid if min-index is specified and is not the value `last`. Only log entries with a timestamp equal to or later than min-timestamp are displayed. Log entries with a timestamp equal to min-timestamp are only displayed if the log entry index is equal to or higher than min-index.</li></ul> 

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
clear       | newtmgr log clear<br>-c profile01 | Clears the logs on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
level_list   | newtmgr log level_list <br>-c profile01  | Shows the log levels on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
list   | newtmgr log list<br>-c profile01  | Shows the log names on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
module_list   | newtmgr log module_list<br>-c profile01  | Shows the log module names on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile. 
show  | newtmgr log show -c profile01  | Displays all logs on a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
show  | newtmgr log show reboot_log -c profile01  | Displays all log entries for the reboot_log on a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
show | newtmgr log show reboot_log last -c profile01 | Displays the last entry from the reboot_log on a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
show | newtmgr log show reboot_log 2 -c profile01 | Displays the reboot_log log entries with an index 2 and higher on a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
show | newtmgr log show reboot_log 5 123456 -c profile01 | Displays the reboot_log log entries with a timestamp higher than 123456 and log entries with a timestamp equal to 123456 and an index equal to or higher than 5.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
