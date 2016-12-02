## Adding an Analog Sensor on nRF52

<br>

### Objective

We will be adding an analog sensor to the NRF52DK development board and using the Analog to Digital Converter
(ADC) to read the values from the sensor. It's also using Bluetooth to allow you to connect to the app and
read the value of the sensor. Please see the following section for the required hardware
in order to complete this tutorial.

<br>

### Hardware needed

* nRF52 Development Kit (one of the following)
    * Dev Kit from Nordic - PCA 10040
    * Eval Kit from Rigado - BMD-300-EVAL-ES
* eTape Liquid Sensor -- buy from [Adafruit](https://www.adafruit.com/products/1786)
* Laptop running Mac OS
* It is assumed you have already installed newt tool. 
* It is assumed you already installed native tools as described [here](../get_started/native_tools.md)

<br>

### Create a project.  

Create a new project to hold your work.  For a deeper understanding, you can read about project creation in 
[Get Started -- Creating Your First Project](../get_started/project_create.md)
or just follow the commands below.

```
    $ mkdir ~/dev
    $ cd ~/dev
    $ newt new myadc
    Downloading project skeleton from apache/incubator-mynewt-blinky...
    Installing skeleton in myadc...
    Project myadc successfully created.
    
    $ cd myadc
    
``` 

<br>

###Add Additional Repositories

The board-specific libraries for the NRF52dk board are in an external repository at present, so
you'll need to include that remote repository and install it as well. If you're not familiar
with using repositories, see the section on [repositories](repo/add_repos.md) before
continuiing. Or just copy and paste the following.

In your `project.yml` file, add `- mynewt_nordic` to the `project.repositories` section, and 
then add the proper repository definition. When you're done, your `project.yml` file
should look like this:

```
project.name: "my_project"

project.repositories:
    - apache-mynewt-core
    - mynewt_nordic

# Use github's distribution mechanism for core ASF libraries.
# This provides mirroring automatically for us.
#
repository.apache-mynewt-core:
    type: github
    vers: 0-dev
    user: apache
    repo: incubator-mynewt-core
repository.mynewt_nordic:
    type: github
    vers: 0-latest
    user: runtimeinc
    repo: mynewt_nordic
```

<br>

###Install Everything

Now that you have defined the needed repositories, it's time to install everything so
that you can get started.

```
    $ newt install -v 
    apache-mynewt-core
    Downloading repository description for apache-mynewt-core... success!
    ...
    apache-mynewt-core successfully installed version 0.9.0-none
    ...
    mynewt_nordic
    Downloading repository description for mynewt_nordic... success!
    ...
    mynewt_nordic successfully installed version 0.9.9-none
```

<br>

### Create the targets

Create two targets - one for the bootloader and one for the nrf52 board.  

<font color="#F2853F">
Note: The correct bsp must be chosen for the board you are using. </font>

* For the Nordic Dev Kit choose @apache-mynewt-core/hw/bsp/nrf52dk instead (in the highlighted lines)
* For the Rigado Eval Kit choose @apache-mynewt-core/hw/bsp/bmd300eval instead (in the highlighted lines)


```hl_lines="3 8"
$ newt target create nrf52_adc
$ newt target set nrf52_adc app=@apache-mynewt-core/apps/nrf52_adc
Target targets/nrf52_adc successfully set target.app to @apache-mynewt-core/apps/nrf52_adc
$ newt target set nrf52_adc_ bsp=@apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set nrf52_adc build_profile=debug

$ newt target create nrf52_boot
$ newt target set nrf52_boot app=@apache-mynewt-core/apps/boot
$ newt target set nrf52_boot bsp=@apache-mynewt-core/hw/bsp/nrf52dk
$ newt target set nrf52_boot build_profile=optimized

$ newt target show 
targets/nrf52_adc
    app=@apache-mynewt-core/apps/nrf52_adc
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    build_profile=debug
targets/nrf52_boot
    app=@apache-mynewt-core/apps/boot
    bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    build_profile=optimized
```

<font color="#F2853F">
Note: If you've already built and installed a bootloader for your NRF52dk then you do
not need to create a target for it here, or build and load it as below. </font>
<br>

### Build the target executables 

```
$ newt build nrf52_boot
...
Compiling boot.c
Archiving boot.a
Linking boot.elf
App successfully built: ~/dev/myadc/bin/nrf52_boot/apps/boot/boot.elf
```
```
$ newt build nrf52_adc
...
Compiling main.c
Archiving nrf52_adc.a
Linking nrf52_adc.elf
App successfully built: ~/dev/myadc/bin/nrf52_adc/apps/nrf52_adc/nrf52_adc.elf
```

<br>

### Sign and create the nrf52_adc application image 

You must sign and version your application image to download it using newt to the board. 
Use the newt create-image command to perform this action. You may assign an arbitrary 
version (e.g. 1.0.0) to the image.

```
$ newt create-image nrf52_adc 1.0.0
App image successfully generated: ~/dev/myadc/bin/nrf52_adc/apps/nrf52_adc/nrf52_adc.img
Build manifest: ~/dev/myadc/bin/nrf52_adc/apps/nrf52_adc/manifest.json
```

<br>

### Connect the board

Connect the evaluation board via micro-USB to your PC via USB cable.
        
<br>

### Download to the target

Download the bootloader first and then the nrf52_adc executable to the target platform. 
Don't forget to reset the board if you don't see the LED blinking right away!

```
$ newt -v load nrf52_boot
$ newt -v load nrf52_adc
```

<br>

**Note:** If you want to erase the flash and load the image again, you can use JLinkExe to issue an `erase` command.

```
$ JLinkExe -device nRF52 -speed 4000 -if SWD
SEGGER J-Link Commander V5.12c (Compiled Apr 21 2016 16:05:51)
DLL version V5.12c, compiled Apr 21 2016 16:05:45

Connecting to J-Link via USB...O.K.
Firmware: J-Link OB-SAM3U128-V2-NordicSemi compiled Mar 15 2016 18:03:17
Hardware version: V1.00
S/N: 682863966
VTref = 3.300V


Type "connect" to establish a target connection, '?' for help
J-Link>erase
Cortex-M4 identified.
Erasing device (0;?i?)...
Comparing flash   [100%] Done.
Erasing flash     [100%] Done.
Verifying flash   [100%] Done.
J-Link: Flash download: Total time needed: 0.363s (Prepare: 0.093s, Compare: 0.000s, Erase: 0.262s, Program: 0.000s, Verify: 0.000s, Restore: 0.008s)
Erasing done.
J-Link>exit
$
```

<br>

### Building the BLE Services

The nrf52_adc app is a Bluetooth-enabled sensor app that will allow you to read the value of the eTape Water Level Sensor
via Bluetooth. So let's go through some of the code.

As with the [ble peripheral](bleprph/bleprph-app.md) app, we will advertise a couple of values from our app. The first is
not strictly necessary, but it will help us build an iOS app later. We've defiined a service and the characteristics in
that service in `bleadc.h` as follows:

```c
/* Sensor Data */
/* e761d2af-1c15-4fa7-af80-b5729002b340 */
static const uint8_t gatt_svr_svc_sns_uuid[16] = {
    0x40, 0xb3, 0x20, 0x90, 0x72, 0xb5, 0x80, 0xaf,
    0xa7, 0x4f, 0x15, 0x1c, 0xaf, 0xd2, 0x61, 0xe7 };
#define ADC_SNS_TYPE          0xDEAD
#define ADC_SNS_VAL           0xBEEF
#define ADC_SNS_STRING "eTape Water Level Sensor"

uint8_t gatt_adc_val; 
```

The first is the UUID of the service, followed by the 2 characteristics we are going to offer.
The first characteristic is going to advertise the *type* of sensor we are advertising, and
it will be a read-only characteristic. The secnd characteristic will be the sensor value
itself, and we will allow connected devices to 'subscribe' to it in order to get 
constantly-updated values.

The value that we'll be updating is also defined here as `gatt_adc_val`.

If we then go look at `gatt_srv.c` we can see the structure of the service and
characteristic offering that we set up:

```c

    {
        /*** Alert Notification Service. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid128 = BLE_UUID16(GATT_SVR_SVC_ALERT_UUID),
        .characteristics = (struct ble_gatt_chr_def[]) { {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_SUP_NEW_ALERT_CAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_NEW_ALERT),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_NOTIFY,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_SUP_UNR_ALERT_CAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_UNR_ALERT_STAT_UUID),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_NOTIFY,
        }, {
            .uuid128 = BLE_UUID16(GATT_SVR_CHR_ALERT_NOT_CTRL_PT),
            .access_cb = gatt_svr_chr_access_alert,
            .flags = BLE_GATT_CHR_F_WRITE,
        }, {
            0, /* No more characteristics in this service. */
        } },
    },
    {
        /*** Water Level Notification Service. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid128 = gatt_svr_svc_sns_uuid,
        .characteristics = (struct ble_gatt_chr_def[]) { {
            .uuid128 = BLE_UUID16(ADC_SNS_TYPE),
            .access_cb = gatt_svr_sns_access,
            .flags = BLE_GATT_CHR_F_READ,
        }, {
            .uuid128 = BLE_UUID16(ADC_SNS_VAL),
            .access_cb = gatt_svr_sns_access,
            .flags = BLE_GATT_CHR_F_NOTIFY,
        }, {
            0, /* No more characteristics in this service. */
        } },
    },
    {
        0, /* No more services. */
    },
};

```

You should recognize the first services from the [BLE Peripheral](bleprph/bleprph-intro.md)
tutorial earlier. We're just adding another Service, with 2 new Characteristics, to 
that application.

We'll need to fill in the function that will be called for this service, `gatt_srv_sns_access`
next so that the service knows what to do.

```c
static int
gatt_svr_sns_access(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt,
                          void *arg)
{
    uint16_t uuid16;
    int rc;

    uuid16 = ble_uuid_128_to_16(ctxt->chr->uuid128);
    assert(uuid16 != 0);

    switch (uuid16) {
    case ADC_SNS_TYPE:
        assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
        rc = os_mbuf_append(ctxt->om, ADC_SNS_STRING, sizeof ADC_SNS_STRING);
        BLEADC_LOG(INFO, "ADC SENSOR TYPE READ: %s\n", ADC_SNS_STRING);
        return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        
    case ADC_SNS_VAL:
        if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR) {
            rc = gatt_svr_chr_write(ctxt->om, 0,
                                    sizeof gatt_adc_val,
                                    &gatt_adc_val,
                                    &gatt_adc_val_len);
            return rc;
        } else if (ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR) {
            rc = os_mbuf_append(ctxt->om, &gatt_adc_val,
                                sizeof gatt_adc_val);
            return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
        }
    default:
        assert(0);
        return BLE_ATT_ERR_UNLIKELY;
    }                              
}
```

You can see that when the `ADC_SNS_TYPE` is read, we return the
Sensor Type we defined earlier. If the `ADC_SNS_VAL` we'll return the
`gatt_adc_val` value. 

If you build, load and run this application now, you will see all those Services and Characteristics
advertised, and you will even be able to read the "Sensor Type" String via the ADC_SNS_TYPE
Characteristic, but when you subscribe to the ADC_SNS_VALUE Characteristic, you
aren't getting any data. That's because we haven't set up the ADC Sensor yet, or
created an task to update the value.

<br>

### Creating the ADC Task

In order for the application to send new sensor readings to a connected device, we'll need
to create a new OS Task to gather values and update them. If you've worked through the
[Add tasks](task_lesson.md) tutorial, this should look familiar to you at this point.

First, in `main.c` we'll define all the task-related requirements:

```c
/* ADC Task settings */
#define ADC_TASK_PRIO           5
#define ADC_STACK_SIZE          (OS_STACK_ALIGN(336))
struct os_task adc_task;
bssnz_t os_stack_t adc_stack[ADC_STACK_SIZE];
```

We'll also need to define a task handler for that task:

```c
/**
 * Event loop for the ADC task.
 */
static void
adc_task_handler(void *unused)
{
    
    gatt_adc_val = 0; 
    int rc = 0;
        
    while (1) {
        gatt_adc_val++;
        uint16_t chr_val_handle;
        
        rc = ble_gatts_find_chr(gatt_svr_svc_sns_uuid,
                                  BLE_UUID16(ADC_SNS_VAL),
                                  NULL, &chr_val_handle);
        assert(rc == 0);

        ble_gatts_chr_updated(chr_val_handle);
        
        /* Wait 2 second */
        os_time_delay(OS_TICKS_PER_SEC*2);
        
    }
}
```

At this point you'll notice that we are just incrementing a value, not sending any actual 
sensor data. Be patient, we'll get there. We're initializiing our 'sensor' data
variable, `gatt_adc_val` and then heading into our task-loop. 

Once in the task loop, we use `ble_gatts_find_chr()` to get the handle for the 
characteristic we're updating. and then we let that characteristic know that
we've updated it's value by calling ` ble_gatts_chr_updated()` with the
handle for the characteristic. 

Finally we set the update frequency of the characteristic's data via a call to 
`os_time_delay()` though there are other meachanisms for doing this.

Now that we have this all done, you can actually run this app and see the 
'sensor' value increase when you're subscribed to it.

<br>

### Adding the eTape Water Sensor

Now that we have a fully functioning BLE App that we can subscribe to sensor
values from, it's time to turn that incrementing-counter into an actual sensor value!

### Conclusion

You have created, setup, compiled, loaded, and ran your first mynewt application
for an nrf52 board.

We have more fun tutorials for you to get your hands dirty. Be bold and work on the OS with tutorials on [writing a test suite](unit_test.md) or try enabling additional functionality such as [remote comms](project-target-slinky.md) or [Bluetooth Low Energy](bletiny_project.md) on your current board.

If you see anything missing or want to send us feedback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and blinking!





