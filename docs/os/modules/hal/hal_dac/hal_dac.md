
# hal_dac


The hardware independent interface to Digital To Analog Converters.

### Description

For a description of Digital to Analog Converters, see 
[wikipedia](https://en.wikipedia.org/wiki/Digital-to-analog_converter)

### Definition

[hal_dac.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_dac.h)

### HAL_DAC Theory Of Operation

DACs have differing conversion resolution (bits), reference voltages (Volts)
and conversion times (sample rate).

The hal_dac implements function to query some of these values from the
BSP.


| **Method Name** | ** Description ** |
|--------------|----------------------|
| hal_dac_get_bits | gets the resolution of the DAC in bits.  For example if the DAC is 10 bits, it supports setting of value from 0 through 2^10 - 1 = 1023.
| hal_dac_get_ref_mv | gets the underlying reference voltage for the DAC in millivolts.  For example, if the DAC is 10 bits and the reference voltage is 5000 mV setting the DAC value to 1023 corresponds to 5V; setting the DAC value to 0 corresponds to 0 volts.  

From these two pieces of information the application or library can
determine how to set a specific output voltage.  NOTE: each underlying
hardware may return different values for these settings.

The API to set the DAC output value is blocking. This means the function 
will return after the DAC value has been programmed.

Future HAL_DAC APIs will include A DMA interface to automatically write 
DMA data to the DAC based in events.

The Mynewt HAL also supports a [PWM](../hal_pwm/hal_pwm.md) interface which can 
be used in conjunction with a low pass filter to set an analog output voltage.
