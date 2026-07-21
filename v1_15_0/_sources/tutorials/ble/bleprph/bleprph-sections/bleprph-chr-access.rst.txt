Characteristic Access
=====================

.. contents::
  :local:
  :depth: 2

Review
^^^^^^

A characteristic's access callback implements its behavior. Recall that
services and characteristics are registered with NimBLE via attribute
tables. Each characteristic definition in an attribute table contains an
*access_cb* field. The *access_cb* field is an application callback
that gets executed whenever a peer device attempts to read or write the
characteristic.

Earlier in this tutorial, we looked at how *bleprph* implements the GAP
service. Let's take another look at how *bleprph* specifies the first
few characteristics in this service.

.. code:: c

    static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
        {
            /*** Service: Security test. */
            .type               = BLE_GATT_SVC_TYPE_PRIMARY,
            .uuid               = &gatt_svr_svc_sec_test_uuid.u,
            .characteristics    = (struct ble_gatt_chr_def[]) { {
                /*** Characteristic: Random number generator. */
                .uuid               = &gatt_svr_chr_sec_test_rand_uuid.u,
                .access_cb          = gatt_svr_chr_access_sec_test,
                .flags              = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_READ_ENC,
            }, {
                /*** Characteristic: Static value. */
                .uuid               = gatt_svr_chr_sec_test_static_uuid.u,
                .access_cb          = gatt_svr_chr_access_sec_test,
                .flags              = BLE_GATT_CHR_F_READ |
                                      BLE_GATT_CHR_F_WRITE | BLE_GATT_CHR_F_WRITE_ENC,
            }, {
        // [...]

As you can see, *bleprph* uses the same *access_cb* function for all
the GAP service characteristics, but the developer could have
implemented separate functions for each characteristic if they
preferred. Here is the *access_cb* function that the GAP service
characteristics use:

.. code:: c

    static int
    gatt_svr_chr_access_sec_test(uint16_t conn_handle, uint16_t attr_handle,
                                 struct ble_gatt_access_ctxt *ctxt,
                                 void *arg)
    {
        const ble_uuid_t *uuid;
        int rand_num;
        int rc;

        uuid = ctxt->chr->uuid;

        /* Determine which characteristic is being accessed by examining its
         * 128-bit UUID.
         */

        if (ble_uuid_cmp(uuid, &gatt_svr_chr_sec_test_rand_uuid.u) == 0) {
            assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);

            /* Respond with a 32-bit random number. */
            rand_num = rand();
            rc = os_mbuf_append(ctxt->om, &rand_num, sizeof rand_num);
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }

        if (ble_uuid_cmp(uuid, &gatt_svr_chr_sec_test_static_uuid.u) == 0) {
            switch (ctxt->op) {
            case BLE_GATT_ACCESS_OP_READ_CHR:
                rc = os_mbuf_append(ctxt->om, &gatt_svr_sec_test_static_val,
                                    sizeof gatt_svr_sec_test_static_val);
                return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;

            case BLE_GATT_ACCESS_OP_WRITE_CHR:
                rc = gatt_svr_chr_write(ctxt->om,
                                        sizeof gatt_svr_sec_test_static_val,
                                        sizeof gatt_svr_sec_test_static_val,
                                        &gatt_svr_sec_test_static_val, NULL);
                return rc;

            default:
                assert(0);
                return BLE_ATT_ERR_UNLIKELY;
            }
        }

        /* Unknown characteristic; the nimble stack should not have called this
        * function.
        */
        assert(0);
        return BLE_ATT_ERR_UNLIKELY;
    }

After you've taken a moment to examine the structure of this function,
let's explore some details.

Function signature
^^^^^^^^^^^^^^^^^^

.. code:: c

    static int
    gatt_svr_chr_access_sec_test(uint16_t conn_handle, uint16_t attr_handle,
                                 struct ble_gatt_access_ctxt *ctxt, void *arg)

A characteristic access function always takes this same set of
parameters and always returns an int. The parameters to this function
type are documented below.

+----------------+--------------+------------+
| **Parameter**  | **Purpose**  | **Notes**  |
+================+==============+============+
| conn\_handle   | Indicates    | Use this   |
|                | which        | value to   |
|                | connection   | determine  |
|                | the          | which peer |
|                | characterist | is         |
|                | ic           | accessing  |
|                | access was   | the        |
|                | sent over.   | characteri |
|                |              | stic.      |
+----------------+--------------+------------+
| attr\_handle   | The          | Can be     |
|                | low-level    | used to    |
|                | ATT handle   | determine  |
|                | of the       | which      |
|                | characterist | characteri |
|                | ic           | stic       |
|                | value        | is being   |
|                | attribute.   | accessed   |
|                |              | if you     |
|                |              | don't want |
|                |              | to perform |
|                |              | a UUID     |
|                |              | lookup.    |
+----------------+--------------+------------+
| ctxt           | Contains the | For        |
|                | characterist | characteri |
|                | ic           | stic       |
|                | value        | accesses,  |
|                | pointer that | use the    |
|                | the          | *ctxt->chr |
|                | application  | \_access*  |
|                | needs to     | member;    |
|                | access.      | for        |
|                |              | descriptor |
|                |              | accesses,  |
|                |              | use the    |
|                |              | *ctxt->dsc |
|                |              | \_access*  |
|                |              | member.    |
+----------------+--------------+------------+

The return value of the access function tells the NimBLE stack how to
respond to the peer performing the operation. A value of 0 indicates
success. For failures, the function returns the specific ATT error code
that the NimBLE stack should respond with. The ATT error codes are
defined in
`net/nimble/host/include/host/ble\_att.h <https://github.com/apache/incubator-mynewt-core/blob/master/net/nimble/host/include/host/ble_att.h>`__.

Determine characteristic being accessed
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code:: c

    ble_uuid_cmp(uuid, &gatt_svr_chr_sec_test_rand_uuid.u)

The function compares UUID with UUIDs of characteristic - if it fits,
characteristic is being accessed. There are two alternative methods *bleprph*
could have used to accomplish this task:

-  Map characteristics to ATT handles during service registration; use
   the *attr\_handle* parameter as a key into this table during
   characteristic access.
-  Implement a dedicated function for each characteristic; each function
   inherently knows which characteristic it corresponds to.

Read access
^^^^^^^^^^^

.. code:: c

        case BLE_GATT_ACCESS_OP_READ_CHR:
            rc = os_mbuf_append(ctxt->om, &gatt_svr_sec_test_static_val,
                                sizeof gatt_svr_sec_test_static_val);
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;


This code excerpt handles read accesses to the device characteristic.
*ctxt->om* is chained memory buffer that for reads is being populated
with characteristic data. Returned value is either 0 for success or
*BLE_ATT_ERR_INSUFFICIENT_RES* if failed. The check makes sure the
NimBLE stack is doing its job; this characteristic was registered as
read-only, so the stack should have prevented write accesses.

Write access
^^^^^^^^^^^^

.. code:: c
    
    static int
    gatt_svr_chr_write(struct os_mbuf *om, uint16_t min_len, uint16_t max_len,
                       void *dst, uint16_t *len)
    {
        uint16_t om_len;
        int rc;

        om_len = OS_MBUF_PKTLEN(om);
        if (om_len < min_len || om_len > max_len) {
            return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
        }

        rc = ble_hs_mbuf_to_flat(om, dst, max_len, len);
        if (rc != 0) {
            return BLE_ATT_ERR_UNLIKELY;
        }

        return 0;
    }
    // [...]
    case BLE_GATT_ACCESS_OP_WRITE_CHR:
        rc = gatt_svr_chr_write(ctxt->om,
                                sizeof gatt_svr_sec_test_static_val,
                                sizeof gatt_svr_sec_test_static_val,
                                &gatt_svr_sec_test_static_val, NULL);
        return rc;

This code excerpt handles writes to the Static value
characteristic. This characteristic was registered as read-write, so the
*return rc* here is just a safety precaution to ensure the NimBLE stack
is doing its job.

Data is written to the *ctxt->om* buffer from *gatt_svr_sec_test_static_val*
by ``ble_hs_mbuf_to_flat()`` function. If length of written data greater or 
smaller than length of *gatt_svr_sec_test_static_val*, function return error.

Many characteristics have strict length requirements for write
operations.