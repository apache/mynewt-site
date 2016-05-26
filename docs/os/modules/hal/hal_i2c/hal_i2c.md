# hal_i2c


The hardware independent interface to I2C Devices.

###Description

An Inter-Integrated Circuit (I²C ] I-squared-C) bus is a multi-master,
multi-save serial interface used to connect components on a circuit board
and often peripherals devices located off the circuit board.

I2C is often though of as a 2-wire protocol because it uses two wires (SDA, SCL)
to send data between devices.  

For a detailed description of I2C, see the [I²C wikipedia page](https://en.wikipedia.org/wiki/I²C)

###Definition

[hal_i2c.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_i2c.h)

###HAL_I2C Theory Of Operation

An I²C transaction typically involves acquiring the bus, sending and/or receiving
data and release the bus.  The bus acquisition portion is important because
the bus is typically multi-master so other devices may be trying to read/write
the same peripheral.  

HAL_I2C implements a master interface to the I²C bus.  Typical usage of the 
interface would involve the following steps.

1. initialize an I²C device using `hal_i2c_init`
2. when you want to perform an I²C transaction:
    1. Issue the `hal_i2c_begin()` command.    
    2. Issue one or more  `hal_i2c_read` and/or `hal_i2c_write` commands
    3. Issue the `hal_i2c_end()` command.

An addition API was added called `hal_i2c_probe`.  This command combines
`hal_i2c_begin()`, `hal_i2c_read`, and `hal_i2c_end()` to try to read 0-bytes
from a specific bus address.  its intended to provide an easy way to probe
the bus for a specific device.  NOTE: if the device is write-only, it will 
not appear with this command.

###HAL_I2C Data

Data to read/write is passed to the hal_i2c APIs via the 

```
struct hal_i2c_master_data {
    uint8_t  address;   /* destination address */
    uint16_t len;       /* number of bytes to transmit or receive */
    uint8_t *buffer;    /* data buffer for transmit or receive */
};
```

`buffer` is a pointer to the data to send.  `len` is the number of bytes
to send over the bus.  `address` is a 7-bit bus address of the device.

When  I²C builds its address, it uses the 7-bit address plus a 1-bit R/W 
(read/write) indicator to identify the device and direction of the 
transaction.  Thus when using this API, you should use a 7-bit address
in the data structure and ensure that address is a value between 0-127.


As an example, consider an  I²C  device address that looks like this:

| B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
|---|---|---|---|---|---|---|---|
| 1 | 0 | 0 | 0 | 1 | 1 | 0 |R/W|
|MSB|   |   |   |   |   |   |LSB|

In the HAL_I2C API you would communicate with this device with address 
`0b1000110`, which is hex 0x46 or decimal 70.  The I²C drive would add the R/W bit
and transmit it as hex 0x8D or 0x8D depending whether it was a read or
write command.






