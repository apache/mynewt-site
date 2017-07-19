## Developing an Application for an Onboard Sensor

This tutorial shows you how to develop a simple application for an onboard sensor.  The Mynewt sensor framework enables you to easily and quickly develop Mynewt sensor applications.  We assume you have completed the [Enabling an Off-Board Sensor in an Existing Application Tutorial](/os/tutorials/sensors/sensor_nrf52_bno055.md) and are familiar with the sensor framework and sensor shell command. 

<br>
This tutorial shows you how to:

* Develop an application with the LIS2DH12 accelerometer onboard sensor enabled on the Nordic Thingy and use the sensor framework `sensor` shell command to view the sensor data.
* Extend the application to use the sensor framework API to read the sensor data and output the data to the Mynewt console.

### Prerequisites

* Meet the prerequisites listed in [Sensor Tutorials](/os/tutorials/sensors/sensors.md).
* Have a Nordic Thingy.

* [Segger J-Link Debug Probe](https://www.segger.com/jlink-debug-probes.html) - any model (this tutorial has been tested with J-Link EDU and J-Link Pro).
* [J-Link 9 pin Cortex-M Adapter](https://www.segger.com/jlink-adapters.html#CM_9pin) that allows JTAG, SWD and SWO connections between J-Link and Cortex M based target hardware systems.
* Install the [Segger JLINK Software and documentation pack](https://www.segger.com/jlink-software.html).
* Complete the [Enabling an Off-Board Sensor in an Existing Application Tutorial](/os/tutorials/sensors/sensor_nrf52_bno055.md).

### Developing a Sensor Enabled Application with Shell Support

We first develop a simple application with the LIS2DH12 onboard sensor on the Nordic Thingy and the `sensor` shell command enabled.

<br>
#### Step 1: Creating a New App Package

We name the new app package `my_sensor_app`. From your project base directory, run the `newt pkg new` command to create a new app package.  This tutorial uses ~/dev/myproj for the project.


```no-highlight
$ cd ~/dev/myproj
$ newt pkg new -t app apps/my_sensor_app
Download package template for package type app.
Package successfuly installed into /Users/wanda/dev/myproj/apps/my_sensor_app

```
<br>
The newt tool creates a skeleton `my_sensor_app` package directory in the `~/dev/myproj/apps/` directory. Go to the `my_sensor_app` directory so we can update the package `pkg.yml` and source files. 


```no-highlight

$ cd apps/my_sensor_app

```

<br>
#### Step 2: Adding the Package Dependencies

The my_sensor_app requires the sensor framework, `hw/sensor`, package as a package dependency.  Note that the BSP creates the sensor devices for the onboard sensors, so the `hw/sensor/creator` package that creates off-board sensor is not needed. 

Add the highlighted line to the `pkg.yml` file to add the `hw/sensor` package as package dependency:

```hl_lines="7"

pkg.deps:
    - "@apache-mynewt-core/kernel/os"
    - "@apache-mynewt-core/sys/console/full"
    - "@apache-mynewt-core/sys/log/full"
    - "@apache-mynewt-core/sys/stats/full"
    - "@apache-mynewt-core/hw/sensor"

```
<br>
#### Step 3: Using the Skeleton main.c File 

The newt tool creates a skeleton main.c file in the `my_sensor_app/src` directory.  The skeleton `main()` code shown is all you need to build an application that only uses the `sensor` shell command to read sensor data. You do not need to make any changes to the file. The sensor framework implements the `sensor` shell command and the shell package processes shell command events from the OS default event queue. 


```c 

int
main(int argc, char **argv)
{
    /* Perform some extra setup if we're running in the simulator. */
#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif

    /* Initialize all packages. */
    sysinit();

    /* As the last thing, process events from default event queue. */
    while (1) {
        os_eventq_run(os_eventq_dflt_get());
    }

    return 0;
}

```

<br>
#### Step 4: Creating the Target for the my_sensor_app Application

You create a target for the my_sensor_app to run on the Nordic Thingy. The following syscfg settings must be set:

* `I2C_0=1` : Enables the I2C interface 0 for the nRF52 Thingy BSP HAL setting to communicate with the onboard sensor.
* `LIS2DH12_ONB=1`: Enables the lis2dh12 onboard sensor support in the nRF52 Thingy BSP. 

    A BSP with onboard sensors defines a syscfg setting for each onboard sensor it supports and uses the naming convention `<SENSORNAME>_ONB`. The `<SENSORNAME>_ONB` setting specifies whether the sensor named SENSORNAME is enabled. The setting is disabled by default. The BSP includes the sensor device driver package `hw/drivers/sensors/<sensorname>` and creates and configures the onboard sensor named SENSORNAME when the `SENSORNAME_ONB` setting is enabled by the application.

* `SHELL_TASK=1`: Enables the shell task for the shell commmand support.
    Note that the `hw/sensor` package enables the `SENSOR_CLI` setting by default. 
* `SENSOR_OIC=0`: Disables the OIC sensor server support in the sensor framework.
* `CONSOLE_RTT=1`: Enables console communication via the SEGGER RTT. The nRF52 Thingy does not have a UART so we use the RTT for the console.
* `CONSOLE_UART=0`: Disables the console communication via a UART.

**Note:** The lis2dh12 sensor device driver package, `/hw/driver/sensors/lis2dh12`, currently does not support a shell command to view information on the device.

<br>
1. Run the following newt commands to create the target and set the application and BSP.

```no-highlight

$ newt target create thingy_my_sensor
Target targets/thingy_my_sensor successfully created
$ newt target set thingy_my_sensor bsp=@apache-mynewt-core/hw/bsp/nrf52-thingy
Target targets/thingy_my_sensor successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52-thingy
$ newt target set thingy_my_sensor app=apps/my_sensor_app
Target targets/thingy_my_sensor successfully set target.app to apps/my_sensor_app
$ newt target set thingy_my_sensor build_profile=debug
Target targets/thingy_my_sensor successfully set target.build_profile to debug

```

<br>
2. Run the following `newt target set ` command to set the syscfg settings:

```no-highlight

$ newt target set thingy_my_sensor syscfg=I2C_0=1:LIS2DH12_ONB=1:SHELL_TASK=1:CONSOLE_RTT=1:CONSOLE_UART=0:SENSOR_OIC=0
Target targets/thingy_my_sensor successfully set target.syscfg to I2C_0=1:LIS2DH12_ONB=1:SHELL_TASK=1:CONSOLE_RTT=1:CONSOLE_UART=0:SENSOR_OIC=0

```

<br>
#### Step 5: Creating and Building the Bootloader Target

Create a target for the bootloader for the nRF52 Thingy. We name the target `thingy_boot`.

<br>
1.  Run the following `newt target` commands to create the target:

```no-highlight

$ newt target create thingy_boot
Target targets/thingy_boot successfully created
$ newt target set thingy_boot bsp=@apache-mynewt-core/hw/bsp/nrf52-thingy
Target targets/thingy_boot successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52-thingy
$ newt target set thingy_boot app=@apache-mynewt-core/apps/boot
Target targets/thingy_boot successfully set target.app to @apache-mynewt-core/apps/boot
$ newt target set thingy_boot build_profile=optimized
Target targets/thingy_boot successfully set target.build_profile to optimized

```

<br>
2. Run the `newt build` command to build the bootloader target:

```no-highlight

$ newt build thingy_boot 
Building target targets/thingy_boot

       ...

Archiving thingy_boot-sysinit-app.a
Archiving util_mem.a
Linking /Users/wanda/dev/myproj/bin/targets/thingy_boot/app/apps/boot/boot.elf
Target successfully built: targets/thingy_boot

```

<br>
#### Step 6: Connecting the Thingy to your Computer
Perform the following steps to connect the Thingy to your computer:

<br>
1. Move the power switch to the left to power ON the Thingy:

<br>
![Thingy](/os/tutorials/pics/thingy.jpg "Thingy On")
<br>

<br>
2. Connect the debug probe to the JTAG port on the board using the Jlink 9-pin adapter and cable, and connect the probe to your computer.

<br>
![J-Link debug probe to Thingy](/os/tutorials/pics/thingy_jlink.jpg "Connecting J-Link debug probe to Thingy")
<br>
<p>
<br>

<br>
#### Step 7: Loading the Image and Connecting to the Console via RTT 

To run the application, you need to load the bootloader on to the device, load the application image, and start GDB debug process for RTT to attach to.

<br>
1. Run the `newt load` command to load the bootloader:

```no-highlight

$ newt load thingy_boot
Loading bootloader

```
<br>
2. Run the `newt run` command to build and create an image for the my_sensor_app, load the image,  and start a GDB process to debug the application:

```no-highlight

$ newt run thingy_my_sensor 1.0.0
Assembling repos/apache-mynewt-core/hw/bsp/nrf52-thingy/src/arch/cortex_m4/gcc_startup_nrf52_split.s
Compiling repos/apache-mynewt-core/hw/cmsis-core/src/cmsis_nvic.c
Assembling repos/apache-mynewt-core/hw/bsp/nrf52-thingy/src/arch/cortex_m4/gcc_startup_nrf52.s
Compiling repos/apache-mynewt-core/encoding/base64/src/hex.c
Compiling apps/my_sensor_app/src/main.c

    ...

Archiving thingy_my_sensor-sysinit-app.a
Archiving time_datetime.a
Archiving util_cbmem.a
Archiving util_crc.a
Archiving util_mem.a
Archiving util_parse.a
Linking /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf
App image succesfully generated: /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.img
Loading app image into slot 1
[/Users/wanda/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52-thingy/nrf52-thingy_debug.sh /Users/wanda/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52-thingy /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app]
Debugging /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf...done.
os_tick_idle (ticks=24)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:204
204	    if (ticks > 0) {
Resetting target
0x000000dc in ?? ()
(gdb) 

```

<br>
3. Enter `c` in the `(gdb)` prompt to continue.

<br>
4.  Run the following telnet command to connect to the Mynewt console via RTT and enter &lt;return&gt; to get the shell prompt after you are connected.

```no-highlight

$ telnet localhost 19021
Trying ::1...
telnet: connect to address ::1: Connection refused
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
SEGGER J-Link V6.14h - Real time terminal output
SEGGER J-Link ARM V10.0, SN=600000268
Process: JLinkGDBServer

011468 compat>

```

<br>
#### Step 8: Viewing the list of Sensors and Sensor Data

<br>
1. Enter `sensor list` on the console to see the sensors that are registered with the sensor manager. You should see the `lis2dh12_0` sensor.  This sensor is only configured for the accelerometer (0x1).


```no-highlight

011468 compat> sensor list
sensor list
029706 sensor dev = lis2dh12_0, configured type = 0x1 
029707 compat> 

```

<br>
2. Enter the `sensor read` command on the console to read some data samples for the accelerometer:

```no-highlight

029707 compat> sensor read lis2dh12_0 0x1 -n 5
sensor read lis2dh12_0 0x1 -n 5
042537 ts: [ secs: 331 usecs: 102682 cputime: 331436945 ]
042537 x = 9.806650176 y = 58.839900992 z = -9894.910156
042537 ts: [ secs: 331 usecs: 104832 cputime: 331439095 ]
042537 x = 19.613300352 y = 98.066497804 z = -9924.330078
042537 ts: [ secs: 331 usecs: 106988 cputime: 331441251 ]
042537 x = 9.806650176 y = 49.033248902 z = -9904.716796
042538 ts: [ secs: 331 usecs: 109137 cputime: 331443400 ]
042538 x = 9.806650176 y = 29.419950496 z = -9904.716796
042538 ts: [ secs: 331 usecs: 111288 cputime: 331445551 ]
042538 x = 58.839900992 y = 0.000000000 z = -9816.457031
042538 compat> 


```

<br>
### Extending the Application to Use the Sensor API to Read Sensor Data

As this tutorial demonstrates so far, the Mynewt sensor framework enables you to easily and quickly develop an application with a sensor and view the sensor data from the `sensor` shell command.  We now extend the application to use the sensor API to read the sensor data. 

You use the `sensor_read()` function to read data for a configured sensor type from a sensor device. You provide a callback that is called when the data is read from the sensor. You can also also register a listener for a sensor with the `sensor_register_listener()` function. A listener is a callback that is called whenever the `sensor_read()` function reads data for that sensor. 

We extend the application to register an OS callout to read data from the accelerometer sensor every 5 seconds. We first only use the `sensor_read()` to read the sensor data, then we extend the application to also register a listener for the sensor.

<br>
#### Step 1: Modifying main.c

Add the following code to the `my_sensor_app/src/main.c` file:

<br>
1. Add the highlighted include files:

```hl_lines="5 6 7 8"

#include "sysinit/sysinit.h"
#include "os/os.h"

#include <defs/error.h>
#include <sensor/sensor.h>
#include <sensor/accel.h>
#include <console/console.h>

```

<br>
2. Add the following variable declarations:

* `struct sensor * my_sensor`: This is the handle for the sensor that the sensor API uses to perform operations on the sensor. We set this variable when we lookup the sensor and pass it to the `sensor_read()` function to read the sensor data.
* `struct os_callout sensor_callout`:  OS callout to read sensor data.

```c

static struct sensor *my_sensor;
static struct os_callout sensor_callout;

```
<br>
3. Add the `read_accelerometer()` function for the sensor read data callback function: 

**Note**: We pass the READ_CB value as the argument for the `read_accelerometer()` callback function because we will also use the `read_accelerometer()` function for the listener callback to keep the tutorial simple. The `read_accelerometer()` function uses this value to print out whether the callback is invoked as a sensor read callback or a listener callback. 


```c 

#define READ_CB    1

static int
read_accelerometer(struct sensor* sensor, void *arg, void *databuf)
{

    char tmpstr[13];
    struct sensor_accel_data *sad;

    if (!databuf) {
        return SYS_EINVAL;

    }
    sad = (struct sensor_accel_data *)databuf;

    if (!sad->sad_x_is_valid ||
        !sad->sad_y_is_valid ||
        !sad->sad_z_is_valid) {

        return SYS_EINVAL;
    }
   
    console_printf("%s: [ secs: %ld usecs: %d cputime: %u ]\n",
                   ((int)arg == READ_CB) ? "READ_CB" : "LISTENER_CB",
                   (long int)sensor->s_sts.st_ostv.tv_sec,
                   (int)sensor->s_sts.st_ostv.tv_usec,
                   (unsigned int)sensor->s_sts.st_cputime);

    console_printf("x = %s ", sensor_ftostr(sad->sad_x, tmpstr, 13));
    console_printf("y = %s ", sensor_ftostr(sad->sad_y, tmpstr, 13));
    console_printf("z = %s\n\n", sensor_ftostr(sad->sad_z, tmpstr, 13));
    return 0;
}

```
<br>
4. Add the event callback for the timer events. The timer fires every 5 seconds.  The callback reads the data from the accelerometer sensor:

```c

/*
 * Event callback function for timer events. The callback reads the sensor data
 */

#define READ_SENSOR_INTERVAL (5 * OS_TICKS_PER_SEC)


static void 
timer_ev_cb(struct os_event *ev)
{


    assert(ev != NULL);

    /* 
     * Read the acceleromter sensor. Pass the read_accelerometer callback 
     * and read_cb_str for the callback arg.
     */
    sensor_read(my_sensor, SENSOR_TYPE_ACCELEROMETER, read_accelerometer,
                 (void *)READ_CB, OS_TIMEOUT_NEVER);
    os_callout_reset(&sensor_callout, READ_SENSOR_INTERVAL);
}

```

<br>
5. Initialize the timer event to fire every five seconds:

```c

static void 
init_timer(void)
{
    /*
     * Initialize the callout for a timer event.
     */
    os_callout_init(&sensor_callout, os_eventq_dflt_get(),
                    timer_ev_cb, NULL);

    os_callout_reset(&sensor_callout, READ_SENSOR_INTERVAL);

}

```

<br>
6. Add the call to `sensor_mgr_find_next_bytype()` function to lookup the accelerometer sensor in `main()` and set the sensor to the `my_sensor` variable. We must lock the sensor manager sensor list before performing the lookup:

```hl_lines="10 11 12 14"

int
main(int argc, char **argv)
{
    ...

    /* Initialize all packages. */
    sysinit();

    sensor_mgr_lock();
    my_sensor = sensor_mgr_find_next_bytype(SENSOR_TYPE_ACCELEROMETER, NULL);
    sensor_mgr_unlock();

    assert(my_sensor != NULL);

    /* As the last thing, process events from default event queue. */
    while (1) {
        os_eventq_run(os_eventq_dflt_get());
    }

    return 0;
}

```

<br>
7. Add the `init_timer()` function to initialize the OS callout:

```hl_lines="8"

int
main(int argc, char **argv)
{
    ...

    assert(my_sensor != NULL);

    init_timer();

    /* As the last thing, process events from default event queue. */
    while (1) {
        os_eventq_run(os_eventq_dflt_get());
    }

    return 0;
}

```
<br>
#### Step 2: Rebuilding the Application and Connecting to Console
<br>
1. Run the `newt run` command to rebuild the application, create a new image, load the image, and start a GDB process:

```no-highlight

$ newt run thingy_my_sensor 2.0.0
Compiling apps/my_sensor_app/src/main.c
Archiving apps_my_sensor_app.a
Linking /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf
App image succesfully generated: /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.img
Loading app image into slot 1
[/Users/wanda/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52-thingy/nrf52-thingy_debug.sh /Users/wanda/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52-thingy /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app]
Debugging /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs

    ...

Reading symbols from /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf...done.
os_tick_idle (ticks=12)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:204
204	    if (ticks > 0) {
Resetting target
0x000000dc in ?? ()
(gdb) c 
Continuing.

```
<br>
2. Connect to the console via RTT:

```no-highlight

$ telnet localhost 19021
Trying ::1...
telnet: connect to address ::1: Connection refused
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
SEGGER J-Link V6.14h - Real time terminal output
SEGGER J-Link ARM V10.0, SN=600000268
Process: JLinkGDBServer
000642 READ_CB: [ secs: 5 usecs: 3651 cputime: 5345645 ]
000642 x = -29.41995049 y = 0.000000000 z = -9796.843750

001282 READ_CB: [ secs: 9 usecs: 986395 cputime: 10328389 ]
001282 x = 68.646553024 y = 49.033248902 z = -9855.683593

001922 READ_CB: [ secs: 14 usecs: 970723 cputime: 15312717 ]
001922 x = 98.066497804 y = 39.226600640 z = -9885.103515

002562 READ_CB: [ secs: 19 usecs: 955844 cputime: 20297838 ]
002562 x = 49.033248902 y = 68.646553024 z = -9914.523437


```

You should see the accelerometer sensor that the application outputs from the READ_CB to the console.

<br>
#### Step 3:  Registering a Sensor Listener 

You can also register a sensor listener callback. When the `sensor_read()` funtion is called to read a sensor, all listeners registered for that sensor are also called.  We extend the my_sensor_app to register a listener for the sensor.

<br>
1. Declare and initialize a listener for the sensor. We use the same callback `read_accelerometer()` function, and set the LISTENER_CB value for the callback argument to the listener callback to indicate that the callback is invoked from the listener.

```hl_lines="3 5 7 8 9 10 11"

#define READ_CB    1
#define LISTENER_CB 2

static int read_accelerometer(struct sensor* sensor, void *arg, void *databuf);

static struct sensor_listener listener = {
   .sl_sensor_type = SENSOR_TYPE_ACCELEROMETER,
   .sl_func = read_accelerometer,
   .sl_arg = (void *)LISTENER_CB,
};

```
<br>
2. Register a listener for the sensor in main():

```hl_lines="5 17 18"

int
main(int argc, char **argv)
{
    int rc;

  /* Perform some extra setup if we're running in the simulator. */
#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif
    ...

    sensor_mgr_unlock();

    assert(my_sensor != NULL);   
    
    rc = sensor_register_listener(my_sensor, &listener);
    assert (rc == 0);

    init_timer();

}

```
<br>
#### Step 4: Rebuilding the Application and Connecting to Console
<br>
1. Run the `newt run` command to rebuild the application, create an new image and start a GDB process:

```no-highlight

$ newt run thingy_my_sensor 3.0.0
Compiling apps/my_sensor_app/src/main.c
Archiving apps_my_sensor_app.a
Linking /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf
App image succesfully generated: /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.img
Loading app image into slot 1
[/Users/wanda/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52-thingy/nrf52-thingy_debug.sh /Users/wanda/dev/myproj/repos/apache-mynewt-core/hw/bsp/nrf52-thingy /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app]
Debugging /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs

     ...

Reading symbols from /Users/wanda/dev/myproj/bin/targets/thingy_my_sensor/app/apps/my_sensor_app/my_sensor_app.elf...done.
os_tick_idle (ticks=12)
    at repos/apache-mynewt-core/hw/mcu/nordic/nrf52xxx/src/hal_os_tick.c:204
204	    if (ticks > 0) {
Resetting target
0x000000dc in ?? ()
(gdb) c
Continuing.

```

<br>
2. Connect to the console via RTT

```no-highlight

$ telnet localhost 19021
Trying ::1...
telnet: connect to address ::1: Connection refused
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
SEGGER J-Link V6.14h - Real time terminal output
SEGGER J-Link ARM V10.0, SN=600000268
Process: JLinkGDBServer

009602 LISTENER_CB: [ secs: 74 usecs: 828580 cputime: 75180590 ]
009602 x = 29.419950496 y = 0.000000000 z = -9865.490234

009602 READ_CB: [ secs: 74 usecs: 828580 cputime: 75180590 ]
009602 x = 29.419950496 y = 0.000000000 z = -9865.490234

010242 LISTENER_CB: [ secs: 79 usecs: 812642 cputime: 80164652 ]
010242 x = 39.226600640 y = 29.419950496 z = -9875.296875

010242 READ_CB: [ secs: 79 usecs: 812642 cputime: 80164652 ]
010242 x = 39.226600640 y = 29.419950496 z = -9875.296875

021122 LISTENER_CB: [ secs: 164 usecs: 568113 cputime: 164920123 ]
021122 x = 39.226600640 y = 9.806650176 z = -9875.296875

021122 READ_CB: [ secs: 164 usecs: 568113 cputime: 164920123 ]
021122 x = 39.226600640 y = 9.806650176 z = -9875.296875

```

You should see the accelerometer sensor data output from both the READ_CB and the LISTENER_CB callbacks.
