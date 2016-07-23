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
| [ble_hs_mbuf_att_pkt](functions/ble_hs_mbuf_att_pkt.md) | Allocates an mbuf suitable for an ATT command packet. |
| [ble_hs_mbuf_from_flat](functions/ble_hs_mbuf_from_flat.md) | Allocates a an mbuf and fills it with the contents of the specified flat buffer. |
| [ble_hs_mbuf_to_flat](functions/ble_hs_mbuf_to_flat.md) | Copies the contents of an mbuf into the specified flat buffer. |
| [ble_ibeacon_set_adv_data](functions/ble_ibeacon_set_adv_data.md) | Configures the device to advertise iBeacons. |
| [ble_uuid_128_to_16](functions/ble_uuid_128_to_16.md) | Attempts to convert the supplied 128-bit UUID into its shortened 16-bit form. |
| [ble_uuid_16_to_128](functions/ble_uuid_16_to_128.md) | Expands a 16-bit UUID into its 128-bit form. |
