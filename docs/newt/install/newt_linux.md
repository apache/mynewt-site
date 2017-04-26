## Installing Newt on Linux

You can install the latest stable release (1.0.0) of the newt tool from a Debian binary package (amd64) or from a Debian source package. This page shows you how to:

1. Set up your computer to retrieve Debian packages from the runtimeco debian package repository.
2. Install the latest stable release version of newt from a Debian binary package. 
3. Install the latest stable release version of newt from a Debian source package.

If you are installing on an amd64 platform, we recommend that you install from the binary package.

**Note:** See [Setting Up an Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env) if you want to:  

* Use the newt tool with the latest updates from the master branch. The master branch may be unstable and we recommend that you use the latest stable release version.
* Contribute to the newt tool. 

<br>

### Setting Up Your Computer to Get Packages from runtimeco 
The newt Debian packages are stored in a private repository on **https://github/runtimeco/debian-mynewt**.  The following steps must be performed on your computer to retreive packages from the repository:

**Note:** You only need to perform this setup once on your computer.

1. Install the `apt-transport-https` package to use HTTPS to retrieve packages. 
2. Download the public key for the runtimeco debian repository and import the key into the apt keychain.
3. Add the repository for the binary and source packages to the apt source list.


<br>
Install the apt-transport-https package:
```no-highlight
$sudo apt-get update
$sudo apt-get install apt-transport-https
```
<br>


Download the public key for the runtimeco apt repo (**Note:** There is  a `-` after  `apt-key add`):

```no-highlight
wget -qO - https://raw.githubusercontent.com/runtimeco/debian-mynewt/master/mynewt.gpg.key | sudo apt-key add -
```
<br>

Add the repository for the binary and source packages to the `mynewt.list` apt source list file.

```no-highlight
$sudo -s
[sudo] password for <user>:
root$ cat > /etc/apt/sources.list.d/mynewt.list <<EOF
deb https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
deb-src https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
EOF
root$exit
```
**Note:** Do not forget to exit the root shell.

<br>
Verify the content of the source list file:

```no-highlight
$more /etc/apt/sources.list.d/mynewt.list
deb https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
deb-src https://raw.githubusercontent.com/runtimeco/debian-package/master latest main
```
<br> 

### Installing the Latest Release of Newt from a Binary Package 

For Linux amd64 platforms, you can install the latest stable version (1.0.0) of newt from the newt Debian binary package:

```no-highlight
$sudo apt-get update
$sudo apt-get install newt
Reading package lists... Done
Building dependency tree       
Reading state information... Done

      ...

Preparing to unpack .../newt_1.0.0-1_amd64.deb ...
Unpacking newt (1.0.0-1) ...
Setting up newt (1.0.0-1) ...
```
<br>
See [Checking the Installed Version of Newt](#check) to verify that you are using the installed version of newt.

<br>
### Installing the Latest Stable Release of Newt from a Source Package 

If you are running Linux on a different architecture, you can install the Debian source package for the latest stable release (1.0.0) of newt. The installation of the source package builds the newt binary and creates a Debian binary package that you then install.

**Note**: Newt version 1.0.0 has been tested on Linux amd64 platforms. Version 1.0.0 does not build on 32 bit platforms but have been fixed for the next release.

<br>
#### Installing Go 1.7 

You need Go version 1.7 or higher to build Newt version 1.0.0.  Currently, the latest Go version that Ubuntu installs is 1.6.  Run `go version` to check if you have Go 1.7 installed. 

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
mkdir newt_source
$cd newt_source
$sudo apt-get --build source newt
[sudo] password for <user>: 
Reading package lists... Done
Need to get 1,866 kB of source archives.
Get:1 https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest/main newt 1.0.0-1 (dsc) [795 B]
Get:2 https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest/main newt 1.0.0-1 (tar) [1,864 kB]
Get:3 https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest/main newt 1.0.0-1 (diff) [2,000 B]
Fetched 1,866 kB in 1s (1,222 kB/s)
dpkg-source: warning: extracting unsigned source package (newt_1.0.0-1.dsc)
dpkg-source: info: extracting newt in newt-1.0.0
dpkg-source: info: unpacking newt_1.0.0.orig.tar.gz
dpkg-source: info: unpacking newt_1.0.0-1.debian.tar.xz

           ...

dpkg-deb: building package 'newt' in '../newt_1.0.0-1_amd64.deb'.
 dpkg-genchanges --build=any,all >../newt_1.0.0-1_amd64.changes
dpkg-genchanges: info: binary-only upload (no source code included)
 dpkg-source --after-build newt-1.0.0
dpkg-buildpackage: info: binary-only upload (no source included)
W: Can't drop privileges for downloading as file 'newt_1.0.0-1.dsc' couldn't be accessed by user '_apt'. - pkgAcquire::Run (13: Permission denied)
```
**Note:** You can ignore the "Permission denied" warning message at the end of the command.

<br>
Install the newt binary package that is created from the source package:

**Note:** The file name for the binary package has the format: newt_1.0.0-1_**arch**.deb,  where **arch** is a value that identifies your host architecture.  

```no-highlight
$sudo dpkg -i newt_1.0.0-1_amd64.deb 
Selecting previously unselected package newt.
(Reading database ... 252969 files and directories currently installed.)
Preparing to unpack newt_1.0.0-1_amd64.deb ...
Unpacking newt (1.0.0-1) ...
Setting up newt (1.0.0-1) ...
```
<br>
###<a name="check"></a> Checking the Installed Version of Newt
After you have installed newt from either a Debian binary or source package, check that you are using the installed version of newt from **/usr/bin**. 

Check the modification time of the binary and the newt tool that you are using:

```no-highlight
$ls -l /usr/bin/newt
-rwxr-xr-x 1 root root 6919280 Apr 22 10:09 /usr/bin/newt
$which newt
/usr/bin/newt
$newt version
Apache Newt (incubating) version: 1.0.0
```

**Note:** If you previously built newt from source and the output of `which newt` shows "$GOPATH/bin/newt", you will need to move "$GOPATH/bin" after "/usr/bin" for your PATH environment variable and export it. 

<br>
Get information about newt:
```no-highlight
$newt
Newt allows you to create your own embedded application based on the Mynewt
operating system. Newt provides both build and package management in a single
tool, which allows you to compose an embedded application, and set of
projects, and then build the necessary artifacts from those projects. For more
information on the Mynewt operating system, please visit
https://mynewt.apache.org/.

Please use the newt help command, and specify the name of the command you want
help for, for help on how to use a specific command

Usage:
  newt [flags]
  newt [command]

Examples:
  newt
  newt help [<command-name>]
    For help on <command-name>.  If not specified, print this message.

Available Commands:
  build        Build one or more targets
  clean        Delete build artifacts for one or more targets
  create-image Add image header to target binary
  debug        Open debugger session to target
  info         Show project info
  install      Install project dependencies
  load         Load built target to board
  mfg          Manufacturing flash image commands
  new          Create a new project
  pkg          Create and manage packages in the current workspace
  run          build/create-image/download/debug <target>
  size         Size of target components
  sync         Synchronize project dependencies
  target       Commands to create, delete, configure, and query targets
  test         Executes unit tests for one or more packages
  upgrade      Upgrade project dependencies
  vals         Display valid values for the specified element type(s)
  version      Display the Newt version number

Flags:
  -h, --help              Help for newt commands
  -j, --jobs int          Number of concurrent build jobs (default 8)
  -l, --loglevel string   Log level (default "WARN")
  -o, --outfile string    Filename to tee output to
  -q, --quiet             Be quiet; only display error output
  -s, --silent            Be silent; don't output anything
  -v, --verbose           Enable verbose output when executing commands

Use "newt [command] --help" for more information about a command.
```
<br>
