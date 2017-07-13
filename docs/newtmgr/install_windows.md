## Installing Newtmgr on Windows
You can build and install the newtmgr tool from the latest source on the master branch.  Newtmgr is a Go (golang) package.  This guide shows you how to install the tool from source. It assumes that you already installed the [newt tool on Windows](/newt/install/newt_windows/) and have the Windows development environment and Go workspace set up.

### Downloading and Installing the Newtmgr Tool
The newtmgr Go package is **mynewt.apache.org/newtmgr/newtmgr**. It is stored in the [Apache Mynewt newtmgr tool repository mirrored on github](https://github.com/apache/incubator-mynewt-newtmgr).


Run the `go get` command, from your Go workspace, to download, build, and install the newtmgr tool:

```no-highlight
$cd $GOPATH
$go get mynewt.apache.org/newtmgr/newtmgr
$cd $GOPATH/src/mynewt.apache.org/newtmgr
$ls
DISCLAIMER	NOTICE		newtmgr
LICENSE		README.md	nmxact
$git status
On branch master
Your branch is up-to-date with 'origin/master'.

nothing to commit, working directory clean
```
<br>
Check that the newtmgr binary is installed and you are using the one from **$GOPATH/bin**:

```no-highlight
$ls $GOPATH/bin/newtmgr
~/dev/go/bin/newtmgr
$which newt
~/dev/go/bin/newtmgr
```
<br>
Get information about the newtmgr tool:

```no-highlight
$newtmgr
Newtmgr helps you manage remote devices running the Mynewt OS

Usage:
  newtmgr [flags]
  newtmgr [command]

Available Commands:
  config      Read or write config value on target
  conn        Manage newtmgr connection profiles
  crash       Send crash command to remote endpoint using newtmgr
  datetime    Manage datetime on the device
  echo        Send data to remote endpoint using newtmgr, and receive data back
  fs          Access files on device
  help        Help about any command
  image       Manage images on remote instance
  log         Handles log on remote instance
  mpstat      Read mempool statistics from a remote endpoint
  reset       Performs a soft reset of target device
  run         Run procedures on remote device
  stat        Read statistics from a remote endpoint
  taskstat    Read statistics from a remote endpoint

Flags:
  -c, --conn string         connection profile to use.
  -n, --devicename string   name of target BLE device; overrides profile setting
  -h, --help                help for newtmgr
  -l, --loglevel string     log level to use (default "info")
  -t, --timeout float       timeout in seconds (partial seconds allowed) (defaul                                                                                               t 10)
  -r, --tries int           total number of tries in case of timeout (default 1)

Use "newtmgr [command] --help" for more information about a command.
```
