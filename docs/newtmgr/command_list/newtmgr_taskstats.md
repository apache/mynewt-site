## <font color="#F2853F" style="font-size:24pt">newtmgr taskstat </font>
Read task statistics from a device.

#### Usage:

```no-highlight
    newtmgr taskstat -c <conn_profile> [flags] 
```

#### Global Flags:

```no-highlight
  -c, --conn string       connection profile to use
  -h, --help              help for newtmgr
  -l, --loglevel string   log level to use (default "info")
      --name string       name of target BLE device; overrides profile setting
  -t, --timeout float     timeout in seconds (partial seconds allowed) (default 10)
  -r, --tries int         total number of tries in case of timeout (default 1)
```

#### Description
Reads and displays the task statistics from a device. Newtmgr uses the `conn_profile` connection profile to connect to the device.  It lists the following statistics for each task: 

* **task**: Task name
* **pri**:  Task priority
* **runtime**: The time (ms) that the task has been running for
* **csw**: Number of times the task has switched context
* **stksz**: Stack size allocated for the task 
* **stkuse**: Actual stack size the task uses
* **last_checkin**: Last sanity checkin with the [Sanity Task](/os/core_os/sanity/sanity.md)
* **next_checkin**: Next sanity checkin


#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
             | newtmgr taskstat<br>-c profile0 | Reads and displays the task statistics from a device. Newtmgr connects to the device over a connection specified in the `profile01` connection profile.

Here is an example output for the `myble` application from the [Enabling Newt Manager in any app](/os/tutorials/add_newtmgr.md) tutiorial:

```no-highlight
newtmgr taskstat -c myserial 
Return Code = 0
      task pri tid  runtime      csw    stksz   stkuse last_checkin next_checkin
      idle 255   0   151917       47       64       34        0        0
      main 127   1        2       59      512      188        0        0
    ble_ll   0   2        0       14       80       56        0        0
```
