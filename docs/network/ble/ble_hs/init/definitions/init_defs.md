## <font color="#F2853F" style="font-size:24pt">Other definitions</font>

```c
/* Defines the IO capabilities for the local device. */
#define BLE_HS_IO_DISPLAY_ONLY              0x00
#define BLE_HS_IO_DISPLAY_YESNO             0x01
#define BLE_HS_IO_KEYBOARD_ONLY             0x02
#define BLE_HS_IO_NO_INPUT_OUTPUT           0x03
#define BLE_HS_IO_KEYBOARD_DISPLAY          0x04
```

```c
struct ble_hs_cfg {
    /*** HCI settings. */
    /**
     * An HCI buffer is a "flat" 260-byte buffer.  HCI buffers are used by the
     * controller to send unsolicited events to the host.
     *
     * HCI buffers can get tied up when the controller sends lots of
     * asynchronous / unsolicited events (i.e., non-acks).  When the controller
     * needs to send one of these events, it allocates an HCI buffer, fills it
     * with the event payload, and puts it on a host queue.  If the controller
     * sends a quick burst of these events, the buffer pool may be exhausted,
     * preventing the host from sending an HCI command to the controller.
     *
     * Every time the controller sends a non-ack HCI event to the host, it also
     * allocates an OS event (it is unfortunate that these are both called
     * "events").  The OS event is put on the host-parent-task's event queue;
     * it is what wakes up the host-parent-task and indicates that an HCI event
     * needs to be processsed.  The pool of OS events is allocated with the
     * same number of elements as the HCI buffer pool.
     */
    uint8_t max_hci_bufs;

    /*** Connection settings. */
    /**
     * The maximum number of concurrent connections.  This is set
     * automatically according to the build-time option
     * NIMBLE_OPT_MAX_CONNECTIONS.
     */
    uint8_t max_connections;

    /*** GATT server settings. */
    /**
     * These are acquired at service registration time and never freed.  You
     * need one of these for every service that you register.
     */
    uint16_t max_services;

    /**
     * The total number of in-RAM client characteristic configuration
     * descriptors (CCCDs).  One of these is consumed each time a peer
     * subscribes to notifications or indications for a characteristic that
     * your device serves.  In addition, at service registration time, the host
     * uses one of these for each characteristic that supports notifications or
     * indications.  So, the formula which guarantees no resource exhaustion
     * is:
     *     (num-subscribable-characteristics) * (max-connections + 1)
     */
    uint16_t max_client_configs;

    /*** GATT client settings. */
    /**
     * The maximum number of concurrent GATT client procedures.  When you
     * initiate a GATT procedure (e.g., read a characteristic, discover
     * services, etc.), one of these is consumed.  The resource is freed when
     * the procedure completes.
     */
    uint8_t max_gattc_procs;

    /*** ATT server settings. */
    /**
     * The total number of local ATT attributes.  Attributes are consumed at
     * service registration time and are never freed.  Attributes are used by
     * GATT server entities: services, characteristics, and descriptors
     * according to the following formula:
     *     (num-services + (num-characteristics * 2) + num-descriptors)
     *
     * Every characteristic that supports indications or notifications
     * automatically gets a descriptor.  All other descriptors are specified by
     * the application at service registration time.
     */
    uint16_t max_attrs;

    /**
     * A GATT server uses these when a peer performs a "write long
     * characteristic values" or "write long characteristic descriptors"
     * procedure.  One of these resources is consumed each time a peer sends a
     * partial write.  These procedures are not used often.
     */
    uint8_t max_prep_entries;

    /*** L2CAP settings. */
    /**
     * Each connection requires three L2CAP channels (signal, ATT, and security
     * manager).  In addition, the nimble host may allow channels to be created
     * "on the fly" (connection-oriented channels).  This functionality is not
     * available at the moment, so a safe formula to use is:
     *     (max-connections * 3)
     */
    uint8_t max_l2cap_chans;

    /**
     * The maximum number of concurrent L2CAP signalling procedures.  Only one
     * L2CAP signalling procedure is supported: slave-initiated connection
     * update.  You will never need more of these than the max number of
     * connections.
     */
    uint8_t max_l2cap_sig_procs;

    /**
     * The maximum number of concurrent security manager procedures.  Security
     * manager procedures include pairing and restoration of a bonded link.
     */
    uint8_t max_l2cap_sm_procs;

    /*** Security manager settings. */
    uint8_t sm_io_cap;
    unsigned sm_oob_data_flag:1;
    unsigned sm_bonding:1;
    unsigned sm_mitm:1;
    unsigned sm_sc:1;
    unsigned sm_keypress:1;
    uint8_t sm_our_key_dist;
    uint8_t sm_their_key_dist;

    /*** Store settings. */
    /**
     * These function callbacks handle persistence of sercurity material
     * (bonding).
     */
    ble_store_read_fn *store_read_cb;
    ble_store_write_fn *store_write_cb;
    ble_store_delete_fn *store_delete_cb;

    /*** privacy settings */
    /**
     * The frequency at which new resovlable private addresses are generated.
     * Units are seconds.
     */
    uint16_t rpa_timeout;
};
```

```c
extern const struct ble_hs_cfg ble_hs_cfg_dflt;
```
