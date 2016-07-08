## <font color="#F2853F" style="font-size:24pt">GAP events</font>

```c
typedef int ble_gap_event_fn(struct ble_gap_event *ctxt, void *arg);
```

```c
#define BLE_GAP_EVENT_CONNECT               0
#define BLE_GAP_EVENT_DISCONNECT            1
#define BLE_GAP_EVENT_CONN_CANCEL           2
#define BLE_GAP_EVENT_CONN_UPDATE           3
#define BLE_GAP_EVENT_CONN_UPDATE_REQ       4
#define BLE_GAP_EVENT_L2CAP_UPDATE_REQ      5
#define BLE_GAP_EVENT_TERM_FAILURE          6
#define BLE_GAP_EVENT_DISC                  7
#define BLE_GAP_EVENT_DISC_COMPLETE         8
#define BLE_GAP_EVENT_ADV_COMPLETE          9
#define BLE_GAP_EVENT_ENC_CHANGE            10
#define BLE_GAP_EVENT_PASSKEY_ACTION        11
#define BLE_GAP_EVENT_NOTIFY                12
```

```c

/**
 * Represents a GAP-related event.  When such an event occurs, the host
 * notifies the application by passing an instance of this structure to an
 * application-specified callback.
 */
struct ble_gap_event {
    /**
     * Indicates the type of GAP event that occurred.  This is one of the
     * BLE_GAP_EVENT codes.
     */
    uint8_t type;

    /**
     * A discriminated union containing additional details concerning the GAP
     * event.  The 'type' field indicates which member of the union is valid.
     */
    union {
        /**
         * Represents a connection attempt.  Valid for the following event
         * types:
         *     o BLE_GAP_EVENT_CONNECT
         */
        struct {
            /**
             * The status of the connection attempt;
             *     o 0: the connection was successfully established.
             *     o BLE host error code: the connection attempt failed for
             *       the specified reason.
             */
            int status;

            /**
             * Information about the established connection.  Only valid on
             * success.
             */
            struct ble_gap_conn_desc conn;
        } connect;

        /**
         * Represents a terminated connection.  Valid for the following event
         * types:
         *     o BLE_GAP_EVENT_DISCONNECT
         */
        struct {
            /**
             * A BLE host return code indicating the reason for the
             * disconnect.
             */
            int reason;

            /** Information about the terminated connection. */
            struct ble_gap_conn_desc conn;
        } disconnect;

        /**
         * Represents an advertising report received during a discovery
         * procedure.  Valid for the following event types:
         *     o BLE_GAP_EVENT_DISC
         */
        struct ble_gap_disc_desc disc;

        /**
         * Represents an attempt to update a connection's parameters.  Valid
         * for the following event types:
         *     o BLE_GAP_EVENT_CONN_UPDATE
         */
        struct {
            /**
             * The result of the connection update attempt;
             *     o 0: the connection was successfully updated.
             *     o BLE host error code: the connection update attempt failed
             *       for the specified reason.
             */
            int status;

            /**
             * Information about the relevant connection.  If the connection
             * update attempt was successful, this descriptor contains the
             * updated parameters.
             */
            struct ble_gap_conn_desc conn;
        } conn_update;

        /**
         * Represents a peer's request to update the connection parameters.
         * This event is generated when a peer performs any of the following
         * procedures:
         *     o L2CAP Connection Parameter Update Procedure
         *     o Link-Layer Connection Parameters Request Procedure
         *
         * Valid for the following event types:
         *     o BLE_GAP_EVENT_L2CAP_UPDATE_REQ
         *     o BLE_GAP_EVENT_CONN_UPDATE_REQ
         * 
         */
        struct {
            /**
             * Indicates the connection parameters that the peer would like to
             * use.
             */
            const struct ble_gap_upd_params *peer_params;

            /**
             * Indicates the connection parameters that the local device would
             * like to use.  The application callback should fill this in.  By
             * default, this struct contains the requested parameters (i.e.,
             * it is a copy of 'peer_params').
             */
            struct ble_gap_upd_params *self_params;

            /** Information about the relevant connection. */
            struct ble_gap_conn_desc conn;
        } conn_update_req;

        /**
         * Represents a failed attempt to terminate an established connection.
         * Valid for the following event types:
         *     o BLE_GAP_EVENT_TERM_FAILURE
         */
        struct {
            /**
             * A BLE host return code indicating the reason for the failure.
             */
            int status;

            /** Information about the relevant connection. */
            struct ble_gap_conn_desc conn;
        } term_failure;

        /**
         * Represents an attempt to change the encrypted state of a
         * connection.  Valid for the following event types:
         *     o BLE_GAP_EVENT_ENC_CHANGE
         */
        struct {
            /**
             * Indicates the result of the encryption state change attempt;
             *     o 0: the encrypted state was successfully updated;
             *     o BLE host error code: the encryption state change attempt
             *       failed for the specified reason.
             */
            int status;

            /**
             * Information about the relevant connection.  If the encryption
             * state change attempt was successful, this descriptor reflects
             * the updated state.
             */
            struct ble_gap_conn_desc conn;
        } enc_change;

        /**
         * Represents a passkey query needed to complete a pairing procedure.
         * Valid for the following event types:
         *     o BLE_GAP_EVENT_PASSKEY_ACTION
         */
        struct {
            /** Contains details about the passkey query. */
            struct ble_gap_passkey_params params;

            /** Information about the relevant connection. */
            struct ble_gap_conn_desc conn;
        } passkey;

        /**
         * Represents a received ATT notification or indication.
         * Valid for the following event types:
         *     o BLE_GAP_EVENT_NOTIFY
         */
        struct {
            /** The handle of the relevant ATT attribute. */
            uint16_t attr_handle;

            /** The contents of the notification or indication. */
            void *attr_data;

            /** The number of data bytes contained in the message. */
            uint16_t attr_len;

            /** Information about the relevant connection. */
            struct ble_gap_conn_desc conn;

            /**
             * Whether the received command is a notification or an
             * indication;
             *     o 0: Notification;
             *     o 1: Indication.
             */
            unsigned indication:1;
        } notify;
    };
};
```

```c
struct ble_gap_sec_state {
    unsigned encrypted:1;
    unsigned authenticated:1;
    unsigned bonded:1;
};
```

```c
/**
 * @param discoverable_mode     One of the following constants:
 *                                  o BLE_GAP_DISC_MODE_NON
 *                                      (non-discoverable; 3.C.9.2.2).
 *                                  o BLE_GAP_DISC_MODE_LTD
 *                                      (limited-discoverable; 3.C.9.2.3).
 *                                  o BLE_GAP_DISC_MODE_GEN
 *                                      (general-discoverable; 3.C.9.2.4).
 * @param connectable_mode      One of the following constants:
 *                                  o BLE_GAP_CONN_MODE_NON
 *                                      (non-connectable; 3.C.9.3.2).
 *                                  o BLE_GAP_CONN_MODE_DIR
 *                                      (directed-connectable; 3.C.9.3.3).
 *                                  o BLE_GAP_CONN_MODE_UND
 *                                      (undirected-connectable; 3.C.9.3.4).
 */
struct ble_gap_adv_params {
    /*** Mandatory fields. */
    uint8_t conn_mode;
    uint8_t disc_mode;

    /*** Optional fields; assign 0 to make the stack calculate them. */
    uint16_t itvl_min;
    uint16_t itvl_max;
    uint8_t channel_map;
    uint8_t filter_policy;
    uint8_t high_duty_cycle:1;
};
```

```c
struct ble_gap_conn_desc {
    struct ble_gap_sec_state sec_state;
    uint8_t peer_ota_addr[6];
    uint8_t peer_id_addr[6];
    uint8_t our_id_addr[6];
    uint8_t our_ota_addr[6];
    uint16_t conn_handle;
    uint16_t conn_itvl;
    uint16_t conn_latency;
    uint16_t supervision_timeout;
    uint8_t peer_ota_addr_type;
    uint8_t peer_id_addr_type;
    uint8_t our_id_addr_type;
    uint8_t our_ota_addr_type;
    uint8_t role;
    uint8_t master_clock_accuracy;
};
```

```c
struct ble_gap_conn_params {
    uint16_t scan_itvl;
    uint16_t scan_window;
    uint16_t itvl_min;
    uint16_t itvl_max;
    uint16_t latency;
    uint16_t supervision_timeout;
    uint16_t min_ce_len;
    uint16_t max_ce_len;
};
```

```c
struct ble_gap_disc_params {
    uint16_t itvl;
    uint16_t window;
    uint8_t filter_policy;
    uint8_t limited:1;
    uint8_t passive:1;
    uint8_t filter_duplicates:1;
};
```

```c
struct ble_gap_upd_params {
    uint16_t itvl_min;
    uint16_t itvl_max;
    uint16_t latency;
    uint16_t supervision_timeout;
    uint16_t min_ce_len;
    uint16_t max_ce_len;
};
```

```c
struct ble_gap_passkey_params {
    uint8_t action;
    uint32_t numcmp;
};
```
