#Bootloader

The bootutil library performs most of the functions of a boot loader.  In
particular, the piece that is missing is the final step of actually jumping to
the main image.  This last step should instead be implemented in an
architecture-specific project.  Boot loader functionality is separated in this
manner for the following two reasons:

1. By keeping architecture-dependent code separate, the bootutil library can be
   reused among several boot loaders.
2. By excluding the last boot step from the library, the rest of the code can
   be tested in a sim environment.

There is a boot loader project specific to the olimex_stm32-e407 devboard
called *boot*.  This project provides an example of how the bootutil library
should be used.

###Limitations

The boot loader currently only supports images with the following
characteristics:

* Built to run from flash.
* Build to run from a fixed location (i.e., position-independent).

These limitations will likely be addressed soon.


###Image Format

The following definitions describe the image header format.

```c
#define IMAGE_MAGIC                 0x96f3b83c

struct image_version {
    uint8_t iv_major;
    uint8_t iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
};

/** Image header.  All fields are in little endian byte order. */
struct image_header {
    uint32_t ih_magic;
    uint32_t ih_crc32; /* Covers remainder of header and all of image body. */
    uint32_t ih_hdr_size;
    uint32_t ih_img_size; /* Does not include header. */
    uint32_t ih_flags;
    struct image_version ih_ver;
};
```

At this time, no flags have been defined.

The `ih_hdr_size` field indicates the length of the header, and therefore the
offset of the image itself.  This field provides for backwards compatibility in
case of changes to the format of the image header.

When security is added, security data will likely go in a footer at the end of
the image.


###Flash Areas

Bootutil uses the same concept of "flash areas" as the nffs file system.
Briefly, an area is a region of disk with the following properties:
1. An area can be fully erased without affecting any other areas.
2. A write to one area does not restrict writes to other areas.

The areas used for image data must not be used for anything else.  In
particular, these areas must be kept separate from the nffs file system.


###Image Slots

A portion of the flash memory is partitioned into two image slots: a primary
slot and a secondary slot.  The boot loader will only run an image from the
primary slot, so images must be built such that they can run from that fixed
location in flash.  If the boot loader needs to run the image resident in the
secondary slot, it must swap the two images in flash prior to booting.

In addition to the two image slots, the boot loader requires a scratch area to
allow for reliable image swapping.

All areas used by image data (including the scratch area) must be the same
size.


###Boot Vector

Bootutil determines which image it should boot into by reading the contents of
the boot vector.  The boot vector comprises the following files in the flash
file system:

```c
#define BOOT_PATH_MAIN      "/boot/main"
#define BOOT_PATH_TEST      "/boot/test"
```

Each file, if present, must contain a 64-bit image version.  This version is
simply a "binary dump" of an `image_version` struct.  The test file is used to
indicate that an image is being "tested out," and should only be booted once.
The main file indicates the "last known good" image which should be booted
repeatedly.

The boot loader uses the following procedure to determine which image to boot:

1. If the test file is present and contains a valid image version:
    * Delete the test file.
    * Boot into the specified image.
2. Else if the main file is present and contains a valid image version:
    * Boot into the specified image.
3. Else:
    * Just boot into whichever image is in the primary slot.  If there is no
image in the primary slot, boot into the image in the secondary slot.

If a vector file contains a version which doesn't correspond to an image
actually present in flash, the boot loader deletes the file and procedes as
though the file was not present.


###Boot Status

The boot status file allows the boot loader to recover in case it was reset
while in the middle of an image swap operation.  Image swapping is discussed
later in this document; the structure of the boot status file is presented
here.  To ensure recovery is always possible, bootutil updates the status file
at each step throughout the image swap process.  The boot status is contained
in the following file:

```c
#define BOOT_PATH_STATUS    "/boot/status"
```

The contents of the boot status file are defined below.

```c
struct boot_status {
    uint32_t bs_img1_length;
    uint32_t bs_img2_length;
    /* Followed by sequence of boot status entries; file size indicates number
     * of entries.
     */
};

struct boot_status_entry {
    uint8_t bse_image_num;
    uint8_t bse_part_num;
};

#define BOOT_IMAGE_NUM_NONE     0xff
```

There is a separate boot status entry for each flash area used by the boot
loader (i.e., each area in the two slots, plus one for the scratch area).  The
entries are placed in the file in the same order as their corresponding areas
in flash.  Each entry indicates which image part is resident in the
corresponding flash area.  If a flash area does not contain any image data, its
corresponding entry will have a `bse_image_num` value of `BOOT_IMAGE_NUM_NONE`.

Consider the following example:

Five flash areas are dedicated to image data, as follows:

| Area | Slot | Value |
|------|------|-------|
| Area 0 | slot 0 | 0/1 |
| Area 1 | slot 0 | 1/1 |
| Area 2 | slot 1 | 0/1 |
| Area 3 | slot 1 | 1/1 |
| Area 4 | scratch ||

The following array of boot status entries is read from the status file:

```c
    [0] = {
        .bse_image_num = 0,
        .bse_part_num = 0,
    },
    [1] = { 
        .bse_image_num = 0,
        .bse_part_num = 1,
    },
    [2] = { 
        .bse_image_num = 1,
        .bse_part_num = 0,
    },
    [3] = { 
        .bse_image_num = 1,
        .bse_part_num = 1,
    },
    [4] = { 
        .bse_image_num = 0xff,
        .bse_part_num = 0xff,
    },
```
    
This status file indicates the following image placement:

| Area | Image | Part |
|------|------|-------|
| Area 0 | image 0 | part 0 |
| Area 1 | image 0 |  part 1 |
| Area 2 | image 1 | part 0 |
| Area 3 | image 1 | part 1 |
| Scratch area | empty ||

Images don't have an instrinsic image number.  When a swap operation is
started, the image initially in the primary slot is labelled `image 0`, and the
image in the secondary slot is labelled `image 1`.  All swap operations end with
`image 1` in the primary slot, and `image 0` in the secondary slot.

The boot status header containing the image sizes is necessary so that `bootutil`
can determine how many flash areas each image occupies.  Without this
information, `bootutil` would need to swap the full contents of the image slots,
including useless data after the end of each image.

The status file is always deleted upon successful boot.


###Image Swapping

If the boot vector indicates that the image in the secondary slot should be
run, the boot loader needs to copy it to the primary slot.  The image currently
in the primary slot also needs to be retained in flash so that it can be used
later.  Furthermore, both images need to be recoverable if the boot loader
resets in the middle of the process.  The two images are swapped according to
the following procedure:

1. Determine how many flash areas are required to hold the desired image.
2. For each required area in the primary slot ("destination area"):
    a. Identify the flash area in the secondary slot which contains the
           required image data ("source area").
    b. Erase scratch area.
    c. Copy destination area to scratch area.
    d. Write updated boot status to the file system.
    e. Erase destination area.
    f. Copy source area to destination area.
    g. Write updated boot status to the file system.
    h. Erase source area.
    i. Copy scratch area to source area.
    j. Write updated boot status to the file system.
3. Determine how many flash areas are required to hold image 1.
4. For each required area in the secondary slot ("destination area"):
    a. If the destination area already contains the required image data,
           advance to the next image part.
    b. Else, identify the flash area in the primary slot which contains the
           required image data ("source area").
    c. Repeat steps b through j from step 2.

This procedure ensures that the contents of the boot status file are always
accurate, so the boot loader can recover after an unexpected reset.

Step 4 is necessary in case the two images do not occupy the same number of
flash areas.


###Reset Recovery

If the boot loader resets in the middle of a swap operation, the two images may
be discontiguous in flash.  Bootutil recovers from this condition by using the
boot status file to determine how the image parts are placed in flash.

If the boot status file indicates that the images are not contiguous, bootutil
completes the swap operation that was in progress when the system was reset.
In other words, it applies the procedure defined in the previous section,
moving image 1 into slot 0 and image 0 into slot 1.  If the boot status file
indicates that an image part is present in the scratch area, this part is
copied into the correct location by starting at step e or step h in the
area-swap procedure, depending on whether the part belongs to image 0 or image
1.

After the swap operation has been completed, the boot loader proceeds as though
it had just been started.


###API

The API consists of a single function:

```c
int boot_go(const struct boot_req *req, struct boot_rsp *rsp)
```
        
The request and response structures are defined as follows:

```c
struct boot_req {
    
    struct nffs_area_desc *br_area_descs;

    uint8_t *br_image_areas;

    uint8_t *br_slot_areas;

    uint8_t br_num_image_areas;


    uint8_t br_scratch_area_idx;
};
```

```c
struct boot_rsp {
    const struct image_header *br_hdr;

    uint32_t br_image_addr;
};
```

###Example

In this example, each image slot consists of three flash areas.

```c
/** Internal flash layout. */
static struct nffs_area_desc boot_area_descs[] = {
    [0] =  { 0x08000000, 16 * 1024 },
    [1] =  { 0x08004000, 16 * 1024 },
    [2] =  { 0x08008000, 16 * 1024 },
    [3] =  { 0x0800c000, 16 * 1024 },
    [4] =  { 0x08010000, 64 * 1024 },
    [5] =  { 0x08020000, 128 * 1024 }, /* Image data; 0,0. */
    [6] =  { 0x08040000, 128 * 1024 }, /* Image data; 0,1. */
    [7] =  { 0x08060000, 128 * 1024 }, /* Image data; 0,2. */
    [8] =  { 0x08080000, 128 * 1024 }, /* Image data; 1,0. */
    [9] =  { 0x080a0000, 128 * 1024 }, /* Image data; 1,1. */
    [10] = { 0x080c0000, 128 * 1024 }, /* Image data; 1,2. */
    [11] = { 0x080e0000, 128 * 1024 }, /* Image scratch area. */
    { 0, 0 },
};

/** Contains indices of the areas which can contain image data. */
static uint8_t boot_img_areas[] = {
    5, 6, 7, 8, 9, 10, 11,
};

/** Areas representing the beginning of image slots. */
static uint8_t boot_slot_areas[] = {
    5, 8,
};

#define BOOT_NUM_IMG_AREAS \
    ((int)(sizeof boot_img_areas / sizeof boot_img_areas[0]))

/** The scratch area to use during an image swap operation. */
#define BOOT_AREA_IDX_SCRATCH 11

int
main(void)
{
    struct boot_rsp rsp;
    int rc;

    const struct boot_req req = {
        .br_area_descs = boot_area_descs,
        .br_image_areas = boot_img_areas,
        .br_slot_areas = boot_slot_areas,
        .br_num_image_areas = BOOT_NUM_IMG_AREAS,
        .br_scratch_area_idx = BOOT_AREA_IDX_SCRATCH,
    };

    rc = boot_go(&req, &rsp);
    assert(rc == 0);

    /* Perform jump to address indicated by the response object. */

    return 0;
}
```

###Dependencies
* `nffs` (for the boot vector and boot status files).
* `os` (for `os_malloc()` and `os_free()`).

###List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>


The functions available in bootloader are:

* [boot_build_status](boot_build_status.md)
* [boot_build_status_one](boot_build_status_one.md)
* [boot_clear_status](boot_clear_status.md)
* [boot_copy_area](boot_copy_area.md)
* [boot_copy_image](boot_copy_image.md)
* [boot_erase_area](boot_erase_area.md)
* [boot_fill_slot](boot_fill_slot.md)
* [boot_find_image_area_idx](boot_find_image_area_idx.md)
* [boot_find_image_part](boot_find_image_part.md)
* [boot_find_image_slot](boot_find_image_slot.md)
* [boot_go](boot_go.md)
* [boot_init_flash](boot_init_flash.md)
* [boot_move_area](boot_move_area.md)
* [boot_read_image_header](boot_read_image_header.md)
* [boot_read_image_headers](boot_read_image_headers.md)
* [boot_read_status](boot_read_status.md)
* [boot_select_image_slot](boot_select_image_slot.md)
* [boot_slot_addr](boot_slot_addr.md)
* [boot_slot_to_area_idx](boot_slot_to_area_idx.md)
* [boot_swap_areas](boot_swap_areas.md)
* [boot_vect_delete_main](boot_vect_delete_main.md)
* [boot_vect_delete_test](boot_vect_delete_test.md)
* [boot_vect_read_main](boot_vect_read_main.md)
* [boot_vect_read_one](boot_vect_read_one.md)
* [boot_vect_read_test](boot_vect_read_test.md)
* [boot_write_status](boot_write_status.md)
