# Flash Circular Buffer (FCB)

Flash circular buffer provides an abstration through which you can treat flash like a FIFO. You append entries to the end, and read data from the beginning.

###Description

Elements in the flash contain the length of the element, the data within the element, and checksum over the element contents.

Storage of elements in flash is done in a FIFO fashion. When user requests space for the next element, space is located at the end of the used area. When user starts reading, the first element served is the oldest element in flash.

Elements can be appended to the end of the area until storage space is exhausted. User has control over what happens next; either erase oldest block of data, thereby freeing up some space, or stop writing new data until existing data has been collected. FCB treats underlying storage as an array of flash sectors; when it erases old data, it does this a sector at a time.

Elements in the flash are checksummed. That is how FCB detects whether writing element to flash completed ok. It will skip over entries which don't have a valid checksum.

### Usage

To add an element to circular buffer:

* Call fcb_append() to get the location where data can be written. If this fails due to lack of space, you can call fcb_rotate() to make some. And then call fcb_append() again.
* Use flash_area_write() to write element contents.
* Call fcb_append_finish() when done. This completes the entry by calculating the checksum.

To read contents of the circular buffer:
* Call fcb_walk() with a pointer to your callback function.
* Within callback function copy in data from the element using flash_area_read(). You can tell when all data from within a sector has been read by monitoring returned element's area pointer. Then you can call fcb_rotate(), if you're done with that data.

Alternatively:
* Call fcb_getnext() with 0 in element offset to get the pointer to oldest element.
* Use flash_area_read() to read element contents.
* Call fcb_getnext() with pointer to current element to get the next one. And so on.

###Data structures

This data structure describes the element location in the flash. You would use it figure out what parameters to pass to flash_area_read() to read element contents. Or to flash_area_write() when adding a new element.

```c
struct fcb_entry {
    struct flash_area *fe_area;
    uint32_t fe_elem_off;
    uint32_t fe_data_off;
    uint16_t fe_data_len;
};
```

| Element | Description |
|---------|-------------|
| fe_area | Pointer to info about the flash sector. Pass this to flash_area_xx() routines. |
| fe_elem_off | Byte offset from the start of the sector to beginning of element. |
| fe_data_off | Byte offset from start of the sector to beginning of element data. Pass this to to flash_area_xx() routines. |
| fe_data_len | Number of bytes in the element.  |


The following data structure describes the FCB itself. First part should be filled in by the user before calling fcb_init(). The second part is used by FCB for its internal bookkeeping.
```c
struct fcb {
    /* Caller of fcb_init fills this in */
    uint32_t f_magic;           /* As placed on the disk */
    uint8_t f_version;          /* Current version number of the data */
    uint8_t f_sector_cnt;       /* Number of elements in sector array */
    uint8_t f_scratch_cnt;      /* How many sectors should be kept empty */
    struct flash_area *f_sectors; /* Array of sectors, must be contiguous */

    /* Flash circular buffer internal state */
    struct os_mutex f_mtx;      /* Locking for accessing the FCB data */
    struct flash_area *f_oldest;
    struct fcb_entry f_active;
    uint16_t f_active_id;
    uint8_t f_align;            /* writes to flash have to aligned to this */
};
```

| Element | Description |
|---------|-------------|
| f_magic | Magic number in the beginning of FCB flash sector. FCB uses this when determining whether sector contains valid data or not. |
| f_version | Current version number of the data. Also stored in flash sector header. |
| f_sector_cnt | Number of elements in the f_sectors array. |
| f_scratch_cnt | Number of sectors to keep empty. This can be used if you need to have scratch space for garbage collecting when FCB fills up. |
| f_sectors | Array of entries describing flash sectors to use. |
| f_mtx | Lock protecting access to FCBs internal data. |
| f_oldest | Pointer to flash sector containing the oldest data. This is where data is served when read is started. |
| f_active | Flash location where the newest data is. This is used by fcb_append() to figure out where the data should go to. |
| f_active_id | Flash sectors are assigned ever-increasing serial numbers. This is how FCB figures out where oldest data is on system restart. |
| f_align | Some flashes have restrictions on alignment for writes. FCB keeps a copy of this number for the flash here. |

###List of Functions

The functions available in this OS feature are:

| Function | Description |
|---------|-------------|
| [fcb_init](fcb_init.md) | Initializes the FCB. After calling this, you can start reading/writing data from FCB. |
| [fcb_append](fcb_append.md) | Start writing a new element to flash. |
| [fcb_append_finish](fcb_append_finish.md) | Finalizes the write of new element. FCB computes the checksum over the element and updates it in flash. |
| [fcb_walk](fcb_walk.md) | Walks over all log entries in FCB. |
| [fcb_getnext](fcb_getnext.md) | Fills given FCB location with information about next element. |
| [fcb_rotate](fcb_rotate.md) | Erase the oldest sector in FCB. |
| [fcb_append_to_scratch](fcb_append_to_scratch.md) | If FCB uses scratch blocks, use reserve blocks when FCB is filled. |
| [fcb_is_empty](fcb_is_empty.md) | Returns 1 if there are no elements stored in FCB, otherwise returns 0. |
| [fcb_offset_last_n](fcb_offset_last_n.md) | Returns the offset of n-th last element. |
| [fcb_clear](fcb_clear.md) | Wipes out all data in FCB. |
