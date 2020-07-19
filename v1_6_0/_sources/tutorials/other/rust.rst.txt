..
  #
  # Copyright 2020 Casper Meijn <casper@meijn.net>
  #
  # Licensed under the Apache License, Version 2.0 (the "License");
  # you may not use this file except in compliance with the License.
  # You may obtain a copy of the License at
  #
  #     http://www.apache.org/licenses/LICENSE-2.0
  #
  # Unless required by applicable law or agreed to in writing, software
  # distributed under the License is distributed on an "AS IS" BASIS,
  # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  # See the License for the specific language governing permissions and
  # limitations under the License.
  #

Rust Blinky application
===========================================

This tutorial shows you how to convert the Blinky application to Rust. This includes 
integrating Cargo into newt builder.

.. contents::
  :local:
  :depth: 2

Prerequisites
~~~~~~~~~~~~~

Ensure that you meet the following prerequisites before continuing with
this tutorial:

- You have basic knowledge about `Rust <https://doc.rust-lang.org/stable/book/>`__.
- You have basic knowledge about `Rust Embedded <https://rust-embedded.github.io/book/>`__.
- You have rust installed using `rustup <https://doc.rust-lang.org/stable/book/ch01-01-installation.html>`__.
-  Follow :doc:`Blinky tutorial <../blinky/blinky>` to create a 
   project with a basic application. You will extend that application in this 
   tutorial.

Initialize Rust
~~~~~~~~~~~~~~~

The first step is to initialize a crate for developing your application in. You
can do this in the existing `blinky` directory. 

.. code-block:: console

        $ cargo init --lib apps/blinky
        Created library package
        $ tree apps/blinky
        apps/blinky
        ├── Cargo.toml
        ├── pkg.yml
        └── src
            ├── lib.rs
            └── main.c

        1 directory, 4 files

This creates a Cargo.toml configuration file and src/lib.rs. We will use these 
files to place our application in. You may notice that the Rust application is
not configured as an app, but as an lib. This is needed later to allow linking
to the rest of mynewt.

Setup the basics
~~~~~~~~~~~~~~~~

Now we want to actually convert the application code to Rust. Let's open `src/lib.rs`
and remove the contents. Then start with some basic setup:

.. code-block:: rust

    #![no_std]

    extern crate panic_halt;

    #[no_mangle]
    pub extern "C" fn main() {

        loop {
        }
    }

The first line states that this program doesn't use the standard library. This
means that only the core library is linked to the program. See 
`rust-embedded book <https://rust-embedded.github.io/book/intro/no-std.html>`__ 
for more information.

The next line specifies the panic handler. Panicking is an important feature of
Rust. To ease this tutorial we choose to halt the processor on panic. See 
`rust-embedded book <https://docs.rust-embedded.org/book/start/panicking.html>`__
for alternatives.

Then we have the ``main`` function. It contains a endless loop as it should never
return, but doesn't do anything useful yet. It is marked ``no_mangle`` and ``extern "C"``
to make sure it can be called from the mynewt C code.

Converting sysinit
~~~~~~~~~~~~~~~~~~

The next step is to do the sysinit. This is implemented as a C macro, which is
incompatible with Rust. This could be solved by using a C library, but for this
tutorial we will simply execute the macro manually.

.. code-block:: rust
    :emphasize-lines: 3-7, 13-16

    #![no_std]

    extern "C" {
        fn sysinit_start();
        fn sysinit_app();
        fn sysinit_end();
    }

    extern crate panic_halt;

    #[no_mangle]
    pub extern "C" fn main() {
        /* Initialize all packages. */
        unsafe { sysinit_start(); }
        unsafe { sysinit_app(); }
        unsafe { sysinit_end(); }

        loop {
        }
    }

First we manually define the three sysinit functions. This is similar to the
C header file. Then we execute the sysinit as the macro would do. 

We need the ``unsafe`` indication because the C code doesn't have the same memory
guarantees as Rust. Normally we need to build a safe Rust wrapper, but that is 
out of scope for this tutorial.

Doing GPIO and delays
~~~~~~~~~~~~~~~~~~~~~

Now it is time to do some GPIO and add a delay. Again we define the functions 
and then use them in and around the loop. We need some constants that are 
normally defined by the BSP or MCU. These constants need to move to a better 
place later.

.. code-block:: rust
    :emphasize-lines: 7-9, 14, 16, 25, 28-29, 31-32

    #![no_std]

    extern "C" {
        fn sysinit_start();
        fn sysinit_app();
        fn sysinit_end();
        fn hal_gpio_init_out(pin: i32, val: i32) -> i32;
        fn hal_gpio_toggle(pin: i32);
        fn os_time_delay(osticks: u32);
    }

    extern crate panic_halt;

    const OS_TICKS_PER_SEC: u32 = 128;

    const LED_BLINK_PIN: i32 = 23;

    #[no_mangle]
    pub extern "C" fn main() {
        /* Initialize all packages. */
        unsafe { sysinit_start(); }
        unsafe { sysinit_app(); }
        unsafe { sysinit_end(); }

        unsafe { hal_gpio_init_out(LED_BLINK_PIN, 1); }

        loop {
            /* Wait one second */
            unsafe { os_time_delay(OS_TICKS_PER_SEC); }

            /* Toggle the LED */
            unsafe { hal_gpio_toggle(LED_BLINK_PIN); }
        }
    }

Cargo build
~~~~~~~~~~~

Now that the application is converted we need to build it and link it the rest of mynewt. We start with Cargo.toml:

.. code-block:: toml
    :emphasize-lines: 7-8, 10-11

    [package]
    name = "rust-klok"
    version = "0.1.0"
    authors = ["Casper Meijn <casper@meijn.net>"]
    edition = "2018"

    [dependencies]
    panic-halt = "0.2.0"

    [lib]
    crate-type = ["staticlib"]

This adds the ``panic-halt`` dependency, which is needed for the panic handler as 
mentioned earlier. It also configures the crate as staticlib, which causes the
application to be build as .a-library. This will be needed in a later step.

Next we need a script for running ``cargo`` and moving the library to the correct 
place. Create a new file named ``apps/blinky/cargo_build.sh`` with the following contents:

.. code-block:: bash
    :emphasize-lines: 1-21

    #!/bin/bash

    set -eu

    if [[ ${MYNEWT_VAL_ARCH_NAME} == '"cortex_m0"' ]]; then
      TARGET="thumbv6m-none-eabi"
    elif [[ ${MYNEWT_VAL_ARCH_NAME} == '"cortex_m3"' ]]; then
      TARGET="thumbv7m-none-eabi"
    elif [[ ${MYNEWT_VAL_ARCH_NAME} == '"cortex_m4"' || ${MYNEWT_VAL_ARCH_NAME} == '"cortex_m7"' ]]; then
      if [[ $MYNEWT_VAL_HARDFLOAT -eq 1 ]]; then
        TARGET="thumbv7em-none-eabihf"
      else
        TARGET="thumbv7em-none-eabi"
      fi
    else
      echo "The ARCH_NAME ${MYNEWT_VAL_ARCH_NAME} is not supported"
      exit 1
    fi

    cargo build --target="${TARGET}" --target-dir="${MYNEWT_PKG_BIN_DIR}"
    cp "${MYNEWT_PKG_BIN_DIR}"/${TARGET}/debug/*.a "${MYNEWT_PKG_BIN_ARCHIVE}"

The script first sets the name of the target as the Rust compiler knows it. Sadly
this is not the same as the names mynewt uses. You need to choose the same type of
compiler as mynewt uses. The following targets are available depending on the
MCU type:

* ``thumbv6m-none-eabi`` - use this for Cortex-M0 and Cortex-M0+.
* ``thumbv7m-none-eabi`` - use this for Cortex-M3.
* ``thumbv7em-none-eabi`` - use this for Cortex-M4 and Cortex-M7.
* ``thumbv7em-none-eabihf`` - use this for Cortex-M4 and Cortex-M7 with the
  ``HARDFLOAT`` syscfg enabled.

Then it runs ``cargo build`` with
the target directory set to a path that ``newt`` provides. Lastly it copies the 
generated library to the correct path.

Don't forget to mark the script as executable: 

.. code-block:: console

    $ chmod +x apps/blinky/cargo_build.sh 

Newt integration
~~~~~~~~~~~~~~~~

To automatically run ``cargo`` we need to add the following to pkg.yml:

.. code-block:: yaml
    :emphasize-lines: 3-4, 5-7

    ...

    pkg.pre_build_cmds:
        './cargo_build.sh': 1

    pkg.lflags:
        - '-Wl,--allow-multiple-definition'

The first section tells the mynewt build system to run ``cargo_build.sh`` as part 
of ``newt build``. The second section tells the linker to ignore double function
definitions. This is needed as the Rust compiler adds some functions that are
also in baselibc.

Now we are ready to build a firmware! Remove ``main.c`` and start the build:

.. code-block:: console

    $ rm apps/blinky/src/main.c
    $ newt build nrf52_blinky

If this command complains about a target may not be installed, then you need to 
install it. You need the same toolchain as configured earlier for the ``TARGET``
variable:

.. code-block:: console

    $ rustup target add <your-target>

Conclusion
~~~~~~~~~~

You now have a firmware where the application is written in Rust. It is nicely 
integrated into newt builder. However it still needs some work: it misses safe
Rust wrappers for the mynewt libraries and there are some magic constants that
need to be moved to a better location.
