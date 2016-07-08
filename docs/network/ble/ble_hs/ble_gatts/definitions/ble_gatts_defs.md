## <font color="#F2853F" style="font-size:24pt">GATT Client Definitions/font>

```c
typedef int ble_gatt_access_fn(uint16_t conn_handle, uint16_t attr_handle,
                               uint8_t op, struct ble_gatt_access_ctxt *ctxt,
                               void *arg);
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
struct ble_gatt_access_ctxt {
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

    struct ble_att_svr_access_ctxt *att;
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
