
# Using HAL in Your Libraries

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
    extern int bsp_light_app_get_light_gpio();
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
execution. For example this shows both ways the library could interface to the 
bsp to get the right GPIO:

```no-highlight
    void light_on(void) {
        . . .
        /* finally time to turn the light on */
        hal_gpio_set(light_switch_gpio);
    }

    void light_on(void) {
        . . .
        int pin = bsp_light_app_get_light_gpio();
        /* finally time to turn the light on */
        hal_gpio_set(pin);
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

The user can determine (when writing code) from their boards physical pinmap 
and from the `hal_gpio.c` MCU mapping which virtual device_id corresponds 
to the correct physical pin in their system.
 