## BLE Peripheral Project

### Characteristic Access

<br>

#### Review

A characteristic's access callback implements its behavior.  Recall that
services and characteristics are registered with NimBLE via attribute tables.
Each characteristic definition in an attribute table contains an *access_cb*
field.  The *access_cb* field is an application callback that gets executed
whenever a peer device attempts to read or write the characteristic.

Earlier in this tutorial, we looked at how *bleprph* implements the ANS
service.  Let's take another look at how *bleprph* specifies the first few
characteristics in this service.

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

As you can see, *bleprph* uses the same *access_cb* function for all the ANS
service characteristics, but the developer could have implemented separate
functions for each characteristic if they preferred.  Here is part of the
*access_cb* function that the ANS service characteristics use:

<br>

```c

static int
gatt_svr_chr_access_alert(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt,
                          void *arg)
{
    uint16_t uuid16;
    int rc;

    uuid16 = ble_uuid_128_to_16(ctxt->chr->uuid128);
    assert(uuid16 != 0);

    switch (uuid16) {
    case GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID:
        assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
        rc = os_mbuf_append(ctxt->om, &gatt_svr_new_alert_cat,
                            sizeof gatt_svr_new_alert_cat);
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;

    case GATT_SVR_CHR_UNR_ALERT_STAT_UUID:
        if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
            if (OS_MBUF_PKTLEN(ctxt->om) != sizeof gatt_svr_unr_alert_stat) {
                return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
            }

            rc = ble_hs_mbuf_to_flat(ctxt->om, &gatt_svr_unr_alert_stat,
                                     sizeof gatt_svr_unr_alert_stat, NULL);
            if (rc != 0) {
                return BLE_ATT_ERR_UNLIKELY;
            }

            return 0;

    /* [...] */

    default:
        assert(0);
        return BLE_ATT_ERR_UNLIKELY;
    }
}
```

After you've taken a moment to examine the structure of this function, let's explore some details.

<br>

#### Function signature

```c
static int
gatt_svr_chr_access_alert(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt,
                          void *arg)
```

A characteristic access function always takes this same set of parameters and
always returns an int.  The parameters to this function type are documented
below.

| **Parameter** | **Purpose** | **Notes** |
| ------------- | ----------- | --------- |
| conn_handle   | Indicates which connection the characteristic access was sent over. | Use this value to determine which peer is accessing the characteristic. |
| attr_handle   | The low-level ATT handle of the characteristic value attribute. | Can be used to determine which characteristic is being accessed if you don't want to perform a UUID lookup. |
| op            | Indicates whether this is a read or write operation | Valid values are:<br>*BLE_GATT_ACCESS_OP_READ_CHR*<br>*BLE_GATT_ACCESS_OP_WRITE_CHR* |
| ctxt          | Contains the characteristic value mbuf that the application needs to access. | For characteristic accesses, use the *ctxt->chr* member; for descriptor accesses, use the *ctxt->dsc* member. |

The return value of the access function tells the NimBLE stack how to respond
to the peer performing the operation.  A value of 0 indicates success.  For
failures, the function returns the specific [ATT error code](../../../network/ble/ble_hs/ble_hs_return_codes/#return-codes-att) that the NimBLE
stack should respond with.  *Note:* The return code is a formal code, **not** a NimBLE value!

<br>

#### Determine characteristic being accessed

```c
{
    uint16_t uuid16;

    uuid16 = ble_uuid_128_to_16(ctxt->chr->uuid128);
    assert(uuid16 != 0);

    switch (uuid16) {
        // [...]
```

This function uses the UUID to determine which characteristic is being
accessed.  There are two alternative methods *bleprph* could have used to
accomplish this task:

* Map characteristics to ATT handles during service registration; use the *attr_handle* parameter as a key into this table during characteristic access.
* Implement a dedicated function for each characteristic; each function inherently knows which characteristic it corresponds to.

All the ANS service characteristics have 16-bit UUIDs, so this function uses
the *ble_uuid_128_to_16()* function to convert the 128-bit UUID to its
corresponding 16-bit UUID.  This conversion function returns the corresponding
16-bit UUID on success, or 0 on failure.  Success is asserted here to ensure
the NimBLE stack is doing its job properly; the stack should only call this
function for accesses to characteristics that it is registered with, and all
ANS service characteristics have valid 16-bit UUIDs.

<br>

#### Read access

```c
    case GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID:
        assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
        rc = os_mbuf_append(ctxt->om, &gatt_svr_new_alert_cat,
                            sizeof gatt_svr_new_alert_cat);
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
```

This code excerpt handles read accesses to the Supported New Alert Category
characteristic.  The *assert()* here is another case of making sure the NimBLE
stack is doing its job; this characteristic was registered as read-only, so the
stack should have prevented write accesses.

To fulfill a characteristic read request, the application needs fill a buffer (*om*) with the characteristic value.  The NimBLE host will then include the contents of this buffer in its read response.  NimBLE uses [mbufs](../../../os/core_os/mbuf/mbuf) to exchange data between itself and the application.  To fill an mbuf with data that is available in a contiguous chunk of memory, the *os_mbuf_append()* function suffices.  The source of the data, *gatt_svr_new_alert_cat*, is is stored in read-only memory as follows:

<br>

```c
static const uint8_t gatt_svr_new_alert_cat = 0x01; /* Simple alert. */
```

It is not shown in the above snippet, but this function ultimately returns 0.
By returning 0, *bleprph* indicates that the characteristic data in
*ctxt->om* is valid and that NimBLE should include it in its response
to the peer.

<br>

#### Write access

```c
static uint16_t gatt_svr_unr_alert_stat;
```

```c
    case GATT_SVR_CHR_UNR_ALERT_STAT_UUID:
        if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
            if (OS_MBUF_PKTLEN(ctxt->om) != sizeof gatt_svr_unr_alert_stat) {
                return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
            }

            rc = ble_hs_mbuf_to_flat(ctxt->om, &gatt_svr_unr_alert_stat,
                                     sizeof gatt_svr_unr_alert_stat, NULL);
            if (rc != 0) {
                return BLE_ATT_ERR_UNLIKELY;
            }

            return 0;
        } else /* [...] */
```

This code excerpt handles writes to the New Alert characteristic.  For writes,
the role of the *ctxt->om* field is the reverse of the read case.  The NimBLE
stack uses these fields to indicate the data written by the peer.

Many characteristics have strict length requirements for write operations.
This characteristic has such a restriction; if the written data is not a 2-byte
value, the application tells NimBLE to respond with an invalid attribute value
length error.

*bleprph* copies the data out of the supplied mbuf and writes it to a contiguous chunk of storage (the *gatt_svr_unr_alert_stat* variable).  This is accomplished with the [ble_hs_mbuf_to_flat()](../../../network/ble/ble_hs/other/functions/ble_hs_mbuf_to_flat) function.  If the application did not have a suitable destination for the data handy, it could have inherited the mbuf from the context object.  This is done by saving a copy of the mbuf pointer, and assigning *NULL* to *ctxt->om*.  By assigning *NULL* to the mbuf pointer, your application prevents the stack from freeing the mbuf while it is still being used.  Be aware, however, that it is the application's responsibility to free inherited mbufs.
