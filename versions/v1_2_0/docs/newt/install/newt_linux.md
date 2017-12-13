## Installing Newt on Linux

You can install the latest release (1.2.0) of the newt tool from a Debian binary package (amd64). You can also download and build the latest release version of newt from source.

This page shows you how to:

1. Set up your computer to download Debian binary packages from the runtimeco APT repository.

    **Note:** The key for signing the repository has changed. If you set up your computer before release 1.1.0, you will need to download and import the public key again.

2. Install the latest release version of newt from a Debian binary package. You can use apt-get to install the package or manually download and install the Debian binary package.

3. Download, build, and install the latest release version of newt from source.

If you are installing on an amd64 platform, we recommend that you install from the binary package.

See [Installing Previous Releases of Newt](/newt/install/prev_releases.md) to install an earlier version of newt.

**Note:**  We have tested the newt tool binary and apt-get install from the runtimeco APT repository for Ubuntu version 16.  Earlier Ubuntu versions (for example: Ubuntu 14) may have incompatibility with the repository. You can manually download and install the Debian binary package.

**Note:** See [Setting Up a Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env) if you want to:

* Use the newt tool with the latest updates from the master branch. The master branch may be unstable and we recommend that you use the latest stable release version.
* Contribute to the newt tool.

<br>
### Setting Up Your Computer to use apt-get to Install the Package

The newt Debian packages are stored in a private APT repository on **https://github/runtimeco/debian-mynewt**.   To use apt-get, you must set up the following on your computer to retrieve packages from the repository:

**Note**: You only need to perform this setup once on your computer. However, if you previously downloaded and imported the public key for the runtimeco APT repository, you will need to perform step 2 again as the key has changed.


1. Install the `apt-transport-https` package to use HTTPS to retrieve packages. 
2. Download the public key for the runtimeco APT repository and import the key into the apt keychain.
3. Add the repository for the binary and source packages to the apt source list.


<br>
Install the apt-transport-https package:
```no-highlight
$ sudo apt-get update
$ sudo apt-get install apt-transport-https
```
<br>


Download the public key for the runtimeco apt repo (**Note:** There is  a `-` after  `apt-key add`):

```no-highlight
$ wget -qO - https://raw.githubusercontent.com/runtimeco/debian-mynewt/master/mynewt.gpg.key | sudo apt-key add -
```
<br>

Add the repository for the binary and source packages to the `mynewt.list` apt source list file:

```no-highlight
$ sudo tee /etc/apt/sources.list.d/mynewt.list <<EOF
deb https://raw.githubusercontent.com/runtimeco/debian-mynewt/master latest main
EOF
```

<br>
Update the available packages: 
```no-highlight
$ sudo apt-get update
```
<br>
**Note:** If you are not using Ubuntu version 16, you may see the following errors.  We have provided instructions on how to manually download and install the binary package.

```no-highlight

W: Failed to fetch https://raw.githubusercontent.com/runtimeco/debian-mynewt/master/dists/latest/main/source/Sources  HttpError404

```
<br>
## Installing the Latest Release of Newt from a Binary Package

You can use either apt-get to install the package, or manually download and install the Debian binary package.

<br>
#### Method 1: Using apt-get to Upgrade or to Install

Run the following commands to upgrade or install the latest version of newt:

```no-highlight
$ sudo apt-get update 
$ sudo apt-get install newt
```

**Note:** If you encounter build errors (such as missing `sys/mman.h`), please make sure you have a 32-bit glibc:

```no-highlight
$ sudo apt-get install gcc-multilib
```

<br>
#### Method 2: Downloading and Installing the Debian Package Manually

Download and install the package manually.

```no-highlight
$wget https://raw.githubusercontent.com/runtimeco/binary-releases/master/mynewt-newt-tools_1.2.0/newt_1.2.0-1_amd64.deb
$sudo dpkg -i newt_1.2.0-1_amd64.deb
```
<br>
See [Checking the Installed Version of Newt](#check) to verify that you are using the installed version of newt.

<br>
### Installing the Latest Release of Newt from a Source Package 

If you are running Linux on a different architecture, you can build and install the latest release version of newt from source.

<br>
1.  You need Go version 1.7.6 or higher to build Newt.  Currently, the latest Go version that Ubuntu installs is 1.6.  Run `go version` to check if you have Go 1.7.6 installed. You can download Go from [https://golang.org/dl/](https://golang.org/dl/).

<br>
2. Download and unpack the newt source:

```no-highlight
$ wget -P /tmp https://github.com/apache/mynewt-newt/archive/mynewt_1_2_0_tag.tar.gz
$ tar -xzf /tmp/mynewt_1_2_0_tag.tar.gz
```

<br>
3. Run the build.sh to build the newt tool.

```no-highlight

$ cd mynewt-newt-mynewt_1_2_0_tag
$ ./build.sh
$ rm /tmp/mynewt_1_2_0_tag.tar.gz
```

<br>
4. You should see the `newt/newt` executable. Move the executable to a bin directory in your PATH:

* If you previously built newt from the master branch, you can move the binary to your $GOPATH/bin directory.
  
        $ mv newt/newt $GOPATH/bin

* If you are installing newt for the first time and do not have a Go workspace set up, you can move the binary to /usr/bin or a directory in your PATH:

        $ mv newt/newt /usr/bin


<br>
###<a name="check"></a> Checking the Installed Version of Newt

<br>
1. Check which newt you are using and that the version is the latest release version.

```no-highlight
$ which newt
/usr/bin/newt
$ newt version
Apache Newt version: 1.2.0
```

<br>
2. Get information about newt:
```no-highlight
$ newt
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
  resign-image Re-sign an image.
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
