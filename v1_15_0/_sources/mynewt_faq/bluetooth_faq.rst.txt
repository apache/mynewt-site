Mynewt FAQ - Bluetooth
======================

.. contents::
  :local:
  :depth: 1

NimBLE on nRF52840
------------------

**Q**: Is the nRF52840 supported by NimBLE?

**A**: The nRF52840 is supported, including Bluetooth 5 features.

Trigger Exactly One BLE Advertisement Immediately
-------------------------------------------------

**Q**: Is there a way to trigger exactly one BLE advertisement immediately? I basically want to use BLE as a means 
to advertise to a whole group of devices and it needs to be relatively time-precise. Hoping for about 1ms precision, 
but it's okay if there's a delay as long as it's deterministic. 

**A**: With extended advertising you can enable an advertising instance for exactly 1 advertising event but there will 
be some delay before controller starts advertising which depends on the level of precision. The NimBLE controller always 
schedules the 1st advertising event with a constant 5ms delay. However, if there are other things scheduled in the 
controller it may need to schedule it later so it’s not guaranteed to be deterministic. Periodic advertising is currently 
not supported.


Supported Bluetooth Radio Transceivers
--------------------------------------

**Q**: Are there any other Bluetooth radio transceivers that are supported already or anyone working on? If there is a 
Bluetooth radio that can be integrated using the HCI, we can use the NimBLE host? If so, I suppose we don't need detailed 
specs of the Bluetooth radio?

**A**: You should be able to run the NimBLE host against pretty much any controller using HCI. We have a BLE controller 
implementation for Nordic only, but host (in theory) should work with all. More likely, it will work with 5.0 controller. 
For 4.x controllers it may fail on initialization since we do not check controller features - but this can be fixed as 
for other radio transceivers. For example, there's NXP KW41Z which has BLE-compatible radio documented. However, NXP 
documentation is more or less a description of zillions of different registers so not as friendly as the one from Nordic 
which explains how to actually use it.

NimBLE Operational Questions
----------------------------

**Q**: Can I update firmware via BLE for multiple devices simultaneously using a single device/phone supporting Bluetooth?

**A**: Yes, it is possible to update several Nimble devices simultaneously from a single phone (e.g., central) as long as 
the central can handle all the simultaneous Bluetooth connections. You can also do it using your computer as a central with 
newtmgr.  Just open two terminals and initiate a newtmgr image upload command in each, each to a different device.  You will, 
however, get better overall throughput if you limit yourself to one upgrade at a time.

**Q**: I have the following doubts on NimBLE: The document says 32+ concurrent connections, multiple connections in simultaneous 
central and peripheral roles. Does that mean the “device running NimBLE” can connect to 32 different other devices like phones?

**A**: Yes, with one caveat: each of the 32 centrals needs to be sufficiently cooperative in choosing connection partners 
(http://www.novelbits.io/ble-connection-intervals/). Your app might need to request different connection parameters from 
the centrals (using ``ble_gap_update_params``). 

Of course, you will also need to build the Mynewt image device with a configuration suitable for 32 concurrent connections 
(e.g., ``NIMBLE_MAX_CONNECTIONS=32``, etc.)

``blemesh`` Forgets All Keys on Restart
---------------------------------------
  
**Q**: Is it expected that the blemesh example forgets all the keys on restart and needs to be provisioned again? If so, 
how can I implement key persistence myself? Is there any API to obtain / provide mesh keys before the mesh node is started? 
I found bt_mesh_provision, but the comment there seems to indicate that this is not the right way to use it.
  
**A**: Mesh implementations do not persist keys at the moment. There is a plan to add it but not sure about timeline. It 
probably needs to be implemented inside mesh implementation so there's no API, but if you'd like to hack something I suggest 
taking a look at shell.c and testing.c - there are some testing functions to add/display keys. Another area to look if you 
actually want to persist keys to flash is ``net/nimble/host/store/config/src/ble_store_config.c``.  This is the code that 
persists and restores security material for (non-mesh) Bluetooth.

L2CAP Connection
----------------

**Q**: I want to do an L2CAP connection, and am trying the auth-passkey command, but am not sure about the parameters ``psm``, 
``action``, and ``oob``. What is ``psm``, and what is the value of that parameter in the btshell command ``l2cap-connect``? How 
do I set the parameters ``action`` and ``oob``?

**A**: ``psm`` stands for Protocol Service Multiplexer. You pass the ``psm`` value to either ``l2-cap-connect`` or 
``l2cap-create-server``. The parameters ``action`` and ``oob`` are just passing constant values as defined in the API. 

Bitbang, BLE Mesh, BLE Advertising
----------------------------------

**Q**: Is it possible to run bitbanging and BLE mesh at the same time? How about running BLE Mesh and BLE advertising at 
the same time?
  
**A**: It is possible to run bitbanging and BLE mesh at the same time, but the bitbanging UART takes a lot of CPU on Nordic. 
We’ve run it at 9600 which would probably be okay for lower rate devices, but for reliability it is recommended to run at 
4800. If this is just for the console and your UART port is tied up, ``rtt`` is recommended. Take a look at
:doc:`Segger RTT Console <../../tutorials/tooling/segger_rtt>` for more information. However, bitbanger can be handy given limited UARTs. 

You can certainly continue advertisements during connections, if you are using the GATT bearer for mesh. Mesh is also tied 
into the ext-adv bearer in Mynewt, which also allows for interleaving, even if you’re transmitting mesh data on advertising channels.

Extended Advertising with ``btshell``
-------------------------------------

**Q**: I am using ``btshell`` for advertising with nRF52. When I use 31 bytes, ``mfg_data`` accepts the data with extended 
advertising. But when I use more bytes than that, ``mfg_data`` doesn’t accept it. Is 251 byte payload supported in extended 
advertising? How can I send more than a 251 byte payload on extended advertising? 

**A**: You need to set the ``BLE_EXT_ADV_MAX_SIZE`` syscfg to your required value. For example: 

.. code-block:: console

  newt target amend <your_target> syscfg=BLE_EXT_ADV=1:BLE_EXT_ADV_MAX_SIZE=1650

The default is 31 bytes, and the max is 1650. 

Keep in mind that with extended advertising, you cannot set advertising data for an instance configured as scannable 
(e.g. ``advertise-configure scannable=1``). Either set scan response data using ``advertise-set-scan-rsp`` command 
(parameters are the same as for ``advertise-set-adv-data``) or configure the instance as non-scannable. For example, 
``advertise-configure`` alone will configure the instance as non-connectable and non-scannable which means you can 
set advertising data. Also note that if you continue to use a scannable instance you will need to perform active 
scanning in order to get scan response data. 

FYI, legacy advertising instances can accept both advertising and scan response data but since they use legacy PDUs 
the limit is still 31 bytes. 
  
Configuring Maximum Number of Connections for ``blehci``
--------------------------------------------------------

**Q**: How do I set the maximum number of connections for the ``blehci`` :doc:`example <../../tutorials/ble/blehci_project>`? 
I see there is a ``MYNEWT_VAL_BLE_MAX_CONNECTIONS``, but I don't know how to set it.

**A**:  You can to set it in target settings:

.. code-block:: console

  newt target amend <target> syscfg=BLE_MAX_CONNECTIONS=2

and then rebuild using ``newt build <target>``. ``MYNEWT_VAL_BLE_MAX_CONNECTIONS`` is just a symbol that is defined in 
``syscfg.h`` which is autogenerated by ``newt`` tool and contains all the settings set at package/app/target level.

**Q**: What if I need to set 2 constants? What's the syntax?

**A**: You can set each setting in separate commands or separate ``key=value`` pairs with colon:

.. code-block:: console

  newt target amend <target> syscfg=FOO=1:BAR=2

**Q**: How do you know the constant is ``BLE_MAX_CONNECTIONS`` and not ``MYNEWT_VAL_BLE_MAX_CONNECTIONS``? 
Is there a place I can see those names?

**A**: This is actually one of NimBLE’s settings - you can find these settings available for different packages in the 
``syscfg.yml`` files in the repository. You can also use ``newt target config show <target>`` to show all settings with 
their current values, and then change any of these settings accordingly. Each setting will get a symbol prefixed by 
``MYNEWT_VAL_`` in the autogenerated ``syscfg.h`` file so you can get the actual setting name from this symbol. For more 
info on System Configuration and Initialization, please visit the :doc:`Compile-Time Configuration and Initialization <../../../../os/modules/sysinitconfig/sysinitconfig>` page in the OS User Guide.

Disconnect/Crash While Writing Analog Value From Central Module
---------------------------------------------------------------

**Q**: I’m trying to write analog sensor data from my central module to my peripheral module. I can receive the values 
from the ADC callback perfectly, but I’m not able to write them to the peripheral module. The peripheral module disconnects 
right when the ``ble_gattc_write_flat`` command is called. What could be causing the issue?

**A**: First, check the reason for the disconnect. The gap event callback should indicate the reason in ``disconnect.reason``. 
If the code never reaches the disconnect callback, then the code most likely crashed. If so, check whether ``ble_gattc_write_flat`` 
is called from an interrupt context. Calling into the BLE host from within an interrupt is a bad idea in general, and may cause a 
crash to occur because the Bluetooth host attempts to log to the console during the write procedure. Logging to the console uses 
quite a bit of stack space, so it is likely that the interrupt stack is overflowing. 

Instead, you should send an event to the event queue and handle this in a task context. You’ll need to associate the characteristic 
data with the event so that your event callback knows what payload to pass to the ``ble_gattc_write_flat()`` function. If you don’t 
need to perform multiple writes in rapid succession, then you can just use a single global event and single global buffer. However, 
you will still need to make sure your buffer doesn’t become corrupted by a subsequent ADC interrupt while you are in mid-write. 

Documentation for ``ble_gap_disc_params``
-----------------------------------------

**Q**: Is there documentation somewhere on correct values for ``ble_gap_disc_params``? I'm trying to do a passive discovery and getting 
``BLE_HS_EINVAL``.

**A**: Unfortunately, not at the moment. Here is a brief description of the fields:

- ``itvl``: This is defined as the time interval from when the Controller started its last LE scan until it begins the subsequent LE scan. (units=0.625 msec)  
- ``window``: The duration of the LE scan. ``LE_Scan_Window`` shall be less than or equal to ``LE_Scan_Interval`` (units=0.625 msec)  
- ``filter_policy``: The only useful documentation is the table in the Bluetooth spec (section 2.E.7.8.10).  This field controls which types of devices to listen for.  
- ``limited``: If set, only discover devices in limited discoverable mode.  
- ``passive``: If set, don't send scan requests to advertisers (i.e., don't request additional advertising data).  
- ``filter_duplicates``: If set, the controller ignores all but the first advertisement from each device.

Multicast Messaging and Group Messaging
---------------------------------------

**Q**: Is it possible to send a broadcast message by one of the devices present in the mesh (e.g. broadcast an event which happened)? Something like a push notification instead of continuously polling for it by a client. 

**A**: It is possible to do so with a publish model. Group address or virtual address should help here, according to the Mesh spec. There is no real documentation on it but you can try it out on our ``btmesh_shell`` app. There is a ``shell.c`` file which exposes configuration client which you can use for testing (e.g. you can subscribe to virtual addresses). You can also trigger sending messages to devices. By playing with the ``dst`` command, you probably should be able to set destination to some group. However, since we do not support the provisioner role, there is a command provision which sets fixed keys so you can create a mesh network out of a couple of nodes without the actual provisioner. 

Read the Value of a Characteristic of a Peripheral Device from a Central Device
-------------------------------------------------------------------------------

**Q**: I want to read the value of a characteristic of a peripheral device from a central device which runs on Mynewt OS. How can I obtain the value using the following function?

.. code-block:: c

	int ble_gattc_read(uint16_t conn_handle, uint16_t attr_handle,
                   ble_gatt_attr_fn *cb, void *cb_arg);

**A**: To see an example of this function being used, take a look at the ``blecent`` sample app. The data is in ``attr->om``, which is an ``mbuf`` struct. There are dedicated APIs to access data in mbufs (see ``os_mbuf.h``). ``attr->om->om_data`` is a raw pointer to access data in mbuf so you could also use it, but keep in mind that data in mbuf can be fragmented so you may not be able to access them easily like this. Thus, it is safer to use mbuf APIs instead. ``os_mbuf_copydata`` should be especially useful here since it can copy data from mbuf to flat buffer. 