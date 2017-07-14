## <font color="#F2853F" style="font-size:24pt">newtmgr run </font>
Run test procedures on a device.

#### Usage:

```no-highlight
    newtmgr run [command] -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

#### Description
The run command provides subcommands to run test procedures on a device. Newtmgr uses the `conn_profile` connection profile to connect to the device.

Sub-command  | Explanation
-------------| ------------------------
list       | The newtmgr run list command lists the registered tests on a device.
test       | The newtmgr run test [all&#124;testname] [token-value] command runs the `testname` test or all tests on a device.  All tests are run if `all` or no `testname` is specified. If a `token-value` is specified, the token value is output with the log messages.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
list         | newtmgr run<br>list -c profile01 | Lists all the registered tests on a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
test | newtmgr run <br>test all<br>201612161220<br>-c profile01 | Runs all the tests on a device. Outputs the `201612161220` token with the log messages. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
test | newtmgr run <br>test mynewtsanity<br>-c profile01 | Runs the `mynewtsanity` test on a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
