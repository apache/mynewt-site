## Introduction

### What is Apache Mynewt?

Apache Mynewt is an Operating System for Microcontrollers (MCUs.) 

Apache Mynewt is very well suited for developing constrained IoT 
devices.  Typical use cases for Apache Mynewt include:

* Lights 
* Locks
* Wearables


### Basic components in the ecosystem

* NewtOS is an open-source RTOS (Real Time Operating System) that
works on a variety of hardware. The goal is to develop a pre-emptive,
multitasking OS that is highly modular, making it possible to mix
and match components to enable desired features and capabilities
on multiple hardware architectures. Examples of components being
worked on are the Core RTOS, a flash file system, utility functions,
a variety of board support packages, packages of microcontrollers
etc.


* Network protocol stacks such as Bluetooth Low Energy, and more


* Newt Tool helps you mix the specific packages for the combination
of hardware and low-level embedded architecture features of the
user's choice and generate the corresponding run-time image based
on the NewtOS. It provides the infrastructure to manage and build
for different CPU architectures, memory units, board support packages
etc., allowing a user to formulate the contents according to the
low-level features needed by his or her project.


### Terminology

A Mynewt user starts with a project in mind that defines the
application or utility that he or she wants to implement on an
embedded device. Making an LED blink on an electronics prototyping
board is a common starter project. Enabling a BLE (Bluetooth Low
Energy) peripheral mode on a development board is a more complex
project. Specifying a project requires naming it, at the very least,
and then adding the desired properties or attributes. In order to
actualize a project, it needs to be applied to a target which is
essentially a combination of some specified hardware and the execution
environment.

In the mynewt lifecycle, a project grows in a nest. A nest may house
multiple projects. The nest is, therefore, a repository where various
component packages for one or more projects reside. Each package
is an egg (naturally!). However, in the world of Mynewt an egg may
consist of other eggs! For example, the starter project Blinky is
an egg consisting of several constituent eggs that enable core
features. The egg form is suitable for elemental units of code as
it explicitly exposes characteristics such as dependencies, versions,
capabilities, requirements etc., thus making assembling appropriate
components for a project and building an image for it easy to follow,
modular, and robust.

A nest can be given any name. For example, you will see a nest named
"tadpole" in Mynewt
([https://git-wip-us.apache.org/repos/asf?p=incubator-mynewt-tadpole.git](https://git-wip-us.apache.org/repos/asf?p=incubator-mynewt-tadpole.git)).
It contains all the core libraries of the operating system for the
native platform which currently supports compilation on Mac OS X.
The core libraries are contained in the form of eggs where an egg
is a basic unit of implementation of any aspect of the RTOS. The
eggs are distributed in the following directory structure inside
the nest:

* libs: contains the two eggs `os` and `testutil` * hw: contains
three eggs - (i) `hal` which has the abstraction layer (HAL) API
definitions that all BSP and MCU implementations must support, (ii)
`/mcu/native` which in an MCU implementation for the native platform
(a simulator, in this case), and (iii) `bsp/native` which is a BSP
implementation for the native platform * compiler: contains the
`sim` egg which bundles the compiler specifications for the native
platform.

Let's explore this sample nest a bit further. The `libs/os` egg
contains code for scheduler, process/thread/memory management,
semaphores etc. It is the core RTOS which ports to all supported
chip platforms.The `libs/testutil` egg contains code for testing
packages on hardware or simulated environment. The `hw/hal` egg
contains header files that provide abstraction for physical hardware
components such as GPIO (general purpose input/output), network
adapters, timers, and UARTs. This `hw/hal` egg is an MCU peripheral
abstraction designed to make it easy to port to different MCUs
(microcontrollers). The `hw/mcu/native` egg contains code for
microcontroller operations on the native platform. The `hw/bsp/native`
egg contains the board support package for the native platform. And
finally, the sixth egg `sim` contains the compiler specifications
such as path and flags. Currently the compilation is supported on
Mac OS X.

You can see another nest in the mynewt ecosystem called the "larva".
It was spawned from the skeletal "tadpole" nest using the newt tool.
Spawning is easy - ` $ newt create nest <your_nest_name> `. "larva"
is the developer's test repository containing all sorts of eggs
being written and incubated, including ones to enhance the core
operating system which should eventually make their way into the
"tadpole" nest. There is a `hatch_tadpole` script to update the
"tadpole" nest when the core OS related eggs in "larva" are ready.

There is a third nest named "newt" that contains all the eggs needed
to support the build and release process of mynewt software. In the
future, there will also be pre-built nests for certain common
hardware devices to enable a user to quickly get started with a
project.

