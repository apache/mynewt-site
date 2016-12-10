## <font color="F2853F" style="font-size:24pt">NimBLE Host Init and Config Reference</font>

### Introduction

This section is a reference on initializing and configuring the NimBLE host.

### Header

```c
#include "host/ble_hs.h"
```

### Definitions

[BLE host init and config definitions](definitions/init_defs.md)

### Functions

| Function | Description |
|----------|-------------|
| [ble_hs_init](functions/ble_hs_init.md) | Initializes the NimBLE host. |
| [ble_hs_start](functions/ble_hs_start.md) | Synchronizes the host with the controller by sending a sequence of HCI commands. |
| [ble_hs_synced](functions/ble_hs_synced.md) | Indicates whether the host has synchronized with the controller. |
