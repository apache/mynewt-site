## BLE Peripheral Project

### Service Registration

<br>

#### Attribute Set

The NimBLE host uses a table-based design for GATT server configuration.  The
set of supported attributes are expressed as a series of tables that resides in
your C code.  When possible, we recommend using a single monolithic table, as
it results in code that is simpler and less error prone.  Multiple tables
can be used if it is impractical for the entire attribute set to live in one
place in your code.

*bleprph* uses a single attribute table located in the *gatt_svr.c* file,
so let's take a look at that now.  The attribute table is called
`gatt_svr_svcs`; here are the first several lines from this table:

<br>

```c
static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        /*** Service: Security test. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = &gatt_svr_svc_sec_test_uuid.u,
        .characteristics = (struct ble_gatt_chr_def[]) { {
            /*** Characteristic: Random number generator. */
            .uuid = &gatt_svr_chr_sec_test_rand_uuid.u,
            .access_cb = gatt_svr_chr_access_sec_test,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            /*** Characteristic: Static value. */
            .uuid = &gatt_svr_chr_sec_test_static_uuid.u,
            .access_cb = gatt_svr_chr_access_sec_test,
            .flags = BLE_GATT_CHR_F_READ,
    // [...]
```

<br>

As you can see, the table is an array of service definitions (
`struct ble_gatt_svc_def`). Let's now consider the contents of this table in more
detail.

A service definition consists of the following fields:

| *Field* | *Meaning* | *Notes* |
| ------- | --------- | ------- |
| type        | Specifies whether this is a primary or secondary service. | Secondary services are not very common.  When in doubt, specify *BLE_GATT_SVC_TYPE_PRIMARY* for new services. |
| uuid     | The UUID of this characteristic. | This field accepts a pointer to a variable of type `ble_uuid_t`. You could directly use the `BLE_UUID16_DECLARE()` macro or to pass a pointer to a `ble_uuid16_t` variable you could type `&uuid_variable.u` |
| characteristics | The array of characteristics that belong to this service.   | |

<br>

A service is little more than a container of characteristics; the
characteristics themselves are where the real action happens. A characteristic
definition consists of the following fields:

| *Field* | *Meaning* | *Notes* |
| ------- | --------- | ------- |
| uuid     | The UUID of this characteristic. | This field accepts a pointer to a variable of type `ble_uuid_t`. You could directly use the `BLE_UUID16_DECLARE()` macro or to pass a pointer to a `ble_uuid16_t` variable you could type `&uuid_variable.u` |
| access\_cb  | A callback function that gets executed whenever a peer device accesses this characteristic. | *For reads:* this function generates the value that gets sent back to the peer.<br>*For writes:* this function receives the written value as an argument. |
| flags       | Indicates which operations are permitted for this characteristic.  The NimBLE stack responds negatively when a peer attempts an unsupported operation. | The full list of flags can be found under `ble_gatt_chr_flags` in [net/nimble/host/include/host/ble_gatt.h](https://github.com/apache/mynewt-core/blob/master/net/nimble/host/include/host/ble_gatt.h).|

The access callback is what implements the characteristic's behavior. Access
callbacks are described in detail in the next section:
[BLE Peripheral - Characteristic Access](bleprph-chr-access/).

The service definition array and each characteristic definition array is
terminated with an empty entry, represented with a 0. The below code listing
shows the last service in the array, including terminating zeros for the
characteristic array and service array.

<br>

```c hl_lines="16 21"
    {
        /*** Service: Security test. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = &gatt_svr_svc_sec_test_uuid.u,
        .characteristics = (struct ble_gatt_chr_def[]) { {
            /*** Characteristic: Random number generator. */
            .uuid = &gatt_svr_chr_sec_test_rand_uuid.u,
            .access_cb = gatt_svr_chr_access_sec_test,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            /*** Characteristic: Static value. */
            .uuid = &gatt_svr_chr_sec_test_static_uuid.u,
            .access_cb = gatt_svr_chr_access_sec_test,
            .flags = BLE_GATT_CHR_F_READ,
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

After you have created your service table, your app needs to register it with the NimBLE stack.  This is done by calling the following function:

```c
int
ble_gatts_add_svcs(const struct ble_gatt_svc_def *svcs)
```

The function parameters are documented below.

| *Parameter* | *Meaning* | *Notes* |
| ----------- | --------- | ------- |
| svcs        | An array of service definitions to queue for registration. This array must be terminated with an entry whose 'type' equals 0. | |

The `ble_gatts_register_svcs()` function returns 0 on success, or a
*BLE_HS_E[...]* error code on failure.

The *bleprph* app registers its services as follows:

```c
    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }
```

More detailed information about the registration function can be found
in the BLE User Guide: [ble_gatts_add_svcs](../../../network/ble/ble_hs/ble_gatts/functions/ble_gatts_add_svcs/).

<br>

#### Registration callback function

It is possible to set a callback function that gets executed each time a service, characteristic, or descriptor is registered. This is done by setting the following attribute:

```c
ble_hs_cfg.gatts_register_cb = gatt_svr_register_cb;
```
In the above example `gatt_svr_register_cb` is the function that will be called. This line can be found in *bleprph*'s `main.c` file

More detailed information about the registration callback function can be found
in the [BLE User Guide](../../../network/ble/ble_intro/) (TBD).

<br>

#### Descriptors and Included Services

Your peripheral can also expose descriptors and included services.  These are
less common, so they are not covered in this tutorial.  For more information,
see the [BLE User Guide](../../../network/ble/ble_intro/).
