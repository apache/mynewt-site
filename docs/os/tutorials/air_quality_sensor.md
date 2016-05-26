## Air quality sensor project

### Setting up source tree for stuff you need

To start with, you need to create a new project under which you will do this development. So you type in:

```no-highlight
    $ mkdir $HOME/src
    $ cd $HOME/src
    $ newt new air_quality
```

Let's say you are using STM32F3discovery board as the platform. You know you need the board support package for that hardware. You can look up its location, add it your project, and fetch that along with the core OS components.

To make this happen, you'll need to modify the project.yml in your project's root directory.

```no-highlight
    [user@IsMyLaptop:~/src/air_quality]$ emacs project.yml &
    [user@IsMyLaptop:~/src/air_quality]$ cat project.yml
    project.name: "air_quality"

    project.repositories:
        - apache-mynewt-core
        - mynewt_stm32f3

    # Use github's distribution mechanism for core ASF libraries.
    # This provides mirroring automatically for us.
    #
    repository.apache-mynewt-core:
        type: github
        vers: 0-latest
        user: apache
        repo: incubator-mynewt-core

    repository.mynewt_stm32f3:
        type: github
        vers: 0-latest
        user: runtimeinc
        repo: mynewt_stm32f3
    [user@IsMyLaptop:~/src/air_quality]$ newt install
    apache-mynewt-core
    mynewt_stm32f3
    [user@IsMyLaptop:~/src/air_quality]$ ls repos/
    apache-mynewt-core	mynewt_stm32f3
```

Good. You want to make sure you have all the needed bits for supporting your board; so you decide to build the blinky project for the platform first.

Now create a target for it and build it. Easiest way to proceed is to copy the existing target for blinky, and modify it to build for STM32F3Discovery board.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt target copy my_blinky_sim blink_f3
Target successfully copied; targets/my_blinky_sim --> targets/blink_f3
[user@IsMyLaptop:~/src/air_quality]$ newt target set blink_f3 bsp=@mynewt_stm32f3/hw/bsp/stm32f3discovery
Target targets/blink_f3 successfully set target.bsp to @mynewt_stm32f3/hw/bsp/stm32f3discovery
[user@IsMyLaptop:~/src/air_quality]$ newt build blink_f3
Compiling hal_bsp.c
...
Linking blinky.elf
App successfully built: /Users/user/src/air_quality/bin/blink_f3/apps/blinky/blinky.elf
```

Good.

You know that this platform uses bootloader, which means you have to create a target for that too.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt target create boot_f3
Target targets/boot_f3 successfully created
[user@IsMyLaptop:~/src/air_quality]$ newt target show
@apache-mynewt-core/targets/unittest
    bsp=hw/bsp/native
    build_profile=debug
    compiler=compiler/sim
targets/blink_f3
    app=apps/blinky
    bsp=@mynewt_stm32f3/hw/bsp/stm32f3discovery
    build_profile=debug
targets/boot_f3
targets/my_blinky_sim
    app=apps/blinky
    bsp=@apache-mynewt-core/hw/bsp/native
    build_profile=debug
[user@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 bsp=@mynewt_stm32f3/hw/bsp/stm32f3discovery
Target targets/boot_f3 successfully set target.bsp to @mynewt_stm32f3/hw/bsp/stm32f3discovery
[user@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 app=@apache-mynewt-core/apps/boot
Target targets/boot_f3 successfully set target.app to @apache-mynewt-core/apps/boot
[user@IsMyLaptop:~/src/air_quality]$ newt target set boot_f3 build_profile=optimized
Target targets/boot_f3 successfully set target.build_profile to optimized
```

And then build it, and load it onto the board.
```no-highlight
newt build boot_f3
....
Linking boot.elf
App successfully built: /Users/user/src/air_quality/bin/boot_f3/apps/boot/boot.elf
[user@IsMyLaptop:~/src/air_quality]$ newt load boot_f3
```

Next you must download the targets to board, and see that the LED actually blinks. You plug in the STM32F3 discovery board to your laptop, and say:

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt load blink_f3
Downloading /Users/user/src/air_quality/bin/blink_f3/apps/blinky/blinky.img to 0x08009000
Open On-Chip Debugger 0.9.0 (2015-05-28-12:05)
....
xPSR: 0x01000000 pc: 0x0800026c msp: 0x10002000
auto erase enabled
Error: couldn't open /Users/user/src/air_quality/bin/blink_f3/apps/blinky/blinky.img

Error: exit status 1

load - Load app image to target for <target-name>.

Usage:
  newt load [flags]

Examples:
  newt load <target-name>


Global Flags:
  -l, --loglevel string   Log level, defaults to WARN. (default "WARN")
  -o, --outfile string    Filename to tee log output to
  -q, --quiet             Be quiet; only display error output.
  -s, --silent            Be silent; don't output anything.
  -v, --verbose           Enable verbose output when executing commands.
exit status 1
```

Ah. Forgot to create an image out of the blinky binary. Note that every time you want to build and load a new firmware image to target board, you need to run 'create-image' on it.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt create-image blink_f3 0.0.1
App image successfully generated: /Users/user/src/air_quality/bin/blink_f3/apps/blinky/blinky.img
Build manifest: /Users/user/src/air_quality/bin/blink_f3/apps/blinky/manifest.json
[user@IsMyLaptop:~/src/air_quality]$ newt load blink_f3 0.0.1
```

And it's blinking.

Shortcut for doing build/create-image/load/debug steps all in one is 'newt run' command. Check out the usage from command line help.

### Create test project

Now that you have your system setup, you can start creating your own stuff.
First you want to create a project for yourself - you can start by getting project template from blinky, as it pretty much has what you want.

```no-highlight
    [user@IsMyLaptop:~/src/air_quality]$ mkdir apps/air_quality
    [user@IsMyLaptop:~/src/air_quality]$ cp repos/apache-mynewt-core/apps/blinky/pkg.yml apps/air_quality/
    [user@IsMyLaptop:~/src/air_quality]$ mkdir apps/air_quality/src
    [user@IsMyLaptop:~/src/air_quality]$ cp repos/apache-mynewt-core/apps/blinky/src/main.c apps/air_quality/src/
```

Then you modify the apps/air_quality/pkg.yml for air_quality in order to change the *pkg.name* to be *apps/air_quality*.
You also need to point the package dependencies to point to packages in apache-mynewt-core repository.
STM32F3discovery board has limited amount of memory, so you must also switch your libc to be baselibc, instead of the standard one.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ cat apps/air_quality/pkg.yml
pkg.name: apps/air_quality
pkg.type: app
pkg.description: Air quality sensor test
pkg.keywords:

pkg.deps:
    - "@apache-mynewt-core/libs/console/full"
    - "@apache-mynewt-core/libs/newtmgr"
    - "@apache-mynewt-core/libs/os"
    - "@apache-mynewt-core/libs/shell"
    - "@apache-mynewt-core/sys/config"
    - "@apache-mynewt-core/sys/log"
    - "@apache-mynewt-core/sys/stats"
    - "@apache-mynewt-core/libs/baselibc"
```

And create a target for it:
```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt target create air_q
Target targets/air_q successfully created
[user@IsMyLaptop:~/src/air_quality]$ newt target set air_q bsp=@mynewt_stm32f3/hw/bsp/stm32f3discovery
Target targets/air_q successfully set target.bsp to @mynewt_stm32f3/hw/bsp/stm32f3discovery
[user@IsMyLaptop:~/src/air_quality]$ newt target set air_q app=apps/air_quality 
Target targets/air_q successfully set target.app to apps/air_quality
[user@IsMyLaptop:~/src/air_quality]$ newt target set air_q build_profile=debug
Target targets/air_q successfully set target.build_profile to debug
[user@IsMyLaptop:~/src/air_quality]$ newt build air_q
 ....
Linking air_quality.elf
App successfully built: /Users/user/src/air_quality/bin/air_q/apps/air_quality/air_quality.elf
```

### Create packages for drivers

One of the sensors you want to enable is SenseAir K30, which will connect to the board over serial port.
To start development of the driver, you first need to create a package description for it, and add stubs for sources.

So you add few files. pkg.yml to describe the driver, and then header stub followed by source stub.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/pkg.yml
```

```c
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
    - "@apache-mynewt-core/hw/hal"
```

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/include/senseair/senseair.h
```

```c
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
[user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/src/senseair.c
```

```c
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

Here's from apps/air_quality/pkg.yml

```no-highlight
pkg.name: apps/air_quality
pkg.type: app
pkg.description: Air quality sensor test
pkg.keywords:

pkg.deps:
    - "@apache-mynewt-core/libs/console/full"
    - "@apache-mynewt-core/libs/newtmgr"
    - "@apache-mynewt-core/libs/os"
    - "@apache-mynewt-core/libs/shell"
    - "@apache-mynewt-core/sys/config"
    - "@apache-mynewt-core/sys/log"
    - "@apache-mynewt-core/sys/stats"
    - "@apache-mynewt-core/libs/baselibc"
    - libs/my_drivers/senseair
```

And add a call to your main() to initialize this driver.

```no-highlight
    [user@IsMyLaptop:~/src/air_quality]$ diff project/blinky/src/main.c project/air_quality/src/main.c
    28a29
    > #include <senseair/senseair.h>
    190a192
    > senseair_init();
    [user@IsMyLaptop:~/src/air_quality
```

And then build it to make sure all goes well.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt build air_q
Compiling senseair.c
Archiving senseair.a
Linking air_quality.elf
App successfully built: /Users/user/src/air_quality/bin/air_q/apps/air_quality/air_quality.elf
```

All looks good.

### Add CLI commands for testing drivers

While developing the driver, you want to issue operations from console asking it to do stuff. The way to do this is to register your command handler with shell. Whenever your custom command is issued, you can respond to it.

The way you do this is first adding a dependency to shell package for your senseair driver. So you change libs/my_drivers/senseair/pkg.yml to have the following:

```no-highlight
pkg.name: libs/my_drivers/senseair
pkg.deps:
    - "@apache-mynewt-core/hw/hal"
    - "@apache-mynewt-core/libs/shell"
```

And then register your shell command in *senseair_init()*.

```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/src/senseair.c
 ....
```

```c
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
    [user@IsMyLaptop:~]$ minicom -D /dev/tty.usbserial-AH02MIE2
    
    
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
[user@IsMyLaptop:~/src/air_quality]$ mkdir hw
[user@IsMyLaptop:~/src/air_quality]$ mkdir hw/bsp

[user@IsMyLaptop:~/src/air_quality]$ cp -R repos/mynewt_stm32f3/hw/bsp/stm32f3discovery hw/bsp/stm32f3discovery_with_senseair
```

Then you modify the pkg.yml in the copied BSP to assign name for this package. And modify the dependency for MCU package to point to mynewt_stm32f3 repository.

```no-highlight
    [user@IsMyLaptop:~/src/air_quality]$ grep pkg.name hw/bsp/stm32f3discovery_with_senseair/pkg.yml
    pkg.name: "hw/bsp/stm32f3discovery_with_senseair"
    [user@IsMyLaptop:~/src/air_quality]$ tail -2 hw/bsp/stm32f3discovery_with_senseair/pkg.yml
pkg.deps:
    - "@mynewt_stm32f3/hw/mcu/stm/stm32f3xx"

```

And you want to use this BSP with my target. So you change the BSP in the target definition.

Here's your new target.
```no-highlight
[user@IsMyLaptop:~/src/air_quality]$ newt target show air_q
targets/air_q
    app=apps/air_quality
    bsp=hw/bsp/stm32f3discovery_with_senseair
    build_profile=debug
```

You add the 2nd serial port to my new BSP. Go to hw/bsp/stm32f3discovery_with_senseair directory to do this.

Modify the include/hal/bsp.h to increase UART_CNT to 2, and add a definition of the 2nd logical UART. You will use this in your sensor driver.

```c 
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

```c
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

```c 
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
    uint8_t rx_data[32]; 
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

```c
int
main(int argc, char **argv)
{
    ....
    senseair_init(1);
    ....
    }
```
You can see from the code that you are using the HAL interface to open a UART port, and using OS semaphore as a way of blocking the task when waiting for read response to come back from the sensor.
