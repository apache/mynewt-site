## Building newt tool on your Mac

### Getting your Mac Ready 

If you want to build the *newt* tool from its source code, follow the following steps:
#### 1. Install Homebrew on your Mac OS X 

* Do you have Homebrew? If not, open a terminal on your Mac and paste the following at a Terminal prompt. It will ask you for your sudo password.

```no-highlight
        $ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
   Alternatively, you can just extract (or `git clone`) Homebrew and install it to `/usr/local`.

#### 2. Install Go, the programming language

* Go language enviroment dictates a directory structure. Known in Go parlanace as workspace, it must contain three sibling directories with the directory names src, pkg and bin, as explained below. 

    * src contains Go source files organized into packages (one package per directory),

    * pkg contains package objects, and

    * bin contains executable commands.

    The GOPATH environment variable specifies the location of your workspace. To setup this workspace environment, create a 'dev' directory and then a 'go' directory under it. Set the GOPATH environment variable to this directory where you will soon clone the *newt* tool repository.
    
```no-highlight
        $ cd $HOME
        $ mkdir -p dev/go  
        $ cd dev/go
        $ export GOPATH=`pwd`
```
  (Note that you need to add export statements to ~/.bash_profile to export variables permanently. Don't forget to source the file for the change to go into effect.)

```no-highlight
        $ vi ~/.bash_profile
        $ source ~/.bash_profile
```
* Next, using *brew*, install Go. When installed, Go offers you as a developer a language enviroment (to compile Go code), construct Go packages (to assemble Go packages) and import Go code (from github). In the next step, you will use the Go commands to import *newt* repo into your local Go environment.
     
```no-highlight
        $ brew install go
        ==> 
        ...
        ... 
        ==> *Summary*
        🍺  /usr/local/Cellar/go/1.5.1: 5330 files, 273M
```
  Alternatively, you can download the Go package directly from (https://golang.org/dl/) instead of brewing it. Install it in /usr/local directory.
    

#### 3. Create local repository

* Use Go commands to copy the directory (currently the ASF incubator directory). Be patient as it may take a minute or two. Check the directories installed.

```no-highlight
        $ go get mynewt.apache.org/newt/...

```

* Check that newt.go is in place.
```no-highlight
        $ ls $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt  
        Godeps			README.md		coding_style.txt    newt.go
        LICENSE			cli			    design.txt
```

#### 4. Build the Newt tool

* Use Go to run the newt.go program to build the *newt* tool. The command `go install` compiles and writes the resulting executable to an output file named `newt`, which is then installed, along with its dependencies, in $GOPATH/bin.

```no-highlight
        $ cd $GOPATH/src/mynewt.apache.org/newt/newt
        $ go install
        $
        $ ls "$GOPATH"/bin/
        newt newtmgr newtvm
```
* At this point, you can try using *newt*. For example, check for the version number by typing 'newt version'. See all the possible commands available to a user of newt by typing 'newt -h'.

   (Note: If you are going to be modifying the *newt* often and going to be compile the program every time you call it, you will want to store the command in a variable in your .bash_profile. So type in `export newt="go run $GOPATH/mynewt.apache.org/newt/newt/newt.go"` in your .bash_profile and execute it by calling `$newt` at the prompt instead of `newt`. Essentially, `$newt` calls `go run` which runs the compiled binary directly without producing an executable. Don't forget to reload the updated bash profile by typing `source ~/.bash_profile` at the prompt! )
   
```no-highlight
        $ newt version
        Newt version:  1.0
        $ newt -h
        Newt allows you to create your own embedded project based on the Mynewt
        operating system. Newt provides both build and package management in a
        single tool, which allows you to compose an embedded workspace, and set
        of projects, and then build the necessary artifacts from those projects.
        For more information on the Mynewt operating system, please visit
        https://www.github.com/mynewt/documentation.

        Please use the newt help command, and specify the name of the command
        you want help for, for help on how to use a specific command

        Usage:
         newt [flags]
         newt [command]

        Examples:
         newt
         newt help [<command-name>]
           For help on <command-name>.  If not specified, print this message.


        Available Commands:
         version     Display the Newt version number.
         target      Set and view target information
         egg         Commands to list and inspect eggs on a nest
         nest        Commands to manage nests & clutches (remote egg repositories)
         help        Help about any command

        Flags:
         -h, --help=false: help for newt
         -l, --loglevel="WARN": Log level, defaults to WARN.
         -q, --quiet=false: Be quiet; only display error output.
         -s, --silent=false: Be silent; don't output anything.
         -v, --verbose=false: Enable verbose output when executing commands.


        Use "newt help [command]" for more information about a command.
```
* Without creating a project repository, you can't do a whole lot with the *newt tool. So you'll have to wait till you have downloaded an app to try out the tool. 

