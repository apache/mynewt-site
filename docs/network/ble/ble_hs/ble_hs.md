# NimBLE Host

### Introduction

At a high level, the NimBLE stack is is divided into two components:

* Host
* Controller

This document is an API reference for the host component.  If you are interested in the general structure of the NimBLE stack and its non-host components, you might want to read the [BLE introduction](../ble_intro.md).

The host sits directly below the application, and it serves as the interface to the application for all BLE operations.

### Reference

* [NimBLE Host Return Codes](ble_hs_return_codes.md)
* [Initialization and Configuration](init/init.md)
* [Generic Access Protocol (GAP)](ble_gap/ble_gap.md)
* [Generic Attribute Profile (GATT) Client](ble_gattc/ble_gattc.md)
* [Generic Attribute Profile (GATT) Server](ble_gatts/ble_gatts.md)
* [Identity](ble_hs_id/ble_hs_id.md)
* [Other](other/other.md)
