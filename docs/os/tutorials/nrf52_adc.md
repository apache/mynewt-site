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

uint16_t gatt_adc_val; 
```

The first is the UUID of the service, followed by the 2 characteristics we are going to offer.
The first characteristic is going to advertise the *type* of sensor we are advertising, and
it will be a read-only characteristic. The second characteristic will be the sensor value
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
created a task to update the value.

<br>

### Creating the ADC Task

In order for the application to send new sensor readings to a connected device, we'll need
to create a new OS Task to gather values and update them. If you've worked through the
[Add tasks](task_lesson.md) tutorial, this should look familiar to you at this point.

First, in `main.c` we'll define all the ADC-related things we'll need:

```c
/* ADC */
#include "nrf.h"
#include "app_util_platform.h"
#include "app_error.h"
#include <adc/adc.h>
#include <adc_nrf52/adc_nrf52.h>
#include <adc_nrf52/adc_nrf52.h>
#include "nrf_drv_saadc.h"

nrf_drv_saadc_config_t adc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
```

Next we need to add the task-related requirements:

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

### Implementing an Analog to Digital Converter (ADC)

So far we have a functioning BLE Peripheral device that will update a counter
and send that counter's value to any connected device that asks for it. It's
a lot, but it's still a far cry from useful. What we realy need is to add a
real sensor! The sensor we're using, the eTape Liquid Level Sensor, is a
pretty basic Analog Sensor. As the fluid level changes, the voltage output
of the sensor changes. In order to read this value, we'll need to access
the ADC on the nrf52dk, and that's going to take a bit of work. 

If we look at the configuration for the project by running `newt target config nrf52_adc`
you'll see the configuration of the ADC:

```no-highlight
* PACKAGE: hw/bsp/nrf52dk
  * Setting: ADC_0
    * Description: TBD
    * Value: 1
  * Setting: ADC_0_INTERRUPT_PRIORITY
    * Description: TBD
    * Value: SAADC_CONFIG_IRQ_PRIORITY
  * Setting: ADC_0_OVERSAMPLE
    * Description: TBD
    * Value: SAADC_CONFIG_OVERSAMPLE
  * Setting: ADC_0_RESOLUTION
    * Description: TBD
    * Value: SAADC_CONFIG_RESOLUTION
  * Setting: BSP_NRF52
    * Description: TBD
    * Value: 1
```

Next we can look in `hw/bsp/nrf52dk/src/hal_bsp.c`
and make sure the proper device-creation takes place:

```c
#if MYNEWT_VAL(ADC_0)
static struct adc_dev os_bsp_adc0;
static nrf_drv_saadc_config_t os_bsp_adc0_config = {
    .resolution         = MYNEWT_VAL(ADC_0_RESOLUTION),
    .oversample         = MYNEWT_VAL(ADC_0_OVERSAMPLE),
    .interrupt_priority = MYNEWT_VAL(ADC_0_INTERRUPT_PRIORITY),
};
#endif
```

And also make sure that it gets properly initialized in the 
`hal_bsp_init()` function:

```
#if MYNEWT_VAL(ADC_0)
    rc = os_dev_create((struct os_dev *) &os_bsp_adc0, "adc0",
            OS_DEV_INIT_KERNEL, OS_DEV_INIT_PRIO_DEFAULT,
            nrf52_adc_dev_init, &os_bsp_adc0_config);
    assert(rc == 0);
#endif
```


### Adding the eTape Water Sensor

Now that we have a fully functioning BLE App that we can subscribe to sensor
values from, it's time to turn that incrementing-counter into an actual sensor value!

As previous;y mentioned, we're going to be using an eTape Water Level Sensor. You can 
get one from [Adafruit](https://www.adafruit.com/products/1786). 

We're going to use the sensor as a resistive sensor, and the setup is very simple. 
I'll be using a 'breadboard` to put this all together for illustrative purposes. 
First, attach a jumper-wire from Vdd on the board to the breadboard.
Next, attach a jumper wire from pin P0.03 on the board to the breadboard. This will be
our ADC-in. The sensor should have come with a 560 ohm resistor, so plug that
into the baord between Vdd and ADC-in holes. Finally, attach a jumper from
GND on the board to your breadboard. At this point, your breadboard should look
like this:

![Bread Board Setup](pics/breadboard.png)

Now attach one of the middle 2 leads from the sensor to ground on the breadboad and 
the other middle lead to the ADC-in on the breadboard. Your breadboard should now look
like this:

![Bread Board Final](pics/adc-demo-1.png)

And yhour eTape Sensor should look like this (at least if you have it mounted in a
graduated cylinder as I do).

![eTape Sensor Setup](pics/adc-demo-2.png)

That concludes the hardware portion. Easy!

<br>

### Reading the eTape Water Sensor Values

This is the meat of the application. We've got our BLE application broadcasting and we can connect
to it and get notified when sensor values change. And we've got our sensor all wired
up correctly. So let's now make sure the correct values get sent.

First we'll make some changes to the `adc_task_handler()` function to properly initialize
the ADC.

```c
    struct adc_dev *adc;
    nrf_saadc_channel_config_t cc =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);
    cc.gain = NRF_SAADC_GAIN1_6;
    cc.reference = NRF_SAADC_REFERENCE_INTERNAL;
    adc = (struct adc_dev *) os_dev_open("adc0", 0, &adc_config);
    assert(adc != NULL);
    
    adc_chan_config(adc, 0, &cc);
    
    sample_buffer1 = malloc(adc_buf_size(adc, ADC_NUMBER_CHANNELS, ADC_NUMBER_SAMPLES));
    sample_buffer2 = malloc(adc_buf_size(adc, ADC_NUMBER_CHANNELS, ADC_NUMBER_SAMPLES));
    memset(sample_buffer1, 0, adc_buf_size(adc, ADC_NUMBER_CHANNELS, ADC_NUMBER_SAMPLES));
    memset(sample_buffer2, 0, adc_buf_size(adc, ADC_NUMBER_CHANNELS, ADC_NUMBER_SAMPLES));
    
    adc_buf_set(adc, sample_buffer1, sample_buffer2,
            adc_buf_size(adc, ADC_NUMBER_CHANNELS, ADC_NUMBER_SAMPLES));
    adc_event_handler_set(adc, adc_read_event, (void *) NULL);
```

A few things need to be said about this part, as it is the most confusing. First, 
we're using a **default** configuration for the ADC Channel via the `NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE`
macro. The important part here is that we're actually using `AIN1`. I know what you're thinking, "But 
we want ADC-0!" and that's true. The board is actually labelled 'A0, A1, A2' etc., and the actual pin 
numbers are also listed on the board, which seems handy. At first. But it gets messy very
quickly.

If you try to use AIN0, and then go poke around in the registers while this is running, 

```
(gdb) p/x {NRF_SAADC_Type}0x40007000
...
 CH = {{
      PSELP = 0x1,
      PSELN = 0x0,
      CONFIG = 0x20000,
      LIMIT = 0x7fff8000
    }, 
```

You'll see that the pin for channel 0 is set to 1, which corresponts to AIN0, but that's **NOT**
the same as A0 -- pin P0.03, the one we're using. For that, you use AIN1, which would set the
pin value to 2. Messy. 


The only other thing to note here is that we're using the internal reference voltage, rather than
setting our own. There's nothing wrong with that, but since we are, we'll have to crank up
the gain a bit by using `NRF_SAADC_GAIN1_6`.

So, since that's all clear, our task-loop in the `adc_task_handler()` function is extremely simple:

```c
while (1) {
    adc_sample(adc);
    /* Wait 2 second */
    os_time_delay(OS_TICKS_PER_SEC * 2);
}
```

We'll just sample the ADC every 2 seconds or so.

If you noticed above the call to `adc_event_handler_set()` then you'll also know that we'd 
better define that callback function we set `adc_read_event()`

```c
int
adc_read_event(struct adc_dev *dev, void *arg, uint8_t etype,
        void *buffer, int buffer_len)
{
    int i;
    int adc_result;
    uint16_t chr_val_handle;
    int rc;
    for (i = 0; i < ADC_NUMBER_SAMPLES; i++) {
        rc = adc_buf_read(dev, buffer, buffer_len, i, &adc_result);
        if (rc != 0) {
            goto err;
        }
        
        gatt_adc_val = adc_result_mv(dev, 0, adc_result);
        rc = ble_gatts_find_chr(gatt_svr_svc_sns_uuid, BLE_UUID16(ADC_SNS_VAL), NULL, &chr_val_handle);
        assert(rc == 0);
        ble_gatts_chr_updated(chr_val_handle);
    }

    adc_buf_release(dev, buffer, buffer_len);
    return (0);
err:
    return (rc);
}
```

Whenever the ADC has a sample for us in its buffer, we'll run through the samples available, convert them
to millivolts, and then update the NOTIFY value so that any connected devices get the updated
sensor values.

<br>

### Conclusion

Congratulations, you've now completed both a hardware project and a software project by connecting a
sensor to your device and using Mynewt to read data from that sensor and send it via Bluetooth
to a connected device. That's no small feat!

If you see anything missing or want to send us feedback, please do so by signing up for 
appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and sensing!





