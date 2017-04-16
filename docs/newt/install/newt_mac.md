## Installing Newt on Mac OS

Newt is supported on Mac OS X 64 bits platforms and has been tested on Mac OS Maverick (10.9) and later.

This page shows you how to install the following versions of newt:

* The latest stable release version (1.0.0) 
* The latest from the master branch (unstable)

### Installing Homebrew 

If you do not have Homebrew installed, run the following command. You will be prompted for your sudo password.

```no-highlight
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
You can also extract (or `git clone`) Homebrew and install it to /usr/local.

<br>

### Installing Newt
Add the ** runtimeco/homebrew-mynewt ** tap:
```no-highlight
$brew tap runtimeco/homebrew-mynewt
$brew update
```
<br>
#### Installing the Latest Release Version of Newt
Install the latest stable release version (1.0.0) of newt:
```no-highlight
$brew install mynewt-newt
==> Installing mynewt-newt from runtimeco/mynewt
==> Downloading https://github.com/runtimeco/binary-releases/raw/master/mynewt-newt-tools_1.0.0/mynewt-newt-1.0.0.mavericks.bottle.tar.gz
==> Downloading from https://raw.githubusercontent.com/runtimeco/binary-releases/master/mynewt-newt-tools_1.0.0/mynewt-newt-1.0.0.mavericks.
######################################################################## 100.0%
==> Pouring mynewt-newt-1.0.0.mavericks.bottle.tar.gz
🍺  /usr/local/Cellar/mynewt-newt/1.0.0: 3 files, 10.4MB
```
<br>
**Note:** This installs the newt 1.0.0 binary that has been tested on Mac OS 10.9 and higher. If you are running an earlier version of Mac OS, the installation will install the latest version of Go and compile newt locally.

<br>
Check that you are using the installed version of newt:
```no-highlight
$which newt
/usr/local/bin/newt
$ls -l /usr/local/bin/newt
lrwxr-xr-x  1 user  staff  36 Apr 15 08:18 /usr/local/bin/newt -> ../Cellar/mynewt-newt/1.0.0/bin/newt
$newt version
Apache Newt (incubating) version: 1.0.0
```
**Note:** If you previously built newt from source and the output of `which newt` shows "$GOPATH/bin/newt", you will need to move "$GOPATH/bin"  after "/usr/local/bin" in your $PATH.

<br>
Run `newt help` to get information about newt:
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
####Installing Newt from the Master Branch 
We recommend that you use the latest stable release version (1.0.0) of newt. If you would like to use the master branch with the latest updates, you can install newt from the HEAD of the master branch. 

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
$brew install --HEAD mynewt-newt
==> Installing mynewt-newt from runtimeco/mynewt
==> Cloning https://github.com/apache/incubator-mynewt-newt.git
Cloning into 'Users/<username>/Library/Caches/Homebrew/mynewt-newt--git'...
remote: Counting objects: 623, done.
remote: Compressing objects: 100% (501/501), done.
remote: Total 623 (delta 154), reused 323 (delta 84), pack-reused 0
Receiving objects: 100% (623/623), 1.10 MiB | 0 bytes/s, done.
Resolving deltas: 100% (154/154), done.
==> Checking out branch master
==> go install
🍺  /usr/local/Cellar/mynewt-newt/HEAD-409f7d3: 3 files, 10.4MB, built in 10 seconds
$newt version
Apache Newt (incubating) version: 1.0.0-dev
```
<br>
####Switching Back to the Stable Release Version
You can switch back to the stable release version (1.0.0) of newt:
```no-highlight
$brew switch mynewt-newt 1.0.0
Cleaning /usr/local/Cellar/mynewt-newt/1.0.0
Cleaning /usr/local/Cellar/mynewt-newt/HEAD-409f7d3
1 links created for /usr/local/Cellar/mynewt-newt/1.0.0
$newt version
Apache Newt (incubating) version: 1.0.0
```
<br>
**Note:** If you would like to contribute to the newt tool, see [Setting Up Go Environment to Contribute to Newt and Newtmgr Tools](/faq/go_env).
