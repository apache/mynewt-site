## <font color="F2853F" style="font-size:24pt">NimBLE Host ATT Client Reference</font>

### Introduction

The Attribute Protocol (ATT) is a mid-level protocol that all BLE devices use to exchange data.  Data is exchanged when an ATT client reads or writes an attribute belonging to an ATT server.  Any device that needs to send or receive data must support both the client and server functionality of the ATT protocol.  The only devices which do not support ATT are the most basic ones: broadcasters and observers (i.e., beaconing devices and listening devices).

Most ATT functionality is not interesting to an application.  Rather than use ATT directly, an application uses the higher level GATT profile, which sits directly above ATT in the host.  NimBLE exposes the few bits of ATT functionality which are not encompassed by higher level GATT functions.  This section documents the ATT functionality that the NimBLE host exposes to the application.

### Header

```c
#include "host/ble_hs.h"
```

### Definitions

None.

### Functions

| Function | Description |
|----------|-------------|
| [ble_att_mtu](functions/ble_att_mtu.md) | Retrieves the ATT MTU of the specified connection. |
| [ble_att_preferred_mtu](functions/ble_att_preferred_mtu.md) | Retrieves the preferred ATT MTU. |
| [ble_att_set_preferred_mtu](functions/ble_att_set_preferred_mtu.md) | Sets the preferred ATT MTU; the device will indicate this value in all subseqeunt ATT MTU exchanges. |
| [ble_att_svr_read_local](functions/ble_att_svr_read_local.md) | Reads a locally registered attribute. |
| [ble_att_svr_write_local](functions/ble_att_svr_write_local.md) | Writes a locally registered attribute. |
