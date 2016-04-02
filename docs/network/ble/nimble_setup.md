## Set up a NimBLE application

This tutorial explains how to set up an application using the NimBLE stack. The end result will be a framework that you can use to create your own BLE application using the nimble stack.

This tutorial assumes that you have already installed the newt tool and are familiar with its concepts.


### Create the application directory

You start by creating a project space for your own application work using the Newt tool (`my_proj1` in this example) and installing all the additional apps and libraries available by adding the repo `apache-mynewt-core`. See the tutorial on [adding a repo](../../os/tutorials/add_repos.md) for more on working with repos.

```
$ newt new my_proj1
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in my_proj1...
Project my_proj1 successfully created.
$ tree
.
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
    
$ cd my_proj1
$ newt install
apache-mynewt-core
$ tree 
.
├── DISCLAIMER
├── LICENSE
├── NOTICE
├── README.md
├── apps
│   └── blinky
│       ├── pkg.yml
│       └── src
│           └── main.c
├── project.state
├── project.yml
├── repos
│   └── apache-mynewt-core
│       ├── DISCLAIMER
│       ├── LICENSE
│       ├── NOTICE
│       ├── README.md
│       ├── RELEASE_NOTES.md
│       ├── apps
│       │   ├── bleprph
│       │   │   └── src
│       │   │       ├── bleprph.h
│       │   │       ├── gatt_svr.c
│       │   │       └── main.c
│       │   ├── bletest
│       │   │   ├── pkg.yml
│       │   │   └── src
│       │   │       └── main.c
│       │   ├── bletiny
│       │   │   ├── pkg.yml
│       │   │   └── src
│       │   │       ├── bletiny_priv.h
│       │   │       ├── cmd.c
│       │   │       ├── main.c
│       │   │       ├── parse.c
│       │   │       └── periph.c
<snip>

232 directories, 846 files
```

<br>

It's time to build your own app using one or more of the example apps available in the repo `apache-mynewt-core`. 

```
$ ls repos/apache-mynewt-core/apps
bleprph		bletiny		boot		luatest		test
bletest		blinky		ffs2native	slinky
```

<br>

At the very least your app must contain a `main.c()` and a `pkg.yml` file. So copy the ones from `bletiny` and start enhancing it for your own custom use case!

<br>

### Create the target

Now you have to create the target that you will use to build your application. We will call this target "ble\_tgt". Type the `newt target create ble_tgt` command. You should get this:

```no-highlight
$ newt target create ble_tgt
Target targets/ble_tgt successfully created
```

What this command just did was to create a directory called `ble_tgt` in the targets directory of your project. Two files are created in that directory: pkg.yml and target.yml.

The target is not yet complete though! We need to set some target variables for this project. Currently, the nimble stack has been ported to the Nordic nrf5x chipsets; specifically the nrf51 and nrf52. This application will use the nrf52 but we will also show the setup for the nrf51 in case your project uses that chip.

Here is the command you will need to set up your target for the nrf52:

```no-highlight
$ newt target set ble_tgt app=apps/ble_app                              \
                          bsp=@apache-mynewt-core/hw/bsp/nrf52pdk       \
                          build_profile=optimized
Target targets/ble_tgt successfully set target.app to apps/ble_app
Target targets/ble_tgt successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52pdk
Target targets/ble_tgt successfully set target.build_profile to optimized
```

Here is the command you will need to set up your target for the nrf51:

```no-highlight
$ newt target set ble_tgt app=apps/ble_app                              \
                          bsp=@apache-mynewt-core/hw/bsp/nrf51dk        \
                          build_profile=optimized
Target targets/ble_tgt successfully set target.app to apps/ble_app
Target targets/ble_tgt successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf51dk
Target targets/ble_tgt successfully set target.build_profile to optimized
```

<br>


### Nimble stack initialization

There are certain stack initialization steps that are required for a BLE application to be up and running. If you are running a canned example (e.g. bletiny), these steps are already done for you. When you are writing your own app, you may want to assign different initial values or initialize additional packages that you may have added to your project or written yourself. 

Details of the initialization step requirements are covered in [Initialize Stack](ini_stack/ble_ini_intro.md) step.

<br>

### Building the application

Now that we have created the application and the target we can build it and test it out. The command you need to run is the newt build command with the target we created (ble\_tgt). The output will show the files being compiled and linked. You should see this when all is done (except for the ... of course):

```no-highlight
wes@~/dev/larva$ newt build ble_tgt
...
Archiving os.a
Compiling cons_fmt.c
Compiling cons_tty.c
Archiving full.a
Linking ble_app.elf
App successfully built: /Users/wes/dev/larva/bin/ble_tgt/apps/ble_app/ble_app.elf
```

### Conclusion

You now have a fully functional BLE app (never mind the fact that it doesn't
actually do anything yet!).  With all the necessary infrastructure in place,
you can now start turning this into a real applicaiton.  Additional tutorials
with focus on adding application-layer functionality to your Nimble application
will be coming soon.  In the meantime, you might get some inspiration from
apache-mynewt-core's example Nimble apps.  These apps can be found at the below locations, relative to your project's base directory:

* _repos/apache-mynewt-core/apps/bleprph_
* _repos/apache-mynewt-core/apps/bletiny_
