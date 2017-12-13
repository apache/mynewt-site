## Installing Newtmgr on Mac OS

Newtmgr is supported on Mac OS X 64 bit platforms and has been tested on Mac OS Sierra.

This page shows you how to install the following versions of newtmgr:

* Upgrade to or install the latest release version (1.2.0).
* Install the latest from the master branch (unstable).

See [Installing Previous Releases of Newtmgr](/newtmgr/prev_releases) to install an earlier version of newtmgr.

**Note:** If you would like to contribute to the newtmgr tool, see [Setting Up Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env).

### Adding the Mynewt Homebrew Tap

You should have added the **runtimeco/homebrew-mynewt** tap when you installed the **newt** tool. Run the following commands if you have not done so:

```no-highlight

$ brew tap runtimeco/homebrew-mynewt
$ brew update

```

### Upgrading to or Installing the Latest Release Version

Perform the following to upgrade or install the latest release version of newtmgr.

#### Upgrading to the Latest Release Version of Newtmgr

If you have installed an earlier version of newtmgr using brew, run the following commands to upgrade to the latest version of newtmgr:

```no-highlight

$ brew update
$ brew upgrade mynewt-newtmgr

```

<br>
#### Installing the Latest Release Version of Newtmgr

Run the following command to install the latest release version of newtmgr:

```no-highlight

$ brew update
$ brew install mynewt-newtmgr
```
<br>
**Notes:** Homebrew bottles for newtmgr 1.2.0 are available for Mac OS Sierra.  If you are running an earlier version of Mac OS, the installation will install the latest version of Go and compile newtmgr locally.

<br>
### Checking the Installed Version

Check that you are using the installed version of newtmgr:
```no-highlight
$which newtmgr
/usr/local/bin/newtmgr
```
**Note:** If you previously built newtmgr from source and the output of `which newtmgr` shows "$GOPATH/bin/newtmgr", you will need to move "$GOPATH/bin"  after "/usr/local/bin" for your PATH in  ~/.bash_profile, and source ~/.bash_profile.

<br>
Get information about newtmgr:

```no-highlight

$ newtmgr help
Usage:
  newtmgr [flags]
  newtmgr [command]

Available Commands:
  config      Read or write a config value on a device
  conn        Manage newtmgr connection profiles
  crash       Send a crash command to a device
  datetime    Manage datetime on a device
  echo        Send data to a device and display the echoed back data
  fs          Access files on a device
  help        Help about any command
  image       Manage images on a device
  log         Manage logs on a device
  mpstat      Read mempool statistics from a device
  reset       Perform a soft reset of a device
  run         Run test procedures on a device
  stat        Read statistics from a device
  taskstat    Read task statistics from a device

Flags:
  -c, --conn string       connection profile to use
  -h, --help              help for newtmgr
  -l, --loglevel string   log level to use (default "info")
      --name string       name of target BLE device; overrides profile setting
  -t, --timeout float     timeout in seconds (partial seconds allowed) (default 10)
  -r, --tries int         total number of tries in case of timeout (default 1)

Use "newtmgr [command] --help" for more information about a command.

```
<br>

### Installing Newtmgr from the Master Branch 

We recommend that you use the latest release version of newtmgr. If you would like to use the master branch with the latest updates, you can install newtmgr from the HEAD of the master branch. 

** Notes: **

* The master branch may be unstable.
* This installation will install the latest version of Go on your computer, if it is not installed, and compile newtmgr locally. 

<br>
If you already installed newtgmr, unlink the current version:
```no-highlight
$brew unlink mynewt-newtmgr
```
<br>
Install the latest unstable version of newtmgr from the master branch:
```no-highlight
$brew install mynewt-newtmgr --HEAD
```
<br>
To switch back to the latest stable release version of newtmgr, you can run:
```no-highlight
$brew switch mynewt-newtmgr 1.2.0
```
<br>
