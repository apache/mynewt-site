##Enabling Newt Manager (newtmgr) in a project

<br>

This tutorial explains how to add the newtmgr task to a project so that you can interact with your project over newtmgr.

<br>

### Pre-Requisites

* Ensure you have installed [newt](../../newt/install/newt_mac.md) and that the 
newt command is in your system path. 
* Ensure that you have installed the newtmgr tool [newtmgr](../../newtmgr/installing.md)
* You must have Internet connectivity to fetch remote Mynewt components.
* You must [install the compiler tools](../get_started/native_tools.md) to 
support native compiling to build the project this tutorial creates.  
* You must install the [Segger JLINK package]( https://www.segger.com/jlink-software.html) to load your project on the board.
* Cable to establish a serial USB connection between the board and the laptop

<br>

### Use an existing project

Since all we're doing is adding newtmgr capability to a project, we assume that you have worked through at least some of the other tutorials, and have an existing project.
For this example, we'll be modifying the [ble_tiny](bletiny_project.md) project to enable newtmgr connectivity. We'll be calling our app myble as in that project as well. 
Feel free to use whatever project you'd like though.

The first thing you'll need to add is a new dependency for your app. In the repo for the bletiny app you'll need to add the following line to the pkg.yml file:

```
 - libs/newtmgr
```
 
Now the application will know to pull in the newtmgr code.

<br>

###Modify the source

First, you'll need to include the newtmgr header file:

```

#include <newtmgr/newtmgr.h>
```


Next, you'll need to declare a task for the newtmgr:

```

#define NEWTMGR_TASK_PRIO (4)
#define NEWTMGR_TASK_STACK_SIZE (OS_STACK_ALIGN(896))
os_stack_t newtmgr_stack[NEWTMGR_TASK_STACK_SIZE];
```

Next you'll scroll down (way down) to the ```main()``` function and find the lines:

```
rc = console_init(shell_console_rx_cb);
assert(rc == 0);
```

After those lines, add:

```
nmgr_task_init(NEWTMGR_TASK_PRIO, newtmgr_stack, NEWTMGR_TASK_STACK_SIZE);
```

### Build targets

Then build the two targets.

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

### Create the app image

Generate a signed application image for the `myble` target. The version number is arbitrary.

```
$ newt create-image myble 1.0.0
App image succesfully generated: ./bin/makerbeacon/apps/bletiny/bletiny.img
Build manifest: ./bin/makerbeacon/apps/bletiny/manifest.json
```

<br>

### Load the image

Make sure the USB connector is in place and the power LED on the board is lit. Use the Power ON/OFF switch to reset the board after loading the image.

```
$ newt load nrf52_boot
$ newt load myble
```

<br>

### Set up newtmgr connection

Newtmgr requires a connection profile in order to connect to your board. If you haven't yet, follow the [instructions](../../newtmgr/overview.md) for setting up your connection profile.

<br>

###Connecting with your app

Once you have a connection profile set up, you can connect to your device with ```newtmgr -c myconn <command>``` to run commands agains your app. 
    
To test and make sure that newtmgr is working, try the echo command:

```
# newtmgr -c myconn echo hello
{"r": "hello"}
```

Newtmgr wraped the response in valid JSON notation. Now let's look at some BLE stats using newtmgr:

```
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
  read_mult_rsp_tx: 0
  exec_write_req_rx: 0
  exec_write_rsp_tx: 0
  error_rsp_tx: 0
  find_type_value_rsp_rx: 0
  read_type_req_tx: 0
  read_type_rsp_rx: 0
  read_rsp_tx: 0
  read_blob_req_tx: 0
  mtu_req_tx: 0
  read_req_tx: 0
  read_blob_rsp_tx: 0
  read_mult_req_rx: 0
  write_req_tx: 0
  prep_write_rsp_tx: 0
  indicate_rsp_rx: 0
  write_cmd_rx: 0
  exec_write_rsp_rx: 0
  find_info_req_rx: 0
  mtu_rsp_rx: 0
  prep_write_req_rx: 0
  notify_req_rx: 0
  read_group_type_rsp_rx: 0
  prep_write_rsp_rx: 0
  indicate_rsp_tx: 0
  find_info_rsp_tx: 0
  read_blob_req_rx: 0
  read_group_type_req_rx: 0
  write_cmd_tx: 0
  mtu_req_rx: 0
  read_mult_rsp_rx: 0
  write_rsp_rx: 0
  write_req_rx: 0
  read_type_rsp_tx: 0
  read_mult_req_tx: 0
  error_rsp_rx: 0
  find_info_rsp_rx: 0
  find_type_value_req_tx: 0
  read_req_rx: 0
  read_type_req_rx: 0
  notify_req_tx: 0
  mtu_rsp_tx: 0
  find_type_value_req_rx: 0
  read_blob_rsp_rx: 0
  read_group_type_req_tx: 0
  exec_write_req_tx: 0
```

Your application is now able to communicate via newtmgr!

