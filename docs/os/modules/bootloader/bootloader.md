#Bootloader

The "bootloader" is the code that loads the Mynewt OS image into memory and conducts some checks before allowing the OS to be run. The bootloader in the Apache Mynewt project verifies the cryptographic signature of the firmware image before running it. It maintains a detailed status log for each stage of the boot process. For verification of the authenticity of the OS image, it:

* Calculates hash of the image.
* Uses public key to uncover hash value from included signature. 
* Compares the calculated and uncovered hashes for a match.

The "secure bootloader" should be placed in protected memory on a given microcontroller.
 
The Mynewt code is structured so that the generic bootutil library performs most of the functions of a boot loader. The final step of actually jumping to the main image is kept out of the bootutil library.  This last step should instead be implemented in an
architecture-specific project.  Boot loader functionality is separated in this
manner for the following two reasons:

1. By keeping architecture-dependent code separate, the bootutil library can be
   reused among several boot loaders.
2. By excluding the last boot step from the library, the rest of the code can
   be tested in a sim environment.

###Limitations

The boot loader currently only supports images with the following
characteristics:

* Built to run from flash.
* Build to run from a fixed location (i.e., position-independent).


###Image Format

The following definitions describe the image header format.

```c
#define IMAGE_MAGIC                 0x96f3b83c
#define IMAGE_MAGIC_NONE            0xffffffff

struct image_version {
    uint8_t iv_major;
    uint8_t iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
};

/** Image header.  All fields are in little endian byte order. */
struct image_header {
    uint32_t ih_magic;
    uint16_t ih_tlv_size; /* Trailing TLVs */
    uint8_t  ih_key_id;
    uint8_t  _pad1;
    uint16_t ih_hdr_size;
    uint16_t _pad2;
    uint32_t ih_img_size; /* Does not include header. */
    uint32_t ih_flags;
    struct image_version ih_ver;
    uint32_t _pad3;
};
```

The `ih_hdr_size` field indicates the length of the header, and therefore the
offset of the image itself.  This field provides for backwards compatibility in
case of changes to the format of the image header.

The following are the image header flags available.

```c
#define IMAGE_F_PIC                   0x00000001
#define IMAGE_F_SHA256                0x00000002	/* Image contains hash TLV */
#define IMAGE_F_PKCS15_RSA2048_SHA256 0x00000004 /* PKCS15 w/RSA and SHA */
#define IMAGE_F_ECDSA224_SHA256       0x00000008  /* ECDSA256 over SHA256 */
#define IMAGE_F_NON_BOOTABLE          0x00000010
#define IMAGE_HEADER_SIZE           32
``` 

Security data gets added as a footer at the end of the image.

```c
/*
 * Image trailer TLV types.
 */
#define IMAGE_TLV_SHA256            1	/* SHA256 of image hdr and body */
#define IMAGE_TLV_RSA2048           2	/* RSA2048 of hash output */
#define IMAGE_TLV_ECDSA224          3   /* ECDSA of hash output */
```


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



If a vector file contains a version which doesn't correspond to an image
actually present in flash, the boot loader deletes the file and procedes as
though the file was not present.


###Boot Status

The boot status record allows the boot loader to recover in case it was reset
while in the middle of an image swap operation.  Image swapping is discussed
later in this document. 


```c
struct boot_status_table {
    /**
     * For each field, a value of 0 means "any".
     */
    uint8_t bst_magic_slot0;
    uint8_t bst_magic_scratch;
    uint8_t bst_copy_done_slot0;
    uint8_t bst_status_source;
};
```


```c
struct boot_status {
    uint32_t idx;       /* Which area we're operating on */
    uint8_t state;      /* Which part of the swapping process are we at */
};
```



###Image Swapping

If the boot vector indicates that the image in the secondary slot should be
run, the boot loader needs to copy it to the primary slot.  The image currently
in the primary slot also needs to be retained in flash so that it can be used
later.  Furthermore, both images need to be recoverable if the boot loader
resets in the middle of the process.  The two images are swapped according to
the following procedure:


###Verifying integrity of image

 

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


###Example


###Dependencies

The bootloader depends on the following OS kernel functions:


The bootloader does not depend on any flash file system.

###List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>


The functions available in bootloader are:

