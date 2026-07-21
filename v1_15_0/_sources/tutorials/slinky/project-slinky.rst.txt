.. _slinky_tutorials:

Project Slinky
==============

.. toctree::
   :hidden:

   Slinky on Simulated device <project-sim-slinky>
   Slinky on nRF52 <project-nrf52-slinky>
   Slinky on Olimex <project-stm32-slinky>

The goal of the project is to use a sample application called "Slinky"
included in the Mynewt repository to enable remote communications with a
device running the Mynewt OS. The protocol for remote communications is
called newt manager (newtmgr).

If you have an existing project using a target that does not use the Slinky application and you wish to add newtmgr functionality to 
it, check out the tutorial titled :doc:`../devmgmt/add_newtmgr`

.. contents::
  :local:
  :depth: 2

Available Tutorials
~~~~~~~~~~~~~~~~~~~

Tutorials are available for the following boards:

-  :doc:`project-sim-slinky`. This is supported on Mac OS and Linux platforms.
-  :doc:`project-nrf52-slinky`.
-  :doc:`project-stm32-slinky`.

Prerequisites
~~~~~~~~~~~~~

Ensure that you meet the following prerequisites before continuing with
this tutorial:

-  Have Internet connectivity to fetch remote Mynewt components.
-  Have a computer to build a Mynewt application and connect to the
   board over USB.
-  Have a Micro-USB cable to connect the board and the computer.
-  Have a :doc:`serial port setup <../../../get_started/serial_access>`.
-  Install the newt tool and the toolchains (See :doc:`Basic Setup 
   <../../../get_started/index>`).
-  Install the :doc:`newtmgr tool <../../newtmgr/install/install_mac>`.
-  Read the Mynewt OS :doc:`Concepts <../../../concepts>` section.
-  Create a project space (directory structure) and populated it with
   the core code repository (apache-mynewt-core) or know how to as
   explained in :doc:`Creating Your First Project 
   <../../../get_started/project_create>`.

Overview of Steps
~~~~~~~~~~~~~~~~~

-  Install dependencies.
-  Define the bootloader and Slinky application target for the target
   board.
-  Build the bootloader target.
-  Build the Slinky application target and create an application image.
-  Set a up serial connection with the targets.
-  Create a connection profile using the newtmgr tool.
-  Use the newtmgr tool to communicate with the targets.
