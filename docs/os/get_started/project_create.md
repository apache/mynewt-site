# Creating a Mynewt Project

This page shows how to create a Mynewt Project using `newt`

# Pre-Requisites

* Ensure you have installed [newt](../../newt/newt_intro) and that the 
newt command is in your system path.
* You must have Internet connectivity to fetch remote Mynewt components
* You must [install the compiler tools](project1.md) to 
support native compiling to build the project this tutorial creates.  

## Newt New

Chose a project name. For this tutorial we will call this project `myproj`.
Enter the `newt new myproj` command. Your put
```no-highlight
$ newt new myproj

Downloading project skeleton from apache/incubator-mynewt-blinky...
Downloading repository incubator-mynewt-blinky (branch: develop) at https://github.com/apache/incubator-mynewt-blinky.git
Cloning into '/var/folders/x0/1yjkfd_93j79r64d2vf104d40000gp/T/newt-repo290518149'...
remote: Counting objects: 727, done.
remote: Compressing objects: 100% (29/29), done.
remote: Total 727 (delta 7), reused 0 (delta 0), pack-reused 696
Receiving objects: 100% (727/727), 201.64 KiB | 0 bytes/s, done.
Resolving deltas: 100% (329/329), done.
Checking connectivity... done.
Installing skeleton in myproj...
Project myproj successfully created
```

The `newt` tool has created a project directory structure like the one below:

```no-highlight
─── myproj
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
```

`newt` has installed the base files for a project comprising the following.

1. file `project.yml` contains the repository list that the project uses to fetch
its packages. Your project is a collection of repositories.  In this case, the project just
comprises the core mynewt repository.  Later you will add more repositories
to include other mynewt components.
2. the file `apps/blinky/pkg.yml` contains the description of your application
and its package dependencies.
3.  A target directory containing `my_blinky_sim`, a target descriptor used to
build a version of myproj.  Use `newt target show` to see available build 
targets.
4. A non-build-able target called `unittest`.  This is used
internally by `newt` and is not a formal build target.

 NOTE: the actual code and package files are not installed 
(except the template for `main.c`.  See the next step for installing 
the packages.

## Newt Install

change into the `myproj` directory.  Then ask newt to install all the 
project package dependencies using `newt install`

```no-highlight
$ newt install

Downloading repository description for apache-mynewt-core... success!
Downloading repository incubator-mynewt-core (branch: develop) at https://github.com/apache/incubator-mynewt-core.git
Cloning into '/var/folders/x0/1yjkfd_93j79r64d2vf104d40000gp/T/newt-repo379645046'...
remote: Counting objects: 17684, done.
remote: Compressing objects: 100% (377/377), done.
remote: Total 17684 (delta 190), reused 0 (delta 0), pack-reused 17284
Receiving objects: 100% (17684/17684), 6.11 MiB | 2.19 MiB/s, done.
Resolving deltas: 100% (10395/10395), done.
Checking connectivity... done.
Repos successfully installed
$ 
```

Now you will have installed packages required to build your project. Note in 
the package you now have dependent packages stored in the `repos` directory
under the specific repository you have included in the base project.  

```no-highlight
.
├── apps
│   └── blinky
│       └── src
├── repos
│   └── apache-mynewt-core
│       ├── apps
│       ├── compiler
│       ├── fs
│       ├── hw
│       ├── libs
│       ├── net
│       ├── scripts
│       ├── sys
│       └── targets
└── targets
    ├── my_blinky_sim
    └── unittest
```

Within each of these directories are the packages required to build your
project for the various targets.

## Testing the Project

To validate, you can also run all the units test through simulation.

```no-highlight
newt test all
...lots of compiling and testing...
...about 2 minutes later ...
Archiving bootutil.a
Linking test_bootutil
Executing test: /myproj/bin/unittest/libs/bootutil/test_bootutil
Passed tests: [net/nimble/host fs/nffs libs/os hw/hal libs/mbedtls libs/util sys/config libs/bootutil]
All tests passed
```

## Building the Project

To build the project you can use `newt build` using the target 

```no-highlight
$ newt build targets/my_blinky_sim
App successfully built: /bin/my_blinky_sim/apps/blinky/blinky.elf
```

You can run the simulated version of your project and see the simulated LED
blink
```no-highlight
./bin/my_blinky_sim/apps/blinky/blinky.elf
hal_gpio set pin  1 to 0
```

Just do `ctrl-c` to exit.

## Complete

Congratulations, you have created your first project.  This project contains 
the core OS, a simple application to blink an LED and all of the dependencies
required.