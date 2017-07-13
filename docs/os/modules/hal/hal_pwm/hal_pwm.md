# hal_pwm

The hardware independent interface to Pulse Width Modulators

### Description

Pulse Width Modulators (PWMs) are hardware devices that output digital waveforms
with programmable duty cycle and frequency.  They use a digital waveform
but can contiuously adjust the amount of power delivered to their load via
duty cycle.  They are often used to create analog waveforms via low pass filter, 
drive LEDs at various intensities, and control DC or servo motors.

For a description of PSM, see [wikipedia](https://en.wikipedia.org/wiki/Pulse-width_modulation)

### Definition

[hal_pwm.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_pwm.h)

### HAL_PWM Theory Of Operation

The HAL_PWM interface was designed with some specific use cases in mind.  It
was also designed to exploit a subset of the functionality provided by 
common PWM controllers.

Fundamentally, a PWM has at it root an N-bit COUNTER, a CLOCK source, one or 
more CAPTURE registers, and sometimes a TOP register.

The clock source feeds the COUNTER register which is continuously counting
(up or down), When the COUNTER is less than the value of the CAPTURE
register, the PWM outputs a logic HIGH.  When the counter is greater than
the CAPTURE register the PWM outputs logic LOW. When the counter reaches the TOP
register, it wraps back to zero.  If the PWM has no TOP register, it simply
wraps back to zero after reaching 2^N-1.

The HAL_PWM abstracts this implementation and provides methods to set the
PWM frequency and duty cycle.  The frequency is the rate at which the counter
wraps back to zero.  The duty cycle is the fraction of time the PWM is in 
logic HIGH state.

The HAL_PWM API provides a few methods to get information on the PWM.

| **Method Name** | ** Description ** |
|--------------|----------------------|
| hal_pwm_get_source_clock_freq | gets the frequency of the CLOCK that is driving the COUNTER 
| hal_pwm_get_resolution_bits | gets the number of bits in the COUNTER

To use a PWM via HAL_PWM, follow these simple steps.

1) initialize a PWM using `hal_pwm_init` -- this binds the driver to the device
for the specific PWM you are using
2) Optionally set the frequency of the PWM using `hal_pwm_set_frequency`
-- PWMs that support a TOP register have fine control over their frequency 
settings.  If this command is not supported by the PWM it will return an error 
and its likely that there is no TOP register; the frequency resolution is not 
finely adjustable.  See the BSP for coarse adjustment of the PWM frequency.  
3) Enable the PWM to output a specific duty cycle using the 
`hal_pwm_enable_duty_cycle` API

To change the duty cycle dynamically, just issue another 
`hal_pwm_enable_duty_cycle` command.

To disable the PWM waveform, use `hal_pwm_disable`.



