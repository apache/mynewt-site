## <font color="#F2853F" style="font-size:24pt">newtmgr fs</font>
Access files on a device.

#### Usage:

```no-highlight
    newtmgr fs [command] -c <conn_profile> [flags] 
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
The fs command provides the subcommands to download a file from and upload a file to a device.  Newtmgr uses the `conn_profile` connection profile to connect to the device.

Sub-command  | Explanation
-------------| ------------------------
download     | The newtmgr download &lt;src-filename&gt; &lt;dst-filename&gt; command downloads the file named &lt;src-filename&gt; from a device and names it &lt;dst-filename&gt; on your host.
upload       | The newtmgr upload &lt;src-filename&gt; &lt;dst-filename&gt; command uploads the file named &lt;src-filename&gt; to a device and names the file &lt;dst-filename&gt; on the device.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
download       | newtmgr fs download /cfg/mfg mfg.txt -c profile01 | Downloads the file name `/cfg/mfg` from a device and names the file `mfg.txt` on your host.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile. 
upload       | newtmgr fs upload mymfg.txt /cfg/mfg -c profile01 | Uploads the file name `mymfg.txt` to a device and names the file `cfg/mfg` on the device.  Newtmgr connects to the device over a connection specified in the `profile01` connection profile. 
