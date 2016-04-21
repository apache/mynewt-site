
# Creating New HAL Interfaces

## HAL API

A HAL always includes header file with function declarations 
for the HAL functionality in `/hw/hal/include/hal`.
The first argument of all functions in the interface include the virtual 
device_id of the device you are controlling.  

For example, in [`hal_gpio.h`](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_gpio.h) 
the device enumeration is the first argument to all methods and called `pin`.

```no-highlight
    void hal_gpio_set(int pin);
```

The device_id (in this case called `pin`) is not a physical device 
(actual hardware pin), but a virtual pin which is defined by the 
implementation of the HAL (and documented in the implementation of the HAL)

Below this, there are two different paradigms for HAL interface.  They are 
discussed below.


## Direct HAL Interface

In one HAL paradigm called **direct HAL**, the header file is the only component 
of the HAL interface.   Implementers of this HAL would create a source file
that implements these methods.  

This has the advantage of being simple, small, and low execution overhead.

It has the disadvantage that its not possible to have two different implementations
of the same **direct HAL** within the same image. Said another way, if I create
a **direct HAL** `hal_foo.h`, there can be many implementations of 
`xxx/hal_foo.c` but only one can be included in a project.  

For example, support there is an ADC attached directly to the MCU and an ADC
that is attached via SPI.  There would be no way in this simple paradigm
to use both these devices from the HAL API at the same time.

Current Direct HAL interfaces include:

| **Hal Name** | ** Interface File ** |
|--------------|----------------------|
| [hal_gpio]   |  [hal_gpio.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_gpio.h)     |
| [hal_uart]   |  [hal_uart.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_uart.h)     |
| [hal_cputime]|  [hal_cputime.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_cputime.h)    |

This brings up the second paradigm.

## Indirect HAL Interface

The second paradigm, **indirect HAL**  preserves the simple function 
API with enumerated device_id but adds a small layer of code in the 
HAL to allow different implementations to connect at runtime.

The abstract interface contains three components:

* A header file `hal_foo.h` that includes the API above with a `device_id`
*  An implementation `hal/hal_foo.c` which maps the `device_id` to 
a driver interface structure.  
*  A driver interface structure that is defined for the underlying implementation

Using this simple model, the user can be exposed to a simple function 
interface (without structures or function pointers) and the system can provide
a different software implementation for each device id.

Although the GPIO interface for Mynewt uses the **direct HAL**, we can describe
what it might look like for an indirect HAL.  

The API `hal_gpio.h` is identical with a direct or indirect HAL.

In the indirect HAL there is an additional header file `hal_gpio_int.h`
 which describes the driver interface for underlying implementations.  It 
looks similar to the HAL API except is driven by function pointers.

```no-highlight
struct hal_gpio_funcs {
    void (*hgpio_set)(void);
    . . .
};

struct hal_gpio_int {
    struct hal_gpio_funcs funcs;
}

const struct hal_gpio_int *bsp_gpio_dev(uint8_t pin);
```
The BSP specific function is what will map the specific pin (device_id) 
to its implementation.

This is different than the **direct HAL** which maps this virtual/physical 
device pairing in the MCU implementation.  For the **indirect HAL** the 
mapping has to be done in the BSP since that is the place where multiple 
disparate devices can be enumerated into a single `device_id` space.

An interface file `hal/hal_gpio.c` would perform the mapping as 
follows:

```no-highlight
    void hal_gpio_set(int pin) {
        const struct hal_gpio_int *pgpio;
        pgpio = bsp_get_gpio_device(pin);
        if(pgpio) {
            pgpio->funcs.set();
        }
    }
```

The implementer of GPIO functionality (say in `mcu/xxx/hal_gpio.c`) would 
implement the structure and provide the function pointers.

```no-highlight
void xxx_hal_gpio_set(void) {
    /* implementation for this particular gpio device */
    . . .
}

struct hal_gpio_int xxx_hal_gpio = {
    .funcs.hgpio_set = xxx_hal_gpio_set;
}
```

This leaves the BSP implementation to complete the function 

```no-highlight
const struct hal_gpio_int *bsp_gpio_dev(uint8_t pin) {
    switch(pin) {
        case 0:
            return &xxx_hal_gpio;
        case 1:
            return &yyy_hal_gpio;
    }
    return NULL;
}
```

**NOTE**: In this example there could be 10s of GPIO. It may be memory inefficient
to have that many `hal_gpio_int` structures around to basically call the 
same functions.  In Mynewt today, the hal_gpio is a **direct HAL** and does 
not have this overhead. More HAL paradigms may be added in the future to address 
the flexibility of the **indirect HAL** with the memory efficiency of the **direct HAL**

Current Indirect HAL interfaces include:

| **Hal Name** | ** Interface File ** |
|--------------|----------------------|
| [adc_int](hal_adc/hal_adc_int.md)    |  [hal_adc_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_adc_int.h)    
| [dac_int](hal_dac/hal_dac_int.md)    |  [hal_dac_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_dac_int.h)
| [flash_int](hal_flash/hal_flash_int.md)    |  [hal_flash_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_flash_int.h) 
| [pwm_int](hal_pwm/hal_pwm_int.md)    |  [hal_pwm_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_pwm_int.h)  
| [i2c_int](hal_i2c/hal_i2c_int.md)    |  [hal_i2c_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_i2c_int.h)    | [spi_int](hal_spi/hal_spi_int.md)    |  [hal_spi_int.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_spi_int.h)    