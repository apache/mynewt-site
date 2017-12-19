## GATT feature API for btshell

<br>

GATT(GENERIC ATTRIBUTE PROFILE) describes a service framework using the Attribute Protocol for discovering services, and for reading and writing characteristic values on a peer device. There are 11 features defined in the GATT Profile, and each of the features is mapped to procedures and sub-procedures: 


| **Item No.** | **Feature**                            | **Sub-Procedure**                         | **nimBLE command**                                                |
|--------------|----------------------------------------|-------------------------------------------|-------------------------------------------------------------------|
|            1 | Server Configuration                   | Exchange MTU                              | `gatt-exchange-mtu conn=x`                                        |
|            2 | Primary Service Discovery              | Discover All Primary Services             | `gatt-discover-service conn=x`                                    |
|              |                                        | Discover Primary Services By Service UUID | `gatt-discover-service conn=x uuid=x`                             |
|            3 | Relationship Discovery                 | Find Included Services                    | `gatt-find-included-services conn=x start=x end=x`                |
|            4 | Characteristic Discovery               | Discover All Characteristic of a Service  | `gatt-discover-characteristic conn=x start=x end=x`               |
|              |                                        | Discover Characteristic by UUID           | `gatt-discover-characteristic conn=x start=x end=x uuid=x`        |
|            5 | Characteristic Descriptor Discovery    | Discover All Characteristic Descriptors   | `gatt-discover-descriptor conn=x start=x end=x`                   |
|            6 | Reading a Characteristic Value         | Read Characteristic Value                 | `gatt-read conn=x attr=x`                                         |
|              |                                        | Read Using Characteristic UUID            | `gatt-read conn=x start=x end=x uuid=x`                           |
|              |                                        | Read Long Characteristic Values           | `gatt-read conn=x attr=x long=1`                                  |
|              |                                        | Read Multiple Characteristic Values       | `gatt-read conn=x attr=x attr=y attr=z`                           |
|            7 | Writing a Characteristic Value         | Write Without Response                    | `gatt-write conn=x value=0xXX:0xXX no_rsp=1`                      |
|              |                                        | Signed Write Without Response             | NOT SUPPORTED                                                     |
|              |                                        | Write Characteristic Value                | `gatt-write conn=x attr=x value=0xXX:0xXX`                        |
|              |                                        | Write Long Characteristic Values          | `gatt-write conn=x attr=x value=0xXX:0xXX long=1`                 |
|              |                                        | Characteristic Value Reliable Writes      | `gatt-write conn=x attr=x value=0xXX:0xXX attr=y value=0xYY:0xYY` |
|            8 | Notification of a Characteristic Value | Notifications                             | Write _0x01:0x00_ to CLIENT CONFIGURATION characteristic          |
|            9 | Indication of a Characteristic Value   | Indications                               | Write _0x02:0x00_ to CLIENT CONFIGURATION characteristic          |
|           10 | Reading a Characteristic Descriptor    | Read Characteristic Descriptors           | `gatt-read conn=x attr=x`                                         |
|              |                                        | Read Long Characteristic Descriptors      | `gatt-read conn=x attr=x long=1`                                  |
|           11 | Writing a Characteristic Descriptor    | Write Characteristic Descriptors          | `gatt-write conn=x value=0xXX:0xXX`                               |
|              |                                        | Write Long Characteristic Descriptors     | `gatt-write conn=x value=0xXX:0xXX long=1`                        |


<br>

### Using NimBLE commands 


Assuming you have discovered and established a BLE connection with at least one peer device (as explained earlier in [API for btshell app](btshell_api.md), you can find out what characteristics and services are available over these connections. Here is a recap.

To show established connections:
```
gatt-show-conn
```

To show discovered services, characteristics, and descriptors:
```
gatt-show
```

To show local database of services, characteristics, and descriptors:
```
gatt-show-local
```

To show connection RSSI:
```
conn-rssi conn=x
```
