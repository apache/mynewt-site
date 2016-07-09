## <font color="#F2853F" style="font-size:24pt">ATT Definitions</font>

```c
/**
 * Context for an access to an ATT attribute.  When a client reads or writes a
 * locally registered attribute, an instance of this struct gets passed to the
 * access callback.
 */
struct ble_att_svr_access_ctxt {
    /**
     * The ATT operation being performed dictates which field in this union is
     * valid.  If a read is being performed, the read field is valid.
     * Otherwise, a write is being performed, in which case the write field is
     * valid.
     */
    union {
        /** Context for reads of ATT attributes. */
        struct {
            /**
             * (stack --> app)
             * The offset within the attribute that the client is reading from.
             */
            uint16_t offset;

            /**
             * (stack --> app)
             * Maximum number of data bytes the stack can send in the read
             * response.  This is based on the connection's ATT MTU.
             */
            uint16_t max_data_len;

            /**
             * (stack --> app)
             * A buffer that the app can use to write the characteristic
             * response value to.  This buffer can hold up to max_data_len
             * bytes.
             */
            uint8_t *buf;

            /**
             * (app --> stack)
             * App points this at the characteristic data to respond with.
             * Initially this points to "buf".
             */
            const void *data;

            /**
             * (app --> stack)
             * App fills this with the number of data bytes contained in
             * characteristic response.
             */
            uint16_t len;
        } read;

        /** Context for writes of ATT attributes. */
        struct {
            /**
             * (stack --> app)
             * The data that the peer is writing to the characteristic.
             */
            const void *data;

            /**
             * (stack --> app)
             * The offset within the attribute that the client is writing to.
             */
            uint16_t offset;

            /**
             * (stack --> app)
             * The number of bytes of characteristic data being written.
             */
            int len;
        } write;
    };
};
```
