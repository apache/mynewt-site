Air Quality Sensor Project
--------------------------
This tutorial will show you how to set up and use the Senseair K30 air quality sensor with the nRF52 Development Kit. Afterwards, you can set it up via Bluetooth so you can read values remotely. 

.. contents::
   :local:
   :depth: 2

Prerequisites
~~~~~~~~~~~~~
- Complete one of the other tutorials (e.g. :doc:`Project Blinky <../blinky/blinky>`) to famliarize yourself with Mynewt
- Nordic nRF52 Development - PCA 10040
- Senseair K30 CO2 Sensor

Setting Up the Source Tree
~~~~~~~~~~~~~~~~~~~~~~~~~~

To start, create a new project under which you will do development for this application:

.. code-block:: console

        $ mkdir $HOME/src
        $ cd $HOME/src
        $ newt new air_quality

If you are using a different development board, you will need to know the board support package for that hardware. You can look up its location, add it your project, and fetch that along with the core OS components. Since the nRF52DK is supported in the Mynewt Core, we don't need to do much here.

Your project.yml file should look like this:

.. code-block:: console

        [user@IsMyLaptop:~/src/air_quality]$ emacs project.yml &
        [user@IsMyLaptop:~/src/air_quality]$ cat project.yml
        project.name: "air_quality"

        project.repositories:
            - apache-mynewt-core

        # Use github's distribution mechanism for core ASF libraries.
        # This provides mirroring automatically for us.
        #
        repository.apache-mynewt-core:
            type: github
            vers: 0-latest
            user: apache
            repo: mynewt-core

        [user@IsMyLaptop:~/src/air_quality]$ newt upgrade
        Downloading repository mynewt-core (commit: master) ...
        Downloading repository mynewt-nimble (commit: master) ...
        apache-mynewt-core successfully upgraded to version 0.0.0
        apache-mynewt-nimble successfully upgraded to version 0.0.0
        [user@IsMyLaptop:~/src/air_quality]$ ls repos/
        apache-mynewt-core

Next, create a target for the nRF52DK bootloader: 

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ newt target create boot_nrf52dk
    Target targets/boot_nrf52dk successfully created
    [user@IsMyLaptop:~/src/air_quality]$ newt target set boot_nrf52dk bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    Target targets/boot_nrf52dk successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52dk
    [user@IsMyLaptop:~/src/air_quality]$ newt target set boot_nrf52dk app=@mcuboot/boot/mynewt
    Target targets/boot_nrf52dk successfully set target.app to @mcuboot/boot/mynewt
    [user@IsMyLaptop:~/src/air_quality]$ newt target set boot_nrf52dk build_profile=optimized
    Target targets/boot_nrf52dk successfully set target.build_profile to optimized
    [user@IsMyLaptop:~/src/air_quality]$ newt target show
    @apache-mynewt-core/targets/unittest
        bsp=hw/bsp/native
        build_profile=debug
        compiler=compiler/sim
    targets/boot_nrf52dk
        app=@mcuboot/boot/mynewt
        bsp=@apache-mynewt-core/hw/bsp/nrf52dk
        build_profile=optimized
    targets/my_blinky_sim
        app=apps/blinky
        bsp=@apache-mynewt-core/hw/bsp/native
        build_profile=debug

Build the bootloader target and load it onto the board:

.. code-block:: console

    newt build boot_nrf52dk
    ....
    Linking boot.elf
    App successfully built: /Users/user/src/air_quality/bin/boot_nrf52dk/boot/mynewt/mynewt.elf
    [user@IsMyLaptop:~/src/air_quality]
    $ newt load boot_nrf52dk

Create a Test Project
~~~~~~~~~~~~~~~~~~~~~

Now that you have your system setup, you can start building the application. First you want to create a project for yourself - since we're eventually going to want to be able to access the data via Bluetooth, let's use the ``bleprph`` Bluetooth Peripheral project as the project template.

.. code-block:: console

        [user@IsMyLaptop:~/src/air_quality]$ mkdir apps/air_quality
        [user@IsMyLaptop:~/src/air_quality]$ cp repos/apache-mynewt-core/apps/bleprph/pkg.yml apps/air_quality/
        [user@IsMyLaptop:~/src/air_quality]$ cp -Rp repos/apache-mynewt-core/apps/bleprph/src apps/air_quality/

Modify the apps/air\_quality/pkg.yml for air_quality in order to change the *pkg.name* to be *apps/air\_quality*. You'll need to add the ``@apache-mynewt-core/`` path to all the package dependencies, since the app no longer resides within the apache-mynewt-core repository.

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ cat apps/air_quality/pkg.yml
    pkg.name: apps/air_quality
    pkg.type: app
    pkg.description: BLE Air Quality application.
    pkg.author: "Apache Mynewt <dev@mynewt.apache.org>"
    pkg.homepage: "http://mynewt.apache.org/"
    pkg.keywords:

    pkg.deps:
        - "@apache-mynewt-core/boot/split"
        - "@mcuboot/boot/bootutil"
        - "@apache-mynewt-core/kernel/os"
        - "@apache-mynewt-core/mgmt/imgmgr"
        - "@apache-mynewt-core/mgmt/newtmgr"
        - "@apache-mynewt-core/mgmt/newtmgr/transport/ble"
        - "@apache-mynewt-core/net/nimble/controller"
        - "@apache-mynewt-core/net/nimble/host"
        - "@apache-mynewt-core/net/nimble/host/services/ans"
        - "@apache-mynewt-core/net/nimble/host/services/gap"
        - "@apache-mynewt-core/net/nimble/host/services/gatt"
        - "@apache-mynewt-core/net/nimble/host/store/config"
        - "@apache-mynewt-core/sys/console/full"
        - "@apache-mynewt-core/sys/log/full"
        - "@apache-mynewt-core/sys/stats/full"
        - "@apache-mynewt-core/sys/sysinit"
        - "@apache-mynewt-core/sys/id"
        - "@apache-mynewt-core/net/nimble/transport/ram"
        - "@apache-mynewt-core/sys/shell"

Next create a target for it:

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ newt target create air_q
    Target targets/air_q successfully created
    [user@IsMyLaptop:~/src/air_quality]$ newt target set air_q bsp=@apache-mynewt-core/hw/bsp/nrf52dk
    Target targets/air_q successfully set target.bsp to @apache-mynewt-core/hw/bsp/nrf52dk
    [user@IsMyLaptop:~/src/air_quality]$ newt target set air_q app=apps/air_quality 
    Target targets/air_q successfully set target.app to apps/air_quality
    [user@IsMyLaptop:~/src/air_quality]$ newt target set air_q build_profile=debug
    Target targets/air_q successfully set target.build_profile to debug
    [user@IsMyLaptop:~/src/air_quality]$ newt build air_q
     ....
    Linking /Users/users/dev/myproj/bin/targets/air_q/app/apps/air_quality/air_quality.elf
    Target successfully built: targets/air_q

Create Packages For Drivers
~~~~~~~~~~~~~~~~~~~~~~~~~~~

We need to enable the SenseAir K30 CO2 sensor, which will connect to the board over a serial port. To start development of the
driver, you first need to create a package description for it, and add stubs for sources.

The first thing to do is to create the directory structure for your
driver:

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ mkdir -p libs/my_drivers/senseair/include/senseair
    [user@IsMyLaptop:~/src/air_quality]$ mkdir -p libs/my_drivers/senseair/src

Now you can add the files you need. You'll need a ``pkg.yml`` to describe the driver, and then header stub followed by source stub.

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/pkg.yml

.. code-block:: c

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
    pkg.description: Host side of the nimble Bluetooth Smart stack.
    pkg.author: "Apache Mynewt <dev@mynewt.apache.org>"
    pkg.homepage: "http://mynewt.apache.org/"
    pkg.keywords:
        - ble
        - bluetooth

    pkg.deps:
        - "@apache-mynewt-core/kernel/os"

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/include/senseair/senseair.h

.. code-block:: c

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

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ cat libs/my_drivers/senseair/src/senseair.c

.. code-block:: c

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

And add a dependency to this package in your project.yml file.

Here's the listing from apps/air\_quality/pkg.yml:

.. code-block:: console

    pkg.name: apps/air_quality
    pkg.type: app
    pkg.description: Air quality sensor test
    pkg.keywords:

    pkg.deps:
        - "@apache-mynewt-core/boot/split"
        - "@mcuboot/boot/bootutil"
        - "@apache-mynewt-core/kernel/os"
        ....
        - "@apache-mynewt-core/sys/id"
        - "@apache-mynewt-core/net/nimble/transport/ram"
        - "@apache-mynewt-core/sys/shell"
        - libs/my_drivers/senseair

Add a call to your ``main()`` to initialize this driver:

.. code-block:: console

        [user@IsMyLaptop:~/src/air_quality]$ diff project/blinky/src/main.c project/air_quality/src/main.c
        28a29
        > #include <senseair/senseair.h>
        190a192
        > senseair_init();
        [user@IsMyLaptop:~/src/air_quality

Add CLI Commands For Testing Drivers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

While developing the driver, it would be helpful to issue operations from the console to verify the driver is responding correctly. Since the nRF52DK only has one UART, which will be used to connect to the CO2 sensor, the console we'll use instead is the :doc:`Segger RTT Console <../tooling/segger_rtt>`. To configure this, make the following changes in your project's ``syscfg.yml`` file:

.. code-block:: console

    [user@IsMyLaptop:~/src/air_quality]$ cat targets/air_q/syscfg.yml
    syscfg.vals:
        # Enable the shell task.
        SHELL_TASK: 1
        # Use the RTT Console
        CONSOLE_UART: 0
        CONSOLE_RTT: 1

Then register your senseair command with the shell by adding the following to ``libs/my_drivers/senseair/src/senseair.c``

.. code-block:: c
    
    #include <syscfg/syscfg.h>
    #include <shell/shell.h>
    #include <console/console.h>
    #include <assert.h>


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

Build the target, create an image, and load it onto your board. Then run ``telnet localhost 19021`` to start the RTT Console. 

.. code-block:: console

        [user@IsMyLaptop:~]$ telnet localhost 19021
        Trying 127.0.0.1...
        Connected to localhost.
        Escape character is '^]'.
        SEGGER J-Link V6.30j - Real time terminal output
        J-Link OB-SAM3U128-V2-NordicSemi compiled Jan 12 2018 16:05:20 V1.0, SN=682771074
        Process: JLinkGDBServerCLExe
        x03 0x03 0x11 0x18 0x0f 0x09 0x6e 0x69 0x6d 0x62 0x6c 0x65 0x2d 0x62 0x6c 0x65 0x70 0x72 0x70 0x68 0x02 0x0a 0x00 0x00         0x00 0x00 0x00 0x00 
        000006 [ts=46872ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x8 ocf=0x8 status=0 
        000006 [ts=46872ssb, mod=4 level=1] GAP procedure initiated: advertise; disc_mode=2 adv_channel_map=0 own_addr_type=0         adv_filter_policy=0 adv_itvl_min=0 adv_itvl_max=0
        000006 [ts=46872ssb, mod=4 level=0] ble_hs_hci_cmd_send: ogf=0x08 ocf=0x0006 len=15
        000006 [ts=46872ssb, mod=4 level=0] 0x06 0x20 0x0f 0x30 0x00 0x60 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00           0x07 0x00 
        000006 [ts=46872ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x8 ocf=0x6 status=0 
        000006 [ts=46872ssb, mod=4 level=0] ble_hs_hci_cmd_send: ogf=0x08 ocf=0x000a len=1
        000006 [ts=46872ssb, mod=4 level=0] 0x0a 0x20 0x01 0x01 
        000006 [ts=46872ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x8 ocf=0xa status=0 
        000006 [ts=46872ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x0 ocf=0x0

        001215 compat> 

        001957 compat> help
        help
        002162 help
        002162 tasks                         
        002162 mpool                         
        002162 date                          
        002162 senseair                      
        002162 compat> senseair
        senseair
        002514 Yay! Somebody called!
        002514 compat> 

If you can see the ``senseair`` command, and get the proper response, you can connect the hardware to your board and start
developing code for the driver itself.

Using HAL for Drivers
~~~~~~~~~~~~~~~~~~~~~

We will connect the CO2 sensor using a serial port connection to the UART. We'll also use the HAL UART abstraction to do the UART port setup and data transfer. That way you don't need to have any platform dependent pieces within your little driver. Moreover, this also gives you the option to connect this sensor to another board, like Olimex or the Arduino Primo.

You will now see what the driver code ends up looking like. Here's the header file, filled in from the stub you created earlier:

.. code-block:: c

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
    };

    int senseair_init(int uartno);

    int senseair_read(enum senseair_read_type);

    #endif /* _SENSEAIR_H_ */

As you can see, logical UART number has been added to the init routine. A 'read' function has also been added, which is a blocking read. If you were making a commercial product, you would probably have a callback for reporting the results.

And here is the source for the driver:

.. code-block:: c

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
    #include <syscfg/syscfg.h>  
    #include <shell/shell.h>
    #include <console/console.h>
    #include <os/os.h>
        
    #include <hal/hal_uart.h>
        
    #include "senseair/senseair.h"
        
    static const uint8_t cmd_read_co2[] = {
        0xFE, 0X44, 0X00, 0X08, 0X02, 0X9F, 0X25
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
            console_printf("%s co2\n", argv[0]);
            return 0;
        }
        if (!strcmp(argv[1], "co2")) {
            type = SENSEAIR_CO2;
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

And your modified main() for senseair driver init.

.. code-block:: c

    int
    main(int argc, char **argv)
    {
        ....
        senseair_init(0);
        ....
        }

You can see from the code that you are using the HAL interface to open a UART port, and using OS semaphore as a way of blocking the task when waiting for read response to come back from the sensor.

Now comes the fun part: Hooking up the sensor! It's fun because a) hooking up a sensor is always fun and b) the SenseAir sensor's PCB is entirely unlabeled, so you'll have to trust us on how to hook it up.

You'll have to do a little soldering. I soldered some header pins to the SenseAir K30 board to make connecting wires easier using standard jumper wires, but you can also just solder wires straight to the board if you prefer.

Here's what your SenseAir board should look like once it's wired up:

.. figure:: ../pics/K30labeled.JPG
   :alt: SenseAir Wiring

   SenseAir Wiring

Now that you have that wired up, let's connect it to the nRF52DK board. Since we will be using the built-in UART, we can simply connect it to the pre-configured pins for TX (P.06) and RX (P.08). Here's what your board should look like once everything is connected: 

.. figure:: ../pics/nrf52labeled.JPG
   :alt: SenseAir and nRF52DK Wiring

   SenseAir and nRF52DK Wiring

Everything is wired and you're ready to go! Build and load your new app:

.. code-block:: console

    $ newt build air_q
    Building target targets/air_q
    Compiling apps/air_quality/src/main.c
    Archiving apps_air_quality.a
    Linking myproj/bin/targets/air_q/app/apps/air_quality/air_quality.elf
    Target successfully built: targets/air_q
    $ newt create-image air_q 1.0.0
    App image succesfully generated: myproj/bin/targets/air_q/app/apps/air_quality/air_quality.img
    $ newt load air_q
    Loading app image into slot 1

Now, you should be able to connect to your serial port and read values:

.. code-block:: console

    user@IsMyLaptop:~]$ telnet localhost 19021
    Trying 127.0.0.1...
    Connected to localhost.
    Escape character is '^]'.
    SEGGER J-Link V6.30j - Real time terminal output
    J-Link OB-SAM3U128-V2-NordicSemi compiled Jan 12 2018 16:05:20 V1.0, SN=682771074
    Process: JLinkGDBServerCLExe
    x03 0x03 0x11 0x18 0x0f 0x09 0x6e 0x69 0x6d 0x62 0x6c 0x65 0x2d 0x62 0x6c 0x65 0x70 0x72 0x70 0x68 0x02 0x0a 0x00 0x00         0x00 0x00 0x00 0x00 
    000006 [ts=46872ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x8 ocf=0x8 status=0 
    000006 [ts=46872ssb, mod=4 level=1] GAP procedure initiated: advertise; disc_mode=2 adv_channel_map=0 own_addr_type=0         adv_filter_policy=0 adv_itvl_min=0 adv_itvl_max=0
    000006 [ts=46872ssb, mod=4 level=0] ble_hs_hci_cmd_send: ogf=0x08 ocf=0x0006 len=15
    000006 [ts=46872ssb, mod=4 level=0] 0x06 0x20 0x0f 0x30 0x00 0x60 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x07       0x00 
    000006 [ts=46872ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x8 ocf=0x6 status=0 
    000006 [ts=46872ssb, mod=4 level=0] ble_hs_hci_cmd_send: ogf=0x08 ocf=0x000a len=1
    000006 [ts=46872ssb, mod=4 level=0] 0x0a 0x20 0x01 0x01 
    000007 [ts=54684ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x8 ocf=0xa status=0 
    000007 [ts=54684ssb, mod=4 level=0] Command complete: cmd_pkts=1 ogf=0x0 ocf=0x0


    000895 compat> 

    000998 compat> help
    help
    001414 help
    001414 tasks                         
    001414 mpool                         
    001414 date                          
    001414 senseair                      
    001414 compat> senseair
    senseair
    001714 senseair co2
    001714 compat> senseair co2
    senseair co2
    002098 Got 0
    002098 compat> senseair co2
    senseair co2
    002719 Got 1168
        

And you're getting valid readings! Congratulations!

Next we'll hook this all up via Bluetooth so that you can read those
values remotely.
