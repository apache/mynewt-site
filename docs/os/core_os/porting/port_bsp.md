
#Create a BSP for your Target

###Introduction

If you are using a board or system not currently supported by Mynewt, you will need to create a BSP for the new target.   If another similar BSP exists it is recommended to copy that BSP as a starting point.  For example, if another BSP exists using the same MCU, start with a copy of that BSP.

Either way, this document describes the steps necessary to create a new BSP from scratch.  

###Keep your Reference Documents handy

To build a proper BSP, you will typically need the following:

* The datasheet for the MCU you have chosen
* The schematic of your board
* The information on the CPU core within your MCU if it is not included in your MCU documentation
* This Mynewt documentation

###Name your BSP

Select a name for your BSP.  For the remainder of this document, we'll assume the bsp is named `myboard`. In general its best to select a name that describes the board/system you are creating.

###Create a BSP directory

Create a directory `hw/bsp/myboard` using the name chosen above. Within this BSP directory, create the following subdirectories:

Select a name for your BSP.  For the remainder of this document,
well assume the bsp is named `myboard`. In general its best to select a
name that describes the board/system you are creating.

* `include`
* `include/bsp`
* `src`

###Create a Target using Mynewt

Create a newt target for your test project for the BSP. To learn how to create a target, see this **howto** [Tutorial](../../get_started/project_create). Once you are familiar with creating targets, move on below to create a target to use to test your BSP.

It is recommended that you use a simple `project` like `blinky` to minimize time to get a working Mynewt system.  For this document, we will assume the `target` is called `myboard_blinky` and uses project `blinky`.  

Set the `bsp` of the project to `/hw/bsp/myboard`. While creating your target, you will need to specify your `arch`and `compiler`. If your platform requires an architecture or compiler that are not defined in Mynewt, you will need to add them first.  To add a CPU architecture see [CPU Porting](port_cpu.md).

When you are complete, your `target` may look similar to this.

```c
    $newt target show
        myboard_blinky
            arch=cortex_m0
            bsp=hw/bsp/myboard
            compiler=arm-none-eabi-m0
            compiler_def=debug
            name=myboard_blinky
            project=blinky
```

###Create Required Files For Compilation

Create the following files within the BSP directory tree. For now, they can be empty files. We will fill them out one at a time.

| **File Path Name** | **Description** |
|-----------|-------------|
| LICENSE   | A File to present the source license for your BSP |
| README.md | A markdown file to write documentation for your BSP |
| pkg.yml   | A package file to describe your BSP contents |
| include/bsp/bsp.h | A header file to include definitions required by system from the BSP |
| include/bsp/bsp_sysid.h | A header file to enumerate the devices in your BSP |
| src/os_bsp.c | A C source file to provide functions required by the OS from your BSP |
| src/sbrk.c | A C source file to memory from your heap to the OS |
| src/libc_stubs.c | A C source file to provide stubs/methods required by libc |
| myboard.ld | A linker script to provide the memory map for your linked code |

Optionally, create these files as necessary to provide all functionality from Mynewt.

| **File Path Name** | **Description** |
|-----------|-------------|
| myboard_boot.ld | A linker script to provide the memory map for your bootloader |
| myboard_download.sh | A bash script to download code into your platform |
| myboard_debug.sh | A bash script to intiate a gdb session with your platform |
| src/hal_bsp.c | A C source file to provide functions required by the HAL from your BSP |

###Fill Out your Package File

Edit the package file to describe your BSP.

The package file must contain:

```c
    pkg.name: "hw/bsp/myboard"
    pkg.linkerscript: "myboard.ld"
```

| **Attribute** | **Description** |
|-----------|-------------|
| pkg.name |  The name of your bsp package  |
| pkg.linkerscript |  The linker script that controls the memory placement of the compiled code sections from the Mynewt OS and your applications.   |

The linker script is a key component of the BSP and specifies where each section of code and data are stored within your CPU which can vary with the BSP depending on your chosen memory layout.  For a tutorial on writing linker scripts, see [Create or Copy Linker Script(s)](#create-or-copy-linker-script).

The package file typically contains:

```c
    pkg.linkerscript.bootloader.OVERWRITE: "myboard_boot.ld"
    pkg.downloadscript: "myboard_download.sh"
    pkg.debugscript: "myboard_debug.sh"
    pkg.deps:
    - hw/mcu/mymcu/variant
```
where `mymcu/variant` should be replaced with the specific MCU and variant used in your design.

The following table describes additional attributes relevant to the BSP `pkg.yml` file.

| **Attribute** | **Description** |
|-----------|-------------|
| pkg.linkerscript.bootloader.OVERWRITE |  A special linker for creating a bootloader for Mynewt |
| pkg.downloadscript |  A script that can download a flash image into your target platform |
| pkg.debugscript |  A script that can run the GDB debugger on your board |
| pkg.deps |  Any dependencies on your BSP |

The BSP will invariably depend upon an MCU ( in this sample it's `hw/mcu/mymcu/variant`) since the Mynewt OS runs on an MCU within your target.  If your MCU is not supported by Mynewt, see [MCU Porting](port_mcu.md) for details on how to create an MCU in Mynewt.

The package file may also contain:

```c
    pkg.cflags: -D__MY_SPECIAL_BSP_OPTIONS_
    pkg.deps:
    - libs/cmsis-core

```
| **Attribute** | **Description** |
|-----------|-------------|
| pkg.cflags | Any specific compiler flags for your bsp |
| pkg.deps | Any other libraries that may be required.  Some architectures (like ARM) have special libraries to make BSP creation easier. |

###Create or Copy Linker Script

It's probably best to start with a linker script from another BSP using the same MCU.  If this is not available, consult your MCU documentation and library samples to find a linker script to start with.

Typically, a linker script has to specify the following sections for code:

* .text -- the location and alignment of the memory section to store your code
* .data -- the location and alignment of the memory section to store initialized data
* .bss -- the location and alignment of the memory section to store uninitialized data
* .heap -- the location and alignment of the memory section to provide system memory

The linker script should specify the location and size of the different memory regions in your BSP and map the code sections described above into these regions.  

The linker script should also include an ENTRY point. This is used by the debugger to know where to start the program counter when the target is debugged.

There may be additional requirements from the MCU or OS that you may find easiest to place in the linker script. Some specific variables that the OS and MCU depends on are :

| **Variable** | **Description** |
|-----------|-------------|
|\__bss_start__ | a variable located at the start of the BSS section |
|\__bss_end__ | a variable located at the end of the BSS section |
|\__isr_vector | Some CPUs map their interrupt vectors. They may need to be specified in the linker |
|\_user_heap_start | the start of the heap for unallocated memory |
|\_user_heap_end | the end of the heap for unallocated memory |

Create an alternate linker script for the bootloader since it is typically linked to use different addresses to boot the main image.  

###Add Functions and Defines

At this point, it will be possible to run the `newt` tool to build your target.

You may run into complaints from the linker script that a few Mynewt specific functions are missing.  We will describe these below.

| **Function** | **Description** |
|-----------|-------------|
| os_bsp_init() | code to initialize the bsp |
| os_bsp_systick_init() | code to setup the system tick for the OS |

There are also several libc definitions that can be stubbed in your first BSP. Examples are `_write`, `_read`, etc. that can be found in `libc_stubs.c`. But you _must_ implement the following function to provide memory to the OS and system.

| **Function** | **Description** |
|-----------|-------------|
| _sbrk | Returns memory from heap (used by malloc) |

* Implement `_sbrk()`

`sbrk()` is required by libc to get memory from the heap for things like malloc. Although not strongly BSP dependent, this is currently in the BSP to allow  flexibility in providing system memory.  See other BSPs for providing `sbrk` functionality.

* Implement `os_bsp_init()`

`os_bsp_init` should initialize anything required by the OS by the BSP. Typically this is a very small set.  

NOTE: Currently we are making calls to `_sbrk()` and `close(0)` from `os_bsp_init` to get around a linker issue where some of libc is not getting included.  Please include this in your `os_bsp_init`.

```c
    /*
     * XXX these references are here to keep the functions in for libc to find.
     */
    _sbrk(0);
    _close(0);

```

* Other Unresolved Defines or Functions

There may be other unresolved defines or functions that are required by the specific MCU within your BSP. Below lists some sample defines.

| **Undefined Variable** | **Description** |
|-----------|-------------|
| CONSOLE_UART_PORT | Which communications port on your target runs the console |
| LED_BLINK_PIN |   which pin on your target runs the blinky LED |

The set of missing functionality depends upon the libraries and dependencies you have included in the project.  That's why its best to keep your first project pretty simple then add incrementally.  For example, if you include Newtron file system, you will need to define a file system map for your BSP.

Missing functionality may take the form of `#define` items required to compile, or they may take the form of missing functions.  

* `cmsis_nvic.h`

If you are using an ARM cortex architecture, you need to define the number of interrupts supported by your system.  If you are not using ARM Cortex architecture this may not be required (but something else might be).

###Add Debug Script

The debug script in the bsp directory allows the newt tool to automatically connect to the debugger, and create a debug session with the target.  This requires knowledge of your target debug interface. Most of the Mynewt BSP targets use [openocd](http://openocd.org) to perform debugging.  This script typically creates an openocd connection to the target and then connects a gdb instance to this openocd connection.  There are several examples in existing BSPs to follow.

The script must take a single argument which is the name of the image file minus the '.elf' suffix.

The BSP is complete without this file, but newt will be unable to establish a debug session without it.

###Add Download Script

Similar to the debug script, the download script is a hook for newt to download the image to the target system.  The download script also typically uses openocd interface to erase flash, and progam the code into the device.

NOTE: The download script needs to command openocd to program the image into the appropriate location, which is typically called `FLASH_OFFSET` in  these scripts. This location has to match the linker script location of the image link address.  For example, if your linker links the code to be run at `0xC000` your download script should download the image to the same
address in the correct flash.  

###Add License and Documentation

The `LICENSE` file is an ASCII text file that describes the source license for this
package.

The `README.md` is a [markdown](https://en.wikipedia.org/wiki/Markdown)
 file that contains any documentation you
want to provide for the BSP.
