## <font color="F2853F" style="font-size:24pt">NimBLE Host GATT Server Reference</font>

### Introduction

The Generic Attribute Profile (GATT) manages all activities involving services, characteristics, and descriptors.  The server half of the GATT API handles registration and responding to GATT clients.

### Header

```c
#include "host/ble_hs.h"
```

### Definitions

[BLE host GATT server definitions](definitions/ble_gatts_defs.md)

### Functions

| Function | Description |
|----------|-------------|
| [ble_gatts_add_svcs](functions/ble_gatts_add_svcs.md) | Queues a set of service definitions for registration. |
| [ble_gatts_count_cfg](functions/ble_gatts_count_cfg.md) | Adjusts a host configuration object's settings to accommodate the specified service definition array. |
| [ble_gatts_find_chr](functions/ble_gatts_find_chr.md) | Retrieves the pair of attribute handles associated with a local GATT characteristic. |
| [ble_gatts_find_dsc](functions/ble_gatts_find_dsc.md) | Retrieves the attribute handle associated with a local GATT descriptor. |
| [ble_gatts_find_svc](functions/ble_gatts_find_svc.md) | Retrieves the attribute handle associated with a local GATT service. |
