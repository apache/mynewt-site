## Air quality sensor project

### Setting up source tree for stuff you need

To start with, you need to create a new app under which you will do this development. So you type in:

```no-highlight
$ mkdir $HOME/src
$ cd $HOME/src
$ newt new air_quality
```

Let's say you are using STM32F3discovery board for this project. You know you need the board support package for that hardware. You can look up its location in the repository, fetch the package list from there, and install the egg for the BSP.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt app add-pkg-list mynewt_stm32f3 https://github.com/runtimeinc/mynewt_stm32f3.git
Downloading pkg-list.yml from https://github.com/runtimeinc/mynewt_stm32f3.git/master... ok!
Verifying pkg-list.yml format...
 ok!
Package list mynewt_stm32f3 successfully installed to application.
[user@IsMyLaptop:~/src/air_quality]$ newt pkg install hw/bsp/stm32f3discovery
Downloading mynewt_stm32f3 from https://github.com/runtimeinc/mynewt_stm32f3.git/master... ok!
Installing hw/bsp/stm32f3discovery
Installing hw/mcu/stm/stm32f3xx
Error: No package libs/cmsis-core found
```

Ooops. You forgot to bring in the package list for larva itself. That's the one with most of the packages. Including libs/cmsis-core.

You want the latest and greatest from larva, so you want to bring in the 'develop' branch. Note that normally the use of the more stable master branch is recommended. In that case you would drop the '-b develop' from command line.

However, you want to bring in the packages from develop branch. To make that happen you say:

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt app add-pkg-list -b develop larva https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git
Downloading pkg-list.yml from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva.git/develop... ok!
Verifying pkg-list.yml format...
 ok!
Package list larva successfully installed to application.
[marko@IsMyLaptop:~/src/air_quality]$ newt pkg install libs/cmsis-core          Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/develop... ok!
Installing libs/cmsis-core
Installation was a success!
```

That's better. You want to make sure you have all the needed bits for supporting your board; so you decide to build the blinky project for it first.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt pkg install project/blinky
Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/develop... ok!
Installing project/blinky
Installing libs/console/full
Installing libs/newtmgr
Installing libs/json
Installing libs/shell
Installing sys/config
Installing sys/log
Installing sys/stats
Installation was a success!
[marko@IsMyLaptop:~/src/air_quality]$ newt pkg install compiler/arm-none-eabi-m4
Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/develop... ok!
Installing compiler/arm-none-eabi-m4
Installation was a success!
```
As you can see, this brought in quite a few other dependencies as well.


Now create a target for it and build it.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target create blink_f3
Creating target blink_f3
Target blink_f3 successfully created!
[marko@IsMyLaptop:~/src/air_quality]$ newt target set blink_f3 arch=cortex_m4
Target blink_f3 successfully set arch to cortex_m4
[marko@IsMyLaptop:~/src/air_quality]$ newt target set blink_f3 bsp=hw/bsp/stm32f3discovery
Target blink_f3 successfully set bsp to hw/bsp/stm32f3discovery
[marko@IsMyLaptop:~/src/air_quality]$ newt target set blink_f3 compiler=arm-none-eabi-m4
Target blink_f3 successfully set compiler to arm-none-eabi-m4
[marko@IsMyLaptop:~/src/air_quality]$ newt target set blink_f3 compiler_def=debug
Target blink_f3 successfully set compiler_def to debug
[marko@IsMyLaptop:~/src/air_quality]$ newt target set blink_f3 project=blinky
Target blink_f3 successfully set project to blinky
[marko@IsMyLaptop:~/src/air_quality]$ newt target build blink_f3
Building target blink_f3 (project = blinky)
 ...
[marko@IsMyLaptop:~/src/air_quality]$ newt target build blink_f3
Building target blink_f3 (project = blinky)
Building project blinky
Linking blinky.elf
/usr/local/Cellar/gcc-arm-none-eabi-49/20150609/bin/../lib/gcc/arm-none-eabi/4.9.3/../../../../arm-none-eabi/bin/ld: /Users/marko/src/air_quality/project/blinky//bin/blink_f3/blinky.elf section `.text' will not fit in region `FLASH'
/usr/local/Cellar/gcc-arm-none-eabi-49/20150609/bin/../lib/gcc/arm-none-eabi/4.9.3/../../../../arm-none-eabi/bin/ld: region `FLASH' overflowed by 5180 bytes
collect2: error: ld returned 1 exit status
```

The error indicates that the images need to be smaller for this board, so you decide to switch over to using baselibc instead of libc.

To do that, you modify the project's egg file project/blinky/pkg.yml. And add *libs/baselibc* to list of package dependencies (pkg.deps).

Now:
```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target build blink_f3
Building target blink_f3 (project = blinky)
....
Archiving libstm32f3discovery.a
Compiling main.c
Building project blinky
Linking blinky.elf
Successfully run!
```

That's better.

You know that this platform uses bootloader, which means you have to create a target for that too. And download the bootloader package.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target create boot_f3
Creating target boot_f3
Target boot_f3 successfully created!
[marko@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 arch=cortex_m4
newTarget boot_f3 successfully set arch to cortex_m4
[marko@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 bsp=hw/bsp/stm32f3discovery
newtTarget boot_f3 successfully set bsp to hw/bsp/stm32f3discovery
[marko@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 compiler=arm-none-eabi-m4
Target boot_f3 successfully set compiler to arm-none-eabi-m4
[marko@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 compiler_def=optimized
Target boot_f3 successfully set compiler_def to optimized
[marko@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 project=boot
Target boot_f3 successfully set project to boot
[marko@IsMyLaptop:~/src/air_quality]$ newt pkg install project/boot
Downloading larva from https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva/develop... ok!
Installing project/boot
Installing fs/nffs
Installing fs/fs
Installing libs/bootutil
Installing libs/mbedtls
Installing libs/console/stub
Installation was a success!
```

And then build it:
```no-highlight
newt target build boot_f3
....
Linking boot.elf
Successfully run!
```

Next you must download the targets to board, and see that the LED actually blinks. You plug in the STM32F3 discovery board to your laptop, and say:

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target download blink_f3
Downloading with /Users/marko/src/air_quality/hw/bsp/stm32f3discovery/stm32f3discovery_download.sh
Downloading /Users/marko/src/air_quality/project/blinky/bin/blink_f3/blinky.img to 0x08008000
Open On-Chip Debugger 0.9.0 (2015-05-28-12:05)
...
target state: halted
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x0800026c msp: 0x10002000
auto erase enabled
Error: couldn't open /Users/marko/src/air_quality/project/blinky/bin/blink_f3/blinky.img

Error: exit status 1
exit status 1
```

Ah. Forgot to create an image out of the blinky binary.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target create-image blink_f3 0.0.1
Building target blink_f3 (project = blinky)
Compiling hal_flash.c
Archiving libhal.a
Compiling cons_tty.c
Archiving libfull.a
Compiling hal_uart.c
Archiving libstm32f3xx.a
Compiling hal_bsp.c
Archiving libstm32f3discovery.a
Compiling main.c
Building project blinky
Linking blinky.elf
[marko@IsMyLaptop:~/src/air_quality]$ newt target download blink_f3
Downloading with /Users/marko/src/air_quality/hw/bsp/stm32f3discovery/stm32f3discovery_download.sh
```

And it's blinking.

### Create test project

Now that you have your system setup, you can start creating your own stuff.
First you want to create a project for myself - you can start by getting project template from blinky, as it pretty much has what you want.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ mkdir project/air_quality
[marko@IsMyLaptop:~/src/air_quality]$ cp project/blinky/pkg.yml project/air_quality/
[marko@IsMyLaptop:~/src/air_quality]$ mkdir project/air_quality/src
[marko@IsMyLaptop:~/src/air_quality]$ cp project/blinky/src/main.c project/air_quality/src/
```

Then you modify the pkg.yml for air_quality in order to change the *pkg.name* to be *project/air_quality*.

And create a target for it:
```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target create air_q
newt targCreating target air_q
Target air_q successfully created!
[marko@IsMyLaptop:~/src/air_quality]$ newt target set air_q arch=cortex_m4
Target air_q successfully set arch to cortex_m4
[marko@IsMyLaptop:~/src/air_quality]$ newt target set air_q bsp=hw/bsp/stm32f3discovery
Target air_q successfully set bsp to hw/bsp/stm32f3discovery
[marko@IsMyLaptop:~/src/air_quality]$ newt target set air_q compiler=arm-none-eabi-m4
Target air_q successfully set compiler to arm-none-eabi-m4
[marko@IsMyLaptop:~/src/air_quality]$ newt target set air_q compiler_def=debug
Target air_q successfully set compiler_def to debug
[marko@IsMyLaptop:~/src/air_quality]$ newt target set air_q project=air_quality
Target air_q successfully set project to air_quality
[marko@IsMyLaptop:~/src/air_quality]$ newt target build air_q
   ....
Successfully run!
```

### Create packages for drivers

One of the sensors you want to enable is SenseAir K30, which will connect to my board over serial port.
To start development of the driver, you first need to create a package description for it, and add stubs for sources.

So you add few files. pkg.yml to describe the driver, and then header stub followed by source stub.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/pkg.yml
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# 
#  http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
pkg.name: libs/my_drivers/senseair
pkg.deps:
    - hw/hal
```

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/include/senseair/senseair.h
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/
#ifndef _SENSEAIR_H_
#define _SENSEAIR_H_

void senseair_init(void);

#endif /* _SENSEAIR_H_ */

```

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/src/senseair.c
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

void
senseair_init(void)
{
}
```

And add dependency to this package in my project yml file.

Here's from project/air_quality/pkg.yml
```no-highlight
pkg.name: project/air_quality
pkg.vers: 0.8.0
pkg.description: Basic example application which blinks an LED.
pkg.author: Marko Kiiskila <marko@runtime.io>
pkg.homepage: http://mynewt.apache.org/os/get_acclimated/project2/
pkg.repository: https://git-wip-us.apache.org/repos/asf/incubator-mynewt-larva
pkg.keywords:


pkg.deps:
    - libs/console/full
    - libs/newtmgr
    - libs/os
    - libs/shell
    - libs/baselibc
    - sys/config
    - sys/log
    - sys/stats
    - libs/my_drivers/senseair
```

And add a call to your main() to initialize this driver.
```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ diff project/blinky/src/main.c project/air_quality/src/main.c
28a29
> #include <senseair/senseair.h>
190a192
>     senseair_init();
[marko@IsMyLaptop:~/src/air_quality
```

And then build it to make sure all goes well.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target build air_q
Building target air_q (project = air_quality)
Building project air_quality
Successfully run!
```

All looks good.

### Add CLI commands for testing drivers

While developing the driver, you want to issue operations from console asking it to do stuff. The way to do this is to register your command handler with shell. Whenever your custom command is issued, you can respond to it.

The way you do this is first adding a dependency to shell package for your senseair driver. So you change libs/my_drivers/senseair/pkg.yml to have the following:
```no-highlight
pkg.name: libs/my_drivers/senseair
pkg.deps:
    - hw/hal
    - libs/shell
```

And then register your shell command in *senseair_init()*.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/src/senseair.c
 ....

#include <shell/shell.h>
#include <console/console.h>

static int senseair_shell_func(int argc, char **argv);
static struct shell_cmd senseair_cmd = {
	.sc_cmd = "senseair",
	.sc_cmd_func = senseair_shell_func,
};
	
void
senseair_init(void)
{
	int rc;

	rc = shell_cmd_register(&senseair_cmd);
	assert(rc == 0);
}

static int
senseair_shell_func(int argc, char **argv)
{
	console_printf("Yay! Somebody called!\n");
	return 0;
}
```

Then you build this, download to target, and start minicom on your console port.

```no-highlight
[marko@IsMyLaptop:~]$ minicom -D /dev/tty.usbserial-AH02MIE2


Welcome to minicom 2.7

OPTIONS: 
Compiled on Oct 12 2015, 07:48:30.
Port /dev/tty.usbserial-AH02MIE2, 13:44:40

Press CTRL-X Z for help on special keys

?
141964:Unknown command ?
?
143804:config   log     echo    ?       tasks   mempools 
143806:stat     senseair 
senseair
150644:Yay! Somebody called!
```

Now that's great. You can connect the hardware to board and start developing code for the driver itself.

### Use of HAL for drivers

The sensor has a serial port connection, and that's how you are going to connect to it. Your original BSP, hw/bsp/stm32f3discovery, has only one UART set up (as specified in src/hal_bsp.c, include/hal/bsp.h). Therefore, you need to create your own bsp which has configuration for this added hardware.

So in the shell you make a copy of the original BSP, and then change the package file a little.
```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ cp -R hw/bsp/stm32f3discovery hw/bsp/stm32f3discovery_with_senseair
```

Then you modify the pkg.yml in the copied BSP to assign name for this package.

```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ grep pkg.name hw/bsp/stm32f3discovery_with_senseair/pkg.yml
pkg.name: "hw/bsp/stm32f3discovery_with_senseair"
```

And you want to use this BSP with my target. So you change the BSP in the target definition.

Here's your new target.
```no-highlight
[marko@IsMyLaptop:~/src/air_quality]$ newt target show air_q                    air_q
	arch=cortex_m4
	bsp=hw/bsp/stm32f3discovery_with_senseair
	compiler=arm-none-eabi-m4
	compiler_def=debug
	name=air_q
	project=air_quality
	vers=0.0.1
```

You add the 2nd serial port to my new BSP.

You modify the include/hal/bsp.h to increase UART_CNT to 2, and add a definition of the 2nd logical UART. You will use this in your sensor driver.

```no-highlight
static const struct stm32f3_uart_cfg uart_cfg[UART_CNT] = {
    [0] = {
        .suc_uart = USART1,
        .suc_rcc_cmd = RCC_APB2PeriphClockCmd,
        .suc_rcc_dev = RCC_APB2Periph_USART1,
        .suc_pin_tx = 9,
        .suc_pin_rx = 10,
        .suc_pin_rts = 12,
        .suc_pin_cts = 11,
        .suc_pin_af = GPIO_AF_7,
        .suc_irqn = USART1_IRQn
    },
    [1] = {
        .suc_uart = USART2,
        .suc_rcc_cmd = RCC_APB1PeriphClockCmd,
        .suc_rcc_dev = RCC_APB1Periph_USART2,
        .suc_pin_tx = 19, /* PB3 */
        .suc_pin_rx = 20, /* PB4 */
        .suc_pin_rts = 1,
        .suc_pin_cts = 0,
        .suc_pin_af = GPIO_AF_7,
        .suc_irqn = USART2_IRQn
    }
};
```

With this in place, you can refer to serial port where your SenseAir sensor is by a logical number. This makes the code more platform independent - you could connect this sensor to another board, like Olimex. You will also use the HAL UART abstraction to do the UART port setup and data transfer. That way you don't need to have any platform dependent pieces within your little driver.

You will now see what the driver code ends up looking like. Here's the header file, filled in from stub you created earlier.

```no-highlight
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/
#ifndef _SENSEAIR_H_
#define _SENSEAIR_H_

enum senseair_read_type {
        SENSEAIR_CO2,
        SENSEAIR_TEMPERATURE,
        SENSEAIR_HUMIDITY
};

int senseair_init(int uartno);

int senseair_read(enum senseair_read_type);

#endif /* _SENSEAIR_H_ */
```

As you can see, logical UART number has been added to the init routine. A 'read' function has been added, which is a blocking read. If you were making a commercial product, you would probably have a callback for reporting the results.


And here is the source for the driver.

```no-highlight
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <string.h>

#include <shell/shell.h>
#include <console/console.h>
#include <os/os.h>

#include <hal/hal_uart.h>

#include "senseair/senseair.h"

static const uint8_t cmd_read_co2[] = {
    0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25
};
static const uint8_t cmd_read_temp[] = {
    0xFE, 0X44, 0X00, 0X12, 0X02, 0X94, 0X45
};
static const uint8_t cmd_read_humidity[] = {
    0xFE, 0x44, 0x00, 0x14, 0x02, 0x97, 0xE5
};

static int senseair_shell_func(int argc, char **argv);
static struct shell_cmd senseair_cmd = {
    .sc_cmd = "senseair",
    .sc_cmd_func = senseair_shell_func,
};

struct senseair {
    int uart;
    struct os_sem sema;
    const uint8_t *tx_data;
    int tx_off;
    int tx_len;
    uint8_t rx_data[32]; /* XXX what's the max? */
    int rx_off;
    int value;
} senseair;

static int
senseair_tx_char(void *arg)
{
    struct senseair *s = &senseair;
    int rc;

    if (s->tx_off >= s->tx_len) {
        /*
         * Command tx finished.
         */
        s->tx_data = NULL;
        return -1;
    }

    rc = s->tx_data[s->tx_off];
    s->tx_off++;
    return rc;
}

/*
 * CRC for modbus over serial port.
 */
static const uint16_t mb_crc_tbl[] = {
    0x0000, 0xcc01, 0xd801, 0x1400, 0xf001, 0x3c00, 0x2800, 0xe401,
    0xa001, 0x6c00, 0x7800, 0xb401, 0x5000, 0x9c01, 0x8801, 0x4400
};

static uint16_t
mb_crc(const uint8_t *data, int len, uint16_t crc)
{
    while (len-- > 0) {
        crc ^= *data++;
        crc = (crc >> 4) ^ mb_crc_tbl[crc & 0xf];
        crc = (crc >> 4) ^ mb_crc_tbl[crc & 0xf];
    }
    return crc;
}

static int
mb_crc_check(const void *pkt, int len)
{
    uint16_t crc, cmp;
    uint8_t *bp = (uint8_t *)pkt;

    if (len < sizeof(crc) + 1) {
        return -1;
    }
    crc = mb_crc(pkt, len - 2, 0xffff);
    cmp = bp[len - 2] | (bp[len - 1] << 8);
    if (crc != cmp) {
        return -1;
    } else {
        return 0;
    }
}

static int
senseair_rx_char(void *arg, uint8_t data)
{
    struct senseair *s = (struct senseair *)arg;
    int rc;

    if (s->rx_off >= sizeof(s->rx_data)) {
        s->rx_off = 0;
    }
    s->rx_data[s->rx_off] = data;
    s->rx_off++;

    if (s->rx_off == 7) {
        rc = mb_crc_check(s->rx_data, s->rx_off);
        if (rc == 0) {
            s->value = s->rx_data[3] * 256 + s->rx_data[4];
            os_sem_release(&s->sema);
        }
    }
    return 0;
}

void
senseair_tx(struct senseair *s, const uint8_t *tx_data, int data_len)
{
    s->tx_data = tx_data;
    s->tx_len = data_len;
    s->tx_off = 0;
    s->rx_off = 0;

    hal_uart_start_tx(s->uart);
}

int
senseair_read(enum senseair_read_type type)
{
    struct senseair *s = &senseair;
    const uint8_t *cmd;
    int cmd_len;
    int rc;

    if (s->tx_data) {
        /*
         * busy
         */
        return -1;
    }
    switch (type) {
    case SENSEAIR_CO2:
        cmd = cmd_read_co2;
        cmd_len = sizeof(cmd_read_co2);
        break;
    case SENSEAIR_TEMPERATURE:
        cmd = cmd_read_temp;
        cmd_len = sizeof(cmd_read_temp);
        break;
    case SENSEAIR_HUMIDITY:
        cmd = cmd_read_humidity;
        cmd_len = sizeof(cmd_read_humidity);
        break;
    default:
        return -1;
    }
    senseair_tx(s, cmd, cmd_len);
    rc = os_sem_pend(&s->sema, OS_TICKS_PER_SEC / 2);
    if (rc == OS_TIMEOUT) {
        /*
         * timeout
         */
        return -2;
    }
    return s->value;
}

static int
senseair_shell_func(int argc, char **argv)
{
    int value;
    enum senseair_read_type type;

    if (argc < 2) {
usage:
        console_printf("%s <co2|temp|humidity>\n", argv[0]);
        return 0;
    }
    if (!strcmp(argv[1], "co2")) {
        type = SENSEAIR_CO2;
    } else if (!strcmp(argv[1], "temp")) {
        type = SENSEAIR_TEMPERATURE;
    } else if (!strcmp(argv[1], "humidity")) {
        /*
         * timeout
         */
        return -2;
    }
    return s->value;
}

static int
senseair_shell_func(int argc, char **argv)
{
    int value;
    enum senseair_read_type type;

    if (argc < 2) {
usage:
        console_printf("%s <co2|temp|humidity>\n", argv[0]);
        return 0;
    }
    if (!strcmp(argv[1], "co2")) {
        type = SENSEAIR_CO2;
    } else if (!strcmp(argv[1], "temp")) {
        type = SENSEAIR_TEMPERATURE;
    } else if (!strcmp(argv[1], "humidity")) {
        type = SENSEAIR_HUMIDITY;
    } else {
        goto usage;
    }
    value = senseair_read(type);
    if (value >= 0) {
        console_printf("Got %d\n", value);
    } else {
        console_printf("Error while reading: %d\n", value);
    }
    return 0;
}

int
senseair_init(int uartno)
{
    int rc;
    struct senseair *s = &senseair;

    rc = shell_cmd_register(&senseair_cmd);
    if (rc) {
        return rc;
    }

    rc = os_sem_init(&s->sema, 1);
    if (rc) {
        return rc;
    }
    rc = hal_uart_init_cbs(uartno, senseair_tx_char, NULL,
      senseair_rx_char, &senseair);
    if (rc) {
        return rc;
    }
    rc = hal_uart_config(uartno, 9600, 8, 1, HAL_UART_PARITY_NONE,
      HAL_UART_FLOW_CTL_NONE);
    if (rc) {
        return rc;
    }
    s->uart = uartno;

    return 0;
}
```

And you modified your main() for senseair driver init.

```no-highlight
int
main(int argc, char **argv)
{
    ....
    senseair_init(1);
    ....
}
```

You can see from the code that you are using the HAL interface to open a UART port, and using OS semaphore as a way of blocking the task when waiting for read response to come back from the sensor.
