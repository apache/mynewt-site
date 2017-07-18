## <font color="#F2853F" style="font-size:24pt">newtmgr crash </font>
Send a crash command to a device.


#### Usage:

```no-highlight
    newtmgr crash <div0|jump0|ref0|assert|wdog> -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

#### Description
Sends a crash command to a device to run one of the following crash tests: `div0`, `jump0`, `ref0`, `assert`, `wdog`.  Newtmgr uses the `conn_profile` connection profile to connect to the device.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr crash div0<br>-c profile01 | Sends a request to a device to execute a divide by 0 test. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
             | newtmgr crash ref0<br>-c profile01 | Sends a request to a device to execute a nil pointer reference test. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
