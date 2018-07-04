
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

### Available commands

Parameters default values are marked red.

## Configuration

|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**set**      |                  |                           | Set configuration options                                  |
|             |addr              | XX:XX:XX:XX:XX:XX         | Local device address                                       |
|             |addr_type         | `public`                  | Local device address type                                  |
|             |                  | random                    | Use random address for scan requests                       |
|             |mtu               | [23-UINT16_MAX]           | GATT Maximum Transmission Unit (MTU)                       |
|             |irk               | XX:XX:XX...               | Local Identity Resolving Key (16 byte                      |
|**set-priv-mode**   |           |                           | Set privacy mode for device                                |
|             | addr             | XX:XX:XX:XX:XX:XX         | Remote device address                                      |
|             | addr_type        | `public`                  | Remote device public address type                          |
|             |                  | random                    | Remote device random address type                          |
|             | mode             | [`0`-1]                   | 0 - use network privacy, 1 - use device privacy            |
|**white-list**|                 |                           | Add devices to white list <br> (this command accepts multiple instances of addr and addr_type parameters) |
|             | addr             | XX:XX:XX:XX:XX:XX         | Remote device address                                      |
|             | addr_type        | `public`                  | Remote device public address type                          |
|             |                  | random                    | Remote device random address type                          |

## Device discovery and connection

|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**scan**     |                  |                           | Discover remote devices                                    |
|             |cancel            |                           | cancel ongoing scan procedure                              |
|             |extended          | `none`                    | Start legacy scan                                          |
|             |                  | 1M                        | Start extended scan on 1M PHY                              |
|             |                  | coded                     | Start extended scan on Coded PHY                           |
|             |                  | both                      | Start extended scan on both PHYs                           |
|             |duration          | [1-`INT32_MAX`],          | Duration of scan in milliseconds                           |
|             |limited           | [`0`-1]                   | Use limited discovery procedure                            |
|             |passive           | [`0`-1]                   | Use passive scan                                           |
|             |interval          | [`0`-UINT16_MAX]          | Scan interval, if 0 use stack's default                    |
|             |window            | [`0`-UINT16_MAX]          | Scan window,  if 0 use stack's default                     |
|             |filter            | `no_wl`                   | Scan filter policy - Accept all advertising packets        |
|             |                  | use_wl                    | Accept only advertising packets from devices on White List |
|             |                  | no_wl_inita               | Accept all advertising packets (including directed RPA)    |
|             |                  | use_wl_inita              | Accept only advertising packets from devices on White List <br>(including directed RPA)|
|             |nodups            | [`0`-1]                   | Disable duplicates filtering                               |
|             |own_addr_type     | `public`                  | Use public address for scan requests                       |
|             |                  | random                    | Use random address for scan requests                       |
|             |                  | rpa_pub                   | Use RPA address for scan requests <br> (fallback to public if no IRK) |
|             |                  | rpa_rnd                   | Use RPA address for scan requests <br> (fallback to random if no IRK) |
|             |extended_duration | [`0`-UINT16_MAX]          | Duration of extended scan in 10 milliseconds               |
|             |extended_period   | [`0`-UINT16_MAX]          | Periodic scan interval in 1.28 seconds (0 disabled)        |
|             |longrange_interval| [`0`-UINT16_MAX]          | Scan interval for Coded Scan , if 0 use stack's default    |
|             |longrange_window  | [`0`-UINT16_MAX]          | Scan window for Coded Scan , if 0 use stack's default      |
|             |longrange_passive | [`0`-1]                   | Use passive scan for Coded Scan                            |
|**connect**  |                  |                           | Initiate connection to remote device                       |
|             |cancel            |                           | Cancel ongoing connection procedure                        |
|             |extended          |`none`                     | Use legacy connection procedure                            |
|             |                  |1M                         | Extended connect using 1M PHY scan parameters              |
|             |                  |coded                      | Extended connect using Coded PHY scan parameters           |
|             |                  |both                       | Extended connect using 1M and Coded PHYs scan parameters   |
|             |                  |all                        | Extended connect using 1M and Coded PHYs scan parameters <br> (Provide also connection parameters for 2M PHY) |
|             |peer_addr_type    | `public`                  | Remote device public address type                          |
|             |                  | random                    | Remote device random address type                          |
|             |                  | public_id                 | Remote device public address type (Identity)               |
|             |                  | random_id                 | Remote device random address type (Identity)               |
|             |peer_addr         | XX:XX:XX:XX:XX:XX         | Remote device address                                      |
|             |own_addr_type     | `public`                  | Use public address for scan requests                       |
|             |                  | random                    | Use random address for scan requests                       |
|             |                  | rpa_pub                   | Use RPA address for scan requests <br> (fallback to public if no IRK) |
|             |                  | rpa_rnd                   | Use RPA address for scan requests <br> (fallback to random if no IRK) |
|             |duration          | [`0`-INT32_MAX]           | Connection attempt duration, if 0 use stack's default      |
|             |scan_interval     | [0-UINT16_MAX]            | Scan interval, default: 0x0010                             |
|             |scan_window       | [0-UINT16_MAX]            | Scan window, default: 0x0010                               |
|             |interval_min      | [0-UINT16_MAX]            | Minimum connection interval, default: 30                   |
|             |interval_max      | [0-UINT16_MAX]            | Maximum connection interval, default: 50                   |
|             |latency           | [UINT16]                  | Connection latency, default: 0                             |
|             |timeout           | [UINT16]                  | Connection timeout, default: 0x0100                        |
|             |min_conn_event_len| [UINT16]                  | Minimum length of connection event, default: 0x0010        |
|             |max_conn_event_len| [UINT16]                  | Maximum length of connection event, default: 0x0300        |
|             |coded_scan_interval     | [0-UINT16_MAX]      | Coded PHY Scan interval, default: 0x0010                   |
|             |coded_scan_window       | [0-UINT16_MAX]      | Coded PHY Scan window, default: 0x0010                     |
|             |coded_interval_min      | [0-UINT16_MAX]      | Coded PHY Minimum connection interval, default: 30         |
|             |coded_interval_max      | [0-UINT16_MAX]      | Coded PHY Maximum connection interval, default: 50         |
|             |coded_latency           | [UINT16]            | Coded PHY  Connection latency, default: 0                  |
|             |coded_timeout           | [UINT16]            | Coded PHY  Connection timeout, default: 0x0100             |
|             |coded_min_conn_event_len| [UINT16]            | Coded PHY Minimum length of connection event, default: 0x0010  |
|             |coded_max_conn_event_len| [UINT16]            | Coded PHY  Maximum length of connection event, default: 0x0300 |
|             |2M_scan_interval     | [0-UINT16_MAX]         | 2M PHY Scan interval, default: 0x0010                      |
|             |2M_scan_window       | [0-UINT16_MAX]         | 2M PHY Scan window, default: 0x0010                        |
|             |2M_interval_min      | [0-UINT16_MAX]         | 2M PHY Minimum connection interval, default: 30            |
|             |2M_interval_max      | [0-UINT16_MAX]         | 2M PHY Maximum connection interval, default: 50            |
|             |2M_latency           | [UINT16]               | 2M PHY Connection latency, default: 0                      |
|             |2M_timeout           | [UINT16]               | 2M PHY Connection timeout, default: 0x0100                 |
|             |2M_min_conn_event_len| [UINT16]               | 2M PHY Minimum length of connection event, default: 0x0010 |
|             |2M_max_conn_event_len| [UINT16]               | 2M PHY Maximum length of connection event, default: 0x0300 |
|**disconnect**  |              |                            | Disconnect exisiting connection                            |
|             |conn             | [UINT16]                   | Connection handle                                          |
|             |reason           | [UINT8]                    | Disconnect reason                                          | 
|**show-addr**      |           |                            | Show local public and random identity addresses            |
|**show-conn**      |           |                            | Show current connections                                   |
|**conn-rssi**|                 |                            | Obtain RSSI of specified connection                        |
|             |conn             | [UINT16]                   | Connection handle                                          |
|**conn-update-params**|        |                            | Update parameters of specified connection                  |
|             |conn             | [UINT16]                   | Connection handle                                          |
|             |interval_min      | [0-UINT16_MAX]            | Minimum connection interval, default: 30                   |
|             |interval_max      | [0-UINT16_MAX]            | Maximum connection interval, default: 50                   |
|             |latency           | [UINT16]                  | Connection latency, default: 0                             |
|             |timeout           | [UINT16]                  | Connection timeout, default: 0x0100                        |
|             |min_conn_event_len| [UINT16]                  | Minimum length of connection event, default: 0x0010        |
|             |max_conn_event_len| [UINT16]                  | Maximum length of connection event, default: 0x0300        |
|**conn-datalen**|              |                            | Set DLE parmaeters for connection                          |
|             |conn             | [UINT16]                   | Connection handle                                          |
|             |octets           | [UINT16]                   | Maximum transmission packet size                           |
|             |time             | [UINT16]                   | Maximum transmission packet time                           |
|**phy-set**  |                 |                            | Set prefered PHYs used for connection                      |
|             |conn             | [UINT16]                   | Connection handle                                          |
|             |tx_phys_mask     | [UINT8]                    | Prefered PHYs on TX is mask of following bits<br>0x00 - no preference<br>0x01 - 1M, 0x02 - 2M, 0x04 - Coded                                          
|             |rx_phys_mask     | [UINT8]                    | Prefered PHYs on RX is mask of following bits<br>0x00 - no preference<br>0x01 - 1M, 0x02 - 2M, 0x04 - Coded                                          
|             |phy_opts         | [UINT16]                   | Options for Coded PHY<br> 0 - any coding, 1 - prefer S2, 2 - prefer S8 |
|**phy-set-default**  |         |                            | Set default prefered PHYs used for new connection          |
|             |tx_phys_mask     | [UINT8]                    | Prefered PHYs on TX is mask of following bits<br>0x00 - no preference<br>0x01 - 1M, 0x02 - 2M, 0x04 - Coded                                          
|             |rx_phys_mask     | [UINT8]                    | Prefered PHYs on RX is mask of following bits<br>0x00 - no preference<br>0x01 - 1M, 0x02 - 2M, 0x04 - Coded    
|**phy-read**  |                |                            | Read connection current PHY                                |
|             |conn             | [UINT16]                   | Connection handle                                          |
|**l2cap-update**  |             |                           | Update connection parameters                               |
|             |interval_min      | [0-UINT16_MAX]            | Minimum connection interval, default: 30                   |
|             |interval_max      | [0-UINT16_MAX]            | Maximum connection interval, default: 50                   |
|             |latency           | [UINT16]                  | Connection latency, default: 0                             |
|             |timeout           | [UINT16]                  | Connection timeout, default: 0x0100                        |

## Security

|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**security-set-data**     |     |                           | Set security configuration                                 |
|             |oob-flag          | [`0`-1]                   | Set Out-Of-Band (OOB) flag in Security Manager             |
|             |mitm-flag         | [`0`-1]                   | Set Man-In-The-Middle (MITM) flag in Security Manager      |
|             |io_capabilities   | 0                         | Set Input-Output Capabilities to "DisplayOnly"             |
|             |                  | 1                         | Set Input-Output Capabilities to "DisplayYesNo"            |
|             |                  | 2                         | Set Input-Output Capabilities to "KeyboardOnly"            |
|             |                  | 3                         | Set Input-Output Capabilities to "NoInputNoOutput"         |
|             |                  | 4                         | Set Input-Output Capabilities to "KeyboardDisplay"         |
|             |our_key_dist      | [UINT8]                   | Set Local Keys Distribution, this is a bit field of possible values: <br> LTK (0x01), IRK (0x02), CSRK (0x04), LTK_SC(0x08) |
|             |their_key_dist    | [UINT8]                   | Set Remote Keys Distribution, this is a bit field of possible values: <br> LTK (0x01), IRK (0x02), CSRK (0x04), LTK_SC(0x08) |
|             |bonding-flag      | [`0`-1]                   | Set Bonding flag in Security Manager                       |
|             |sc-flag           | [`0`-1]                   | Set Secure Connections flag in Security Manager            |
|**security-pair**|              |                           | Start pairing procedure                                    |
|             |conn              | [UINT16]                  | Connection handle                                          |
|**security-encryption**|        |                           | Start encryption procedure                                 |
|             |conn              | [UINT16]                  | Connection handle                                          |
|             |ediv              | [UINT16]                  | EDIV for LTK to use (use storage if not provided)          |
|             |rand              | [UINT64]                  | Rand for LTK                                               |
|             |ltk               | XX:XX:XX...               | LTK (16 bytes)                                             |
|**security-start**|             |                           | Start security procedure <br>(This starts either pairing or encryption depending if keys are stored)|
|             |conn              | [UINT16]                  | Connection handle                                          |
|**auth-passkey**|               |                           | Reply to Passkey request                                   |
|             |conn              | [UINT16]                  | Connection handle                                          |
|             |action            | [UINT16]                  | Action to reply (as received in event)                     |
|             |key               | [0-999999]                | Passkey to reply (Input or Display action)                 |
|             |oob               | XX:XX:XX:...              | Out-Of-Band secret (16 bytes) (OOB action)                 |
|             |yesno             | Yy-Ny                     | Confirm passkey (for Passkey Confirm action)               |

## Advertising with Extended Advertising enabled

|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**advertise-configure**     |   |                           | Configure new advertising instance                         |
|             |instance          | [`0`-UINT8_MAX]           | Advertising instance                                       |
|             |connectable       | [`0`-1]                   | Use connectable advertising                                |
|             |scannable         | [`0`-1]                   | Use scannable advertising                                  |
|             |peer_addr_type    | `public`                  | Remote device public address type                          |
|             |                  | random                    | Remote device random address type                          |
|             |                  | public_id                 | Remote device public address type (Identity)               |
|             |                  | random_id                 | Remote device random address type (Identity)               |
|             |peer_addr         | XX:XX:XX:XX:XX:XX         | Remote device address - if provided perform directed advertising |
|             |own_addr_type     | `public`                  | Use public address for scan requests                       |
|             |                  | random                    | Use random address for scan requests                       |
|             |                  | rpa_pub                   | Use RPA address for scan requests <br> (fallback to public if no IRK) |
|             |                  | rpa_rnd                   | Use RPA address for scan requests <br> (fallback to random if no IRK) |
|             |channel_map       | [`0`-UINT8_MAX}           | Primary advertising channels map. If 0 use all channels.   |
|             |filter            | `none`                    | Advertising filter policy - no filtering, no whitelist used|
|             |                  | scan                      | process all connection requests but only scans from white list|
|             |                  | conn                      | process all scan request but only connection requests from white list|
|             |                  | both                      | ignore all scan and connection requests unless in white list|
|             |interval_min      | [`0`-UINT32_MAX]          | Minimum advertising interval in 0.625 miliseconds <br> If 0 use stack default. |
|             |interval_max      | [`0`-UINT32_MAX]          | Maximum advertising interval in 0.625 miliseconds <br> If 0 use stack default. |
|             |rx_power          | [-127 - `127`]            | Advertising TX power in dBm                                |
|             |primary_phy       | `1M`                      | Use 1M PHY on primary advertising channels                 |
|             |                  | `coded`                   | Use Coded PHY on primary advertising channels              |
|             |secondary_phy     | `1M`                      | Use 1M PHY on secondary advertising channels               |
|             |                  | `coded`                   | Use coded PHY on primary advertising channels              |
|             |                  | `2M`                      | Use 2M PHY on primary advertising channels                 |
|             |sid               | [`0`-16]                  | Adsertising instance SID                                   |
|             |high_duty         | [`0`-1]                   | Use high_duty advertising                                  |
|             |anonymous         | [`0`-1]                   | Use anonymous advertising                                  |
|             |legacy            | [`0`-1]                   | Use legacy PDUs for advertising                            |
|             |include_tx_power  | [`0`-1]                   | Include TX power information in advertising PDUs           |
|             |scan_req_notif    | [`0`-1]                   | Enable SCAN_REQ notifications                              |
|**advertise-set-addr**|         |                           | Configure *random* adress for instance                     |
|             |instance          | [`0`-UINT8_MAX]           | Advertising instance                                       |
|             |addr              | XX:XX:XX:XX:XX:XX         | Random address                                             |
|**advertise-set-adv-data**|     |                           | Configure advertising instance ADV_DATA. This allow to configure following TLVs:|
|**advertise-set-scan-rsp**|     |                           | Configure advertising instance SCAN_RSP. This allow to configure following TLVs:|
|             |instance          | [`0`-UINT8_MAX]           | Advertising instance                                       |
|             |flags             | [`0`-UINT8_MAX]           | Flags value                                                |
|             |uuid16            | [UINT16]                  | 16-bit UUID value (can be passed multiple times)           |
|             |uuid16_is_complete| [`0`-1]                   | I 16-bit UUID list is complete                             |
|             |uuid32            | [UINT32]                  | 32-bit UUID value (can be passed multiple times)           |
|             |uuid32_is_complete| [`0`-1]                   | I 32-bit UUID list is complete                             |
|             |uuid128           | XX:XX:XX:...              | 128-bit UUID value (16 bytes) (can be passed multiple times)|
|             |uuid128_is_complete| [`0`-1]                  | I 128-bit UUID list is complete                            |
|             |tx_power_level    | [-127 - 127]              | TX Power level to include                                  |
|             |appearance        | [UINT16]                  | Appearance                                                 |
|             |name              | string                    | Name                                                       |
|             |advertising_interval| [UINT16]                | Advertising interval                                       |
|             |service_data_uuid32| XX:XX:XX:...             | 32-bit UUID service data                                   |
|             |service_data_uuid128| XX:XX:XX:...            | 128-bit UUID service data                                  |
|             |uri               | XX:XX:XX:...              | URI                                                        |
|             |msg_data          | XX:XX:XX:...              | Manufacturer data                                          |
|             |eddystone_url     | string                    | Eddystone with specified URL                               |
|**advertise-start**|            |                           | Start advertising with configured instance                 |
|             |instance          | [`0`-UINT8_MAX]           | Advertising instance                                       |
|             |duration          | [`0`-UINT16_MAX]          | Advertising duration in 10ms units. 0 - forver             |
|             |max_events        | [`0`-UINT8_MAX]           | Maximum number of advertising events. 0 - no limit         |
|**advertise-stop**|             |                           | Stop advertising                                           |
|             |instance          | [`0`-UINT8_MAX]           | Advertising instance                                       |
|**advertise-remove**|           |                           | Remove configured advertising instance                     |
|             |instance          | [`0`-UINT8_MAX]           | Advertising instance                                       |

## Legacy Advertising with Extended Advertising disabled

|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**advertise**|                  |                           | Enable advertising                                         |
|             |stop              |                           | Stop enabled advertising                                   |
|             |conn              | `und`                     | Connectable mode: undirected                               |
|             |                  | non                       | non-connectable                                            |
|             |                  | dir                       | directed                                                   |
|             |discov            | `gen`                     | Discoverable mode: general discoverable                    |
|             |                  | ltd                       | limited discoverable                                       |
|             |                  | non                       | non-discoverable                                           |
|             |scannable         | [`0`-1]                   | Use scannable advertising                                  |
|             |peer_addr_type    | `public`                  | Remote device public address type                          |
|             |                  | random                    | Remote device random address type                          |
|             |                  | public_id                 | Remote device public address type (Identity)               |
|             |                  | random_id                 | Remote device random address type (Identity)               |
|             |peer_addr         | XX:XX:XX:XX:XX:XX         | Remote device address - if provided perform directed advertising |
|             |own_addr_type     | `public`                  | Use public address for scan requests                       |
|             |                  | random                    | Use random address for scan requests                       |
|             |                  | rpa_pub                   | Use RPA address for scan requests <br> (fallback to public if no IRK) |
|             |                  | rpa_rnd                   | Use RPA address for scan requests <br> (fallback to random if no IRK) |
|             |channel_map       | [`0`-UINT8_MAX}           | Primary advertising channels map. If 0 use all channels.   |
|             |filter            | `none`                    | Advertising filter policy - no filtering, no whitelist used|
|             |                  | scan                      | process all connection requests but only scans from white list|
|             |                  | conn                      | process all scan request but only connection requests from white list|
|             |                  | both                      | ignore all scan and connection requests unless in white list|
|             |interval_min      | [`0`-UINT32_MAX]          | Minimum advertising interval in 0.625 miliseconds <br> If 0 use stack default. |
|             |interval_max      | [`0`-UINT32_MAX]          | Maximum advertising interval in 0.625 miliseconds <br> If 0 use stack default. |
|             |high_duty         | [`0`-1]                   | Use high_duty advertising                                  |
|             |duration          | [`1`-INT32_MAX]           | Advertising duration in ms                                 |
|**set-adv-data**|     |                                     | Configure advertising instance ADV_DATA. This allow to configure following TLVs:|
|**set-scan-rsp**|     |                                     | Configure advertising instance SCAN_RSP. This allow to configure following TLVs:|
|             |flags             | [`0`-UINT8_MAX]           | Flags value                                                |
|             |uuid16            | [UINT16]                  | 16-bit UUID value (can be passed multiple times)           |
|             |uuid16_is_complete| [`0`-1]                   | I 16-bit UUID list is complete                             |
|             |uuid32            | [UINT32]                  | 32-bit UUID value (can be passed multiple times)           |
|             |uuid32_is_complete| [`0`-1]                   | I 32-bit UUID list is complete                             |
|             |uuid128           | XX:XX:XX:...              | 128-bit UUID value (16 bytes) (can be passed multiple times)|
|             |uuid128_is_complete| [`0`-1]                  | I 128-bit UUID list is complete                            |
|             |tx_power_level    | [-127 - 127]              | TX Power level to include                                  |
|             |appearance        | [UINT16]                  | Appearance                                                 |
|             |name              | string                    | Name                                                       |
|             |advertising_interval| [UINT16]                | Advertising interval                                       |
|             |service_data_uuid32| XX:XX:XX:...             | 32-bit UUID service data                                   |
|             |service_data_uuid128| XX:XX:XX:...            | 128-bit UUID service data                                  |
|             |uri               | XX:XX:XX:...              | URI                                                        |
|             |msg_data          | XX:XX:XX:...              | Manufacturer data                                          |
|             |eddystone_url     | string                    | Eddystone with specified URL                               |

## L2CAP Connection Oriented Channels
|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**l2cap-create-server**     |   |                           | Create L2CAP server                                        |
|             |psm               | [UINT16]                  | PSM                                                        |
|**l2cap-connect**  |            |                           | Connect to remote L2CAP server                             |
|             |conn              | [UINT16]                  | Connection handle                                          |
|             |psm               | [UINT16]                  | PSM                                                        |
|**l2cap-disconnect**  |         |                           | Disconnec from L2CAP server                                |
|             |conn              | [UINT16]                  | Connection handle                                          |
|             |idx               | [UINT16]                  | L2CAP connection oriented channel identifier               |
|**l2cap-send**  |               |                           | Send data over connected L2CAP channel                     |
|             |conn              | [UINT16]                  | Connection handle                                          |
|             |idx               | [UINT16]                  | L2CAP connection oriented channel identifier               |
|             |bytes             | [UINT16]                  | Number of bytes to send (hardcoded data pattern)           |
|**l2cap-show-coc**  |           |                           | Show connected L2CAP channels                              |

## Keys storage
|**Command**  | **Parmeters**    | ** Possible values**      | **Description**                                            |
|-------------|------------------|---------------------------|------------------------------------------------------------|
|**keystore-add**    |           |                           | Add keys to storage                                        |
|             |type              | msec                      | Master Key                                                 |
|             |                  | ssec                      | Slave Key                                                  |
|             |                  | cccd                      | Client Characteristic Configuration Descriptor             |
|             |addr              | XX:XX:XX:XX:XX:XX         | Device address                                             |
|             |addr_type         | `public`                  | Device address type                                        |
|             |                  | random                    | Use random address for scan requests                       |
|             |ediv              | [UINT16]                  | EDIV for LTK to add                                        |
|             |rand              | [UINT64]                  | Rand for LTK                                               |
|             |ltk               | XX:XX:XX...               | LTK (16 bytes)                                             |
|             |irk               | XX:XX:XX...               | Identity Resolving Key (16 bytes)                          |
|             |csrk              | XX:XX:XX...               | Connection Signature Resolving Key (16 bytes)              |
|**keystore-del**    |           |                           | Delete keys from storage                                   |
|             |type              | msec                      | Master Key                                                 |
|             |                  | ssec                      | Slave Key                                                  |
|             |                  | cccd                      | Client Characteristic Configuration Descriptor             |
|             |addr              | XX:XX:XX:XX:XX:XX         | Device address                                             |
|             |addr_type         | `public`                  | Device address type                                        |
|             |                  | random                    | Use random address for scan requests                       |
|             |ediv              | [UINT16]                  | EDIV for LTK to remove                                     |
|             |rand              | [UINT64]                  | Rand for LTK                                               |
|**keystore-show**   |           |                           | Show stored keys                                           |
|             |type              | msec                      | Master Keys                                                |
|             |                  | ssec                      | Slave Keys                                                 |
|             |                  | cccd                      | Client Characteristic Configuration Descriptor s           |
