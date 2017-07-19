# hal_adc

The hardware independent interface to Analog To Digital Controllers

###Description

Analog to Digital converters (ADCs) read analog values (voltage) and convert
them to digital values to be used in your applications.  For a description
of ADC, see [wikipedia](https://en.wikipedia.org/wiki/Analog-to-digital_converter)

###Definition

[hal_adc.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_adc.h)

###HAL_ADCs Theory Of Operation

ADCs have different conversion rates, resolution (bits) and reference voltages.

The HAL_ADC has APIs to allow the application or library to query the capabilities
of a specific ADC.


| **Method Name** | ** Description ** |
|--------------|----------------------|
| hal_adc_get_bits | gets the resolution of the ADC in bits.  For example if the ADC is 10 bits, a read will return a value from 0 through 2^10 - 1 = 1023.
| hal_adc_get_ref_mv | gets the underlying reference voltage for the ADC in millivolts.  For example, if the ADC is 10 bits and the reference voltage is 5000 mV a ADC reading of 1023 corresponds to 5V; a ADC reading of 0 corresponds to 0 volts.  

Given this information, the application or library could convert any reading
to millivolts.  Since this is a common operation, the HAL_ADC API has a helper
function to perform this function: `hal_adc_to_mv()`.
 
The current HAL_ADC API provides a blocking read command to initiate an ADC
conversion, and return the result of that conversion.  Conversion time is
hardware dependent, but this is not an instantaneous operation.  Libraries
can use the [hal_cputime](../hal_cputime/hal_cpu_timer.md) APIs to 
time conversions if that is relevant to the application.

Future HAL_ADC APIs will include periodic ADC conversion, non-blocking ADC
conversion and direct-to-memory DMA conversion. 




