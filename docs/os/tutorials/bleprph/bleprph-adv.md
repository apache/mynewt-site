## BLE Peripheral Project

### Advertising

<br>

#### Overview


A peripheral announces its presence to the world by broadcasting
advertisements.  An advertisement typically contains additional information
about the peripheral sending it, such as the device name and an abbreviated
list of supported services.  The presence of this information helps a listening
central to determine whether it is interested in connecting to the peripheral.
Advertisements are quite limited in the amount of information they can contain,
so only the most important information should be included.

When a listening device receives an advertisement, it can choose to connect to
the peripheral, or query the sender for more information.  This second action
is known as an *active scan*.  A peripheral responds to an active scan with
some extra information that it couldn't fit in its advertisement.  This
additional information is known as *scan response data*.  *bleprph* does not
configure any scan response data, so this feature is not discussed in the
remainder of this tutorial.

*bleprph* constantly broadcasts advertisements until a central connects to it.
When a connection is terminated, *bleprph* resumes advertising.

Let's take a look at *bleprph*'s advertisement code (*main.c*):

<br>

```c
/**
 * Enables advertising with the following parameters:
 *     o General discoverable mode.
 *     o Undirected connectable mode.
 */
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

    /* Indicate that the flags field should be included; specify a value of 0
     * to instruct the stack to fill the value in for us.
     */
    fields.flags_is_present = 1;
    fields.flags = 0;

    /* Indicate that the TX power level field should be included; have the
     * stack fill this one automatically as well.  This is done by assiging the
     * special value BLE_HS_ADV_TX_PWR_LVL_AUTO.
     */
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

    name = ble_svc_gap_device_name();
    fields.name = (uint8_t *)name;
    fields.name_len = strlen(name);
    fields.name_is_complete = 1;

    fields.uuids16 = (uint16_t[]){ GATT_SVR_SVC_ALERT_UUID };
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
    rc = ble_gap_adv_start(BLE_ADDR_TYPE_PUBLIC, 0, NULL, BLE_HS_FOREVER,
                           &adv_params, bleprph_gap_event, NULL);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
}
```

Now let's examine this code in detail.

<br>

#### Setting advertisement data


A NimBLE peripheral specifies what information to include in its advertisements with the [ble_gap_adv_set_fields()](../../../network/ble/ble_hs/ble_gap/functions/ble_gap_adv_set_fields.md) function.

The *fields* argument specifies the fields and their contents to include in
subsequent advertisements.  The Bluetooth [Core Specification
Supplement](https://www.bluetooth.org/DocMan/handlers/DownloadDoc.ashx?doc_id=302735)
defines a set of standard fields that can be included in an advertisement; the
member variables of the *struct ble_hs_adv_fields* type correspond to these
standard fields.  Information that doesn't fit neatly into a standard field
should be put in the *manufacturing specific data* field.

As you can see in the above code listing, the `struct ble_hs_adv_fields`
instance is allocated on the stack.  It is OK to use the stack for this struct
and the data it references, as the `ble_gap_adv_set_fields()`
function makes a copy of all the advertisement data before it returns.
*bleprph* doesn't take full advantange of this; it stores its device name in a
static array.

The code sets several members of the *struct ble_hs_adv_fields* instance.  Most
of them are quite straight-forward.  However, the *name\_is\_complete* field
requires some explanation.  Bluetooth specifies two name-related advertisement
fields: *Shortened Local Name* and *Complete Local Name*.  Setting the
`name_is_complete` variable to 1 or 0 tells NimBLE which of these two fields to
include in advertisements.  Some other advertisement fields also correspond to
multiple variables in the field struct, so it is a good idea to review the
*ble\_hs\_adv\_fields* reference to make sure you get the details right in your
app.

<br>

#### Begin advertising


An app starts advertising with
[ble_gap_adv_start()](../../../network/ble/ble_hs/ble_gap/functions/ble_gap_adv_start.md)
function.  This function allows a lot of flexibility, and it might seem
daunting at first glance.  *bleprph* specifies a simple set of arguments that
is appropriate for most peripherals.  When getting started on a typical
peripheral, we recommend you use the same arguments as *bleprph*, with the
exception of the last two (*cb* and *cb_arg*; *bleprph_gap_event* and *NULL* in
this case).  These last two arguments will be specific to your app, so let's
talk about them.

*cb* is a callback function.  It gets executed when a central connects to your
peripheral after receiving an advertisement.  The *cb_arg* argument gets passed
to the *cb* callback.  If your callback doesn't need the *cb_arg* parameter,
you can do what *bleprph* does and pass *NULL*.  Once a connection is
established, the *cb* callback becomes permanently associated with the
connection.  All subsequent events related to the connection are communicated
to your app via calls to this callback function.  GAP event callbacks are an
important part of building a BLE app, and we examine *bleprph*'s connection
callback in detail in the next section of this tutorial.

<br>

**One final note:** Your peripheral automatically stops advertising when a
central connects to it.  You can immediately resume advertising if you want to
allow another central to connect, but you will need to do so explicitly by
calling `ble_gap_adv_start()` again.  Also, be aware NimBLE's default
configuration only allows a single connection at a time.  NimBLE supports
multiple concurrent connections, but you must configure it to do so first.
