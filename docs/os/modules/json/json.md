# JSON

JSON is a data interchange format. The description of this format can be found from IETF RFC 4627.

## Description

This package helps in converting between C data types and JSON data objects. It supports both encoding and decoding.

## Data structures

### Encoding

```c
/* Encoding functions */
typedef int (*json_write_func_t)(void *buf, char *data,
        int len);

struct json_encoder {
    json_write_func_t je_write;
    void *je_arg;
    int je_wr_commas:1;
    char je_encode_buf[64];
};
```
Here's the data structure encoder funtions use, and it must be initialized by the caller. The key element is *je_write*, which is a function pointer which gets called whenever encoding routine is ready with encoded data. The element *je_arg* is passed to *je_write* as the first argument. The rest of the structure contents are for internal state management.
This function should collect all the data encoder function generates. It can collect this data to a flat buffer, chain of mbufs or even stream through.

```c
/**
 * For encode.  The contents of a JSON value to encode.
 */
struct json_value {
    uint8_t jv_pad1;
    uint8_t jv_type;
    uint16_t jv_len;

    union {
        uint64_t u;
        float fl;
        char *str;
        struct {
            char **keys;
            struct json_value **values;
        } composite;
    } jv_val;
};
```
This data structure is filled with data to be encoded. It is best to fill this using the macros *JSON_VALUE_STRING()* or *JSON_VALUE_STRINGN()* when value is string, *JSON_VALUE_INT()* when value is an integer, and so forth.

###Decoding
```c
/* when you implement a json buffer, you must implement these functions */

/* returns the next character in the buffer or '\0'*/
typedef char (*json_buffer_read_next_byte_t)(struct json_buffer *);
/* returns the previous character in the buffer or '\0' */
typedef char (*json_buffer_read_prev_byte_t)(struct json_buffer *);
/* returns the number of characters read or zero */
typedef int (*json_buffer_readn_t)(struct json_buffer *, char *buf, int n);

struct json_buffer {
    json_buffer_readn_t jb_readn;
    json_buffer_read_next_byte_t jb_read_next;
    json_buffer_read_prev_byte_t jb_read_prev;
};
```
Function pointers within this structure are used by decoder when it is reading in more data to decode.

```c
struct json_attr_t {
    char *attribute;
    json_type type;
    union {
        int *integer;
        unsigned int *uinteger;
        double *real;
        char *string;
        bool *boolean;
        char *character;
        struct json_array_t array;
        size_t offset;
    } addr;
    union {
        int integer;
        unsigned int uinteger;
        double real;
        bool boolean;
        char character;
        char *check;
    } dflt;
    size_t len;
    const struct json_enum_t *map;
    bool nodefault;
};
```
This structure tells the decoder about a particular name/value pair. Structure must be filled in before calling the decoder routine *json_read_object()*.

| Element | Description |
|---------|-------------|
| attribute | Name of the value |
| type | The type of the variable; see enum json_type |
| addr | Contains the address where value should be stored |
| dflt | Default value to fill in, if this name is not found |
| len | Max number of bytes to read in for value |
| nodefault | If set, default value is not copied name |

## List of Functions

Functions for encoding:

* [json_encode_object_start](json_encode_object_start.md)
* [json_encode_object_key](json_encode_object_key.md)
* [json_encode_object_entry](json_encode_object_entry.md)
* [json_encode_object_finish](json_encode_object_finish.md)

Functions for decoding:

* [json_read_object](json_read_object.md)
