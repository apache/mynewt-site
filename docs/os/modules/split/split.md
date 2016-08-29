
#Split Images


## Description

Split images allow the user to build the application content separate from the library content by splitting an application into two pieces:

* A "loader" which contains a separate application that can perform upgrades and manage split images. The "loader" resides in slot 1.
* A "split app" which contains the main application content and references the libraries in the loader by static linkage. The "split app" resides in slot 2.

## Goals

The goal of split images is to allow a larger application to run along with large components of mynewt such as [nimble BLE stack](../../../network/ble/ble_intro/) and [neutron flash file system(nffs)](../fs/nffs/nffs.md).

## Concept

In a typical mynewt application, an application is contained wholly within an image slot.  Typically there are at least two image slots since the image runs from one slot while uploading new code into the second slot.  Each image is capable of erasing and uploading another image.  Each image is completely stand-alone; that is, each image contains all of the libraries and components that it needs.   

On a typical 256 kbyte flash, a flash layout might look like this:

| Name  | Size  |
|---|---|
| bootloader  | 16 k  |
| image slot 1  | 108 k  |
| image slot 2  | 108 k  |
| scratch  | 8 k  |
| Flash file system  | 16 k  |

Now, suppose the desired image contains:

|  Package | Size  |
|---|---|
|  nimble |  69 k |
|  os  | 6 k  |
|  logging  |  3 k |
|  imagemgr | 3 k  |
| config | 3 k | 
| nffs | 15 k |
| newtmgr | 7 k |


which total 106k.  With an image slot size of 108k this leaves only a small amount of code space remaining for the application.

However, we can see that these packages contain everything you need to upgrade and configure, so if we build a stand-alone loader with these components, we can build the app as a split image and get the entire second image slot to store application code and constant data.


## When do I use split images

If your application fits into the available image slots, there is no advantage to using split images.  In general, split images are harder to debug and more complicated to upload. However for a larger application, there may not be enough flash space to have two copies of the entire application. This is when split image becomes necessary.

## How do I tell Newt I am building a split image?

Newt looks for the variable `loader` in your target file. If it finds `loader` variable, it will build a split image.  For example, 

```
targets/app
    app=@apache-mynewt-core/apps/splitty
    loader=@apache-mynewt-core/apps/slinky
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    build_profile=optimized
```
shows an application called splitty which uses slinky as its loader.

## Platforms

Split image requires BSP support.  The following BSPs support split images:

* nrf52dk

## Loaders

The following applications have been enabled as loaders. You may choose to build your own loader application, and these can serve as samples.

* @apache-mynewt-core/apps/slinky
* @apache-mynewt-core/apps/bleprph

## Split Apps

The following applications have been enabled as split applications. If you choose to build your own split application these can serve as samples. Note that slinky can be either a loader image or a split app image.

* @apache-mynewt-core/apps/slinky
* @apache-mynewt-core/apps/splitty

## Theory of Operation

A split image is built as follows:

First newt builds the `app` and `loader` images separately to ensure they are consistent (no errors) and to generate elf files which can inform newt of the symbols used by each part.

Then newt collects the symbols used by both `app` and `loader` in two ways.  It collects the set of symbols from the `.elf` files. It also collects all the possible symbols from the `.a` files for each application.

Newt builds the set of packages that the two applications share.  It ensures that all the symbols used in those packages are matching.  NOTE: because of features and #ifdefs, its possible for the two package to have symbols that are not the same.  In this case newt generates an error and will not build a split image.  

Then newt creates the list of symbols that the two applications share from those packages (using the .elf files).

Newt re-links the loader to ensure all of these symbols are present in the loader application (by forcing the linker to include them in the `.elf`).  

Newt builds a special copy of the loader.elf with only these symbols (and the handful of symbols discussed in the linking section above).

Finally, newt links the application, replacing the common .a libraries with the special loader.elf image during the link. 

## Design

### Bootloader

The bootloader has been modified to support "non bootable" images like split app images.  A flag in the image header denotes the image as "non-bootable". When this flag is set, the bootloader will not boot the split app image, nor will it copy it to the slot 1 location. Loader images are bootable, split app images are not.

### Newt

Newt builds a split image when the token `loader=@apache-mynewt-core/apps/slinky` is present in the target file.

Newt has a `Builder` object that is responsible for building an image.  This features a `targetBuilder` object that contains two builders (one for the app and one for the loader).

The `Builder` object has been expanded to include options for building as part of a split image.
* Ability to specify the linker file during the link
* Ability to specify a set of keep_symbols during the link

Newt commands like download, size, create-image have been expanded to perform operations twice (once for loader and once for app) if the loader target is present.

During normal single-image builds, the `targetBuilder` initializes and builds the application `builder`. During the split image build, the `targetBuilder` performs the steps outlined in the section above using the two `builder`s for the loader and app.

Special symbol and link features are designed as follows:

* Newt uses objdump to parse the symbol maps in the `.a` and `.elf` files. 
* Newt uses the `--undefined=` option of the linker to force the loader to keep symbols used by the app (but not used by the linker)
* Newt uses objcopy with the `-K` (keep) option when building the special linker `.elf`.
* Newt uses the `--just-symbols` option of the linker to link against the loader `.elf` file.  

#### newt create-image

Create image uses two different methods to compute the image hash for standard and split images.  For split images, the hash is computed starting with the 32-byte hash of the loader, then continuing with the hashing algorithm used by the standard application.  This ensures that the split app can be "validated" against a loader image specifically.  

#### newt errors

Newt has several new build errors when building split images.  

* Linker script undefined.  If the BSP for your application does not define a split image linker script the build will fail.

If newt finds that the same library (for example libs/os) has a different implementaiton in the loader and app, it will generate an error and fail to build.  These differences can arise when `#ifdef` or features are included in one app and not the other.  For example, it the loader includes `libs/console/stubs` and the app includes `libs/console/full` this may change implementations of certain functions within other packages.  

### Image manifest

newt builds a single manifest for split images, adding extra tags to the manifest when the image is a split image.

```
  "loader": "slinky.img",
  "loader_hash": "55e254f133bedf640fc7be7b5bfe3e5fb387cf5e29ecd0d4ea02b5ba617e27e0",
    "loader_pkgs": [
		...
		]
```

The manifest lists packages in both the loader and app.  The app package list only contains those packages that reside in the app image itself.  

### libs/bootutil

Bootutil has been expanded to include a function that looks for a split app image in slot 2, verifies that it matches the loader image in slot 1 and then fetches the entry information for the split app.

### libs/split

A small split image library was created to provide newtmgr commands for split image and to hold the configuration for split image. See newtmgr below for details.

It also contains the function used by a loader to validate and boot a split image.  

### apps/slinky

A sample app that can be built as a split image with slinky.

## Tips when Building Split images

**To be added**

## Adding BSP support for split images

A BSP needs additional components to be "split image ready".

The split image requires a special linker script. The split image needs to run from the second image partition (since it's using the loader library that is linked to be placed in the first partition).  It needs to reserve space for RAM used by the loader.  It also does not need to include the vector table (just a bit of it).

The startup of the split image is different than a typical image.  It needs to copy `.data` from the loader image, and zero the loader image bss.  For this, it must reference symbols defined in the linker script of the loader. It has a special entry symbol that differentiates it from the entry symbol in the loader application.  

Several of the bsp scripts need to handle additional agruments to deal with the two images produced by newt when building split images - mainly download and debug.

Add the following components to enable your BSP for split images:

1. A split image linker file
2. A startup file for the split image
3. A property in the pkg.yml file to tell newt what linker script to use for partition 2 images.  The property is defined as `pkg.part2linkerscript: "split-nrf52dk.ld` for example.
4. Modified download script

An example can be found in the `/hw/bsp/nrf52dk`

### split image linker script

The split image linker script must have the following.

The split linker must define the entry symbol as Reset_Handler_split.   For example:

```
ENTRY(Reset_Handler_split)
```

The split linker must define the first two words in the vector table (initial SP and Reset Vector). The additional vector entries are part of the loader. The bootloader accesses these entries at the beginning of the image slot (first 2 words). For example:

```
    .text :
    {
        __split_isr_vector_start = .;
        KEEP(*(.isr_vector_split))
        __split_isr_vector_end = .;
		...		
```

The split linker must ensure that it doesn't overwrite the BSS and DATA sections of the loader (they are both using RAM).  Note, the two apps don't run at the same time, but the loader has global data that its libraries use.  This cannot be overwritten by the application. An example linker section that accomplishes this can be found in `/hw/bsp/nrf52dk/split-nrf52dk.ld`. When linking against the loader, the loader exports the following symbosl which can be used by the split app code:

* `__HeapBase_loader`
* `__bss_start___loader`
* `__bss_end___loader`
* `__etext_loader`
* `__data_start___loader`
* `__data_end___loader`

The split app linker can use `__HeapBase_loader` to skip RAM used by the loader as follows.

```
    /* save RAM used by the split image. This assumes that 
     * the loader uses all the RAM up to its HeapBase  */
    .loader_ram_contents :
    {
        _loader_ram_start = .;

 	/* this symbol comes from the loader linker */
	. = . + (ABSOLUTE(__HeapBase_loader) - _loader_ram_start);
        _loader_ram_end = .;
    } > RAM
```

### split image startup code

The split application needs separate startup code to intialize the split image before running main.  THe split image is specially linked so that _start and main are included individually for the loader and split app.

The split app startup code must have the following.

1. A definition of the split image vector table (first two words). 
2. The entry point function to start the code `Reset_Handler_split`
3. Code that copies the .data section for the loader from Flash to RAM
4. Code that zeros the .bss section for the loader.
5. Code that calls _sbrkInit to set the heap pointers for the application

An example can be found in the `/hw/bsp/nrf52dk/src/arch/cortex_m4/gcc_startup_nrf52_split.s`

## newtmgr and split Images

newtmgr has support for split images.

`newtmgr image list2` lists the current images in the flash.  Its clear from the output that some images are non-bootable.  For example.

```
Images:
 slot=1
    version=1.2.3
    bootable=true
    hash=55e254f133bedf640fc7be7b5bfe3e5fb387cf5e29ecd0d4ea02b5ba617e27e0
 slot=2
    version=1.2.3
    bootable=false
    hash=1697bd1658f7e902e0191094c5f729446c9dd790c00a58e2bb37f56d6fcb72fe
```

The bootloader is unable to boot split app images (of course it can boot the loader images), so do not use the `boot2` command to instruct mynewt to boot slot 2.  

Instead, use the new `split status` command to see the status of split images and to set their boot status.  The split status command with no arguments returns status of the split image.  The Split Value tells the loader how to boot the split app. Options are:

* `none` Don't boot the split application. Just remain running in the loader.
* `test` Boot the split application, but revert back to the loader on the next reset.
* `run` Boot the split application.

The split status command also verified the hash of the split application (using the hash of the loader as shown above) and returns the status of the check (matching or non-matching).

```
newtmgr -c connection split status 
  Split value is none
  Split status is matching
```

When the split image application is running, the active hash in the boot2 command will match the hash of the split application (in slot 2). For example:

```
prompt$ newtmgr -c foo1 image boot2
   Test image: 55e254f133bedf640fc7be7b5bfe3e5fb387cf5e29ecd0d4ea02b5ba617e27e0
   Main image: 55e254f133bedf640fc7be7b5bfe3e5fb387cf5e29ecd0d4ea02b5ba617e27e0
   Active img: 1697bd1658f7e902e0191094c5f729446c9dd790c00a58e2bb37f56d6fcb72fe
```

## Upgrading a split image with newtmgr

When running via newt, the `newt load` command will load both parts of a split image, the loader and application.

When running via newtmgr a sequence of commands is required to upgrade.  Assuming you are running the split app in `run` mode the following sequence will upgrade

1. newtmgr split status none
2. newtmgr reboot
3. newtmgr image upload <filename of new loader>
4. newtmgr image boot2 <hash of new loader>
5. newtmgr reboot
6. newtmgr image upload <filename of new split app>
7. newtmgr split status test
8. newtmgr reboot
9. newtmgr boot2 (check status to ensure new app is running)
10. newtmgr split status run

This upgrade is robust.  In all steps there is a loader image that is capable of upgrading (or reverting) images.  


