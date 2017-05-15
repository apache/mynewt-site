## Installing Newt on Windows

You can develop and build Mynewt OS applications for your target boards on the Windows platform.  This page shows you how to build the newt tool from the lastest source on the master branch of the [Mynewt newt git repository](https://github.com/apache/incubator-mynewt-newt).  The tool is written in Go (golang).
  
In Windows, we use MinGW as the development environment to build and run Mynewt OS applications for target boards. MinGW runs the bash shell and provides a Unix-like environment. This provides a uniform way to build Mynewt OS applications. The Mynewt documentation and tutorials use Unix commands and you can use the same Unix commands on MinGW to follow the tutorials. The documentation will note any commands or behaviors that are specific to Windows.

This guide shows you how to perform the following:

1. Install MSYS2/MinGW. 
2. Install Git.
3. Install Go. 
4. Setup the Go environment.
5. Download the source, build, and install the newt tool.

<br>
### Step 1: Installing MSYS2/MinGW
MSYS2/MinGW provides a bash shell and tools to build applications that run on Windows. It includes three subsystems:

* MSYS2 toolchain to build POSIX applications that run on Windows. 
* MinGW32 toolchains to build 32 bit native Windows applications.  
* MinGW64 toolchains to build 64 bit native Windows applications.  

The subsystems run the bash shell and provide a Unix-like environment. You can also run Windows applications from the shell. We will use the MinGW subsystem.

To install and setup MSYS2 and MinGW:

1. Download and run the [MSYS2 installer](http://www.msys2.org).  Select the 64 bit version if you are running on a 64 bit platform. Follow the prompts and check the `Run MSYS2 now` checkbox on the `Installation Complete` dialog. 
2. In the MSYS2 terminal, run the `pacman -Syuu` command. If you get a message to run the update again, close the terminal and run the `pacman -Syuu` command in a new terminal. 
	
	To start a new MSYS2 terminal, select the "MSYS2 MSYS" application from the Windows start menu.

3. Add a new user variable named **MSYS2_PATH_TYPE** and set the value to **inherit** in your Windows environment. This enables the MSYS2 and MinGW bash to inherit your Windows user **Path** values. 
	
	To add the variable,  select properties for your computer > Advanced system settings > Environment Variables > New

4. Run the `pacman -Su vim` command to install the vim editor. 
	
	**Note:**You can also use a Windows editor. You can access your files from the **C:\&lt;msys-install-folder&gt;\home\&lt;username&gt;** folder, where **msys-install-folder** is the folder you installed MSYS2 in. For example, if you installed MSYS2 in the **msys64** folder, your files are stored in **C:\msys64\home\&lt;username&gt;**

You will need to start a MinGW terminal to run the commands specified in the Mynewt documentation and  tutorials.  To start a MinGW terminal, select the "MSYS2 Mingw" application from the start Menu (you can use either MinGW32 or MinGW64). 
In Windows, we use the MingGW subsystem to build  Mynewt tools and applications.  

### Step 2: Installing Git for Windows
Download and install [Git for Windows](https://git-for-windows.github.io) if it is not already installed.


### Step 3: Installing Go 
Download and install the latest version of [Go](https://golang.org/dl/). Newt requires Go version 1.7 or higher.

###Step 4: Setting Up Your Go Environment 

This section describes the Go environment and how to setup a Go workspace.  Go provides an environment to compile Go code,  construct Go packages,  and import Go code.  You will use Go commands to import the newt package repository into your local Go environment.  The Go language environment dictates a specific directory structure, or workspace in Go parlance. It must contain three sibling directories with the names **src**, **pkg** and **bin**: 

* src contains Go source files organized into packages (one package per directory)
* pkg contains package objects
* bin contains the Go application executables that Go builds and installs.

The **GOPATH** environment variable specifies the location of your workspace.  To setup this workspace environment, create a **dev** directory and then a **go** directory under it. Set the GOPATH environment variable to this directory where you will clone the newt repository.
    
Start up a MinGW terminal and run the following commands to set up your Go workspace:

```no-highlight
$ cd $HOME
$ mkdir -p dev/go  
$ cd dev/go
$ export GOPATH=`pwd`
```
<br>
Add the following export statements to your ~/.bash_profile file and source the file:
```no-highlight
export GOPATH=$HOME/dev/go
export PATH=$GOPATH/bin:$PATH
```
<br>

###Step 5: Downloading the Source and Installing the Newt Tool 

The newt Go package is **mynewt.apache.org/newt/newt** and is stored in the [Apache Mynewt newt tool repository mirrored on github](https://github.com/apache/incubator-mynewt-newt).  We use the `go get` command to download the source, build, and install the newt tool binary in the **$GOPATH/bin** directory. 

<br>
Download the newt package source and install the tool:

```no-highlight
$cd $GOPATH
$go get mynewt.apache.org/newt/newt
$cd $GOPATH/src/mynewt.apache.org/newt
$ls 
DISCLAIMER		RELEASE_NOTES.md	util
INSTALLING.md		build.sh		viper
LICENSE			newt			yaml
NOTICE			newtmgr
README.md		newtvm
```
<br>
Check that the newt tool is installed and it is in your path:

```no-highlight
$ls $GOPATH/bin/newt
~/dev/go/bin/newt
$which newt
~/dev/go/bin/newt
$ newt version
Apache Newt (incubating) version: 1.0.0-dev
```
<br>
Get information about the newt tool:

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
  -j, --jobs int          Number of concurrent build jobs (default 4)
  -l, --loglevel string   Log level (default "WARN")
  -o, --outfile string    Filename to tee output to
  -q, --quiet             Be quiet; only display error output
  -s, --silent            Be silent; don't output anything
  -v, --verbose           Enable verbose output when executing commands

Use "newt [command] --help" for more information about a command.
```
