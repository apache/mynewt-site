## Installing Newtmgr on Mac OS

Newtmgr is supported on Mac OS X 64 bit platforms and has been tested on Mac OS 10.10 and higher.

This page shows you how to install the following versions of newtmgr:

* Upgrade to or install the latest stable version (1.1.0).
* Install earlier release versions.
* Install the latest from the master branch (unstable).

**Note:** If you would like to contribute to the newtmgr tool, see [Setting Up Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env).

### Adding the Mynewt Homebrew Tap

You should have added the **runtimeco/homebrew-mynewt** tap when you installed the **newt** tool. Run the following commands if you have not done so:

```no-highlight

$ brew tap runtimeco/homebrew-mynewt
$ brew update

```

### Upgrading to or Installing the Latest Release Version

Perform the following to upgrade or install the latest release version of newtmgr (1.1.0).

#### Upgrading to the Latest Release Version of Newtmgr

If you previously installed newtmgr 1.0.0 using brew, run the following commands to upgrade to newtmgr 1.1.0:

```no-highlight

$ brew update
$ brew upgrade mynewt-newtmgr

```

<br>
#### Installing the Latest Release Version of Newtmgr

Run the following command to install the latest stable release version (1.1.0) of newtmgr:

```no-highlight

$ brew install mynewt-newtmgr
==> Installing mynewt-newtmgr from runtimeco/mynewt
==> Downloading https://github.com/runtimeco/binary-releases/raw/master/mynewt-newt-tools_1.1.0/mynewt-newtmgr-1.1.0.sierra.bottle.tar.gz
==> Downloading from https://raw.githubusercontent.com/runtimeco/binary-releases/master/mynewt-newt-tools_1.1.0/mynewt-newtmgr-1.1.0.sierra.bottle.tar.gz
######################################################################## 100.0%
==> Pouring mynewt-newtmgr-1.1.0.sierra.bottle.tar.gz
🍺  /usr/local/Cellar/mynewt-newtmgr/1.1.0: 3 files, 17MB

```
<br>
**Notes:** Homebrew bottles for newtmgr 1.1.0 are available for Mac OS Sierra, El Captian and Yosemite.  If you are running an earlier version of Mac OS, the installation will install the latest version of Go and compile newtmgr locally.

<br>
#### Checking the Installed Version

Check that you are using the installed version of newtmgr:
```no-highlight
$which newtmgr
/usr/local/bin/newtmgr
ls -l /usr/local/bin/newtmgr
lrwxr-xr-x  1 user  staff  42 Jul 25 21:15 /usr/local/bin/newtmgr -> ../Cellar/mynewt-newtmgr/1.1.0/bin/newtmgr
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

### Installing Earlier Release Versions of Newtmgr

If you want to install newtmgr 1.0, run the following commands:

```no-highlight

$ brew update
$ brew install mynewt-newtmgr@1.0

```

**Note:** This is a keg-only installation.  newt 1.0 is installed in /usr/local/Cellar/mynewt-newtmgr@1.0/1.0.0/bin but not symlinked into /usr/local/bin.  

If you need this version of newt first in your PATH, run the following commands:

```no-highlight

$ echo 'export PATH=/usr/local/Cellar/mynewt-newtmgr@1.0/1.0.0/bin:$PATH' >> ~/.bash_profile
$ source ~/.bash_profile

```

<br>
You can also manually symlink into /usr/local/bin as follows:

1. Unlink newtmgr if you have the latest version of newt installed:
    
        $ brew unlink mynewt-newtmgr

2. Link mynewt-newt@1.0 into /usr/local/bin:

        $ brew link -f mynewt-newt@1.0

<br>
### Installing Newtmgr from the Master Branch 

We recommend that you use the latest stable release version (1.1.0) of newtmgr. If you would like to use the master branch with the latest updates, you can install newtmgr from the HEAD of the master branch. 

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
==> Installing mynewt-newtmgr from runtimeco/mynewt
==> Cloning https://github.com/apache/mynewt-newtmgr.git
Cloning into '/Users/wanda/Library/Caches/Homebrew/mynewt-newtmgr--git'...
remote: Counting objects: 650, done.
remote: Compressing objects: 100% (511/511), done.
remote: Total 650 (delta 192), reused 345 (delta 114), pack-reused 0
Receiving objects: 100% (650/650), 4.67 MiB | 4.58 MiB/s, done.
Resolving deltas: 100% (192/192), done.
==> Checking out branch master
==> go get github.com/currantlabs/ble
==> go get github.com/raff/goble
==> go get github.com/mgutz/logxi/v1
==> go install
🍺  /usr/local/Cellar/mynewt-newtmgr/HEAD-7bdd773: 3 files, 17MB, built in 22 seconds
```
<br>
To switch back to the stable release version (1.1.0) of newtmgr, you can run:
```no-highlight
$brew switch mynewt-newtmgr 1.1.0
Cleaning /usr/local/Cellar/mynewt-newtmgr/1.1.0
Cleaning /usr/local/Cellar/mynewt-newtmgr/HEAD-7bdd773
1 links created for /usr/local/Cellar/mynewt-newtmgr/1.1.0
```
<br>
