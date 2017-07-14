## BLE Peripheral Project

### Service Registration

<br>

#### Attribute Set

The NimBLE host uses a table-based design for GATT server configuration.  The
set of supported attributes are expressed as a series of tables that resides in
your C code.

*bleprph* supports the following services:

* GAP
* GATT
* newtmgr
* Alert Notification
* Security Test

The first two services (GAP and GATT) are mandatory services that all BLE peripherals must support.  These are implemented in a separate package which the *bleprph* app depends on.  Later, we will see how the *main()* function initializes and registers this package.  Your app will follow the same procedure when using GATT service libraries.

The third service, newtmgr, is vendor-specific service supported by most Mynewt devices.  This service is used for remote configuration, status queries, and firmware updates.  As with GAP and GATT, this service is implemented in a package separate from the *bleprph* app.

The final two services, *Alert Notification* and *Security Test*, are not implemented in separate libraries.  Rather, these services are specific to the app, so they are implemented the *bleprph* app itself.  The attribute table used to express these services is located in the *gatt_svr.c* file, so let's take a look at that now.  The attribute table is called `gatt_svr_svcs`; here are the first several lines from this table:

<br>

```c
static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        /*** Alert Notification Service. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid128 = BLE_UUID16(GATT_SVR_SVC_ALERT_UUID),
        .characteristics = (struct ble_gatt_chr_def[]) { {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_NEW_ALERT),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_NOTIFY,
        }, {
    // [...]
```

<br>

As you can see, the table is an array of service definitions (
`struct ble_gatt_svc_def`).  This code excerpt contains a small part of the
Alert Notification service.  Let's now consider the contents of this table in
more detail.

A service definition consists of the following fields:

| *Field*         | *Meaning* | *Notes* |
| --------------- | --------- | ------- |
| type            | Specifies whether this is a primary or secondary service. | Secondary services are not very common.  When in doubt, specify *BLE_GATT_SVC_TYPE_PRIMARY* for new services. |
| uuid128         | The 128-bit UUID of this service. | If the service has a 16-bit UUID, you can convert it to its corresponding 128-bit UUID with the `BLE_UUID16()` macro. |
| characteristics | The array of characteristics that belong to this service.   | |

<br>

A service is little more than a container of characteristics; the
characteristics themselves are where the real action happens.  A characteristic
definition consists of the following fields:

| *Field* | *Meaning* | *Notes* |
| ------- | --------- | ------- |
| uuid128     | The 128-bit UUID of this characteristic. | If the characteristic has a 16-bit UUID, you can convert it to its corresponding 128-bit UUID with the `BLE_UUID16()` macro. |
| access\_cb  | A callback function that gets executed whenever a peer device accesses this characteristic. | *For reads:* this function generates the value that gets sent back to the peer.<br>*For writes:* this function receives the written value as an argument. |
| flags       | Indicates which operations are permitted for this characteristic.  The NimBLE stack responds negatively when a peer attempts an unsupported operation. | The full list of flags can be found under `ble_gatt_chr_flags` in [net/nimble/host/include/host/ble_gatt.h](https://github.com/apache/mynewt-core/blob/master/net/nimble/host/include/host/ble_gatt.h).|

A characteristic's access callback implements its behavior.  Access
callbacks are described in detail in the next section:
[BLE Peripheral - Characteristic Access](bleprph-chr-access/).

The service definition array and each characteristic definition array is
terminated with an empty entry, represented with a 0.  The below code listing
shows the last service in the array, including terminating zeros for the
characteristic array and service array.

<br>

```c hl_lines="26 31"
    {
        /*** Service: Security test. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid128 = gatt_svr_svc_sec_test_uuid,
        .characteristics = (struct ble_gatt_chr_def[]) { {
            /*** Characteristic: Random number generator. */
            .uuid128 = gatt_svr_chr_sec_test_rand_uuid,
            .access_cb = gatt_svr_chr_access_sec_test,
            .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_READ_ENC,
        }, {
            /*** Characteristic: Static value. */
            .uuid128 = gatt_svr_chr_sec_test_static_uuid,
            .access_cb = gatt_svr_chr_access_sec_test,
            .flags = BLE_GATT_CHR_F_READ |
                     BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_WRITE_ENC,
        }, {
            0, /* No more characteristics in this service. */
        } },
    },

    {
        0, /* No more services. */
    },
```

<br>

#### Registration function

After you have created your service table, your app needs to register it with the NimBLE stack.  This is done by calling the [ble_gatts_add_svcs()](../../../network/ble/ble_hs/ble_gatts/functions/ble_gatts_add_svcs.md) function.  There is a small complication, though.  The NimBLE host needs to allocate sufficient resources upfront to accommodate all of your peripheral's services.  You can ensure your GATT services are accounted for in the host configuration object by calling the [ble_gatts_count_cfg()](../../../network/ble/ble_hs/ble_gatts/functions/ble_gatts_count_cfg.md) function.

The *bleprph* app registers its services in *gatt_svr.c* as follows:

```c
int
gatt_svr_init(struct ble_hs_cfg *cfg)
{
    int rc;

    rc = ble_gatts_count_cfg(gatt_svr_svcs, cfg);
    if (rc != 0) {
        return rc;
    }

    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    return 0;
}

```

You application will perform the above two-step process for each service definition array that you wish to register.  Libraries that implement GATT services will generally expose an initialization function which does this for you.

<br>

#### Descriptors and Included Services

Your peripheral can also expose descriptors and included services.  These are
less common, so they are not covered in this tutorial.  For more information,
see the [BLE User Guide](../../../network/ble/ble_intro/).
