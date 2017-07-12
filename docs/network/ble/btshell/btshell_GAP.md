
## GAP API for btshell

<br>

Generic Access Profile (GAP) defines the generic procedures related to discovery of Bluetooth devices (idle mode procedures) and link management aspects of connecting to Bluetooth devices (connecting mode procedures). It also defines procedures related to use of different security levels. 

Several different modes and procedures may be performed simultaneously over an LE physical transport. The following modes and procedures are defined for use over an LE physical transport:

1. **Broadcast mode and observation procedure**
    - These allow two devices to communicate in a unidirectional connectionless manner using the advertising events.
2. **Discovery modes and procedures**
    - All devices shall be in either non-discoverable mode or one of the discoverable modes.
    - A device in the discoverable mode shall be in either the general discoverable mode or the limited discoverable mode.
    - A device in non-discoverable mode will not be discovered by any device that is performing either the general discovery procedure or the limited discovery procedure.
3. **Connection modes and procedures**
    - allow a device to establish a connection to another device.
    - allow updating of parameters of the connection 
    - allow termination of the connection 
4. **Bonding modes and procedures**
    - Bonding allows two connected devices to exchange and store security and identity information to create a trusted relationship. 
    - Bonding can occur only between two devices in bondable mode.


<br>


###Usage API


|**Item No.** | **Modes and Procedures** | **nimBLE command** |
|----|---------|---------------|
|  1 | Broadcast Mode | `advertise conn=non discov=x` |
|    | Observation Procedure | `scan duration=x passive=x filter=x` |
|  2 | Non-Discoverable mode   | `advertise conn=x discov=non`  |
|    | Limited Discoverable mode   | `advertise conn=x discov=ltd` |
|    | General Discoverable mode   | `advertise conn=x discov=gen`  |
|    | Limited Discovery procedure | `scan duration=x discov=ltd passive=0 filter=no_wl` |
|    | General Discovery procedure | `scan duration=x discov=gen passive=0 filter=no_wl` |
|    | Name Discovery procedure  | `scan duration=x` <br> `scan cancel` <br> `connect peer_addr_type=x peer_addr=x` <br> `gatt-read conn=x uuid=0x2a00` |
|  3 | Non-connectable mode   | `advertise conn=non discov=x`  |
|    | Directed connectable mode  | `advertise conn=dir [own_addr_type=x] [discov=x] [duration=x]`  |
|    | Undirected connectable mode  | `advertise conn=und [own_addr_type=x] [discov=x] [duration=x]`  |
|    | Auto connection establishment procedure   | `white-list addr_type=x addr=x [addr_type=y addr=y] [...]` <br> `connect addr_type=wl`  |
|    | General connection establishment procedure  | `scan duration=x` <br> `scan cancel` <br> `connect peer_addr_type=x peer_addr=x` |
|    | Selective connection establishment procedure | `white-list addr_type=x addr=x [addr_type=y addr=y] [...]` <br> `scan filter=use_wl duration=x` <br> `scan cancel` <br> `connect peer_addr_type=x peer_addr=x [own_addr_type=x]` |
|    | Direct connection establishment procedure  | `connect addr_type=x addr=x [params]`  |
|    | Connection parameter update procedure   | `conn-update-params conn=x <params>` |
|    | Terminate connection procedure  | `disconnect conn=x` |
|  4 | Non-Bondable mode    | `security-set-data bonding=0` [\*] |
|    | Bondable mode        | `security-set-data bonding=1` [\*] |
|    | Bonding procedure    | `security-start conn=x` [\*] |

**[\*]** Security is disabled by default in btshell.  To use the bonding modes and procedures, add `BLE_SM_LEGACY: 1` or `BLE_SM_SC: 1` to your syscfg.yml file depending on your needs.

<br>

### Address Types

| *btshell string* | *Description*                                       | *Notes*                              |
|------------------|-----------------------------------------------------|--------------------------------------|
| public           | Public address.                                     |                                      |
| random           | Random static address.                              |                                      |
| rpa_pub          | Resolvable private address, public identity.        | Not available for all commands.      |
| rpa_rnd          | Resolvable private address, random static identity. | Not available for all commands.      |
| wl               | Use white list; ignore peer_addr parameter.         | Only availble for "connect" command. |

### Connection Parameters 

The Connection parameter definitions can be found in Section 7.8.12 of the BLUETOOTH SPECIFICATION Version 4.2 [Vol 2, Part E].

| *Name*              | *Description*                                                                                           | *btshell string*   |
|---------------------|---------------------------------------------------------------------------------------------------------|--------------------|
| LE_Scan_Interval    | Recommendation from the Host on how long the Controller should scan                                     | scan_interval      |
| LE_Scan_Window      | Recommendation from the Host on how frequently the Controller should scan                               | scan_window        |
| Peer_Address_Type   | Whether the peer is using a public or random address (see Address types table).                         | peer_addr_type     |
| Peer_Address        | The 6-byte device address of the peer; ignored if white list is used                                    | peer_addr          |
| Own_Address_Type    | The type of address to use when initiating the connection (see Address types table)                     | own_addr_type      |
| Conn_Interval_Min   | Defines minimum allowed connection interval                                                             | interval_min       |
| Conn_Interval_Max   | Defines maximum allowed connection interval                                                             | interval_max       |
| Conn_Latency        | Defines the maximum allowed connection latency                                                          | latency            |
| Supervision_Timeout | Link supervision timeout for the connection.                                                            | timeout            |
| Minimum_CE_Length   | Informative parameter providing the Controller with the expected minimum length of the connection event | min_conn_event_len |
| Maximum_CE_Length   | Informative parameter providing the Controller with the expected maximum length of the connection event | max_conn_event_len |
| Duration            | Number of milliseconds before aborting the connect attempt                                              | duration           |

### Advertisment Parameters

| *btshell string* | *Description*                         | *Notes*                                                      | *Default*                 |
|------------------|---------------------------------------|--------------------------------------------------------------|---------------------------|
| conn             | Connectable mode                      | See Connectable Modes table.                                 | und                       |
| discov           | Discoverable mode                     | See Discoverable Modes table.                                | gen                       |
| own_addr_type    | The type of address to advertise with | See Address Types table.                                     | public                    |
| peer_addr_type   | The peer's address type               | Only used for directed advertising; see Address Types table. | public                    |
| peer_addr        | The peer's address                    | Only used for directed advertising                           | N/A                       |
| channel_map      |                                       |                                                              | 0                         |
| filter           | The filter policy                     | See Advertisement Filter Policies table.                     | none                      |
| interval_min     |                                       | units=0.625ms                                                | non: 100ms; und/dir: 30ms |
| interval_max     |                                       | units=0.625ms                                                | non: 150ms; und/dir: 60ms |
| high_duty        | Whether to use high-duty-cycle        | 0/1                                                          | 0                         |
| duration         |                                       | Milliseconds                                                 | Forever                   |

### Advertisement Filter Policies

| *btshell string*  | *Description*                                                          | *Notes*   |
| ----------------- | ---------------                                                        | --------- |
| none              | No filtering. No whitelist used.                                       | Default   |
| scan              | Process all connection requests but only scans from white list.        |           |
| conn              | Process all scan request but only connection requests from white list. |           |
| both              | Ignore all scan and connection requests unless in white list.          |           |

