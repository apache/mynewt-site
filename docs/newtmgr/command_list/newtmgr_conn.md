## <font color="#F2853F" style="font-size:24pt">newtmgr conn </font>
Manage newtmgr connection profiles.

#### Usage:

```no-highlight
    newtmgr conn [command] [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

#### Description
The conn command provides subcommands to add, delete, and view configuration profiles.

Sub-command  | Explanation
-------------| ------------------------
add       | The newtmgr conn add <conn_profile> <var-name=var-value> command creates a connection profile named `conn_profile`. A profile consists of these variables: <ul><li>`name`: Connection name. Defaults to `conn_profile` when the variable is not set in the command. </li><li>`type`: Connection type. Valid types are: `serial`, `oic_serial`, `ble`, `oic_ble`, `udp`, `oic_udp`.</li><li>`connstring`: The physical or virtual port to use for the connection.</li><li>`addrtype`: Device address type. Use with type `ble`.</li><li>`addr`:  Device address. Use with type `ble`.</ul>
delete    | The newtmgr conn delete &lt;conn_profile&gt; command deletes the `conn_profile` connection profile.
show      | The newtmgr conn show [conn_profile] command shows the information for the `conn_profile` connection profile. It shows information for all the connection profiles if `conn_profile` is not specified.
    

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
add       | newtmgr conn add myserial02 type=serial connstring=/dev/ttys002 | Creates a connection profile for the serial port /dev/ttys002 and names it `myserial02`
delete    | newtmgr conn delete myserial02  | Deletes the connection profile named `myserial02`
show      | newtmgr conn show myserial01 | Displays the information for the `myserial01` connection profile.
show      | newtmgr conn show  | Displays the information for all connection profiles.
