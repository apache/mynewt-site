## Installing Newtmgr on Linux

You can install the latest stable release (1.0.0) of newtmgr from a Debian binary package (amd64) or from a Debian source package. This page shows you how to:

1. Set up your computer to retrieve Debian packages from the runtimeco debian package repository. 

    **Note:** You can skip this step if you already set up your computer to access the runtimeco debian repository when you installed the newt tool. 

2. Install the latest stable release version of newtmgr from a Debian binary package. 
3. Install the latest stable release version of newtmgr from a Debian source package.

If you are running on an amd64 platform, we recommend that you install from the binary package.

**Note:** See [Setting Up an Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env) if you want to:  

* Use the newtmgr tool with the latest updates from the master branch. The master branch may be unstable and we recommend that you use the latest stable release version.
* Contribute to the newtmgr tool. 

<br>

### Setting Up Your Computer to Get Packages from runtimeco 

The newtmgr Debian packages are stored in a private repository on **https://github/runtimeco/debian-mynewt**. 

**Note**: You will only need to perform these steps once on your computer. You can skip this step if you already set up your computer to access the runtimeco debian repository when you installed the newt tool. 

The following steps must be performed on your computer:

1. Add the `apt-transport-https` package to use HTTPS to retrieve packages. 
2. Download the public key for the runtimeco debian repository and import the key into the apt keychain.
3. Add the repository for the binary and source packages to the apt source list.

<br>
Add the apt-transport-https package:
```no-highlight
$sudo apt-get update
$sudo apt-get install apt-transport-https
```
<br>


Download the public key for the runtimeco apt repo (**Note:** There is  `-` after the add):

```no-highlight
wget -qO - https://raw.githubusercontent.com/runtimeco/debian-mynewt/master/mynewt.gpg.key | sudo apt-key add -
```
<br>

Add the repository for the binary and source packages to the apt source list:

```no-highlight
$sudo -s
[sudo] password for <user>:
root$ cat > /etc/apt/sources.list.d/mynewt.list <<EOF
deb https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
deb-src https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
EOF
```
<br>
Check the content of the file:

```no-highlight
root$more /etc/apt/sources.list.d//mynewt.list
deb https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
deb-src https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
```
<br> 

Exit the root shell:

```no-highlight
root$exit
```
<br>
### Installing the Latest Release of Newtmgr from a Binary Package 

For Linux amd64 platform, you can install the latest stable version (1.0.0) of newtmgr from the newtmgr Debian binary package:

```no-highlight
$sudo apt-get update
$sudo apt-get install newtmgr
Reading package lists... Done
Building dependency tree       
Reading state information... Done
The following NEW packages will be installed:
  newtmgr
0 upgraded, 1 newly installed, 0 to remove and 204 not upgraded.
Need to get 0 B/2,312 kB of archives.
After this operation, 11.5 MB of additional disk space will be used.
Selecting previously unselected package newtmgr.
(Reading database ... 211647 files and directories currently installed.)
Preparing to unpack .../newtmgr_1.0.0-1_amd64.deb ...
Unpacking newtmgr (1.0.0-1) ...
Setting up newtmgr (1.0.0-1) 
```
<br>
See [Checking the Installed Version of Newtmgr](#check) to verify that you are using the installed version of newtmgr.

<br>
### Installing the Latest Stable Release of Newtmgr from a Source Package 

If you are running Linux on a different architecture, you can install the Debian source package for the latest stable release (1.0.0) of newtmgr. The installation of the source package builds the newtmgr binary and creates a Debian binary package that you then install.

**Note**: Newtmgr version 1.0.0 has been tested on Linux amd64 platform. 

<br>
#### Installing Go 1.7 

You need Go version 1.7 or higher to build Newtmgr version 1.0.0.  Currently, the latest Go version that Ubuntu installs is 1.6.  Run `go version` to check if you have Go 1.7 installed. 

<br>

Install Go version 1.7:

```no-highlight
$sudo apt-get install golang-1.7-go
Reading package lists... Done
     ...
Unpacking golang-1.7-go (1.7.1-2ubuntu1) ...
Setting up golang-1.7-go (1.7.1-2ubuntu1) ...
$
$sudo ln -sf ../lib/go-1.7/bin/go /usr/bin/go
$go version
go version go1.7.1 linux/amd64
```
You can also download version 1.7 from [https://golang.org/dl/](https://golang.org/dl/). 

<br>
#### Installing from the Source Package
Create a directory and change into the directory, download the source package, and build a binary package from the source package:

```no-highlight
mkdir newtmgr_source
$cd newtmgr_source
$sudo apt-get --build source newtmgr
[sudo] password for <user>: 

sudo apt-get --build source newtmgr
Reading package lists... Done
Need to get 1,867 kB of source archives.
Get:1 https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest/main newtmgr 1.0.0-1 (dsc) [822 B]
Get:2 https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest/main newtmgr 1.0.0-1 (tar) [1,864 kB]
Get:3 https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest/main newtmgr 1.0.0-1 (diff) [2,372 B]
Fetched 1,867 kB in 1s (1,767 kB/s) 

           ...

dpkg-deb: building package 'newtmgr' in '../newtmgr_1.0.0-1_amd64.deb'.
 dpkg-genchanges --build=any,all >../newtmgr_1.0.0-1_amd64.changes
dpkg-genchanges: info: binary-only upload (no source code included)
 dpkg-source --after-build newtmgr-1.0.0
dpkg-buildpackage: info: binary-only upload (no source included)
```

<br>
Install the newtmgr binary package that is created from the source package:

```no-highlight
$sudo dpkg -i newtmgr_1.0.0-1_amd64.deb 

```
<br>
###<a name="check"></a> Checking the Installed Version of Newtmgr
After you have installed newtmgr from either a Debian binary or source package, check that you are using the installed version of newtmgr from **/usr/bin**. 

Check the modification time of the binary and the newtmgr tool that you are using:

```no-highlight
$ls -l /usr/bin/newtmgr
-rwxr-xr-x 1 root root 11473328 Apr 25 10:10 /usr/bin/newtmgr
$which newtmgr
/usr/bin/newtmgr
```

**Note:** If you previously built newtmgr from source and the output of `which newtmgr` shows "$GOPATH/bin/newtmgr", you will need to move "$GOPATH/bin" after "/usr/bin" in your $PATH and export your $PATH.

<br>
Get information about newtmgr:

```no-highlight
$newtmgr
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
  mpstats     Read memory pool statistics from a device
  reset       Send reset request to a device
  run         Run test procedures on a device
  stat        Read statistics from a device
  taskstats   Read task statistics from a device

Flags:
  -c, --conn string       connection profile to use
  -h, --help              Help for newtmgr commands
  -l, --loglevel string   log level to use (default "info")
  -t, --trace             print all bytes transmitted and received

Use "newtmgr [command] --help" for more information about a command.
```

```
<br>
