..
  #
  # Copyright 2020 Casper Meijn <casper@meijn.net>
  #
  # Licensed under the Apache License, Version 2.0 (the "License");
  # you may not use this file except in compliance with the License.
  # You may obtain a copy of the License at
  #
  #     http://www.apache.org/licenses/LICENSE-2.0
  #
  # Unless required by applicable law or agreed to in writing, software
  # distributed under the License is distributed on an "AS IS" BASIS,
  # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  # See the License for the specific language governing permissions and
  # limitations under the License.
  #

Charge control on PineTime
===========================================

This tutorial shows you how to get the charge control status on PineTime smartwatch.

.. contents::
  :local:
  :depth: 2

Prerequisites
~~~~~~~~~~~~~

Ensure that you meet the following prerequisites before continuing with
this tutorial:

-  Follow :doc:`Blinky on PineTime tutorial <../blinky/pinetime>` to create a 
   project with a basic application. You will extend that application in this 
   tutorial.
-  Make sure you have the charger input available. This can either be a fully 
   assembled PineTime (but this prevent you from accessing the SWD pins) or by
   mounting a wire to the 5V charger pad.

Charger hardware
~~~~~~~~~~~~~~~~

First a few words about the PineTime hardware. The PineTime smartwatch uses a 
SGM4056 charger chip. The chip gets it's power from the USB port via the
charging pads at the back of the watch. The charger takes care of battery 
maintenance by providing the correct voltage and current during the charging 
process.

The charger is connected to the main processor via two GPIO pins. This way the 
charger can report it's current charging state: 

- no source connected, 
- charging or
- source connected but not charging.

This tutorial will show you how to obtain this status.

SGM4056 Driver
~~~~~~~~~~~~~~

Communication with the charger is done by the :doc:`SGM4056 Driver <../../os/modules/drivers/chg_ctrl/sgm4056>`. 
This abstracts the hardware and provides a simple interface to the charger. The :doc:`PineTime BSP <../../os/bsp/pinetime>` 
already initializes the driver, so we can use it directly in our the application. 
Let's extend the application with the following code:

.. code-block:: c
    :emphasize-lines: 1-2, 10-11, 20-22, 33-35, 37-39

    #include "sgm4056/sgm4056.h"
    #include "console/console.h"

    ...

    int
    main(int argc, char **argv)
    {
        int rc;
        struct sgm4056_dev *charger;
        charge_control_status_t charger_status;

        ...

        sysinit();

        g_led_pin = LED_BLINK_PIN;
        hal_gpio_init_out(g_led_pin, 1);

        /* Open charger device */
        charger = (struct sgm4056_dev *) os_dev_open("charger", 0, 0);
        assert(charger);

        while (1) {
            ++g_task1_loops;

            /* Wait one second */
            os_time_delay(OS_TICKS_PER_SEC);

            /* Toggle the LED */
            hal_gpio_toggle(g_led_pin);

            /* Get charger state */
            rc = sgm4056_get_charger_status(charger, &charger_status);
            assert(rc == 0);

            /* Print charger state */
            console_printf("Charger state = %i\n", charger_status);
            console_flush();
        }
        assert(0);

        return rc;
    }

First we added a include file for the ``sgm4056`` driver and the console 
interface for output. 

We define a pointer to a ``sgm4056_dev`` charger device and a variable for 
the actual charger status. 

Then we open the charger device using ``os_dev_open``. This will get the driver 
instance that was initialized by the BSP.

In the while loop we ask the driver to get the charger state and print it to
the console as an number.

Let's run this code on the device and watch the output of the console:

.. code-block:: console

    $ newt run blinky-pinetime 0

.. code-block::

    Charger state = 2
    Charger state = 2
    Charger state = 2
    ...

.. warning::
   
   Currently the PineTime BSP doesn't support the serial console properly. 
   Therefore you need to setup ARM semihosting manually in the application to
   make these instructions work. These step are beyond the scope of this tutorial.

If you connect or disconnect the charger input, you will see the number changes. 
However it is not yet clear what the number actually means. Let's make that 
output more useful:

.. code-block:: c
    :emphasize-lines: 3-21, 30

    ...

    char * get_charger_status_string(charge_control_status_t status) {
        static char * no_source_string = "no source detected";
        static char * charging_string = "charging";
        static char * complete_string = "charge completed";
        switch (status)
        {   
        case CHARGE_CONTROL_STATUS_NO_SOURCE:
            return no_source_string;

        case CHARGE_CONTROL_STATUS_CHARGING:
            return charging_string;

        case CHARGE_CONTROL_STATUS_CHARGE_COMPLETE:
            return complete_string;

        default:
            return NULL;
        }
    }

    ...

    main(int argc, char **argv)
    {
    ...

        /* Print charger state */
        console_printf("Charger state = %s\n", get_charger_status_string(charger_status));
        console_flush();

    ...
    }

This adds a function for converting the status enum to a text and then it uses 
that to output a text representation of the state.

Let's run this improved code and connect the charger:

.. code-block:: console

    $ newt run blinky-pinetime 0

.. code-block::

    Charger state = no source detected
    Charger state = no source detected
    Charger state = no source detected
    Charger state = charging
    Charger state = charging
    Charger state = charging

Great, that is more like it. This code can be used to make a great smartwatch 
application. However I think we can do better.

Charge control
~~~~~~~~~~~~~~

The code of the last section works great, however it is very specific to the 
SGM4056 driver. Luckily we can fix that using the :doc:`Charge Control interface <../../os/modules/drivers/chg_ctrl/chg_ctrl>`.
This is enabled by default for the SGM4056 driver, so we don't need to do any 
configuration for using this new interface.

Charge control works with callbacks for reporting the status. Let's start with 
adding our callback to the application.

.. code-block:: c
    :emphasize-lines: 1, 5-16

    #include "charge-control/charge_control.h"

    ...

    static int 
    charger_data_callback(struct charge_control *chg_ctrl, void *arg,
            void *data, charge_control_type_t type) 
    {
        if (type == CHARGE_CONTROL_TYPE_STATUS) {
            charge_control_status_t charger_status = *(charge_control_status_t*)(data);

            console_printf("Charger state = %s\n", get_charger_status_string(charger_status));
            console_flush();
        }
        return 0;
    }
    ...

First we include the ``charge_control.h`` header for the correct types. Then we 
define the callback, which is of the type ``charge_control_data_func_t``.

The first argument is the a pointer to ``charge_control``. This is a 
representation of the charger. The second argument is a arg pointer. We will 
find out later where these two come from.

The third and fourth argument are a pointer to the actual data and a indication 
of the type of data. This callback can only handle status data of type 
``CHARGE_CONTROL_TYPE_STATUS``. After checking that, we convert the data to the 
correct type and print it like in the previous section.

Now we need to change the ``main`` function to actually call the callback:

.. code-block:: c
    :emphasize-lines: 5, 9-11, 16-20

    int
    main(int argc, char **argv)
    {
        int rc;
        struct charge_control *charger;

        ...

        /* Open charger device */
        charger = charge_control_mgr_find_next_bytype(CHARGE_CONTROL_TYPE_STATUS, NULL);
        assert(charger);

        while (1) {
            ...

            /* Get charger state */
            rc = charge_control_read(charger, CHARGE_CONTROL_TYPE_STATUS, 
                charger_data_callback, NULL, OS_TIMEOUT_NEVER);
            assert(rc == 0);
        }
        assert(0);

        return rc;
    }

There are a few important changes:

-  The type of ``charger`` has changed. We now use the generic type 
   ``charge_control``, which will work for all charger drivers. Notice that 
   this is the same type as the first argument as the callback.
-  We don't open a OS device anymore, instead we call the Charge Control Manager
   and ask for the first charger that supports ``CHARGE_CONTROL_TYPE_STATUS``. 
   Notice that this is the same type as in the callback function.
-  Then we execute a read on the ``charger``, for data of type 
   ``CHARGE_CONTROL_TYPE_STATUS``. When finished we want to it to call our callback 
   with the argument ``NULL`` and we disable the timeout.

When you run this code, you will get the same results as the previous run, 
however this code will work with any charger.

Charger interrupt
~~~~~~~~~~~~~~~~~

One of the advantages of charge control is that it supports interrupt-driven 
notifications. This reduces polling and therefore reduces power usage. This 
requires a few small changes to our application:

.. code-block:: c
    :emphasize-lines: 2-5, 21-23, 25-27, 30-31

    ...
    struct charge_control_listener charger_listener = {
        .ccl_type = CHARGE_CONTROL_TYPE_STATUS,
        .ccl_func = charger_data_callback,
    };

    ...

    int
    main(int argc, char **argv)
    {
        int rc;
        struct charge_control *charger;

        ...

        /* Open charger device */
        charger = charge_control_mgr_find_next_bytype(CHARGE_CONTROL_TYPE_STATUS, NULL);
        assert(charger);

        /* Set polling rate */
        rc = charge_control_set_poll_rate_ms("charger", 10000);
        assert(rc == 0);

        /* Register charger callback */
        rc = charge_control_register_listener(charger, &charger_listener);
        assert(rc == 0);

        while (1) {
            /* No charger code needed here */
            os_eventq_run(os_eventq_dflt_get());
        }
        assert(0);

        return rc;
    }

First we need to define a ``charge_control_listener`` structure, this points to 
the callback function and indicates the type of data we are interested in. It 
could also define the argument, but in this example we are not interested in that.

Then we need to set a polling rate, which we can set high as most changes are 
reported by interrupt. Lastly we register the listener to actually receive the 
callbacks.

There is no charger code needed in the while loop. However we need the event queue 
to be handled as charge control will use events to do the polling and interrupt 
handling. Note that you need to remove the ``os_time_delay`` to make the events 
work properly.

Run this code and you see that the charger state is only show every ten seconds.
But when you connect the charger you see the output directly. This shows the 
combination of polling and interrupt-based data acquisition.
    
Conclusion
~~~~~~~~~~

You now have an efficient charger status reading application. It will work with 
any charger driver, not just the one in the PineTime. It uses interrupts to be
notified of changes quickly. The next step is to integrate this into your own 
project.
