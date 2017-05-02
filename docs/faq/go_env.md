## Contributing to Newt or Newtmgr Tools
Newt and Newtmgr are written in Go (golang). This guide shows you how to install Go and setup your environment to update and build the tools if you want to: 

* Contribute to newt or newtmgr features or fix bugs.
* Build the tools with latest updates from the master branch on a Linux platform.

This guide shows you how to perform the following:

1. Install Go on either Mac OS X or Linux. (Tasks that are specific to each platform are called out.)
2. Setup the Go environment.
3. Download the source, build, and install the newt or newtmgr tools.
4. Update and rebuild the tools. 

**Note:** You will also need to read and follow the instructions from the [FAQ](/faq/answers/) to set up your git repos to submit changes.


### Step 1: Installing Go 
The latest master branch of newt and newtmgr requires GO version 1.6 or higher. You can skip this step and proceed to Step 2 if you already have Go version 1.6 or higher installed.

<br>
#### Installing Go on Mac OS X

If you do not have Homebrew installed, run the following command. You will be prompted for your sudo password.

```no-highlight
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
You can also extract (or `git clone`) Homebrew and install it to /usr/local.

<br>
Use brew to install Go:
     
```no-highlight
$ brew install go
==> 
...
... 
==> *Summary*
🍺  //usr/local/Cellar/go/1.8.1: 7,030 files, 281.8MB, built in 1 minute 12 seconds
```
You can also download the Go package directly from (https://golang.org/dl/) instead of brewing it. Install it in /usr/local directory.

<br>
#### Installing Go on Linux

Use apt-get to install Go: 
```no-highlight
$sudo apt-get update
$sudo apt-get install golang 
Reading package lists... Done
Building dependency tree       
Reading state information... Done

      ...

The following NEW packages will be installed:
  golang
0 upgraded, 1 newly installed, 0 to remove and 43 not upgraded.
Need to get 0 B/2,812 B of archives.
After this operation, 10.2 kB of additional disk space will be used.
Selecting previously unselected package golang.
(Reading database ... 244990 files and directories currently installed.)
Preparing to unpack .../golang_2%3a1.6.1+1ubuntu2_all.deb ...
Unpacking golang (2:1.6.1+1ubuntu2) ...
Setting up golang (2:1.6.1+1ubuntu2) ...
$ go version
go version go1.6.3 linux/amd64
```
<br>
###Step 2: Setting Up Your Go Environment 

This section describes the Go environment and how to setup a Go workspace. If you already have a Go workspace for your other Go projects, you can skip this step and proceed to Step 3.

Go provides an environment to compile Go code, construct Go packages,  and import Go code.  You will use Go commands to import the newt or newtmgr package repository into your local Go environment.  The Go language environment dictates a specific directory structure, or workspace in Go parlance. It must contain three sibling directories with the names **src**, **pkg** and **bin**: 

* src contains Go source files organized into packages (one package per directory)
* pkg contains package objects
* bin contains the Go application executables that Go builds and installs.

The **GOPATH** environment variable specifies the location of your workspace.  To setup this workspace environment, create a **dev** directory and then a **go** directory under it. Set the GOPATH environment variable to this directory where you will clone the newt and newtmgr repositories.
    
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

###Step 3: Downloading the Source and Installing the Tools 
Newt and newtmgr are individual Go packages and have their own git repositories. You can download the source and install one or both tools.

We use the `go get` command to download the source, build, and install the binary in the **$GOPATH/bin** directory. 

<br>
####Downloading and Installing the Newt Tool

The newt Go package is **mynewt.apache.org/newt/newt** and is stored in the [Apache Mynewt newt tool repository mirrored on github](https://github.com/apache/incubator-mynewt-newt). 


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
$git status
On branch master
Your branch is up-to-date with 'origin/master'.

nothing to commit, working directory clean
```
<br>
**Note:** The source code under the **newtmgr** directory is no longer used or updated. The current **newtmgr** source has its own Git repository.

<br>
Check that the newt binary is installed and you are using the one from ** $GOPATH/bin**:

```no-highlight
$ls $GOPATH/bin/newt
~/dev/go/bin/newt
$which newt
~/dev/go/bin/newt
$newt version
Apache Newt (incubating) version: 1.0.0-dev
```
<br>
####Downloading and Installing the Newtmgr Tool
The newtmgr Go package is **mynewt.apache.org/newtmgr/newtmgr**. It is stored in the [Apache Mynewt newtmgr tool repository mirrored on github](https://github.com/apache/incubator-mynewt-newtmgr).

Download the newtmgr package and install the tool:

**Note:** `-ldflags -s` must be passed to the `go get` command.

```no-highlight
$cd $GOPATH
$go get -ldflags -s mynewt.apache.org/newtmgr/newtmgr
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
$which newtmgr
~/dev/go/bin/newtmgr
```
<br>
### Step 4: Updating and Rebuilding the Tools:
This section shows you how to rebuild the newt and newtmgr tools with the latest updates from the master branch or after you have made changes in your branch. 

Here is the general procedure to rebuild either the newt or newtmgr tool. The only difference is the directory where you will be executing the commands from. You will need to repeat the procedure to rebuild both tools.

1. Change to the directory where the local Git repository for the tool is installed.
2. Pull the latest changes from the master branch. If you made changes you will need to rebase with **origin master** (See [FAQ](/faq/answers/)).
3. Build and install the tool.

<br>
Change to the directory where the source for the tool is installed.

For the  **newt** tool:
```no-highlight
$cd $GOPATH/src/mynewt.apache.org/newt/newt
```

For the **newtmgr** tool:
```no-highlight
$cd $GOPATH/src/mynewt.apache.org/newtmgr/newtmgr
```
<br>
After you change to the specific tool directory, get the latest updates from the master branch.  If you made changes and need to rebase with the origin, add the `--rebase origin master` arguments to the  `git pull` command:

```no-highlight
$git pull 
```

<br>
Build and install the tool. The updated binary will be installed in the **$GOPATH/bin** directory: 

(**Note:** `-ldflags -s` must be passed to the `go install` command if you are rebuilding newtmgr)

```no-highlight
$go install
```
You can run the `ls -l` command to check the modification time for the binary to ensure the new version is installed. 
