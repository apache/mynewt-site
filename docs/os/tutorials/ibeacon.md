## BLE iBeacon

<br>

### iBeacon Protocol

A beaconing device announces its presence to the world by broadcasting
advertisements.  The iBeacon protocol is built on top of the standard BLE
advertisement specification.  An iBeacon advertisement contains a single field:
*Manufacturer Specific Data*; this field contains the iBeacon-specific
sub-fields.  [This page](http://www.warski.org/blog/2014/01/how-ibeacons-work/)
provides a good summary of the iBeacon sub-fields.

<br>

### Configuration

Use the following function to configure your NimBLE device to send iBeacons:

```c
int
ble_ibeacon_set_adv_data(void *uuid128, uint16_t major, uint16_t minor)
```

This function's parameters are documented below.

| *Parameter* | *Purpose* |
| ----------- | --------- |
| UUID | 128-bit UUID identifying the application |
| Major version number | First number in your app's version |
| Minor version number | Second number in your app's version |

<br>

### Modify bleprph

To demonstrate how the above function is used, we will now modify the *bleprph*
example application to send iBeacons.  For some background behind the *bleprph*
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
    struct ble_hs_adv_fields fields;
    int rc;

    /* Set the advertisement data included in our advertisements. */
    memset(&fields, 0, sizeof fields);
    fields.name = (uint8_t *)bleprph_device_name;
    fields.name_len = strlen(bleprph_device_name);
    fields.name_is_complete = 1;
    rc = ble_gap_adv_set_fields(&fields);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error setting advertisement data; rc=%d\n", rc);
        return;
    }

    /* Begin advertising. */
    rc = ble_gap_adv_start(BLE_GAP_DISC_MODE_GEN, BLE_GAP_CONN_MODE_UND,
                           NULL, 0, NULL, bleprph_on_connect, NULL);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
}
```

The call to `ble_gap_adv_set_fields()` configures the device with normal
(non-iBeacon) advertisements; the call to `ble_gap_adv_start()` tells the
NimBLE stack to start broadcasting.  We are now going to create an iBeacon app
by making the following to changes:

* Call `ble_ibeacon_set_adv_data()` instead of `ble_gap_adv_set_fields()`.
* Modify the call to `ble_gap_adv_start()` such that the device is non-discoverable and non-connectable.

<br>

```c hl_lines="4 7 8 10 11 19"
static void
bleprph_advertise(void)
{
    uint8_t uuid128[16];
    int rc;

    /* Arbitrarily et the UUID to a string of 0x11 bytes. */
    memset(uuid128, 0x11, sizeof uuid128);

    /* Major version=2; minor version=10. */
    rc = ble_ibeacon_set_adv_data(uuid128, 2, 10);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error setting iBeacon advertisement data; rc=%d\n",
                    rc);
        return;
    }

    /* Begin advertising. */
    rc = ble_gap_adv_start(BLE_GAP_DISC_MODE_NON, BLE_GAP_CONN_MODE_NON,
                           NULL, 0, NULL, bleprph_on_connect, NULL);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
}
```

Now when you run this app on your board, you should be able to see it with all
your iBeacon-aware devices.
