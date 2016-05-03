## BLE Peripheral Project

### Connection callbacks

<br>

#### Overview


Every BLE connection has a *connection callback* associated with it.  A
connection callback is a bit of application code which NimBLE uses to inform
you of connection-related events.  For example, if a connection is terminated,
NimBLE lets you know about it with a call to that connection's callback.

In the [advertising section](bleprph-adv/) of this tutorial, we saw how the
application specifies a connection callback when it begins advertising.  NimBLE
uses this callback to notify the application that a central has connected to
your peripheral after receiving an advertisement.  Let's revisit how *bleprph* specifies its connection callback when advertising:

<br>

```c
    /* Begin advertising. */
    rc = ble_gap_adv_start(BLE_GAP_DISC_MODE_GEN, BLE_GAP_CONN_MODE_UND,
                           NULL, 0, NULL, bleprph_on_connect, NULL);
    if (rc != 0) {
        BLEPRPH_LOG(ERROR, "error enabling advertisement; rc=%d\n", rc);
        return;
    }
```

<br>

#### bleprph_on_connect()


The `bleprph_on_connect()` function is *bleprph*'s connection callback; NimBLE
calls this function when the advertising operation leads to connection
establishment.  Upon connecting, this callback becomes permanently associated
with the connection; all subsequent events related to this connection are
communicated through this callback.

Now let's look at the function that *bleprph* uses for all its connection
callbacks: `bleprph_on_connect()`.


```c
static int
bleprph_on_connect(int event, int status, struct ble_gap_conn_ctxt *ctxt,
                   void *arg)
{
    switch (event) {
    case BLE_GAP_EVENT_CONN:
        BLEPRPH_LOG(INFO, "connection %s; status=%d ",
                    status == 0 ? "up" : "down", status);
        bleprph_print_conn_desc(ctxt->desc);
        BLEPRPH_LOG(INFO, "\n");

        if (status != 0) {
            /* Connection terminated; resume advertising. */
            bleprph_advertise();
        }
        break;
    }

    return 0;
}
```

<br>

Connection callbacks are used to communicate a variety of events related to a
connection.  An application determines the type of event that occurred by
inspecting the value of the *event* parameter.  The full list of event codes
can be found in [net/nimble/host/include/host/ble_gatt.h](https://github.com/apache/incubator-mynewt-core/blob/master/net/nimble/host/include/host/ble_gatt.h).
*bleprph* only concerns itself with a single event type: *BLE_GAP_EVENT_CONN*.
This event indicates that a new connection has been established, or an existing
connection has been terminated; the *status* parameter clarifies which.  As you
can see, *bleprph* uses the *status* parameter to determine if it should resume
advertising.

The *ctxt* parameter contains additional information about the connection
event.  *bleprph* does nothing more than log some fields of this struct, but
some apps will likely want to perform further actions, e.g., perform service
discovery on the connected device.  The *struct ble_gap_conn_ctxt* type is
defined as follows:

```c
struct ble_gap_conn_ctxt {
    struct ble_gap_conn_desc *desc;

    union {
        struct {
            struct ble_gap_upd_params *self_params;
            struct ble_gap_upd_params *peer_params;
        } update;

        struct ble_gap_sec_params *sec_params;
    };
};
```

<br>

As shown, a connection context object consists of two parts:

* *desc:* The connection descriptor; indicates properties of the connection.
* *anonymous union:* The contents are event-specific; check the *event* code to determine which member field (if any) is relevant.

For events of type *BLE_GAP_EVENT_CONN*, the anonymous union is not used at all, so the only information carried by the context struct is the connection descriptor.  The *struct ble_gap_conn_desc* type is defined as follows:

```c
struct ble_gap_conn_desc {
    uint8_t peer_addr[6];
    uint16_t conn_handle;
    uint16_t conn_itvl;
    uint16_t conn_latency;
    uint16_t supervision_timeout;
    uint8_t peer_addr_type;
};
```

<br>

We will examine these fields in a slightly different order from how they appear
in the struct definition.

<br>

| *Field* | *Purpose* | *Notes* |
| ------- | --------- | ------- |
| peer\_addr | The 48-bit address of the peer device. | |
| peer\_addr\_type | Whether the peer is using a public or random address. | The address type list is documented in [net/nimble/include/nimble/hci_common.h](https://github.com/apache/incubator-mynewt-core/blob/master/net/nimble/include/nimble/hci_common.h). |
| conn\_handle | The 16-bit handle associated with this connection. | This number is how your app and the NimBLE stack refer to this connection. |
| conn\_itvl,<br>conn\_latency,<br>supervision\_timeout | Low-level properties of the connection. | |

<br>

#### Guarantees

It is important to know what your application code is allowed to do from within
a connection callback.

**No restrictions on NimBLE operations**

Your app is free to make calls into the NimBLE stack from within a connection
callback.  *bleprph* takes advantage of this freedom when it resumes
advertising upon connection termination.  All other NimBLE operations are also
allowed (service discovery, pairing initiation, etc).

**All context data is transient**

Pointers in the context object point to data living on the stack.  Your
callback is free to read (or write, if appropriate) through these pointers, but
you should not store these pointers for later use.  If your application needs
to retain some data from a context object, it needs to make a copy.
