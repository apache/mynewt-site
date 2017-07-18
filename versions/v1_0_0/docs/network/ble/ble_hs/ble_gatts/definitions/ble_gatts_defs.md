## <font color="#F2853F" style="font-size:24pt">GATT Server Definitions</font>

```c
typedef int ble_gatt_access_fn(uint16_t conn_handle, uint16_t attr_handle,
                               struct ble_gatt_access_ctxt *ctxt, void *arg);
```

```c
typedef uint16_t ble_gatt_chr_flags;
```

```c
struct ble_gatt_chr_def {
    /**
     * Pointer to first element in a uint8_t[16]; use the BLE_UUID16 macro for
     * 16-bit UUIDs; NULL if there are no more characteristics in the service.
     */
    const uint8_t *uuid128;

    /**
     * Callback that gets executed when this characteristic is read or
     * written.
     */
    ble_gatt_access_fn *access_cb;

    /** Optional argument for callback. */
    void *arg;

    /**
     * Array of this characteristic's descriptors.  NULL if no descriptors.
     * Do not include CCCD; it gets added automatically if this
     * characteristic's notify or indicate flag is set.
     */
    struct ble_gatt_dsc_def *descriptors;

    /** Specifies the set of permitted operations for this characteristic. */
    ble_gatt_chr_flags flags;

    /** 
     * At registration time, this is filled in with the characteristic's value
     * attribute handle.
     */
    uint16_t * const val_handle;
};
```

```c
struct ble_gatt_svc_def {
    /**
     * One of the following:
     *     o BLE_GATT_SVC_TYPE_PRIMARY - primary service
     *     o BLE_GATT_SVC_TYPE_SECONDARY - secondary service
     *     o 0 - No more services in this array.
     */
    uint8_t type;

    /**
     * Pointer to first element in a uint8_t[16]; use the BLE_UUID16 macro for
     * 16-bit UUIDs.
     */
    const uint8_t *uuid128;

    /**
     * Array of pointers to other service definitions.  These services are
     * reported as "included services" during service discovery.  Terminate the
     * array with NULL.
     */
    const struct ble_gatt_svc_def **includes;

    /**
     * Array of characteristic definitions corresponding to characteristics
     * belonging to this service.
     */
    const struct ble_gatt_chr_def *characteristics;
};
```

```c
struct ble_gatt_dsc_def {
    /**
     * The first element in a uint8_t[16]; use the BLE_UUID16 macro for 16-bit
     * UUIDs; NULL if there are no more descriptors in the characteristic.
     */
    uint8_t *uuid128;

    /** Specifies the set of permitted operations for this descriptor. */
    uint8_t att_flags;

    /** Callback that gets executed when the descriptor is read or written. */
    ble_gatt_access_fn *access_cb;

    /** Optional argument for callback. */
    void *arg;
};
```

```c
/**
 * Context for an access to a GATT characteristic or descriptor.  When a client
 * reads or writes a locally registered characteristic or descriptor, an
 * instance of this struct gets passed to the application callback.
 */
struct ble_gatt_access_ctxt {
    /**
     * Indicates the gatt operation being performed.  This is equal to one of
     * the following values:
     *     o  BLE_GATT_ACCESS_OP_READ_CHR
     *     o  BLE_GATT_ACCESS_OP_WRITE_CHR
     *     o  BLE_GATT_ACCESS_OP_READ_DSC
     *     o  BLE_GATT_ACCESS_OP_WRITE_DSC
     */
    uint8_t op;

    /**
     * A container for the GATT access data.
     *     o For reads: The application populates this with the value of the
     *       characteristic or descriptor being read.
     *     o For writes: This is already populated with the value being written
     *       by the peer.  If the application wishes to retain this mbuf for
     *       later use, the access callback must set this pointer to NULL to
     *       prevent the stack from freeing it.
     */
    struct os_mbuf *om;

    /**
     * The GATT operation being performed dictates which field in this union is
     * valid.  If a characteristic is being accessed, the chr field is valid.
     * Otherwise a descriptor is being accessed, in which case the dsc field
     * is valid.
     */
    union {
        /**
         * The characteristic definition corresponding to the characteristic
         * being accessed.  This is what the app registered at startup.
         */
        const struct ble_gatt_chr_def *chr;

        /**
         * The descriptor definition corresponding to the descriptor being
         * accessed.  This is what the app registered at startup.
         */
        const struct ble_gatt_dsc_def *dsc;
    };
};
```

```c
/**
 * Context passed to the registration callback; represents the GATT service,
 * characteristic, or descriptor being registered.
 */
union ble_gatt_register_ctxt {
    /** Service; valid if op == BLE_GATT_REGISTER_OP_SVC. */
    struct {
        /** The ATT handle of the service definition attribute. */
        uint16_t handle;

        /**
         * The service definition representing the service being
         * registered.
         */
        const struct ble_gatt_svc_def *svc_def;
    } svc;

    /** Characteristic; valid if op == BLE_GATT_REGISTER_OP_CHR. */
    struct {
        /** The ATT handle of the characteristic definition attribute. */
        uint16_t def_handle;

        /** The ATT handle of the characteristic value attribute. */
        uint16_t val_handle;

        /**
         * The characteristic definition representing the characteristic being
         * registered.
         */
        const struct ble_gatt_chr_def *chr_def;

        /**
         * The service definition corresponding to the characteristic's parent
         * service.
         */
        const struct ble_gatt_svc_def *svc_def;
    } chr;

    /** Descriptor; valid if op == BLE_GATT_REGISTER_OP_DSC. */
    struct {
        /** The ATT handle of the descriptor definition attribute. */
        uint16_t handle;

        /**
         * The descriptor definition corresponding to the descriptor being
         * registered.
         */
        const struct ble_gatt_dsc_def *dsc_def;

        /**
         * The characteristic definition corresponding to the descriptor's
         * parent characteristic.
         */
        const struct ble_gatt_chr_def *chr_def;

        /**
         * The service definition corresponding to the descriptor's grandparent
         * service
         */
        const struct ble_gatt_svc_def *svc_def;
    } dsc;
};
```

```c
typedef void ble_gatt_register_fn(uint8_t op,
                                  union ble_gatt_register_ctxt *ctxt,
                                  void *arg);
```

```c
/**
 * Contains counts of resources required by the GATT server.  The contents of
 * this struct are generally used to populate a configuration struct before
 * the host is initialized.
 */
struct ble_gatt_resources {
    /** Number of services. */
    uint16_t svcs;

    /** Number of included services. */
    uint16_t incs;

    /** Number of characteristics. */
    uint16_t chrs;

    /** Number of descriptors. */
    uint16_t dscs;

    /**
     * Number of client characteristic configuration descriptors.  Each of
     * these also contributes to the total descriptor count.
     */
    uint16_t cccds;

    /** Total number of ATT attributes. */
    uint16_t attrs;
};
```
