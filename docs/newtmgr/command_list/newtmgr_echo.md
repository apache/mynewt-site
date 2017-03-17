## <font color="#F2853F" style="font-size:24pt">newtmgr echo </font>
Send data to a device and display the echoed back data.

#### Usage:

```no-highlight
    newtmgr echo <text> -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

####Description
Sends the `text` to a device and outputs the text response from the device. Newtmgr uses the `conn_profile` connection profile to connect to the device. 

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr echo hello<br>-c profile01 | Sends the text 'hello' to a device and displays the echoed back data. Newtmgr connects to the device over a connection specified in the `profile01` profile.
