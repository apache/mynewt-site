## <font color="#F2853F" style="font-size:24pt">newtmgr mpstat </font>
Read memory pool statistics from a device.

#### Usage:

```no-highlight
    newtmgr mpstat -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
    -c, --conn string       connection profile to use.
    -h, --help              Help for newtmgr commands
    -l, --loglevel string   log level to use (default "info")
    -t, --trace             print all bytes transmitted and received
```

####Description
Reads and displays the memory pool statistics from a device.  Newtmgr uses the `conn_profile` connection profile to connect to the device.  It lists the following statistics for each memory pool: 

* **name**: Memory pool name
* **blksz**:  Size (number of bytes) of each memory block 
* **cnt**: Number of blocks allocated for the pool
* **free**: Number of free blocks 
* **min**: The lowest number of free blocks that were available


####Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr mpstat -c profile01 | Reads and displays the memory pool statistics from a device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile.

Here is an example output for the `myble` application from the [Enabling Newt Manager in any app](/os/tutorials/add_newtmgr.md) tutiorial:

```no-highlight
newtmgr mpstat -c myserial 
Return Code = 0
                            name blksz  cnt free  min
         ble_l2cap_sig_proc_pool    20    1    1    1
     ble_att_svr_prep_entry_pool    12   64   64   64
         ble_hci_ram_evt_hi_pool    72    2    2    1
              ble_hs_hci_ev_pool    16   10   10    9
          ble_att_svr_entry_pool    20   75    0    0
             ble_gattc_proc_pool    56    4    4    4
                bletiny_dsc_pool    28   64   64   64
                ble_hs_conn_pool    84    1    1    1
                  ble_gap_update    24    1    1    1
                bletiny_svc_pool    32   32   32   32
          ble_gatts_clt_cfg_pool    12    2    1    1
                          msys_1   292   12    9    6
         ble_hci_ram_evt_lo_pool    72    8    8    8
             ble_l2cap_chan_pool    24    3    3    3
                bletiny_chr_pool    36   64   64   64
```
