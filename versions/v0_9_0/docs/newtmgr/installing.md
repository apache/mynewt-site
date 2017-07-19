
# Installing Newtmgr

This page shows you how to install newtmgr from source code.

### Install Go (golang)

If you have not already done so, install Go for your platform.  

The easiest way on a MAC is to use `brew`.  

```no-highlight
brew install go
==> Downloading https://homebrew.bintray.com/bottles/go-1.5.3.mavericks.bottle.t
...
==> Summary
🍺  /usr/local/Cellar/go/1.5.3: 5,336 files, 259.6M
```

<br>

Alternatively, you can download binaries from 
[the golang.org site](https://golang.org/doc/install)
To test your Go implementation, you can query Go for its version information

```no-highlight
$ go version
go version go1.5.3 darwin/amd64
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
        (wait a few minutes please, this sits without any indications of working)
```

<br>

### Building newtmgr

Change into the directory where the newmgr tool was downloaded and 
install the newtmgr tool

```no-highlight
    cd $GOPATH/src/mynewt.apache.org/newt/newtmgr
    go install
    $ ls $GOPATH/bin
    ... newtmgr	...
```

<br>

**Note:** If the `go install` command results in errors indicating some package 
cannot be found, do a `go get` to download all the third-party files needed 
from github.com and then run `go install` again. 

### Add to your Path

Add your `$GOPATH/bin` directory to your path.

