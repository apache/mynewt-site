## Understanding Newt Terms

### Nest

The nest is the base directory of your embedded software. It is meant to be the workspace containing a logical collection of the source code for one or more of your projects. A nest can contain multiple projects, and reflect multiple end products. 

As the base repository of your source code, the nest has a master branch and several other branches off it. You may choose any branch to nest on. Each project in your nest will typically consist of several [eggs](#egg). A project could be an egg itself as well. In addition to eggs, a local nest will contain additional items such as [target](#target) or build definitions, clutch description files, scripts etc.

For example, a walk through the "larva" nest at [https://github.com/mynewt/larva.git](https://github.com/mynewt/larva.git) shows the following structure. The nest.yml file in the larva directory indicates that it is a nest. An egg will have the egg.yml file in it as shown below. By this nomenclature, each board support package for a particular chip is an egg, the API for the hardware abstraction layer is an egg, and so on. 

```no-highlight
larva
  |- nest.yml 
  |- compiler
        |- arm-none-eabi-m4
        |- sim
  |- hw (hardware)
        |- bsp (board support package)
                |- nrf52pdk (Nordic nRF52 series chip)
                        |- egg.yml
                        |- ...
                |- olimex_stm32-e407_devboard (used in Project Blinky)
                        |- egg.yml
                        |- ...
                |- stm32f3discovery (another board with stm32f3 mcu)
                        |- egg.yml
                        |- ...
                |- yet another board
                        |- egg.yml
                        |- ...
        |- hal (hardware abstraction layer APIs)
                |- egg.yml
                |- include
                        |- hal_cputime.h
                        |- hal_flash.h
                        |- hal_gpio.h
                        |- ... (header files for other peripherals)
        |- mcu (microcontroller)
                |- stm (STMicro family)
                    |- stm32f3xx (STM32f3 series, 32-bit ARM Cortex-M4  core)
                        |- egg.yml
                        |- src
                            |- hal_gpio.c (specific to the STM32f3 mcu)
                            |- hal_cputime.c
                            |- ... (code for other peripherals)
                |- nordic (Nordic Semiconductor family)
                    |- nrf52xxx (nRF52 Series SoC, Cortex-M4F core)
                        |- egg.yml
                        |- src
                            |- hal_gpio.c (specific to the nRF52 mcu )
                            |- hal_cputime.c
                            |- ... (code for other peripherals)
                |- yet another family of mcu
                    |- ...
  |- libs
        |- bootutil (hw architecture independent boot loader library)
                |- egg.yml
                |- src
                    |- loader.c
                    |- ... (related source code files)
        |- nffs (hw architecture independent Newtron Flash File System)
                |- egg.yml
                |- src
                    |- nffs.c
                    |- ... (related source code files)
        |- another library 
                |- egg.yml
                |- src
                    |- ... (related source code files)
  |- project
  |- scripts


```

The newt tool offers the `nest` command to create and manage nests. In general, commands represent actions and flags are modifiers for those actions. A command can have children commands and optionally run an action. A full description of the `nest` command can be found in the newt tool reference in Chapter 3.
```no-highlight
    newt nest [flags]
    newt nest [child-commands] 
```
A complete list of all the nest commands can be found in the newt tool reference in [Newt Tool](../../newt/newt_tool_reference.md).

### Project

Projects represent the individual build configurations of your embedded system and essentially defines your application. The project files are what dictate the resulting binary that is generated. 

Layout-wise, a project is a directory inside a nest and contains eggs required for a certain application. For example, the `blinky` egg sits in `project/blinky` directory of the `larva` nest. This egg is used in the blinky project (application) outlined in [Get Started](../get_started/project1.md). <*Note: This Will Change*>

A project has the following concepts or properties associated with it. You can find them in the `<project-name>.yml` file in the project directory. For example, the `project/blinky` directory has the `blinky.yml` file indicating some or all of the properties below. Only the name of a project is required for the project to exist, however additional properties may need to be specified for the eggs in it to compile properly and produce an executable. 

* Project name
* Base path of the project (nest/project/project-name by default)
* Eggs belonging to the project
* [Capabilities](#capabilities) that are required for the project or target 
* [Identity](#identity) to classify the type of project or target
* Compiler flags to call out any specific compiler requirement

A project could itself be an egg if it is a distributable package for a specific application. 

The newt tool offers various commands that you can use with a project. For example, if your project is an egg, you can use the following command to install a project from a nest.
```no-highlight
    newt egg install [flags] <project egg name>
```
### Egg

An egg is a distributable package of libraries. Just as an egg in nature has various parts each of which serves a certain purpose, the Mynewt egg consists of software parcels or modules that have different functions. However, unlike the egg in nature these software modules can exist by itself and may be distributed; therefore, they too are essentially eggs. Once this concept is grasped it is easy to see how an egg may consist of other eggs.

The two main directories in an egg are `/include` and `/src`.

The newt tool offers several egg commands to list, inspect, install, and do other operations on eggs. For example, the following command
```no-highlight
    newt egg list 
```
outputs all the eggs in the current nest where each egg has details on its version, path, and dependencies. A sample output for an egg is given below.
```no-highlight
    Egg libs/os, version 0.1.0
    path: /Users/aditihilbert/dev/test_project/libs/os
    deps: libs/testutil@none#stable 
```
A complete list of all the egg commands can be found in the newt tool reference in [Newt Tool](../../newt/newt_tool_reference.md).

### Clutch

A clutch is a snapshot of all eggs in a remote nest at any point in time. On any given github branch, a nest with a clutch of eggs will contain a `clutch.yml` file that specifies the version number, dependencies, and hash value for each constituent egg as well as the name of the entire clutch and the github url for it. [Note: Currently ]

You may download multiple clutches into your local nest as long as the names of the clutches are different. This allows you to mix and match various features and functionality coming from different clutches of eggs. You can see all the clutches in the `.nest/clutches` directory in your nest.

The newt tool offers clutch management commands within the `newt nest` command. For example, the following command creates a new clutch using all the eggs in the current directory. It requires that a clutch name be specified and the url for the location of that clutch in the online repository. These two inputs go into the `clutch.yml` file in the nest.
```no-highlight
    newt nest generate-clutch <name> <url>
```
Note that a clutch merely defines the eggs belonging together and requires the eggs to be installed (hatched) for the source code to be populated in the project. 

### Eggshell

The term eggshell is used to refer to the eggs of a clutch in a remote repository. They are not useful on your local machine until you actually install them. So they are mere shells of themselves while sitting on the online repository. When you enter the following command outputs the total number of shells in each remote clutch.
```no-highlight
    newt nest list-clutches
```
So, if you had two clutches installed, the output could be:
```no-highlight
    Remote clutch larva (eggshells: 19)
    Remote clutch ble_test (eggshells: 15)
```    
### Target

A target is the hardware build or its software equivalent (e.g. test, simulator) set for a project. It tells the newt tool how to build the source code within a given nest. Once a new target is created, its architecture and other details needs to be defined. An example of a defined target named "blink_f3disc" is given below.
```no-highlight
    blink_f3disc
	         compiler_def: debug
	         compiler: arm-none-eabi-m4
	         name: blink_f3disc
	         arch: cortex_m4
	         project: blinky
	         bsp: hw/bsp/stm32f3discovery
```
The newt tool offers commands to create, set up and manipulate targets. For example, the create command below creates an empty target named `my_target1` and the set command sets one detail of its definition, namely the architecture.
```no-highlight
    newt target create my_target1
    newt target set my_target1 arch=cortex_m4
```
### Capability

Capability is functionality that is exposed by an egg. A capability is tracked by its name and version. An egg may require capabilities exposed by another egg, thus establishing a dependency tracked through the egg.yml files. 

The newt tool can ascertain a map of all the egg capabilities and use it to check dependencies and make sure all the necessary eggs are in a project for a particular target.

### Identity

Identity is a property of a target or project in the newt world. A target may inherit it from a project or vice versa. It may be used to determine what eggs to include or how an egg code should behave in a build or which linkerscripts to use. For example, the identity of a lock is different from the identity of a wearable monitor. Even if they were to be built on the same hardware target, different features and behavior are required. Their different identities result in differing sets of eggs in the projects and/or the same egg behaving differently depending on the identity.
