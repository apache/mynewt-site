## <font color="#F2853F" style="font-size:24pt">newtmgr echo </font>
Send data to a device and display the echoed back data.

#### Usage:

```no-highlight
    newtmgr echo <text> -c <conn_profile> [flags] 
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
Sends the `text` to a device and outputs the text response from the device. Newtmgr uses the `conn_profile` connection profile to connect to the device. 

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr echo hello<br>-c profile01 | Sends the text 'hello' to a device and displays the echoed back data. Newtmgr connects to the device over a connection specified in the `profile01` profile.
