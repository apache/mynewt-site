# hal_spi


SPI (Serial Peripheral Interface) is a synchronous 4-wire serial interface
commonly used to connect components in embedded systems.

For a detailed description of SPI, see [Wikipedia](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus).

### Description

The Mynewt HAL interface supports the SPI master functionality only.  Future
version will support SPI slave functionality.


### Definition

[hal_spi.h](https://github.com/apache/incubator-mynewt-larva/blob/master/hw/hal/include/hal/hal_spi.h)

### HAL_SPI Theory Of Operation

SPI is called a 4-wire interface because of the 4 signals, MISO, MOSI, CLK, 
and SS.  The SS signal (slave select) is an active low signal that activates
a SPI slave device.  This is how a master "addresses" a particular slave
device.  Often this signal is also referred to as "chip select" as it
selects particular slave device for communications.

The Mynewt SPI HAL has blocking transfers.  This means that the API call
to transfer a byte will wait until the byte completes transmissions before
the function returns.

Since SPI is generally a shared communications bus, the hal_spi API allows
SPI runtime configuration to be compatible with the data format and speed of the 
slave device.  See the `hal_spi_config` method in the API above for a 
description of the available settings.  These settings are critical to the
operation of the slave device.

The Mynewt SPI HAL does not include built-in SS signaling.  Its up to the 
hal_spi user to control their own SS pins.  Typically applications will do 
this with GPIO.

An example of this would look like this (error handling excluded for brevity):

```no-highlight

        /* each device may have different settings */
        extern struct hal_spi_settings dev1;    
        extern struct hal_spi_settings dev2;

        gpio_init_out(SS_DEV_1, 1);
        gpio_init_out(SS_DEV_2, 1);
        hal_spi *pspi = hal_spi_init(SPI0);

        ...
        /* write a single byte (0) to device 1 */
        hal_spi_config(pspi, &dev1);
        gpio_clear(SS_DEV_1)
        rc = hal_spi_transfer(pspi, 0)
        gpio_set(SS_DEV_1)

        /* read a single byte from device 2 */
        hal_spi_config(pspi, &dev2);
        gpio_clear(SS_DEV_2)
        val = hal_spi_transfer(pspi, 0)
        gpio_set(SS_DEV_2)

```

Depending on the device's operation, it may be necessary or more efficient
to write or read multiple bytes in a single transaction.  An example is
shown below

```no-highlight

    void spi_write_buf(struct hal_spi *pspi, uint8_t *buf, int len) {
        char *ptr = buf;

        hal_spi_config(pspi, &dev2);
        gpio_clear(SS_DEV_2)
        while(len--  > 0) {
            val = hal_spi_transfer(pspi, (uint16_t) *ptr++)
        }
        gpio_set(SS_DEV_2)
    }
