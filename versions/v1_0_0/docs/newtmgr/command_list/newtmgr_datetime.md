## <font color="#F2853F" style="font-size:24pt">newtmgr datetime </font>
Manage datetime on a device.

#### Usage:

```no-highlight
    newtmgr datetime [datetime-value] -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

####Description
Reads or sets the datetime on a device. Specify a `datetime-value` in the command to set the datetime on the device. Newtmgr uses the `conn_profile` connection profile to connect to the device.

**Note**: You must specify the  `datetime-value` in the RFC 3339 format.  

####Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr datetime<br>-c profile01 | Reads the datetime value from a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
	     | newtmgr datetime 2017-03-01T22:44:00<br>-c profile01 | Sets the datetime on a device to March 1st 2017 22:44:00 UTC. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
	     | newtmgr datetime 2017-03-01T22:44:00-08:00<br>-c profile01| Sets the datetime on a device to March 1st 2017 22:44:00 PST. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
