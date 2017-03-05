## <font color="#F2853F" style="font-size:24pt">newtmgr log </font>
Manage logs on a device.

#### Usage:

```no-highlight
    newtmgr log [command] [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

####Description
The log command provides subcommands to manage logs on a device. Newtmgr uses the `conn_profile` connection profile to connect to the device.

Sub-command  | Explanation
-------------| ------------------------
clear      | The newtmgr log clear command clears the logs on a device. 
level_list | The newtmgr level_list command shows the log levels on a device.
list      | The newtmgr log list command shows the log names on a device. 
module_list | The newtmgr log module_list command shows the log module names on a device. 
show      | The newtmgr log show command shows the logs on a device.
    

####Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
clear       | newtmgr log clear<br>-c profile01 | Clears the logs on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
level_list   | newtmgr log level_list <br>-c profile01  | Shows the log levels on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
list   | newtmgr log list<br>-c profile01  | Shows the log names on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
module_list   | newtmgr log module_list<br>-c profile01  | Shows the log module names on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
show  | newtmgr log show<br>-c profile01  | Shows the logs on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
