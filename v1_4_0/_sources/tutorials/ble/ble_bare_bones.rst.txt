Set up a bare bones NimBLE application
=======================================

This tutorial explains how to set up a minimal application using the
NimBLE stack. It assumes that you have already installed the
newt tool and are familiar with its concepts.

.. contents::
  :local:
  :depth: 2

Create a Mynewt project
~~~~~~~~~~~~~~~~~~~~~~~

We start by creating a project space for your own application work using
the Newt tool. We will call our project ``my_proj``.

::

    ~/dev$ newt new my_proj1
    Downloading project skeleton from apache/mynewt-blinky...
    Installing skeleton in my_proj1...
    Project my_proj1 successfully created.

The above command created the following directory tree:

::

    ~/dev$ tree my_proj1
    my_proj1
    ├── DISCLAIMER
    ├── LICENSE
    ├── NOTICE
    ├── README.md
    ├── apps
    │   └── blinky
    │       ├── pkg.yml
    │       └── src
    │           └── main.c
    ├── project.yml
    └── targets
        ├── my_blinky_sim
        │   ├── pkg.yml
        │   └── target.yml
        └── unittest
            ├── pkg.yml
            └── target.yml

    6 directories, 11 files

Next, we need to retrieve the Mynewt repositories that our app will
depend on. When you retrieve a repository, your project gains access to
the libraries and applications that the repo contains.

A new project automatically depends on the Apache Mynewt core repo
(``apache-mynewt-core``). The core repo contains the Apache Mynewt
operating system, NimBLE stack, and other system libraries. Later, our
app may need packages from additional repos, but for now the core repo
suits our needs.

We download the dependent repos using the ``newt upgrade`` command:

::

    ~/dev$ cd my_proj1
    ~/dev/my_proj1$ newt upgrade
    Downloading repository mynewt-core (commit: master) ...
    apache-mynewt-core successfully upgraded to version 1.7.0

Now it's time to create your own app.

Create an application package
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    ~/dev/my_proj1$ newt pkg new apps/ble_app -t app
    Download package template for package type app.
    Package successfully installed into /home/me/dev/my_proj1/apps/ble_app.

You now have an application called ``apps/ble_app``. It isn't terribly
interesting as far as applications go, but it does all the configuration
and set up required of a Mynewt app. It will be a useful starting point
for our BLE application.

Create the target
~~~~~~~~~~~~~~~~~

Now you have to create the target that ties your application to a BSP.
We will call this target "ble\_tgt".

.. code-block:: console

    ~/dev/my_proj1$ newt target create ble_tgt
    Target targets/ble_tgt successfully created

We now have a new target:

::

    ~/dev/my_proj1]$ tree targets/ble_tgt
    targets/ble_tgt
    ├── pkg.yml
    └── target.yml

We need to fill out a few details in our target before it is usable. At
a minimum, a target must specify three bits of information:

-  Application pacakge
-  BSP package
-  Build profile

The application package is straightforward; this is the ble\_app package
that we created in the previous step.

For the BSP package, this tutorial chooses to target the nRF52dk BSP. If
you would like to use a different platform, substitute the name of the
appropriate BSP package in the command below.

Finally, the build profile specifies the set of compiler and linker
options to use during the build. Apache Mynewt supports two build
profiles: ``debug`` and ``optimized``.

.. code-block:: console

    ~/dev/my_proj1$ newt target set ble_tgt     \
        app=apps/ble_app                        \
        bsp=@apache-mynewt-core/hw/bsp/nordic_pca10040  \
        build_profile=optimized
    Target targets/ble_tgt successfully set target.app to apps/ble_app
    Target targets/ble_tgt successfully set target.bsp to @apache-mynewt-core/hw/bsp/nordic_pca10040
    Target targets/ble_tgt successfully set target.build_profile to optimized

Enter BLE
~~~~~~~~~

Since our application will support BLE functionality, we need to give it
access to a BLE stack. We do this by adding the necessary NimBLE
packages to the app's dependency list in ``apps/ble_app/pkg.yml``:

.. code-block:: console
    :emphasize-lines: 6,7,8

    pkg.deps:
        - "@apache-mynewt-core/kernel/os"
        - "@apache-mynewt-core/sys/console/full"
        - "@apache-mynewt-core/sys/log/full"
        - "@apache-mynewt-core/sys/stats/full"
        - "@apache-mynewt-nimble/nimble/host"
        - "@apache-mynewt-nimble/nimble/host/store/config"
        - "@apache-mynewt-nimble/nimble/transport"

To enable a combined host-controller in the app set correct transport which will include
NimBLE controller into build. For this update ``apps/ble_app/syscfg.yml``

.. code-block:: console

    syscfg.vals:
            BLE_HCI_TRANSPORT: builtin


**Important note:** The controller package affects system configuration,
see :doc:`this page <../../network/ble_setup/ble_lp_clock>` for
details.

Build the target
~~~~~~~~~~~~~~~~

Now would be a good time for a basic sanity check. Let's make sure the
target builds.

::

    ~/dev/my_proj1$ newt build ble_tgt
    Building target targets/ble_tgt
    Compiling repos/apache-mynewt-core/hw/hal/src/hal_common.c
    Compiling repos/apache-mynewt-core/hw/drivers/uart/src/uart.c
    <...snip...>
    Linking /home/me/dev/my_proj1/bin/targets/ble_tgt/app/apps/ble_app/ble_app.elf
    Target successfully built: targets/ble_tgt

Now let's try running our minimal application on actual hardware. Attach
the target device to your computer and run the application with
``newt run``:

::

    ~/dev/my_proj1$ newt run ble_tgt 0
    App image succesfully generated: /home/me/dev/my_proj1/bin/targets/ble_tgt/app/apps/ble_app/ble_app.img
    <...snip...>
    Resetting target
    [Switching to Thread 57005]
    0x000000dc in ?? ()
    (gdb)

You can start the application by pressing ``c <enter>`` at the gdb
prompt. When the excitement of watching the idle loop run wears off,
quit gdb with ``<ctrl-c> q <enter>``.

If your target fails to build or run, you might want to revisit the
:doc:`project blinky tutorial <../blinky/blinky>` to see if
there is a setup step you missed. You may also find help by posting a
question to the `mailing list </community.html>`__ or searching the
archives.

Conclusion
~~~~~~~~~~

You now have a fully functional BLE app (never mind that it doesn't
actually do anything yet!). With all the necessary infrastructure in
place, you can now start turning this into a real application. A good
next step would be to turn your app into a beaconing device. The :doc:`BLE
iBeacon tutorial <ibeacon>` builds on this one
and ends with a functioning iBeacon. For something a little more
ambitious, the :doc:`BLE peripheral project
tutorial <bleprph/bleprph>` describes a
NimBLE peripheral application in detail.
