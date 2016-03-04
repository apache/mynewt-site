## Concepts

### Application repository or app

The application repository (app) is the base directory of your embedded software. It is a workspace containing a logical collection of the source code for one or more of your [projects](#project). An app can contain multiple projects, and reflects multiple end products. 

As the base repository of your source code, the app has a master branch and several other branches off it. The `master` is typically what developers commit to. Just before your code is ready for a release, a code freeze should prevent all commits to the `master` branch. However, a temporary `develop` branch is opened up for contributors to continue committing their code. When the release is tagged off the `master`, the `develop` branch is merged into `master`. And after the `develop` merge to the `master`, developers may resume commiting changes to `master`, and the `develop` branch is subsequently deleted.

Alternatively, you may choose to create your own branch, specific to an individual developer, and work there.

You can have several [projects](#project) in your app repository, since an application can be used in several projects. Each project in your app will, in turn, consist of several [packages](#package-or-pkg). A project could be a package itself as well. In addition to packages, your app repository will contain additional items such as [target](#target) or build definitions, [package list](#package-list-or-pkg-list) description files, scripts etc.

For example, a walk through the main app at [https://github.com/apache/incubator-mynewt-larva](https://github.com/apache/incubator-mynewt-larva) shows the structure of the repository. The app.yml file in the larva directory indicates that it is an app. A pkg will have the pkg.yml file in it as shown below. By this nomenclature, each board support package for a particular chip is a pkg; for instance, the API for the hardware abstraction layer is a pkg, and so on. 

```no-highlight
larva
  |- app.yml 
  |- compiler
        |- arm-none-eabi-m0
        |- arm-none-eabi-m4
        |- sim
  |- hw (hardware)
        |- bsp (board support package)
                |- nrf52pdk (Nordic nRF52 series chip)
                        |- pkg.yml
                        |- ...
                |- olimex_stm32-e407_devboard (used in Project Blinky)
                        |- pkg.yml
                        |- ...
                |- nrf51dk
                        |- pkg.yml
                        |- ...
                |- yet another board
                        |- pkg.yml
                        |- ...
        |- hal (hardware abstraction layer APIs)
                |- pkg.yml
                |- include
                        |- hal_cputime.h
                        |- hal_flash.h
                        |- hal_gpio.h
                        |- ... (header files for other peripherals)
                |- src
                        |- flash_map.c
                        |- ... (other files)
        |- mcu (microcontroller)
                |- stm (STMicro family)
                    |- stm32f3xx (STM32f3 series, 32-bit ARM Cortex-M4  core)
                        |- pkg.yml
                        |- src
                            |- hal_gpio.c (specific to the STM32f3 mcu)
                            |- hal_cputime.c
                            |- ... (code for other peripherals)
                |- nordic (Nordic Semiconductor family)
                    |- nrf52xxx (nRF52 Series SoC, Cortex-M4F core)
                        |- pkg.yml
                        |- src
                            |- hal_gpio.c (specific to the nRF52 mcu )
                            |- hal_cputime.c
                            |- ... (code for other peripherals)
                |- yet another family of mcu
                    |- ...
  |- libs
        |- bootutil (hw architecture independent boot loader library)
                |- pkg.yml
                |- src
                    |- loader.c
                    |- ... (related source code files)
        |- nffs (hw architecture independent Newtron Flash File System)
                |- pkg.yml
                |- src
                    |- nffs.c
                    |- ... (related source code files)
        |- another library 
                |- pkg.yml
                |- src
                    |- ... (related source code files)
  |- project
  |- scripts
  |- net/nimble (BLE stack)
  |- ... (additional modules or stacks)


```

The *newt* tool offers the `app` sub command to create and manage apps. In general, commands represent actions, and flags act as modifiers for specfied actions. A *newt* command can have subcommands and it can optionally run an action. A full description of the `app` command can be found in the [Newt Tool Manual](../../newt/command_list/newt_app.md).

```no-highlight
    newt app [flags]
    newt app [child-commands] 
```
A complete list of all the app subcommands can be found in the *newt* tool reference in [Newt Tool](http://mynewt.apache.org/newt/command_list/newt_app/).

### Project

Projects represent individual build configurations of your embedded system and (individually or collectively) comprise your application. The project files dictate the generated binary. 

A project is laid out as a directory inside an app and contains required packages for an application. For example, the `blinky` pkg sits in `project/blinky` directory of the `larva` app. This pkg is used in the blinky project (an application) outlined in [Get Started](../get_started/project1.md).

Associated with each project are properties. These properties are defined in the`<project-name>.yml` file in the project directory. For example, the `project/blinky` directory has the `blinky.yml` file indicating some or all of the properties disscused below. Only the name of a project is required for the project to exist; however, additional properties may be specified for the pkgs within it to produce an executable. 

* Project name
* Base path of the project (app/project/project-name by default)
* Pkgs belonging to the project
* [Capabilities](#capabilities) that are required for the project or target 
* [Identity](#identity) to classify the type of project or target
* Compiler flags to call out any specific compiler requirements

Also, a project itself could be a pkg if it is a distributable package for a specific application. That is, the pkg can be resued in other apps as a bundle of libraries.

To work with pkgs, the *newt* tool offers management commands that you can use with your project. For example, if your project is a pkg, you can use the following command to install a project from an app.
```no-highlight
    newt pkg install [flags] <project pkg name>
```
Other commands assocated with pkg are:
```no-highlight
  newt pkg list
  newt pkg checkdeps
  newt pkg search <pkg-name>
  newt pkg show [<pkg-list> ] <pkg-name>
  newt pkg install [<pkg-list> ] <pkg-name>
  newt pkg remove [<pkg-list> ] <pkg-name>
```
### Package or pkg

A package (pkg) is a distributable bundle of libraries. Just as an egg in nature has various parts, each serving a certain purpose, a Mynewt app consists of software modules that have different functions. However, unlike the egg in nature these modules can exist by itself and may be distributed; therefore, they too are essentially eggs. Once this analogy is grasped it is easy to see how a pkg may consist of other pkgs.

The two main directories in a pkg are `/include` and `/src`.

The *newt* tool offers several pkg commands as shown above. For example, you can list all the pkgs
```no-highlight
    newt pkg list 
```
It lists all the pkgs in the current app where each pkg has details, such as version, path, and dependencies. A sample output for a pkg is given below:
```no-highlight
    Package: libs/os, version 0.1.0
    path: /Users/aditihilbert/dev/test_project/libs/os
    deps: libs/testutil@none#stable 
```
For a comprehensive list of all pkg commands, consult the *newt* tool reference in [Newt Tool](../../newt/newt_intro.md).

### Package list or pkg-list

A pkg-list is a snapshot of all pkgs in a remote app at any point in time. On any given github branch, an app with a pkg-list of pkgs will contain a `pkg-list.yml` file that specifies the version number, dependencies, and hash value for each constituent pkg as well as the name of the entire pkg-list and the github url for it. [Note: Currently ]

You may download multiple pkg-lists into your local app as long as the names of the pkg-lists are different. This allows you to mix and match various features and functionality coming from different pkg-lists of pkgs. You can see all the pkg-lists in the `.app/pkg-lists` directory in your app.

As with pkgs, the *newt* tool offers pkg-list management commands within the `newt app` command. For example, the following command creates a new pkg-list using all the pkgs in the current directory. It requires that a pkg-list name be specified and the url for the location of that pkg-list in the remote repository. These two inputs go into the `pkg-list.yml` file in an app.
```no-highlight
    newt app generate-pkg-list <pkg-list-name> <pkg-list-url>
```
**Note**: A pkg-list for a project stipulates all pkgs that belong together that must be installed as project's source code.

### Target

A target is the hardware build or its software equivalent (e.g. test, simulator) set for a project. Targets instruct the *newt* tool how to build the source code within a given app. Once a new target is created, its architecture and other details can be set manually. An example of a defined target named "blink_f3disc" is given below.
```no-highlight
    blink_f3disc
	         compiler_def: debug
	         compiler: arm-none-eabi-m4
	         name: blink_f3disc
	         arch: cortex_m4
	         project: blinky
	         bsp: hw/bsp/stm32f3discovery
```
To that end, *newt* tool offers commands to create, set and manipulate targets. For example, the create command below creates an empty target named `my_target1` and the set command sets one attribute of its definition, namely the architecture.
```no-highlight
    newt target create my_target1
    newt target set my_target1 arch=cortex_m4
```
### Capability

Capability, as the name suggests, is functionality that is exposed by a pkg. A capability is tracked by its name and version. In some cases, a pkg may require capabilities exposed by another pkg, thus establishing a dependency, which is tracked through the pkg.yml files. 

With *newt* tool you can verify a map of pkgs' capabilities, use it to check dependencies, and ensure all the necessary pkgs in a project belong to its target.

### Identity

Identity is a property of a target or project in the *newt* world. A target may inherit its identify from a project or vice versa. It may be used to determine what pkgs to include or how a pkg code should behave in a build or which linkerscripts to use. For example, the identity of a lock device is different from the identity of a wearable monitor. Even if they were built on the same hardware target, different features and behaviors are required. Because of this distinction, a distinct sets of pkgs in the projects and/or the same pkg will behave differently, depending on its identity.
