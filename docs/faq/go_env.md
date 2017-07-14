## Contributing to Newt and Newtmgr Tools
Newt and Newtmgr are written in Go (golang). This guide shows you how to install Go and setup your environment if
you would like to contribute to the newt or newtmgr tools.

This guide shows you how to perform the following:

1. Install Go on either Mac OS or Linux.
2. Setup the Go environment.
3. Download the newt and newtmgr source code.
4. Build the newt and newtmgr tools.
5. Update and rebuild the tools. 

Steps 2-5 apply to both Mac OS and Linux platforms.

**Note:** You will also need to read and follow the instructions from [FAQ](/faq/answers/) to set up your git repos to submit changes.


### Step 1: Installing Go 
The latest master branch of newt and newtmgr requires GO version 1.6 or higher.
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
### Step 2: Setting Up Your Go Environment
Go provides an environment to compile Go code, construct Go packages,  and import Go code.  You will use Go commands to import the **newt** repository into your local Go environment.  The Go language environment dictates a specific directory structure, or workspace in Go parlance. It must contain three sibling directories with the names **src**, **pkg** and **bin**: 

* src contains Go source files organized into packages (one package per directory)
* pkg contains package objects
* bin contains executable commands.

The **GOPATH** environment variable specifies the location of your workspace. To setup this workspace environment, create a **dev** directory and then a **go** directory under it. Set the GOPATH environment variable to this directory where you will clone the newt repository.
    
```no-highlight
$ cd $HOME
$ mkdir -p dev/go  
$ cd dev/go
$ export GOPATH=`pwd`
```
<br>
Add the export GOPATH statement to the ~/.bash_profile file and source the file:

```no-highlight
$ vi ~/.bash_profile
$ source ~/.bash_profile
```

<br>


### Step 3: Downloading the Source

Use Go commands to retrieve the latest source from the newt repository (currently the ASF incubator directory). Check that the directories are installed.

```no-highlight
$ go get mynewt.apache.org/newt/...
$ ls $GOPATH/src/mynewt.apache.org/newt
DISCLAIMER	NOTICE		newt		newtvm      viper
LICENSE		README.md	newtmgr		util        yaml
```

<br>

### Step 4: Building the Newt and Newtmgr Tools
Perform the following commands to build the tools:
```no-highlight
$ cd $GOPATH/src/mynewt.apache.org/newt/newt
$ go install
$ ls $GOPATH/bin/
newt newtmgr newtvm
```

<br>

### Step 5: Updating and Rebuilding the Tools
Change to the directory where you initially installed the source: 

```no-highlight
$ cd $GOPATH/src/mynewt.apache.org/newt
```
<br>
Pull the latest source from the repository (you can change to a different branch using git checkout [branch] if you need to)
```no-highlight
$ git pull
```
<br>
Install the tools from the latest source:
```no-highlight
$ cd newt
$ go install
$ cd ../newtmgr
$ go install
$ ls $GOPATH /bin/
newt newtmgr newtvm
```

This should have updated your newt and newtmgr to the latest version based on the git repository you used.

