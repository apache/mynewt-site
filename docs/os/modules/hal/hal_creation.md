
# Creating New HAL Interfaces

## HAL API

A HAL is always starts with a header file with function declarations 
for your HAL, with the first argument of all functions the virtual 
device_id of the device you are controlling.  

For example, in [`hal_gpio.h`](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_gpio.h) 
the device enumeration is the first argument to all methods and called `pin`.

```no-highlight
    void hal_gpio_set(int pin);
```

The device_id (in this case called `pin`) is not a physical device 
(actual pin), but a virtual pin identified defined by the 
implementation of the HAL (and documented in the implementation of the HAL)

Below this, there have been two paradigms for HAL interface to date.  They are 
discussed below.

## Direct HAL Interface

In one HAL paradigm called **direct HAL**, this is the only component of the HAL
interface.   Implementers of this HAL would create a source file that implements
these methods.  

This has the advantage of being simple, small, and low execution overhead.

It has the disadvantage that its not possible to have two different implementations
of the same **direct HAL** within the same image. Said another way, if I create
a **direct HAL** `hal_foo.h`, there can be many implementations of 
`xxx/hal_foo.c` but only one can be included in a project.  

For example, support there is an ADC attached directly to the MCU and an ADC
that is attached via SPI.  There would be no way in this simple paradigm
to use both these devices from the HAL API at the same time.

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

Although the GPIO interface today for Mynewt uses the **direct HAL** let's illustrate
what it might look like for an indirect HAL.  

The API `hal_gpio.h` is identical.

There would be an additional header file `hal_gpio_int.h` which describes the 
driver interface for underlying implementations.  It looks similar to the 
hal API except is driven by function pointers.


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

An implementation file `hal/hal_gpio.c` would perform the mapping as 
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

**NOTE**: In this example where there are 32 GPIO, it may be memory inefficient
to have 32 structures around to basically call the same functions.  In 
Mynewt today, the hal_gpio is a **direct HAL** and does not have this overhead.
More HAL paradigms may be added in the future to address the flexibility of the 
**indirect HAL** with the memory efficiency of the **direct HAL**

