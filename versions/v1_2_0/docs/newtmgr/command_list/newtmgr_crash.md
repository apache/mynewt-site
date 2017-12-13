## <font color="#F2853F" style="font-size:24pt">newtmgr crash </font>
Send a crash command to a device.


#### Usage:

```no-highlight
    newtmgr crash <assert|div0|jump0|ref0|wdog> -c <conn_profile> [flags] 
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
Sends a crash command to a device to run one of the following crash tests: `div0`, `jump0`, `ref0`, `assert`, `wdog`.  Newtmgr uses the `conn_profile` connection profile to connect to the device.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr crash div0<br>-c profile01 | Sends a request to a device to execute a divide by 0 test. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
             | newtmgr crash ref0<br>-c profile01 | Sends a request to a device to execute a nil pointer reference test. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
