## <font color="#F2853F" style="font-size:24pt">newtmgr config </font>
Read and write config values on a device.

#### Usage:

```no-highlight
    newtmgr config <var-name> [var-value] -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

#### Description
Reads and sets the value for the `var-name` config variable on a device. Specify a `var-value` to set the value for the `var-name` variable.   Newtmgr uses the `conn_profile` connection profile to connect to the device.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr config myvar -c profile01 | Reads the `myvar` config variable value from a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
             | newtmgr config myvar 2 -c profile01 | Sets the `myvar` config variable to the value `2` on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.

