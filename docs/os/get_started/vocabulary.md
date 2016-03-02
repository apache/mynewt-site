## Glossary

### Application workspace or app

The application workspace (app) is the base directory of your embedded software. It is meant to be the workspace containing a logical collection of the source code for one or more of your projects. An app can contain multiple projects, and reflect multiple end products. 

As the base repository of your source code, the app has a master branch and several other branches off it. The `master` is typically what developers commit to. When it is time to get the code ready for a release, a code freeze occurs on the `master` branch. A temporary `develop` branch is opened up for contributors to continue committing their code to. After the release is tagged off the `master`, the `develop` branch is merged into `master`. Developers can thereafter go back to commiting changes to `master`. The `develop` branch is subsequently deleted. You may also choose to create your own branch and work there.

You can have several [projects](#project) in your app repository since an application can be used in several projects. Each project in your app will, in turn, consist of several [packages or pkgs](#package-or-pkg). A project could be a package (pkg) itself as well. In addition to pkgs, your app repository will contain additional items such as [target](#target) or build definitions, [package list or pkg-list](#package-list-or-pkg-list) description files, scripts etc.

<br> 

A walk through the "larva" app at [https://github.com/mynewt/larva.git](https://github.com/mynewt/larva.git) shows you all the different files involved. The app.yml file in the larva directory indicates that it is an app. Pkgs such as fs (file system), nimble (BLE stack), blinky (project), log, stats etc. each has a pkg.yml file. Each board support package for a particular chip is a pkg, the API for the hardware abstraction layer is a pkg, and so on. 


The newt tool offers the `app` command to create and manage apps. In general, commands represent actions and flags are modifiers for those actions. A command can have children commands and optionally run an action. A full description of the `app` command can be found in the command list in the [Newt Tool Manual](../../newt/command_list/newt_app.md).
```no-highlight
    newt app [flags]
    newt app [child-commands] 
```


### Project

Projects represent the individual build configurations of your embedded system and essentially defines your application. The project files are what dictate the resulting binary that is generated. 

Layout-wise, a project is a directory inside an app and contains packages required for a certain application. For example, the `blinky` pkg sits in `project/blinky` directory of the `larva` app. This pkg is used in the blinky project (application) outlined in [Get Started](../get_started/project1.md). 

A project has the following concepts or properties associated with it. You can find them in the `<project-name>.yml` file in the project directory. For example, the `project/blinky` directory has the `blinky.yml` file indicating some or all of the properties below. Only the name of a project is required for the project to exist, however additional properties may need to be specified for the pkgs in it to compile properly and produce an executable. 

* Project name
* Base path of the project (app/project/project-name by default)
* pkgs belonging to the project
* [Capabilities](#capabilities) that are required for the project or target 
* [Identity](#identity) to classify the type of project or target
* Compiler flags to call out any specific compiler requirement

A project could itself be a pkg if it is a distributable package for a specific application. 

The newt tool offers various commands that you can use with a project. For example, if your project is a pkg, you can use the following command to install a project from an app.
```no-highlight
    newt pkg install [flags] <project pkg name>
```
### Package or pkg

A package (pkg) is a distributable bundle of libraries. Just as a pkg in nature has various parts each of which serves a certain purpose, the Mynewt pkg consists of software parcels or modules that have different functions. However, unlike the pkg in nature these software modules can exist by itself and may be distributed; therefore, they too are essentially pkgs. Once this concept is grasped it is easy to see how a pkg may consist of other pkgs.

The two main directories in a pkg are `/include` and `/src`.

The newt tool offers several pkg commands to list, inspect, install, and do other operations on pkgs. For example, the following command
```no-highlight
    newt pkg list 
```
outputs all the pkgs in the current app where each pkg has details on its version, path, and dependencies. A sample output for a pkg is given below.
```no-highlight
    pkg libs/os, version 0.1.0
    path: /Users/aditihilbert/dev/test_project/libs/os
    deps: libs/testutil@none#stable 
```
A complete list of all the pkg commands can be found in the newt tool command list in [Newt Tool Manual](../../newt/command_list/newt_pkg.md).

### Package list or pkg-list

A pkg-list is a snapshot of all pkgs in a remote app at any point in time. On any given github branch, an app with a pkg-list of pkgs will contain a `pkg-list.yml` file that specifies the version number, dependencies, and hash value for each constituent pkg as well as the name of the entire pkg-list and the github url for it. [Note: Currently ]

You may download multiple pkg-lists into your local app as long as the names of the pkg-lists are different. This allows you to mix and match various features and functionality coming from different pkg-lists of pkgs. You can see all the pkg-lists in the `.app/pkg-lists` directory in your app.

The newt tool offers pkg-list management commands within the `newt app` command. For example, the following command creates a new pkg-list using all the pkgs in the current directory. It requires that a pkg-list name be specified and the url for the location of that pkg-list in the online repository. These two inputs go into the `pkg-list.yml` file in the app.
```no-highlight
    newt app generate-pkg-list <name> <url>
```
Note that a pkg-list merely defines the pkgs belonging together and requires the pkgs to be installed for the source code to be populated in the project. 


### Target

A target is the hardware build or its software equivalent (e.g. test, simulator) set for a project. It tells the newt tool how to build the source code within a given app. Once a new target is created, its architecture and other details needs to be defined. An example of a defined target named "blink_f3disc" is given below.
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

Capability is functionality that is exposed by a pkg. A capability is tracked by its name and version. a pkg may require capabilities exposed by another pkg, thus establishing a dependency tracked through the pkg.yml files. 

The newt tool can ascertain a map of all the pkg capabilities and use it to check dependencies and make sure all the necessary pkgs are in a project for a particular target.

### Identity

Identity is a property of a target or project in the newt world. A target may inherit it from a project or vice versa. It may be used to determine what pkgs to include or how a pkg code should behave in a build or which linkerscripts to use. For example, the identity of a lock is different from the identity of a wearable monitor. Even if they were to be built on the same hardware target, different features and behavior are required. Their different identities result in differing sets of pkgs in the projects and/or the same pkg behaving differently depending on the identity.
