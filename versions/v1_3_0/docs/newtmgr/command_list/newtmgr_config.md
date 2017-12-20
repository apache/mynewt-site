## <font color="#F2853F" style="font-size:24pt">newtmgr config </font>
Read and write config values on a device.

#### Usage:

```no-highlight
    newtmgr config <var-name> [var-value] -c <conn_profile> [flags] 
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
Reads and sets the value for the `var-name` config variable on a device. Specify a `var-value` to set the value for the `var-name` variable.   Newtmgr uses the `conn_profile` connection profile to connect to the device.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr config myvar -c profile01 | Reads the `myvar` config variable value from a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
             | newtmgr config myvar 2 -c profile01 | Sets the `myvar` config variable to the value `2` on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.

