## BLE Introduction

Apache Mynewt offers the world's first fully open-source Bluetooth Low Energy (BLE) or Bluetooth Smart stack fully compliant with Bluetooth 5 specifications. It is called NimBLE.

BLE technology operates in the unlicensed industrial, scientific and medical (ISM) band at 2.4 to 2.485 GHz which is available in most countries. It uses a spread spectrum, frequency hopping, full-duplex signal. BLE FHSS employs 40 2-MHz-wide channels to ensure greater reliability over longer distances. It also features 0-dBm (1 mW) power output and a typical maximum range of 50 meters.
With Bluetooth 5 specification range can be increased 4 times and speed 2 time.

Note that BLE is not compatible with standard Bluetooth.

<br>

### Feature Support

NimBLE complies with Bluetooth Core Specification 5.0 which makes it an ideal wireless technology for the Internet of Things (IoT).

* LE Advertising Extensions
* 2Msym/s PHY for higher throughput
* Coded PHY for LE Long Range
* High Duty Cycle Non-Connectable Advertising
* Channel Selection Algorithm #2 to utilize channels in more efficient way.
* LE Privacy 1.2 for frequent changes to the device address to make it difficult to track for outsiders
* LE Secure Connections featuring FIPS-compliant algorithms.
* LE Data Length Extension for higher throughput
* **Coming Soon**: Assigning an Internet Protocol (IP) address (complaint with the IPv6 or 6LoWPAN standard) to a Bluetooth device through Internet Protocol Support Profile (IPSP)

The Bluetooth 5 is backward compatible with previous Bluetooth version 4.2 which is also supported by Apache Mynewt.

### Components

A Bluetooth low energy stack (NimBLE included) consists of two components with several subcomponents:

* **Controller**
    * **Physical Layer**: adaptive frequency-hopping Gaussian Frequency Shift Keying (GFSK) radio using 40 RF channels (0-39), with 2 MHz spacing.
    * **Link Layer**: with one of five states (Standby, Advertising, Scanning, Initiating, Connection states) active at any time

* **Host**
    * **Logical Link Control and Adaptation Protocol (L2CAP)**: provides logical channels, named L2CAP channels, which are multiplexed over one or more logical links to provide packet segmentation and reassembly, flow control, error control, streaming, QoS etc. 
    * **Security Manager (SM)**: uses Security Manager Protocol (SMP) for pairing and transport specific key distribution for securing radio communication 
    * **Attribute protocol (ATT)**: allows a device (*Server*) to expose certain pieces of data, known as *Attributes*, to another device (*Client*)
    * **Generic Attribute Profile (GATT)**: a framework for using the ATT protocol to exchange attributes encapsulated as *Characteristics* or *Services* 
    * **Generic Access Profile (GAP)**: a base profile which all Bluetooth devices implement, which in the case of LE, defines the Physical Layer, Link Layer, L2CAP, Security Manager, Attribute Protocol and Generic Attribute Profile. 
    * **Host Controller Interface (HCI)**: the interface between the host and controller either through software API or by a hardware interface such as SPI, UART or USB.
    
Subsequent chapters in this manual will go into the details of the implementation of each component, APIs available, and things to consider while designing a NimBLE app.

<br>

### Example NimBLE projects

Mynewt comes with several built-in projects or applications using NimBLE. These allow users to try out NimBLE, understand how to use available services, and build their own applications using one or more of the examples as seed.

1. **bletiny** : A simple shell application which provides a basic interface to the host-side of the BLE stack. Supported operations include GAP, GATT, and L2CAP.

2. **bleprph**: A basic peripheral device with no user interface. It advertises automatically on startup, and resumes advertising whenever a connection is terminated. It supports a maximum of one connection.

3. **blecent**: A basic central device with no user interface.  This application scans for a peripheral that supports the alert notification service (ANS).  Upon discovering such a peripheral, blecent connects and performs the following actions:

    * Reads the ANS Supported New Alert Category characteristic.
    * Writes the ANS Alert Notification Control Point characteristic.
    * Subscribes to notifications for the ANS Unread Alert Status characteristic.


4. **blehci**: Implements a BLE controller-only application.  A separate host-only implementation, such as Linux's BlueZ, can interface with this application via HCI over UART.

5. **bleuart**:  Implements a simple BLE peripheral that supports the Nordic
[UART / Serial Port Emulation service](https://developer.nordicsemi.com/nRF5_SDK/nRF51_SDK_v8.x.x/doc/8.0.0/s110/html/a00072.html)

<br>
