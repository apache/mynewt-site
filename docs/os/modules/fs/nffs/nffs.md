# Newtron Flash Filesystem (nffs)

Mynewt includes the Newtron Flash File System (nffs).  This file system is designed with two priorities that makes it suitable for embedded use: 

* Minimal RAM usage
* Reliability

Mynewt also provides an abstraction layer API (fs) to allow you to swap out nffs with a different file system of your choice.

###Description

####Areas

At the top level, an nffs disk is partitioned into *areas*.  An area is a region of disk with the following properties:

1. An area can be fully erased without affecting any other areas.
2. Writing to one area does not restrict writes to other areas.

**Regarding property 1:** Generally, flash hardware divides its memory space into "blocks."  When erasing flash, entire blocks must be erased in a single operation; partial erases are not possible.

**Regarding property 2:** Furthermore, some flash hardware imposes a restriction with regards to writes: writes within a block must be strictly sequential.  For example, if you wish to write to the first 16 bytes of a block, you must write bytes 1 through 15 before writing byte 16.  This restriction only applies at the block level; writes to one block have no effect on what parts of other blocks can be written.

Thus, each area must comprise a discrete number of blocks.

####Initialization

Before nffs can be used, it must be initialized.  There are two means of initializing an nffs file system:

1. Restore an existing file system via detection.
2. Create a new file system via formatting.

A typical initialization sequence is the following:

1. Detect an nffs file system in a specific region of flash.
2. If no file system was detected, format a new file system in the same flash region.

Both methods require the user to describe how the flash memory should be divided into nffs areas.  This is accomplished with an array of [struct nffs\_area\_desc](nffs_area_desc.md).

Typically, a product's flash layout is exposed via its BSP-specific `bsp_flash_dev()` function.  This function retrieves the layout of the specified flash device resident in the BSP.  The result of this function can then be converted into the `struct nffs_area_desc[]` that nffs requires.  The below example, taken from the slinky project, illustrates the nffs initialization procedure.

```c
/*** hw/hal/include/hal/flash_map.h */

/*
 * Flash area types
 */
#define FLASH_AREA_BOOTLOADER           0
#define FLASH_AREA_IMAGE_0              1
#define FLASH_AREA_IMAGE_1              2
#define FLASH_AREA_IMAGE_SCRATCH        3
#define FLASH_AREA_NFFS                 4
```

```c
/*** project/slinky/src/main.c */

int
main(int argc, char **argv)
{
    int rc;
    int cnt;

    /* NFFS_AREA_MAX is defined in the BSP-specified bsp.h header file. */
    struct nffs_area_desc descs[NFFS_AREA_MAX];

    /* Initialize nffs's internal state. */
    rc = nffs_init();
    assert(rc == 0);

    /* Convert the set of flash blocks we intend to use for nffs into an array
     * of nffs area descriptors.
     */
    cnt = NFFS_AREA_MAX;
    rc = flash_area_to_nffs_desc(FLASH_AREA_NFFS, &cnt, descs);
    assert(rc == 0);

    /* Attempt to restore an existing nffs file system from flash. */
    if (nffs_detect(descs) == FS_ECORRUPT) {
        /* No valid nffs instance detected; format a new one. */
        rc = nffs_format(descs);
        assert(rc == 0);
    }
    /* [ ... ] */
}
```

After nffs has been initialized, the application can access the file system via the [file system abstraction layer](../fs/fs.md).

###Configuration

The nffs file system is configured by populating fields in a global [struct nffs\_config](nffs_config.md) instance.  Each field in the structure corresponds to a setting.  All configuration must be done prior to calling nffs\_init().


The global `struct nffs_config` instance is exposed in `nffs/nffs.h` as follows:

```c
extern struct nffs_config nffs_config;
```

###Data Structures

The `fs/nffs` package exposes the following data structures:

| Struct | Description |
|---------|-------------|
| [struct nffs\_area\_desc](nffs_area_desc.md) | Descriptor for a single nffs area. |
| [struct nffs\_config](nffs_config.md) | Configuration struct for nffs. |

###API

The functions available in this OS feature are:

| Function | Description |
|---------|-------------|
| [nffs\_detect](nffs_detect.md) | Searches for a valid nffs file system among the specified areas. |
| [nffs\_format](nffs_format.md) | rases all the specified areas and initializes them with a clean nffs file system. |
| [nffs\_init](nffs_init.md) | Initializes internal nffs memory and data structures. |

###Miscellaneous measures

* RAM usage:
    * 24 bytes per inode
    * 12 bytes per data block
    * 36 bytes per inode cache entry
    * 32 bytes per data block cache entry
    
* Maximum filename size: 256 characters (no null terminator required)
* Disallowed filename characters: '/' and '\0'

###Internals

nffs implementation details can be found here:

* [nffs\_internals](nffs_internals.md)

###Future enhancements

* Error correction.
* Encryption.
* Compression.
