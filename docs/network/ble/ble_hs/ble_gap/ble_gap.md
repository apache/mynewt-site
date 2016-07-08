## <font color="F2853F" style="font-size:24pt">NimBLE Host GAP Reference</font>

### Introduction

The Generic Access Profile (GAP) is responsible for all connecting, advertising, scanning, and connection updating operations.

### Header

```c
#include "host/ble_hs.h"
```

### Definitions

[BLE host GAP definitions](definitions/ble_gap_defs.md)

### Functions

| Function | Description |
|----------|-------------|
| [ble_gap_adv_active](functions/ble_gap_adv_active.md) | Indicates whether an advertisement procedure is currently in progress. |
| [ble_gap_adv_rsp_set_fields](functions/ble_gap_adv_rsp_set_fields.md) | Configures the data to include in subsequent scan responses. |
| [ble_gap_adv_set_fields](functions/ble_gap_adv_set_fields.md) | Configures the data to include in subsequent advertisements. |
| [ble_gap_adv_start](functions/ble_gap_adv_start.md) | Initiates advertising. |
| [ble_gap_adv_stop](functions/ble_gap_adv_stop.md) | Stops the currently-active advertising procedure. |
| [ble_gap_conn_active](functions/ble_gap_conn_active.md) | Indicates whether a connect procedure is currently in progress. |
| [ble_gap_conn_cancel](functions/ble_gap_conn_cancel.md) | Aborts a connect procedure in progress. |
| [ble_gap_conn_find](functions/ble_gap_conn_find.md) | Searches for a connection with the specified handle. |
| [ble_gap_connect](functions/ble_gap_connect.md) | Initiates a connect procedure. |
| [ble_gap_disc](functions/ble_gap_disc.md) | Performs the Limited or General Discovery Procedures. |
| [ble_gap_disc_active](functions/ble_gap_disc_active.md) | Indicates whether a discovery procedure is currently in progress. |
| [ble_gap_disc_cancel](functions/ble_gap_disc_cancel.md) | Cancels the discovery procedure currently in progress. |
| [ble_gap_security_initiate](functions/ble_gap_security_initiate.md) | Initiates the GAP encryption procedure. |
| [ble_gap_terminate](functions/ble_gap_terminate.md) | Terminates an established connection. |
| [ble_gap_update_params](functions/ble_gap_update_params.md) | Initiates a connection parameter update procedure. |
 [ble_gap_wl_set](functions/ble_gap_wl_set.md) | Overwrites the controller's white list with the specified contents. |
