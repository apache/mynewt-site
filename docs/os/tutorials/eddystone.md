## BLE Eddystone

<br>

### Eddystone Beacon Protocol

A beaconing device announces its presence to the world by broadcasting
advertisements.  The Eddystone protocol is built on top of the standard BLE
advertisement specification.  Eddystone supports multiple data packet types

* Eddystone-UID: a unique, static ID with a 10-byte Namespace component and a 6-byte Instance component.
* Eddystone-URL: a compressed URL that, once parsed and decompressed, is directly usable by the client.
* Eddystone-TLM: "telemetry" packets that are broadcast alongside the Eddystone-UID or Eddystone-URL packets and contains beacon’s “health status” (e.g., battery life).
* Eddystone-EID to broadcast an ephemeral identifier that changes every few minutes and allow only parties that can resolve the identifier to use the beacon. 

[This page](https://developers.google.com/beacons/eddystone) describes the Eddystone open beacon format developed by Google.

Apache Mynewt currently supports Eddystone-UID and Eddystone-URL formats only. This tutorial will explain how to get an Eddystone-URL beacon going on a peripheral device.

<br>

### Configuration

Use the following function to configure your NimBLE device to send Eddystone-URL beacons:

```c
int
ble_eddystone_set_adv_data_url(struct ble_hs_adv_fields *adv_fields,
                               uint8_t url_scheme, char *url_body,
                               uint8_t url_body_len, uint8_t url_suffix)
```

This function's parameters are documented below.

| *Parameter* | *Purpose* |
| ----------- | --------- |
| adv_fields | The base advertisement fields to transform into an eddystone beacon.  |
| url_scheme | The prefix of the URL; one of the BLE_EDDYSTONE_URL_SCHEME values from ble_eddystone.h |
| url_body | The middle of the url specified within "". |
| url_body_len | The string length of the url_body argument. |    
| url_suffix | The suffix of the URL; one of the BLE_EDDYSTONE_URL_SUFFIX values from ble_eddystone.h |

<br>

### Modify bleprph

To demonstrate how the above function is used, we will now modify the *bleprph*
example application to send Eddystone beacons.  For some background behind the *bleprph*
app, we recommend you take a look at the [bleprph project
tutorial](bleprph/bleprph-intro/).  If you plan on making these modifications
yourself, it might be a good idea to copy *bleprph* to your local repository
and work with the copy.  In general, you should avoid changing a package that
newt downloads, as you will lose your changes the next time you upgrade the
package.

*bleprph* sets its advertisement data and begins advertising as follows (*main.c*):

```c
static void
bleprph_advertise(void)
{
    struct ble_gap_adv_params adv_params;
    struct ble_hs_adv_fields fields;
    const char *name;
    int rc;

    /**
     *  Set the advertisement data included in our advertisements:
     *     o Flags (indicates advertisement type and other general info).
     *     o Advertising tx power.
     *     o Device name.
     *     o 16-bit service UUIDs (alert notifications).
     */

    memset(&fields, 0, sizeof fields);

    /* Advertise two flags:
     *     o Discoverability in forthcoming advertisement (general)
     *     o BLE-only (BR/EDR unsupported).
     */
    fields.flags = BLE_HS_ADV_F_DISC_GEN |
                   BLE_HS_ADV_F_BREDR_UNSUP;

    /* Indicate that the TX power level field should be included; have the
     * stack fill this value automatically.  This is done by assiging the
     * special value BLE_HS_ADV_TX_PWR_LVL_AUTO.
     */
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

    name = ble_svc_gap_device_name();
    fields.name = (uint8_t *)name;
    fields.name_len = strlen(name);
    fields.name_is_complete = 1;

    fields.uuids16 = (ble_uuid16_t[]){
        BLE_UUID16_INIT(GATT_SVR_SVC_ALERT_UUID)
    };
    fields.num_uuids16 = 1;
    fields.uuids16_is_complete = 1;

    rc = ble_gap_adv_set_fields(&fields);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error setting advertisement data; rc=%d\n", rc);
        return;
    }

    /* Begin advertising. */
    memset(&adv_params, 0, sizeof adv_params);
    adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    rc = ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, NULL, BLE_HS_FOREVER,
                           &adv_params, bleprph_gap_event, NULL);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
}
```

The call to `ble_gap_adv_set_fields()` configures the device with normal
(non-Eddystone) advertisements; the call to `ble_gap_adv_start()` tells the
NimBLE stack to start broadcasting.  We are now going to create an Eddystone app
by making the following changes:

* Call `ble_eddystone_set_adv_data()` instead of `ble_gap_adv_set_fields()`. The tutorial shows how to emit "`https://mynewt.apache.org".
* Remove advertisement data such as device name, flags, tx levels etc. that are not required. 
* Remove unnecessary local variables e.g. `name` pointer.  
* Modify the call to `ble_gap_adv_start()` such that the device is non-discoverable and non-connectable.

<br>

```c hl_lines="9 18 20 29 30"
static void
bleprph_advertise(void)
{   
    struct ble_gap_adv_params adv_params;
    struct ble_hs_adv_fields fields;
    int rc;
    
    /** 
     *  Remove the advertisement data typically included in our advertisements: 
     *     o Flags (indicates advertisement type and other general info).
     *     o Advertising tx power.
     *     o Device name.
     *     o 16-bit service UUIDs (alert notifications).
     */
    
    memset(&fields, 0, sizeof fields);
     
     /* No flags are needed for Eddystone URL. Remove all from default app.*/
    
    rc = ble_eddystone_set_adv_data_url(&fields, BLE_EDDYSTONE_URL_SCHEME_HTTPS, "mynewt.apache", 
                        13, BLE_EDDYSTONE_URL_SUFFIX_ORG); 
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error setting eddystone advertisement data; rc=%d\n", rc);
        return;
    }
    
    /* Begin advertising. */
    memset(&adv_params, 0, sizeof adv_params);
    adv_params.conn_mode = BLE_GAP_CONN_MODE_NON;
    adv_params.disc_mode = BLE_GAP_DISC_MODE_NON;
    rc = ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, NULL, BLE_HS_FOREVER,
                           &adv_params, bleprph_gap_event, NULL);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
}

```

Also include the header file for the eddystone beacon `ble_eddystone.h` in the app's main.c file. 

```c
#include "host/ble_eddystone.h"
``` 

If you have copied the bleprph app into your local repository then make sure that the pkg.yml for the app has the `@apache-mynewt-core/` prefix; otherwise the package dependencies will not be resolved correctly.

```
pkg.deps: 
    - "@apache-mynewt-core/boot/split"
    - "@apache-mynewt-core/kernel/os"
<snip>
```

Finally, enable the `BLE_EDDYSTONE` sysconfig in the syscfg.yml of either your target or your app.
```
syscfg.vals:
    <snip>
    BLE_EDDYSTONE: 1 
```

Now when you run this app on your board, you should be able to see it with all
your Eddystone-aware devices.
