
# Installing Newtmgr on Linux

This page shows you how to install newtmgr from source code on Linux.

### Install Go (golang)

Install Go if it is not installed.  The Newtmgr tool version 1.0.0 requires Go version 1.7 or later.  Currently, the latest Go version that Ubuntu installs is
1.6. You can run `apt-get install golang-1.7-go` to install version 1.7. You can also download version 1.7 from [https:/
/golang.org/dl/](https://golang.org/dl/).

```hl_lines="1 7"
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
<br>

To use go, you must set a `$GOPATH` variable in your environment.  This tells
go where to put all the packages it downloads, builds and runs.

```no-highlight
$ mkdir $HOME/dev
$ export GOPATH=$HOME/dev/Go
```

<br>

Its best to add this to your `.profile` so its set automatically for your 
environment. 

<br>

### Download the newtmgr source 

You will first download the source code for newt.

```no-highlight
go get mynewt.apache.org/newt/...
```

<br>

### Building newtmgr

Change into the directory where the newmgr tool was downloaded and 
install the newtmgr tool

```no-highlight
$cd $GOPATH/src/mynewt.apache.org/newt/newtmgr
$go install
$ls $GOPATH/bin
... newtmgr	...
```

<br>

**Note:** If the `go install` command results in errors indicating some package 
cannot be found, do a `go get` to download all the third-party files needed 
from github.com and then run `go install` again. 

### Add to your Path

Add your `$GOPATH/bin` directory to your path.

