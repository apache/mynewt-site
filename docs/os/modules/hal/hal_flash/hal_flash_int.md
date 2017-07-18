# hal_flash_int

The API that flash drivers have to implement.

### Description

The BSP for the hardware will implement the structs defined in this API.

### Definition

[hal_flash_int.h](https://github.com/apache/incubator-mynewt-core/blob/master/hw/hal/include/hal/hal_flash_int.h)

### Examples

The Nordic nRF52 bsp implements the hal_flash_int API as seen in [hal_bsp.c](https://github.com/apache/incubator-mynewt-core/blob/master/hw/bsp/stm32f4discovery/src/hal_bsp.c)

```
const struct hal_flash *
hal_bsp_flash_dev(uint8_t id)
{
    /*
     * Internal flash mapped to id 0.
     */
    if (id != 0) {
        return NULL;
    }
    return &nrf52k_flash_dev;
}

```



