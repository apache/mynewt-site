## <font color="F2853F" style="font-size:24pt">NimBLE Host Other Reference</font>

### Introduction

This section is a reference on miscellaneous parts of the NimBLE host which don't fit anywhere else!

### Header

```c
#include "host/ble_hs.h"
```

### Definitions

None.

### Functions

| Function | Description |
|----------|-------------|
| [ble_eddystone_set_adv_data_uid](functions/ble_eddystone_set_adv_data_uid.md) | Configures the device to advertise eddystone UID beacons. |
| [ble_eddystone_set_adv_data_url](functions/ble_eddystone_set_adv_data_url.md) | Configures the device to advertise eddystone URL beacons. |
| [ble_hs_evq_set](functions/ble_hs_evq_set.md) | Designates the specified event queue for NimBLE host work. |
| [ble_hs_mbuf_att_pkt](functions/ble_hs_mbuf_att_pkt.md) | Allocates an mbuf suitable for an ATT command packet. |
| [ble_hs_mbuf_from_flat](functions/ble_hs_mbuf_from_flat.md) | Allocates a an mbuf and fills it with the contents of the specified flat buffer. |
| [ble_hs_mbuf_to_flat](functions/ble_hs_mbuf_to_flat.md) | Copies the contents of an mbuf into the specified flat buffer. |
| [ble_hs_sched_reset](functions/ble_hs_sched_reset.md) | Causes the host to reset the NimBLE stack as soon as possible. |
| [ble_hs_synced](functions/ble_hs_synced.md) | Indicates whether the host has synchronized with the controller. |
| [ble_ibeacon_set_adv_data](functions/ble_ibeacon_set_adv_data.md) | Configures the device to advertise iBeacons. |
| [ble_uuid_cmp](functions/ble_uuid_cmp.md) | Compares two Bluetooth UUIDs. |
| [ble_uuid_init_from_buf](functions/ble_uuid_init_from_buf.md) | Constructs a UUID object from a byte array. |
| [ble_uuid_to_str](functions/ble_uuid_to_str.md) | Converts the specified UUID to its string representation. |
| [ble_uuid_u16](functions/ble_uuid_u16.md) | Converts the specified 16-bit UUID to a uint16\_t. |
