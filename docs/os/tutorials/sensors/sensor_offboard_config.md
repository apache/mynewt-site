## Changing the Default Configuration for a Sensor

This tutorial shows you how to change default configuration values for a sensor. It continues with the example in the  [Enabling an Off-Board Sensor in an Existing Application](/os/tutorials/sensors/sensor_offboard_config.md) tutorial.

The tutorial uses an off-board sensor, but the procedure is very similar for an onboard sensor.

###Prerequisite 

Complete the [Enabling an Off-Board Sensor in an Existing Application](/os/tutorials/sensors/sensor_offboard_config.md). 

### Overview on How to Initialize the Configuration Values for a Sensor

The sensor creator package, `hw/sensor/creator`, creates an os device for a sensor in the kernel and initializes the sensor with a default configuration.  The general steps to configure a sensor device are:

1. Open the os device for the sensor.
2. Initialize the sensor driver configuration data structure with default values.
3. Calls the configuration function that the sensor device driver exports.  Each sensor device driver exports a `<sensorname>_config()` function.
4. Close the os device for the sensor.

For the BNO055 sensor device, the creator package calls the local `config_bno055_sensor()` function to configure the sensor. The code excerpt for the function is shown below:

```c
static int
config_bno055_sensor(void)
{
    int rc;
    struct os_dev *dev;
    struct bno055_cfg bcfg;

    dev = (struct os_dev *) os_dev_open("bno055_0", OS_TIMEOUT_NEVER, NULL);
    assert(dev != NULL);

    bcfg.bc_units = BNO055_ACC_UNIT_MS2   | BNO055_ANGRATE_UNIT_DPS |
                    BNO055_EULER_UNIT_DEG | BNO055_TEMP_UNIT_DEGC   |
                    BNO055_DO_FORMAT_ANDROID;

    bcfg.bc_opr_mode = BNO055_OPR_MODE_NDOF;
    bcfg.bc_pwr_mode = BNO055_PWR_MODE_NORMAL;
    bcfg.bc_acc_bw = BNO055_ACC_CFG_BW_125HZ;
    bcfg.bc_acc_range =  BNO055_ACC_CFG_RNG_16G;
    bcfg.bc_use_ext_xtal = 1;
    bcfg.bc_mask = SENSOR_TYPE_ACCELEROMETER|
                   SENSOR_TYPE_MAGNETIC_FIELD|
                   SENSOR_TYPE_GYROSCOPE|
                   SENSOR_TYPE_EULER|
                   SENSOR_TYPE_GRAVITY|
                   SENSOR_TYPE_LINEAR_ACCEL|
                   SENSOR_TYPE_ROTATION_VECTOR;

    rc = bno055_config((struct bno055 *) dev, &bcfg);

    os_dev_close(dev);
    return rc;
}

```
### Changing the Default Configuration Values

You can change the default configuration in your application initialization code or directly edit the fields in the `config_bno055_sensor()` function in the `hw/sensor/creator/sensor_creator.c` file. 

This tutorial shows you how to add the code to `apps/sensor_tests/src/main.c` to remove the accelerometer from the configured sensor type. 
<br>


#### Step 1: Adding the Sensor Device Driver Header File

Add the bno055 device driver header file:

```
#include <bno055/bno055.h> 

```
<br>
#### Step 2: Adding a New Configuration Function 

Add the `sensors_test_config_bno055()` function and copy the code from the `config_bno055_sensor()` function:

```
static int
sensors_test_config_bno055(void)
{
    int rc;
    struct os_dev *dev;
    struct bno055_cfg bcfg;

    dev = (struct os_dev *) os_dev_open("bno055_0", OS_TIMEOUT_NEVER, NULL);
    assert(dev != NULL);

    bcfg.bc_units = BNO055_ACC_UNIT_MS2   | BNO055_ANGRATE_UNIT_DPS |
                    BNO055_EULER_UNIT_DEG | BNO055_TEMP_UNIT_DEGC   |
                    BNO055_DO_FORMAT_ANDROID;

    bcfg.bc_opr_mode = BNO055_OPR_MODE_NDOF;
    bcfg.bc_pwr_mode = BNO055_PWR_MODE_NORMAL;
    bcfg.bc_acc_bw = BNO055_ACC_CFG_BW_125HZ;
    bcfg.bc_acc_range =  BNO055_ACC_CFG_RNG_16G;
    bcfg.bc_use_ext_xtal = 1;
    bcfg.bc_mask = SENSOR_TYPE_ACCELEROMETER|
                   SENSOR_TYPE_MAGNETIC_FIELD|
                   SENSOR_TYPE_GYROSCOPE|
                   SENSOR_TYPE_EULER|
                   SENSOR_TYPE_GRAVITY|
                   SENSOR_TYPE_LINEAR_ACCEL|
                   SENSOR_TYPE_ROTATION_VECTOR;

    rc = bno055_config((struct bno055 *) dev, &bcfg);

    os_dev_close(dev);
    return rc;
}

```
<br>
#### Step 3: Changing the Default Configuration Settings

Delete the `SENSOR_TYPE_ACCELEROMETER` type from the `bcfg.bc_mask` initialization:

```c

static int
sensors_test_config_bno055(void)
{
   int rc
       ...

   /* Delete the SENSOR_TYPE_ACCELEROMETER from the mask */
   bcfg.bc_mask = SENSOR_TYPE_MAGNETIC_FIELD|
                  SENSOR_TYPE_GYROSCOPE|
                  SENSOR_TYPE_EULER|
                  SENSOR_TYPE_GRAVITY|
                  SENSOR_TYPE_LINEAR_ACCEL|
                  SENSOR_TYPE_ROTATION_VECTOR;

    rc = bno055_config((struct bno055 *) dev, &bcfg);

    os_dev_close(dev);
    return rc;

```
<br>

#### Step 4: Calling the Configuration Function From main()

Add the `int rc` declaration and the function call to  `sensors_test_config_bno055()` in the `main()` function:


```c

    /* Add rc for the return value from sensors_test_config_bno055() */
    int rc;

        ....
    /* Add call to sensors_test_config_bno055() and abort on error */
    rc = sensors_test_config_bno055();
    assert(rc == 0);

    /* log reboot */
    reboot_start(hal_reset_cause());

    /*
     * As the last thing, process events from default event queue.
     */
    while (1) {
        os_eventq_run(os_eventq_dflt_get());
    }
```
<br>
#### Step 5: Building a New Application Image

Run the `newt build nrf52_bno055_test` and the `newt create-image nrf52_bno055_test 2.0.0` commands to rebuild the application and create a new image.

<br>
#### Step 6: Loading the New Image and Rebooting the Device

Run the `newt load nrf52_bno055_test` commad to load the image, and power the device OFF and On.

<br>
#### Step 7: Verifing the Sensor is Configured with the New Values

Start up a terminal emulator, and run the `sensor list` command to verify the accelerometer (0x1) is not a configured:

```no-highlight
045930 compat> sensor list
046482 sensor dev = bno055_0, configured type = 0x2 0x4 0x200 0x1000 0x2000 0x4000 
046484 compat>

```
<br>
#### Step 8: Verifying that the Sensor Framework Does not Read Non Configured Sensors

Run the `sensor read` command to read data from the accelerometer:
```no-highlight

046484 compat> sensor read bno055_0 0x1 -n 5
092387 Cannot read sensor bno055_0

```
