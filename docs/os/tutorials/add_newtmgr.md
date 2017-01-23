
##Enabling Newt Manager in Your Application

<br>
In order for your application to communicate with the newtmgr tool and process Newt Manager commands, you must 
enable Newt Manager device management and the support to process Newt Manager commands 
in your application.  This tutorial explains how to add the support to your application.

This tutorial assumes that you have read the [Device Management with Newt Manager](/os/modules/devmgmt/newtmgr/)
guide and are familiar with the `newtmgr` and `oicmgr` frameworks and all the options that are available 
to customize your application.

This tutorial shows you how to configure your application to:

* Use the newtmgr framework.
* Use serial transport to communicate with the newtmgr tool.
* Support all Newt Manager commands.

See [Other Configuration Options](#other-configuration-options) on how to customize your application.

<br>

### Pre-Requisites
Ensure that you have met the following prerequisites before continuing with this tutorial:

* Installed the [newt tool](../../newt/install/newt_mac.md). 
* Installed the [newtmgr tool](../../newtmgr/installing.md).
* Have Internet connectivity to fetch remote Mynewt components.
* Installed the [compiler tools](../get_started/native_tools.md) to 
support native compiling to build the project this tutorial creates.  
* Installed the [Segger JLINK package]( https://www.segger.com/jlink-software.html) to load your project on the board.
* Have a cable to establish a serial USB connection between the board and the laptop.

<br>

### Use an Existing Project

We assume that you have worked through at least some of the other tutorials and have an existing project.
In this example, we modify the [ble_tiny](bletiny_project.md) project to enable Newt Manager support. 
We call our application `myble`.  You can create the application using any name you choose. 

###Modify Package Dependencies and Configurations


Add the following packages to the `pkg.deps` parameter in your target or application `pkg.yml` file:

```no-highlight

pkg.deps:
    - mgmt/newtmgr
    - mgmt/newtmgr/transport/nmgr_shell
    - mgmt/imgmgr
    - sys/log/full
    - sys/stats/full
    - sys/config
    - test/crash_test
    - test/runtest

``` 
Each package provides the following Newt Manager functionality:

* `mgmt/newtmgr`: Supports the newtmgr framework and the 
Newt Manager `echo`, `taskstats` `mpstats`, `datetime`, and `reset` commands.
* `mgmt/newtmgr/transport/nmgr_shell`: Supports serial transport.
* `mgmt/imgmgr`: Supports the `newtmgr image` command 
* `sys/log/full` : Supports the `newtmgr log` command.
* `sys/stats/full`: Supports the `newtmgr stat` command. 
* `sys/config`: Supports the `newtmgr config` command. 
* `test/crash_test`: Supports the `newtmgr crash` command. 
* `test/runtest`: Supports the `newt run` command.


Add the following configuration setting values to the `syscfg.vals` parameter in the target or 
application `syscfg.yml` file:

```no-highlight

syscfg.vals:
    LOG_NEWTMGR: 1
    STATS_NEWTMGR: 1
    CONFIG_NEWTMGR: 1
    CRASH_TEST_NEWTMGR: 1
    RUNTEST_NEWTMGR: 1
    SHELL_TASK: 1
```
The first five configuration settings enable support for the Newt Manager `log`, `stats`, `config`, `crash`, 
and `run` commands. The `SHELL_TASK` setting enables the shell for serial transport.

Note that you may need to override additional configuration settings that are specific to each package to customize the 
package functionality.

<br>

###Modify the Source

Your application must designate an event queue that the `mgmt` package uses to receive request events from 
the newtmgr tool.  It must also initialize a task and implement the task handler to
dispatch events from this queue.  The `mgmt` package executes and processes newtmgr 
request events in the context of this task.  Your application, however, does 
not need to create a dedicated event queue and task for this purpose and can use its default 
event queue.  This example uses the application's default event queue.  

The `mgmt` package exports the `void mgmt_evq_set(struct os_eventq *evq)` function that an application must call 
to designate the event queue. Modify `main.c` to add this call as follows:

Add the `mgmt/mgmt.h` header file: 

```no-highlight

#include <mgmt/mgmt.h>

```
Add the call to designate the event queue. In the `main()` function,  
scroll down to the `os_eventq_dflt_set(&ble_tiny_evq)` function call and add the 
following statement below it:

```no-highlight

mgmt_eventq_set(&ble_tiny_evq)

```
The `mgmt_eventq_set()` function must be called after your application has initialized the event queue and task.


### Build the Targets

Build the two targets as follows:

```
$ newt build nrf52_boot
<snip>
App successfully built: ./bin/nrf52_boot/apps/boot/boot.elf
$ newt build myble
Compiling hci_common.c
Compiling util.c
Archiving nimble.a
Compiling os.c
<snip>
```

<br>

### Create the Application Image

Generate a signed application image for the `myble` target. You can use any version number you choose.

```
$ newt create-image myble 1.0.0
App image successfully generated: ./bin/makerbeacon/apps/bletiny/bletiny.img
Build manifest: ./bin/makerbeacon/apps/bletiny/manifest.json
```

<br>

### Load the Image

Ensure the USB connector is in place and the power LED on the board is lit. Turn the power switch on your board off, 
then back on to reset the board after loading the image.

```
$ newt load nrf52_boot
$ newt load myble
```



### Set Up a Connection Profile

The newtmgr tool requires a connection profile in order to connect to your board. If you have not done so, 
follow the [instructions](../../newtmgr/overview.md) for setting up your connection profile.

<br>

###Connecting with Your Application

Once you have a connection profile set up, you can connect to your device with ```newtmgr -c myconn <command>``` to run commands in your application. 
    
Issue the `echo` command to ensure that your application is communicating with the newtmgr tool:

```no-highlight

# newtmgr -c myconn echo hello
hello

```

Test your application to ensure that it can process a Newt Manager command that is supported by a different package.
Issue the `stat` command to see the BLE stats. 

```no-highlight

newtmgr -c myconn stat ble_att
Return Code = 0
Stats Name: ble_att
  prep_write_req_tx: 0
  indicate_req_tx: 0
  write_rsp_tx: 0
  find_info_req_tx: 0
  read_rsp_rx: 0
  read_group_type_rsp_tx: 0
  indicate_req_rx: 0
  find_type_value_rsp_tx: 0

       ...

  read_req_rx: 0
  read_type_req_rx: 0
  notify_req_tx: 0
  mtu_rsp_tx: 0
  find_type_value_req_rx: 0
  read_blob_rsp_rx: 0
  read_group_type_req_tx: 0
  exec_write_req_tx: 0
```

Your application is now able to communicate with the newtmgr tool.


###Other Configuration Options

This section explains how to customize your application to use other Newt Manager protocol options.

####Newtmgr Framework Transport Protocol Options
The newtmgr framework currently supports BLE and serial transport protocols. 
To configure the transport protocols that are supported, modify the `pkg.yml` 
and `syscfg.yml` files as follows:

* Add the `mgmt/newtmgr/transport/ble` package to `pkg.deps` parameter to enable BLE transport.
* Add the `mgmt/newtmgr/transport/nmgr_shell` package to 
the `pkg.deps` parameter,  and add `SHELL_TASK: 1` to the `syscfg.vals` parameter to enable serial transport.

<br>

#### Oicmgr Framework Options

To use the oicmgr framework instead of the newtmgr framework, modify the `pkg.yml` and `syscfg.yml` files 
as follows:

* Add the `mgmt/oicmgr` package (instead of the `mgmt/newtmgr` and `mgmt/newtmgr/transport` packages 
as described previously) to the `pkg.deps` parameter.
* Add `OC_SERVER: 1` to the `syscfg.vals` parameter.

Oicmgr supports the IP, serial, and BLE transport protocols.  To configure the transport protocols that are supported, 
set the configuration setting values in the `syscfg.vals` parameter as follows:

* Add `OC_TRANSPORT_IP: 1` to enable IP transport. 
* Add `OC_TRANSPORT_GATT: 1` to enable BLE transport.
* Add `OC_TRANSPORT_SERIAL: 1` and `SHELL_TASK: 1`  to enable serial transport.

<br>

#### Customize the Newt Manager Commands that Your Application Supports

We recommend that you only enable support for the Newt Manager commands that your application uses 
to reduce your application code size.  To configure the commands that are supported, set the configuration 
setting values in the `syscfg.vals` parameter as follows:


* Add `LOG_NEWTMGR: 1` to enable support for the `newtmgr log` command.
* Add `STATS_NEWTMGR: 1` to enable support for the `newtmgr stat` command.
* Add `CONFIG_NEWTMGR: 1` to enable support for the `newtmgr config` command.
* Add `CRASH_TEST_NEWTMGR: 1` to enable support for the  `newtmgr crash` command.
* Add `RUNTEST_NEWTMGR: 1` to enable support for the  `newtmgr crash` command.

Notes: 

* When you enable Newt Manager support, using either the newtmgr or oicmgr framework, your application automatically 
supports the Newt Manager `echo`, `taskstats`, `mpstats`, `datetime`, and `reset` commands.  These 
commands cannot be configured individually.
* Currently, the `mgmt/imgmgr` package does not provide a configuration setting to enable or disable support 
for the `newtmgr image` command. 
