## <font color="#F2853F" style="font-size:24pt">newt vals </font>

Displays valid values for the specified element type(s). Appropriate values must be chosen and assigned to one or more elements when defining a package or target. Element types currently available are the following:

* api
* app
* bsp
* build_profile
* compiler
* feature
* lib
* sdk
* target


#### Usage: 

```no-highlight
  newt vals <element-type> [element-types...] [flags]
```

#### Flags:
```no-highlight
    -h, --help=false: help for target
```

#### Global Flags:
```no-highlight
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -o, --outfile string    Filename to tee log output to
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|----------------- 
vals   | newt vals api | Shows the possible values for APIs a package may specify as required. For example, the `pkg.yml` for `adc` specifies that it requires the api named `ADC_HW_IMPL`, one of the values listed by the command.

#### Example output for `newt vals bsp`:

This lists all possible values that may be assigned to a target's bsp attribute.

```no-highlight
$ newt vals bsp
bsp names:
    @apache-mynewt-core/hw/bsp/arduino_primo_nrf52
    @apache-mynewt-core/hw/bsp/bmd300eval
    @apache-mynewt-core/hw/bsp/ci40
    @apache-mynewt-core/hw/bsp/frdm-k64f
    @apache-mynewt-core/hw/bsp/native
    @apache-mynewt-core/hw/bsp/nrf51-arduino_101
    @apache-mynewt-core/hw/bsp/nrf51-blenano
    @apache-mynewt-core/hw/bsp/nrf51dk
    @apache-mynewt-core/hw/bsp/nrf51dk-16kbram
    @apache-mynewt-core/hw/bsp/nrf52dk
    @apache-mynewt-core/hw/bsp/nucleo-f401re
    @apache-mynewt-core/hw/bsp/olimex_stm32-e407_devboard
    @apache-mynewt-core/hw/bsp/rb-nano2
    @apache-mynewt-core/hw/bsp/stm32f4discovery
$ newt target set sample_target bsp=@apache-mynewt-core/hw/bsp/rb-nano2
```
Obviously, this output will grow as more board support packages are added for new boards and MCUs.
