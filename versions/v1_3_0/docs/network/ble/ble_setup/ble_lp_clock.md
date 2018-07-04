## Configure clock for controller

The NimBLE stack uses OS cputime for scheduling various events inside controller.
Since the code of controller is optimized to work with 32768 Hz clock, the OS
cputime has to be configured accordingly.

To make things easier, controller package (`net/nimble/controller`) defines new
system configuration setting `BLE_LP_CLOCK` as sets it to `1` so other packages
can be configured if necessary. The next section describes configuration required
for controller to work properly.

### System configuration

**Note:** All BSPs based on nRF5x have below settings automatically applied when
`BLE_LP_CLOCK` is set, there is no need to configure this in application.

The following things need to be configured for NimBLE controller to work properly:

- OS cputime frequency shall be set to `32768`
- OS cputime timer source shall be set to 32768 Hz clock source
- Default 1 MHz clock source can be disabled if not used by application
- 32768 Hz clock source shall be enabled
- Crystal settling time shall be set to non-zero value (see [below](#crystal-settle-time-configuration))

For example, on nRF52 platform timer 5 can be used as source for 32768 Hz clock.
Also, timer 0 can be disabled since this is the default source for OS cputime
clock and is no longer used. The configuration will look as below:

```
syscfg.vals:
    OS_CPUTIME_FREQ: 32768
    OS_CPUTIME_TIMER_NUM: 5
    TIMER_0: 0
    TIMER_5: 1
    BLE_XTAL_SETTLE_TIME: 1500
```

On nRF51 platform the only difference is to use timer 3 instead of timer 5.

On platforms without 32768 Hz crystal available it usually can be synthesized by
setting `XTAL_32768_SYNTH` to `1` - this is also already configured in existing
BSPs.

### Clock accuracy

Controller needs to know clock source accuracy since this affects sleep time and has
to be taken into account when scheduling Bluetooth events. The configuration variable
`BLE_LL_OUR_SCA` defines clock drift (in ppm) while `BLE_LL_MASTER_SCA` is an
enumerated value derived from clock drift value and shall be set as follows:

- SCA between 251 and 500 ppm = 0
- SCA between 151 and 250 ppm = 1
- SCA between 101 and 150 ppm = 2
- SCA between 76 and 100 ppm = 3
- SCA between 51 and 75 ppm = 4
- SCA between 31 and 50 ppm = 5
- SCA between 21 and 30 ppm = 6
- SCA between 0 and 20 ppm = 7

The default value of 60 ppm is large enough to work with most platforms with LFXO.
For platforms without LFXO (e.g. using internal RC oscillator or synthesized clock
instead) it shall be changed if necessary.

Note that using clock drift value larger than necessary will impact battery life since
controller will use wider margin for scheduling Bluetooth events thus reducing sleep
time. For this reason it is recommended to adjust clock drift value to match clock
source used on platform.

### Crystal settle time configuration

The configuration variable `BLE_XTAL_SETTLE_TIME` is used by the controller to turn
on the necessary clock source(s) for the radio and associated peripherals prior to
Bluetooth events (advertising, scanning, connections, etc). For the nRF5x platforms,
the HFXO needs to be turned on prior to using the radio and the `BLE_XTAL_SETTLE_TIME`
must be set to accommodate this time. The amount of time required is board dependent,
so users must characterize their hardware and set `BLE_XTAL_SETTLE_TIME` accordingly.
The current value of 1500 microseconds is a fairly long time and was intended to work
for most, if not all, platforms.

Note that changing this time will impact battery life with the amount depending on the
application. The HFXO draws a fairly large amount of current when running so keeping
this time as small as possible will reduce overall current drain.