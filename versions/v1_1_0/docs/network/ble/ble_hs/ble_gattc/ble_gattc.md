## <font color="F2853F" style="font-size:24pt">NimBLE Host GATT Client Reference</font>

### Introduction

The Generic Attribute Profile (GATT) manages all activities involving services, characteristics, and descriptors.  The client half of the GATT API initiates GATT procedures.

### Header

```c
#include "host/ble_hs.h"
```

### Definitions

[BLE host GATT client definitions](definitions/ble_gattc_defs.md)

### Functions

| Function | Description |
|----------|-------------|
| [ble_gattc_disc_all_chrs](functions/ble_gattc_disc_all_chrs.md) | Initiates GATT procedure: Discover All Characteristics of a Service. |
| [ble_gattc_disc_all_dscs](functions/ble_gattc_disc_all_dscs.md) | Initiates GATT procedure: Discover All Characteristic Descriptors. |
| [ble_gattc_disc_all_svcs](functions/ble_gattc_disc_all_svcs.md) | Initiates GATT procedure: Discover All Primary Services. |
| [ble_gattc_disc_chrs_by_uuid](functions/ble_gattc_disc_chrs_by_uuid.md) | Initiates GATT procedure: Discover Characteristics by UUID. |
| [ble_gattc_disc_svc_by_uuid](functions/ble_gattc_disc_svc_by_uuid.md) | Initiates GATT procedure: Discover Primary Service by Service UUID. |
| [ble_gattc_exchange_mtu](functions/ble_gattc_exchange_mtu.md) | Initiates GATT procedure: Exchange MTU. |
| [ble_gattc_find_inc_svcs](functions/ble_gattc_find_inc_svcs.md) | Initiates GATT procedure: Find Included Services. |
| [ble_gattc_indicate](functions/ble_gattc_indicate.md) | Sends a characteristic indication. |
| [ble_gattc_indicate_custom](functions/ble_gattc_indicate_custom.md) | Sends a characteristic indication. |
| [ble_gattc_notify](functions/ble_gattc_notify.md) | Sends a characteristic notification. |
| [ble_gattc_notify_custom](functions/ble_gattc_notify_custom.md) | Sends a "free-form" characteristic notification. |
| [ble_gattc_read](functions/ble_gattc_read.md) | Initiates GATT procedure: Read Characteristic Value. |
| [ble_gattc_read_by_uuid](functions/ble_gattc_read_by_uuid.md) | Initiates GATT procedure: Read Using Characteristic UUID. |
| [ble_gattc_read_long](functions/ble_gattc_read_long.md) | Initiates GATT procedure: Read Long Characteristic Values. |
| [ble_gattc_read_mult](functions/ble_gattc_read_mult.md) | Initiates GATT procedure: Read Multiple Characteristic Values. |
| [ble_gattc_write](functions/ble_gattc_write.md) | Initiates GATT procedure: Write Characteristic Value. |
| [ble_gattc_write_flat](functions/ble_gattc_write_flat.md) | Initiates GATT procedure: Write Characteristic Value (flat buffer version). |
| [ble_gattc_write_long](functions/ble_gattc_write_long.md) | Initiates GATT procedure: Write Long Characteristic Values. |
| [ble_gattc_write_no_rsp](functions/ble_gattc_write_no_rsp.md) | Initiates GATT procedure: Write Without Response. |
| [ble_gattc_write_no_rsp_flat](functions/ble_gattc_write_no_rsp_flat.md) | Initiates GATT procedure: Write Without Response. |
| [ble_gattc_write_reliable](functions/ble_gattc_write_reliable.md) | Initiates GATT procedure: Reliable Writes. |
