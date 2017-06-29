## Set up a NimBLE application

This tutorial explains how to set up an application using the NimBLE stack. The
end result will be a framework that you can use to create your own BLE
application using the nimble stack.

This tutorial assumes that you have already installed the newt tool and are
familiar with its concepts.

### Create a Mynewt project

You start by creating a project space for your own application work using the
Newt tool (`my_proj1` in this example) and installing all the additional apps
and libraries available by adding the repo `apache-mynewt-core`. See the
tutorial on [adding a repo](../../os/tutorials/repo/add_repos.md) for more on
working with repos.

```
~/dev$ newt new my_proj1
Downloading project skeleton from apache/incubator-mynewt-blinky...
Installing skeleton in my_proj1...
Project my_proj1 successfully created.
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
    
~/dev$ cd my_proj1
~/dev/my_proj1$ newt install
apache-mynewt-core
```

Now it's time to create your own app.

### Create an application package

```no-highlight
~/dev/my_proj1$ newt pkg new apps/ble_app -t app
Download package template for package type app.
Package successfully installed into /home/me/dev/my_proj1/apps/ble_app.
```

You now have an application called `apps/ble_app`.  It isn't terribly
interesting as far as applications go, but it does all the configuration and
set up required of a Mynewt app.  It will be a useful starting point for our
BLE application.

### Create the target

Now you have to create the target that ties your application to a BSP.  We will
call this target "ble\_tgt".

```no-highlight
~/dev/my_proj1$ newt target create ble_tgt
Target targets/ble_tgt successfully created
```

We now have a new target:

```
~/dev/my_proj1]$ tree targets/ble_tgt
targets/ble_tgt
├── pkg.yml
└── target.yml
```

The target is not yet complete though! We need to set some target variables for
this project. Currently, the nimble stack has been ported to the Nordic nrf5x
chipsets; specifically the nrf51 and nrf52. This application will use the nrf52
but we will also show the setup for the nrf51 in case your project uses that
chip.

Here is the command you will need to set up your target for the nRF52dk:

```no-highlight
~/dev/my_proj1$ newt target set ble_tgt     \
    app=apps/ble_app                        \
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk  \
    build_profile=optimized
Target targets/ble_tgt successfully set target.app to apps/ble_app
Target targets/ble_tgt successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52dk
Target targets/ble_tgt successfully set target.build_profile to optimized
```

Here is the command you will need to set up your target for the nRF51dk:

```no-highlight
~/dev/my_proj1$ newt target set ble_tgt     \
    app=apps/ble_app                        \
    bsp=@apache-mynewt-core/hw/bsp/nrf51dk  \
    build_profile=optimized
Target targets/ble_tgt successfully set target.app to apps/ble_app
Target targets/ble_tgt successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf51dk
Target targets/ble_tgt successfully set target.build_profile to optimized
```

### Enter BLE

Since our application will support BLE functionality, we need to give it access
to a BLE stack.  We do this by adding the necessary NimBLE packages to the
app's dependency list.  To enable a combined host-controller in the app, add
dependencies for the NimBLE controller, host, and in-RAM transport to
`apps/ble_app/pkg.yml`:

```hl_lines="6 7 8"
pkg.deps:
    - "@apache-mynewt-core/kernel/os"
    - "@apache-mynewt-core/sys/console/full"
    - "@apache-mynewt-core/sys/log/full"
    - "@apache-mynewt-core/sys/stats/full"
    - "@apache-mynewt-core/net/nimble/controller"
    - "@apache-mynewt-core/net/nimble/host"
    - "@apache-mynewt-core/net/nimble/transport/ram"
```

### Build the target

Now would be a good time for a basic sanity check.  Let's make sure the target builds.

```
~/dev/my_proj1$ newt build ble_tgt
Building target targets/ble_tgt
Compiling repos/apache-mynewt-core/hw/hal/src/hal_common.c
Compiling repos/apache-mynewt-core/hw/drivers/uart/src/uart.c
<...snip...>
Linking /home/me/dev/my_proj1/bin/targets/ble_tgt/app/apps/ble_app/ble_app.elf
Target successfully built: targets/ble_tgt
```

Now let's try running our minimal application on actual hardware.  Attach the target device to your computer and run the application with `newt run`:

```
~/dev/my_proj1$ newt run ble_tgt 0
App image succesfully generated: /home/me/dev/my_proj1/bin/targets/ble_tgt/app/apps/ble_app/ble_app.img
<...snip...>
Resetting target
[Switching to Thread 57005]
0x000000dc in ?? ()
(gdb)
```

You can start the application by pressing `c <enter>` at the gdb prompt.  When the excitement of watching the idle loop run wears off, quit gdb with `<ctrl-c> q <enter>`.

If your target fails to build or run, you might want to revisit the [project
blinky tutorial](../../os/tutorials/blinky.md) to see if there is a setup step
you missed.  You may also find help by posting a question to the [mailing
list](../../community.md) or searching the archives.

### Conclusion

You now have a fully functional BLE app (never mind that it doesn't actually do
anything yet!).  With all the necessary infrastructure in place, you can now
start turning this into a real application.  A good next step would be to turn
your app into a beaconing device.  The [BLE iBeacon
tutorial](../../os/tutorials/ibeacon.md) builds on this one and ends with a
functioning iBeacon.  For something a little more ambitious, the [BLE
peripheral project tutorial](../../os/tutorials/bleprph.md) describes a NimBLE
peripheral application in detail.
