.. _blinky_tutorials:

Project Blinky
==============

.. toctree::
   :hidden:

   Blinky on Arduino Zero <arduino_zero>
   Blinky on Arduino Primo <blinky_primo>
   Blinky on Olimex <olimex>
   Blinky on nRF52 DK <nRF52>
   Blinky on PineTime <pinetime>
   Blinky on RedBear Nano 2 <rbnano2>
   Blinky on STM32F4-Discovery <blinky_stm32f4disc>
   Add Console and Shell to Blinky <blinky_console>

The set of Blinky tutorials show you how to create, build, and run a
"Hello World" application that blinks a LED on the various target boards
that Mynewt supports. The tutorials use the same Blinky application from
the :doc:`../../get_started/project_create` tutorial.

.. contents::
  :local:
  :depth: 2

Objective
~~~~~~~~~

Learn how to use packages from a default application repository of
Mynewt to build your first *Hello World* application (Blinky) on a
target board. Once built using the *newt* tool, this application will
blink a LED light on the target board.

Available Tutorials
~~~~~~~~~~~~~~~~~~~

Tutorials are available for the following boards:

-  :doc:`arduino_zero`
-  :doc:`blinky_primo`
-  :doc:`olimex`
-  :doc:`nRF52`
-  :doc:`pinetime`
-  :doc:`rbnano2`
-  :doc:`blinky_stm32f4disc`

We also have a tutorial that shows you how to add :doc:`blinky_console`.

Prerequisites
~~~~~~~~~~~~~

Ensure that you meet the following prerequisites before
continuing with one of the tutorials.

-  Have Internet connectivity to fetch remote Mynewt components.
-  Have a computer to build a Mynewt application and connect to the
   board over USB.
-  Have a Micro-USB cable to connect the board and the computer.
-  Install the newt tool and toolchains (See :doc:`../../get_started/index`).
-  Read the Mynewt OS :doc:`../../concepts` section.
-  Create a project space (directory structure) and populate it with the
   core code repository (apache-mynewt-core) or know how to as explained
   in :doc:`../../get_started/project_create`.

Overview of Steps
~~~~~~~~~~~~~~~~~

These are the general steps to create, load and run the Blinky application on your board:

-  Create a project.
-  Define the bootloader and Blinky application targets for the board.
-  Build the bootloader target.
-  Build the Blinky application target and create an application image.
-  Connect to the board.
-  Load the bootloader onto the board.
-  Load the Blinky application image onto the board.
-  See the LED on your board blink.

After you try the Blinky application on your boards, checkout out other
tutorials to enable additional functionality such as :doc:`remote
comms <../slinky/project-slinky>` on the current board. If you have BLE
(Bluetooth Low Energy) chip (e.g. nRF52) on your board, you can try
turning it into an :doc:`iBeacon <../ble/ibeacon>` or :doc:`Eddystone
Beacon <../ble/eddystone>`!

If you see anything missing or want to send us feedback, please sign up
for appropriate mailing lists on our `Community
Page </community>`__.
