## <font color="#F2853F" style="font-size:24pt">newtmgr stat</font>
Read statistics from a device.

#### Usage:

```no-highlight
    newtmgr stat <stats_name> -c <conn_profile> [flags] 
    newtmgr stat [command] -c <conn_profile> [flags] 
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
Displays statistic for the Stats named `stats_name` from a device.  You can use the `list` subcommand to get a list of the Stats names from the device.  Newtmgr uses the `conn_profile` connection profile to connect to the device.

Sub-command  |  Explanation
-------------| -----------------------
             | The newtmgr stat <stats_name> command displays the statistics for the `stats_name` Stats from a device. 
list         | The newtmgr stat list command displays the list of Stats names from a device.  


#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr stat ble_att -c profile01 | Displays the `ble_att` statistics on a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
list         | newtmgr stat list -c profile01 | Displays the list of Stats names from a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.
 
Here are some example outputs for the `myble` application from the [Enabling Newt Manager in any app](/os/tutorials/add_newtmgr.md) tutiorial:

The statistics for the ble_att Stats:
```no-highlight

$ newtmgr stat ble_att -c myserial
Return Code = 0
Stats Name: ble_att
  read_type_req_rx: 0
  read_rsp_rx: 0
  read_group_type_rsp_tx: 0
  prep_write_rsp_tx: 0
  find_type_value_req_tx: 0
  read_type_rsp_rx: 0
  read_mult_req_rx: 0
  notify_req_tx: 0
  indicate_req_tx: 0

       ...
  write_cmd_rx: 0
  prep_write_rsp_rx: 0
  read_type_rsp_tx: 0
  read_req_tx: 0
  read_mult_req_tx: 0
  read_group_type_req_rx: 0
  write_rsp_tx: 0
  exec_write_rsp_rx: 0

```

The list of Stats names using the list subcommand:
```no-highlight

$ newtmgr stat list -c myserial
[stat ble_l2cap ble_att ble_gap ble_gattc ble_gatts ble_hs ble_ll_conn ble_ll ble_phy]
Return Code = 0

```
