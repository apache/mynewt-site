## Installing Newtmgr on Mac OS

Newtmgr is supported on Mac OS X 64 bit platforms and has been tested on Mac OS 10.9 and higher.

This page shows you how to install the following versions of newtmgr:

* The latest stable release version (1.0.0)
* The latest from the master branch (unstable)

**Note:** If you would like to contribute to the newtmgr tool, see [Setting Up Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env).
### Adding the runtimeco/homebrew-mynewt Tap:
You should have added the runtimeco/homebrew-mynewt tap when you installed the *newt* tool. Run the following commands if you have not done so:

```no-highlight
$brew tap runtimeco/homebrew-mynewt
$brew update
```
<br>
### Installing the Latest Release Version of Newtmgr
Install the latest stable release version (1.0.0) of newtmgr:
```no-highlight
brew install mynewt-newtmgr
==> Installing mynewt-newtmgr from runtimeco/mynewt
==> Downloading https://github.com/runtimeco/binary-releases/raw/master/mynewt-newt-tools_1.0.0/mynewt-newtmgr-1.0.0.mavericks.bottle.tar.gz
==> Downloading from https://raw.githubusercontent.com/runtimeco/binary-releases/master/mynewt-newt-tools_1.0.0/mynewt-newtmgr-1.0.0.maveric
######################################################################## 100.0%
==> Pouring mynewt-newtmgr-1.0.0.mavericks.bottle.tar.gz
🍺  /usr/local/Cellar/mynewt-newtmgr/1.0.0: 3 files, 15.2MB
```
<br>
**Note:** This installs the newtmgr 1.0.0 binary that has been tested on Mac OS 10.9 and higher. If you are running an earlier version of Mac OS, the installation will install the latest version of Go and compile newtmgr locally.

<br>
Check that you are using the installed version of newtmgr:
```no-highlight
$which newtmgr
/usr/local/bin/newtmgr
ls -l /usr/local/bin/newtmgr
lrwxr-xr-x  1 user  staff  42 Apr 15 09:14 /usr/local/bin/newtmgr -> ../Cellar/mynewt-newtmgr/1.0.0/bin/newtmgr
```
**Note:** If you previously built newtmgr from source and the output of `which newtmgr` shows "$GOPATH/bin/newtmgr", you will need to move "$GOPATH/bin"  after "/usr/local/bin" in your $PATH.

<br>
Get information about newtmgr:
```no-highlight
$newtmgr help
Newtmgr helps you manage remote devices running the Mynewt OS

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
  image       Manage images on a device
  log         Manage logs on a device
  mpstat      Read memory pool statistics from a device
  reset       Send reset request to a device
  run         Run test procedures on a device
  stat        Read statistics from a device
  taskstat    Read task statistics from a device

Flags:
  -c, --conn string       connection profile to use
  -h, --help              Help for newtmgr commands
  -l, --loglevel string   log level to use (default "info")
  -t, --trace             print all bytes transmitted and received

Use "newtmgr [command] --help" for more information about a command.
```
<br>
#### Installing Newtmgr from the Master Branch 
We recommend that you use the latest stable release version (1.0.0) of newtmgr. If you would like to use the master branch with the latest updates, you can install newtmgr from the HEAD of the master branch. 

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
$brew install --HEAD  mynewt-newtmgr
==> Installing mynewt-newtmgr from runtimeco/mynewt
==> Cloning https://github.com/apache/incubator-mynewt-newt.git
Cloning into '/Users/<user>/Library/Caches/Homebrew/mynewt-newtmgr--git'...
remote: Counting objects: 623, done.
remote: Compressing objects: 100% (501/501), done.
remote: Total 623 (delta 154), reused 323 (delta 84), pack-reused 0
Receiving objects: 100% (623/623), 1.10 MiB | 0 bytes/s, done.
Resolving deltas: 100% (154/154), done.
==> Checking out branch master
==> go install
🍺  /usr/local/Cellar/mynewt-newtmgr/HEAD-409f7d3: 3 files, 15.1MB, built in 14 seconds
```
<br>
To switch back to the stable release version (1.0.0) of newtmgr, you can run:
```no-highlight
$brew switch mynewt-newtmgr 1.0.0
Cleaning /usr/local/Cellar/mynewt-newtmgr/1.0.0
Cleaning /usr/local/Cellar/mynewt-newtmgr/HEAD-409f7d3
1 links created for /usr/local/Cellar/mynewt-newtmgr/1.0.0
```
<br>
