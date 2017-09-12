## Installing Newt on Mac OS

Newt is supported on Mac OS X 64 bit platforms and has been tested on Mac OS 10.11 and higher.

This page shows you how to install the following versions of newt:

* Upgrade to or install the latest release version (1.2.0).
* Install the latest from the master branch (unstable).

See [Installing Previous Releases of Newt](/newt/install/prev_releases) to install an earlier version of newt.

**Note:** If you would like to contribute to the newt tool, see [Setting Up Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env).

### Installing Homebrew 

If you do not have Homebrew installed, run the following command. You will be prompted for your sudo password.

```no-highlight
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
You can also extract (or `git clone`) Homebrew and install it to /usr/local.

### Adding the Mynewt Homebrew Tap

If this is your first time installing newt, add the  **runtimeco/homebrew-mynewt** tap:

```no-highlight

$ brew tap runtimeco/homebrew-mynewt
$ brew update

```

### Upgrading to or Installing the Latest Release Version

Perform the following to upgrade or install the latest release version of newt.

#### Upgrading to the Latest Release Version of Newt

If you have installed an earlier version of newt using brew, run the following commands to upgrade to latest version of newt:

```no-highlight

$ brew update
$ brew upgrade mynewt-newt

```

<br>
#### Installing the Latest Release Version of Newt

Run the following command to install the latest release version of newt:

```no-highlight

$ brew update
$ brew install mynewt-newt
==> Installing mynewt-newt from runtimeco/mynewt
==> Downloading https://github.com/runtimeco/binary-releases/raw/master/mynewt-newt-tools_1.2.0/mynewt-newt-1.2.0.sierra.bottle.tar.gz
==> Downloading from https://raw.githubusercontent.com/runtimeco/binary-releases/master/mynewt-newt-tools_1.2.0/mynewt-newt-1.2.0.sierra.bottle.tar.gz
######################################################################## 100.0%
==> Pouring mynewt-newt-1.2.0.sierra.bottle.tar.gz
🍺  /usr/local/Cellar/mynewt-newt/1.2.0: 3 files, 10.7MB

```
<br>
**Notes:** Homebrew bottles for newt are available for Mac OS Sierra, and El Captian.  If you are running an earlier version of Mac OS, the installation will install the latest version of Go and compile newt locally.

<br>
### Checking the Installed Version

Check that you are using the installed version of newt:

```no-highlight

$which newt
/usr/local/bin/newt
$ls -l /usr/local/bin/newt
lrwxr-xr-x  1 user  staff  36 Sep 11 19:04 /usr/local/bin/newt -> ../Cellar/mynewt-newt/1.2.0/bin/newt
$newt version
Apache Newt version: 1.2.0

```
**Note:** If you previously built newt from source and the output of `which newt` shows "$GOPATH/bin/newt", you will need to move "$GOPATH/bin"  after "/usr/local/bin" for your PATH in  ~/.bash_profile, and source ~/.bash_profile.  

<br>
Get information about newt: 

```no-highlight

$ newt help
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
### Installing Newt from the Master Branch 

We recommend that you use the latest release version of newt. If you would like to use the master branch with the latest updates, you can install newt from the HEAD of the master branch. 

** Notes: **

* The master branch may be unstable.
* This installation will install the latest version of Go on your computer, if it is not installed, and compile newt locally. 


<br>
If you previously installed newt using brew, unlink the current version:
```no-highlight
$brew unlink mynewt-newt
```
<br>
Install the latest unstable version of newt from the master branch:
```no-highlight
$ brew install mynewt-newt --HEAD
==> Installing mynewt-newt from runtimeco/mynewt
==> Cloning https://github.com/apache/mynewt-newt.git
Cloning into '/Users/wanda/Library/Caches/Homebrew/mynewt-newt--git'...
remote: Counting objects: 626, done.
remote: Compressing objects: 100% (504/504), done.
remote: Total 626 (delta 155), reused 323 (delta 85), pack-reused 0
Receiving objects: 100% (626/626), 1.11 MiB | 0 bytes/s, done.
Resolving deltas: 100% (155/155), done.
==> Checking out branch master
==> go install
🍺  /usr/local/Cellar/mynewt-newt/HEAD-59b3a5d: 3 files, 10.7MB, built in 7 seconds
$newt version
Apache Newt version 1.1.0-dev
```
<br>
To switch back to the latest stable release version of newt, you can run:
```no-highlight
$brew switch mynewt-newt 1.2.0
Cleaning /usr/local/Cellar/mynewt-newt/1.2.0
Cleaning /usr/local/Cellar/mynewt-newt/HEAD-59b3a5d
1 links created for /usr/local/Cellar/mynewt-newt/1.2.0
$newt version
Apache Newt version: 1.2.0
```
<br>
