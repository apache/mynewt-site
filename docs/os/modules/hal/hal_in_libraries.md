
# Creating Libraries using the HAL

This page describes the recommended way to implement libraries that 
utilize HAL functionality.

Consider the light switch example from the [HAL overview](hal.md) page.

The light switch module needs a GPIO pin to set
the light switch to on or off.  The module declares that the GPIO to 
control the light switch is declared elsewhere in one of two methods.

```no-highlight
   extern const int light_switch_gpio;
```

or

```no-highlight
    extern int light_switch_gpio = bsp_light_app_get_light_gpio();
```  

Which method a library uses 
(extern const versus function) depends on what functionality the library
might wish to declare.  The `extern const` model uses the smallest code 
footprint, but since its constant cannot be changed at runtime (based on 
the configuration of the device say).  The `extern function` call requires
the BSP to implement a function which allows flexibility to assign the 
GPIO for the light switch to be determined at runtime with a small expense of
slightly more code.

Then the `libs/light` would go on to use the specified GPIO during its runtime
execution. For example:

```no-highlight

    . . .

    void light_on(void) {
        . . .

        /* finally time to turn the light on */
        hal_gpio_set(light_switch_gpio);
    }
```

When you library user includes `libs/light` as a dependency and then builds
with **newt**, they will get an unresolved external for either `light_switch_gpio` 
or `bsp_light_app_get_light_gpio()` and will need to add to their BSP.

In their BSP, they can add 

```no-highlight
   const int light_switch_gpio = 5;
```

or

```no-highlight
   int bsp_light_app_get_light_gpio(void) {
        return my_configured_lightswitch_io();
   }
```

So where did the number `5` come from.  Their BSP already includes the specific
MCU that they are using. And their `mcu/xxx/hal_gpio.c` already defines 
the mapping between physical pins and the virtual device ids.  
So they can determine (when writing code) from their boards physical pinmap 
and from the `hal_gpio.c` MCU mapping which virtual device_id corresponds 
to the correct physical pin in their system.
 
### Discussion

This HAL model is simple, easy to use and offers adequate flexibility 
in using different physical resources at compile time.  Its main drawback 
is that its not possible to have a single application or library use two 
different underlying implementations of the API at the same time.

For example, consider the light app above.  Suppose there are two GPIO 
required, One is a GPIO that comes through the MCU port pins that controls
the lightswitch, but there is another GPIO that comes through an external SPI
display that controls the LED on the faceplate.  it would not be possible 
for the application to do this...

```no-highlight
   extern const int light_switch_gpio;
   extern const int face_plate__gpio;

    void light_on(void) {
        . . .

        /* finally time to turn the light on */
        hal_gpio_set(light_switch_gpio);

        /* turn the faceplate LED off */
        hal_gpio_clear(face_plate_gpio);
    }

```

See [Creating a New HAL](hal_creation.md) for a discussion of this and a 
description of the other hal interface paradigm.

