## GATT feature API for bletiny

<br>

GATT(GENERIC ATTRIBUTE PROFILE) describes a service framework using the Attribute Protocol for discovering services, and for reading and writing characteristic values on a peer device. There are 11 features defined in the GATT Profile, and each of the features is mapped to procedures and sub-procedures: 

|**Item No.** | **Feature** | **Sub-Procedure** | **nimBLE command** |
|----|---------|---------------|------|
| 1  | Server Configuration | Exchange MTU | `b mtu` | 
| 2 | Primary Service Discovery | Discover All Primary Services | `b disc svc conn=x` | 
|   |   | Discover Primary Services By Service UUID | `b disc svc conn=x uuid=x` |
| 3  | Relationship Discovery | Find Included Services | `b find inc_svcs conn=x start=x end=x` |
| 4 | Characteristic Discovery | Discover All Characteristic of a Service | `b disc chr conn=x start=x end=x` |
|   |   | Discover Characteristic by UUID | `b disc chr conn=x start=x end=x uuid=x` |
| 5  | Characteristic Descriptor Discovery | Discover All Characteristic Descriptors | `b disc dsc conn=x start=x end=x` |
| 6 | Reading a Characteristic Value | Read Characteristic Value | `b read conn=x attr=x` |
|   |   | Read Using Characteristic UUID | `b read conn=x start=x end=x uuid=x` |
|   |   | Read Long Characteristic Values | `b read conn=x attr=x long=1` |
|   |   | Read Multiple Characteristic Values | `b read conn=x attr=x attr=y attr=z` |
| 7  | Writing a Characteristic Value  | Write Without Response | `b write conn=x value=0xXX:0xXX no_rsp=1` |
|   |   | Signed Write Without Response | NOT SUPPORTED |
|   |   | Write Characteristic Value | `b write conn=x attr=x value=0xXX:0xXX` |
|   |   | Write Long Characteristic Values | `b write conn=x attr=x value=0xXX:0xXX long=1` |
|   |   | Characteristic Value Reliable Writes | `b write conn=x attr=x value=0xXX:0xXX attr=y value=0xYY:0xYY` |
| 8 | Notification of a Characteristic Value | Notifications | Write CLIENT CONFIGURATION characteristic |
| 9 | Indication of a Characteristic Value | Indications | Write CLIENT CONFIGURATION characteristic |
| 10| Reading a Characteristic Descriptor | Read Characteristic Descriptors | `b read conn=x attr=x` |
|   |   | Read Long Characteristic Descriptors | `b read conn=x attr=x long=1` |
| 11 | Writing a Characteristic Descriptor | Write Characteristic Descriptors | `b write conn=x value=0xXX:0xXX` |
|   |   | Write Long Characteristic Descriptors | `b write conn=x value=0xXX:0xXX long=1` |


<br>
### Using nimBLE commands
Assuming you have discovered and established a BLE connection with at least one peer device (as explained earlier in [API for bletiny app](bletiny_api.md), you can find out what characteristics and services are available over these connections. Here is a recap.

```
b show conn
```
To show discovered services
```
b show svc
```

To show discovered characteristics
```
b show chr
```

To show connection RSSI
```
b show rssi conn=x
```