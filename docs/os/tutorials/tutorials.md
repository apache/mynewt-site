## Tutorials

If the introduction to Mynewt has piqued your interest and you want to familiarize yourself with some of its functionality, this series of tutorials is for you. The lessons are aimed at the beginner.

The full list of tutorials can be seen in the navigation bar on the left. New ones are being constantly added and will show up there automatically.

<br>

###Prerequisites:

* You have installed Docker container of Newt tool and toolchains or you have installed them natively on your machine
* You have created a new project space (directory structure) and populated it with the core code repository (apache-mynewt-core) or know how to as explained in [Creating Your First Project](../get_started/project_create).
* You have at least one of the supported development boards:
    * [STM32F3 discovery kit from ST Micro](STM32F303.md)
    * [Arduino Zero hardware](arduino_zero.md)
    * [Olimex/STM32F407ZGT6 Cortex-M4 hardware](olimex.md)
    * [nRF52 Development Kit from Nordic Semiconductor](nRF52.md)

The Nordic nrf52 developer kit supports Bluetooth Low Energy. We are always looking to add new hardware to the list, so if you want to develop the required Board Support Package (bsp) and/or Hardware Abstraction Layer (HAL) for a new board, you can look [here](../core_os/porting/port_os/) to get started.


<br>

###Tutorial categories:

The tutorials fall into a few broad categories. Some examples in each category are listed below.

* Making an LED blink (the "Hello World" equivalent in the electronics world)
    * [Blinky on Arduino Zero hardware](arduino_zero.md)
    * [Blinky on Olimex/STM32F407ZGT6 Cortex-M4 hardware](olimex.md)
    * [Blinky on STM32F3 discovery kit from ST Micro](STM32F303.md)
    * [Blinky on nRF52 Development Kit from Nordic Semiconductor](nRF52.md) **Note:** This supports BLE.

    <br>

* Tweaking available apps to customize behavior e.g. making a more exciting LED blink pattern
    * [Pinwheel Blinky on STM32F3 discovery board](pin-wheel-mods.md)

    <br>

* Navigating the code and adding functionality  
    * [Adding more repositories to your project](repo/add_repos.md)
    * [Adding a unit test for a package](unit_test.md)
    * [Adding task to manage multiple events](event_queue.md)

<br>

* Bluetooth Low Energy
    * [Running the example BLE app included in the repo](bletiny_project.md)
    * [Working with another example BLE app for a peripheral device](bleprph/bleprph-intro.md)

<br>

* Using NewtMgr
    * [Enabling remote communication with a device running Mynewt OS](project-slinky.md)

<br>

* Additional network connectivity
    * [Connect Arduino to a Wi-Fi network](wi-fi_on_arduino.md)

**Send us an email on the dev@ mailing list if you have comments or suggestions!** If you haven't joined the mailing list, you will find the links [here](../../community.md).

<br>
