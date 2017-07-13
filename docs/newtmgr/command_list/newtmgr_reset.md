## <font color="#F2853F" style="font-size:24pt">newtmgr reset </font>
Send a reset request to a device.

#### Usage:

```no-highlight
    newtmgr reset <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

#### Description
Resets a device.  Newtmgr uses the `conn_profile` connection profile to connect to the device.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
            | newtmgr reset<br>-c profile01 |Resets a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
