
## Advertisement Data Fields

<br>

This part defines the advertisement data fields used in the `bletiny` app. For a complete list of all data types and formats used for Extended Inquiry Response (EIR), Advertising Data (AD), and OOB data blocks, refer to the Supplement to the Bluetooth Core Specification, CSSv6, available for download [here](https://www.bluetooth.org/DocMan/handlers/DownloadDoc.ashx?doc_id=302735&_ga=1.133090766.1368218946.1444779486). 

<br>


|**Name** | **Definition** | **Details** |
|----|---------|---------------|
|  uuids16 |16-bit Bluetooth Service UUIDs | Indicates the Service UUID list is incomplete i.e. more 16-bit Service UUIDs available. 16 bit UUIDs shall only be used if they are assigned by the Bluetooth SIG.  |
| uuids16_is_complete  | 16-bit Bluetooth Service UUIDs | Indicates the Service UUID list is complete. 16 bit UUIDs shall only be used if they are assigned by the Bluetooth SIG.  |
|  uuids32 | 32-bit Bluetooth Service UUIDs   | Indicates the Service UUID list is incomplete i.e. more 32-bit Service UUIDs available. 32 bit UUIDs shall only be used if they are assigned by the Bluetooth SIG.   |
| uuids32_is_complete  | 32-bit Bluetooth Service UUIDs   |  Indicates the Service UUID list is complete. 32 bit UUIDs shall only be used if they are assigned by the Bluetooth SIG. |
| uuids128  | Global 128-bit Service UUIDs   | More 128-bit Service UUIDs available.  |
| uuids128_is_complete  |  Global 128-bit Service UUIDs  | Complete list of 128-bit Service UUIDs  |
| tx_pwr_lvl  | TX Power Level   | Indicates the transmitted power level of the packet containing the data type. The TX Power Level data type may be used to calculate path loss on a received packet using the following equation: <br> <br> pathloss = Tx Power Level – RSSI <br> <br> where “RSSI” is the received signal strength, in dBm, of the packet received.  |
| device_class  |  Class of device  | Size: 3 octets  |
| slave_itvl_range | Slave Connection Interval Range   | Contains the Peripheral’s preferred connection interval range, for all logical connections. Size: 4 Octets . The first 2 octets defines the minimum value for the connection interval in the following manner: <br> <br> connIntervalmin = Conn_Interval_Min * 1.25 ms <br> <br> Conn_Interval_Min range: 0x0006 to 0x0C80 <br> Value of 0xFFFF indicates no specific minimum. <br> <br> The other 2 octets defines the maximum value for the connection interval in the following manner: <br> <br> connIntervalmax = Conn_Interval_Max * 1.25 ms <br> Conn_Interval_Max range: 0x0006 to 0x0C80 <br> Conn_Interval_Max shall be equal to or greater than the Conn_Interval_Min. <br> Value of 0xFFFF indicates no specific maximum.|
| svc_data_uuid16  |  Service Data - 16 bit UUID  | Size: 2 or more octets <br> The first 2 octets contain the 16 bit Service UUID followed by additional service data |
| public_tgt_addr  |  Public Target Address  | Defines the address of one or more intended recipients of an advertisement when one or more devices were bonded using a public address. This data type shall exist only once. It may be sent in either the Advertising or Scan Response data, but not both. |
| appearance  | Appearance   | Defines the external appearance of the device. The Appearance data type shall exist only once. It may be sent in either the Advertising or Scan Response data, but not both.  |
| adv_itvl  | Advertising Interval   | Contains the advInterval value as defined in the Core specification, Volume 6, Part B, Section 4.4.2.2.  |
| le_addr  |  LE Bluetooth Device Address  | Defines the device address of the local device and the address type on the LE transport.  |
| le_role  | LE Role   | Defines the LE role capabilities of the device. <br> 0x00 Only Peripheral Role supported <br> 0x01 Only Central Role supported <br> 0x02 Peripheral and Central Role supported, Peripheral Role preferred for connection establishment <br> 0x03 Peripheral and Central Role supported, Central Role preferred for connection establishment <br> 0x04 – 0xFF Reserved for future use |
| svc_data_uuid32  | Service Data - 32 bit UUID  | Size: 4 or more octets <br> The first 4 octets contain the 32 bit Service UUID followed by additional service data |
| svc_data_uuid128  | Service Data - 128 bit UUID   | Size: 16 or more octets <br> The first 16 octets contain the 128 bit Service UUID followed by additional service data  |
| uri  |  Uniform Resource Identifier (URI) | Scheme name string and URI as a UTF-8 string  |
| mfg_data |   Manufacturer Specific data | Size: 2 or more octets <br> The first 2 octets contain the Company Identifier Code followed by additional manufacturer specific data |

<br>
