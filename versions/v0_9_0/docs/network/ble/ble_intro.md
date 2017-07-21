## BLE Introduction

Apache Mynewt offers the world's first fully open-source Bluetooth Low Energy (BLE) or Bluetooth Smart stack. It is called NimBLE. 

BLE technology operates in the unlicensed industrial, scientific and medical (ISM) band at 2.4 to 2.485 GHz which is available in most countries. It uses a spread spectrum, frequency hopping, full-duplex signal. BLE FHSS employs 40 2-MHz-wide channels to ensure greater reliability over longer distances. It also features 0-dBm (1 mW) power output and a typical maximum range of 50 meters. Note that BLE is not compatible with standard Bluetooth.

<br>

### Features

NimBLE complies with Bluetooth Core Specification 4.2 which introduces several new features that make it an ideal wireless technology for the Internet of Things (IoT).

* LE Privacy 1.2 for frequent changes to the device address to make it difficult to track for outsiders **Roadmap**
* LE Secure Connections featuring FIPS-compliant algorithms. **Roadmap**
* LE Data Length Extension for higher throughput **Available now**
* Enables users to assign an Internet Protocol (IP) address (complaint with the IPv6 or 6LoWPAN standard) to a Bluetooth device through Internet Protocol Support Profile (IPSP) **Roadmap**

NimBLE supports features from older specifications including,

* Support multiple roles (master(central)/slave(peripheral), server/client) simultaneously
* Support simultaneous advertising and scanning
* Support being slave to multiple masters simultaneously (subject to memory and scheduling constraints)
* Low Duty Cycle Directed Advertising
* Connection parameters request procedure
* LE Ping
* 32 bits UUID
* L2CAP Connection Oriented Channels
<br>

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

Mynewt comes with two built-in projects that allow users to play with NimBLE, try the tutorials out with, and see how to use available services.

1. **bletiny** : A simple shell application which provides a basic interface to the host-side of the BLE stack. 
2. **bleprph**: A basic peripheral device with no user interface. It advertises automatically on startup, and resumes advertising whenever a connection is terminated. It supports a maximum of one connection.

<br>
