## Building newt tool on Linux 


### Getting your Ubuntu machine Ready 


#### Installing some prerequisites

* Install git, libcurl, and the Go language if you do not have them already.
```no-highlight
        $ sudo apt-get install git 
        $ sudo apt-get install libcurl4-gnutls-dev 
        $ sudo apt-get install golang 
```

#### Creating local repository 

* The directory structure must be first readied for using Go. Go code must be kept inside a workspace. A workspace is a directory hierarchy with three directories at its root:

    * src contains Go source files organized into packages (one package per directory),

    * pkg contains package objects, and

    * bin contains executable commands.

  The GOPATH environment variable specifies the location of your workspace. First create a 'dev' directory and then a 'go' directory under it. Set the GOPATH environment variable to this directory where you will soon clone the newt tool repository.
```no-highlight
        $ cd $HOME
        $ mkdir -p dev/go  
        $ cd dev/go
        $ export GOPATH=$PWD
```
  Note that you need to add export statements to ~/.bashrc (or equivalent) to export variables permanently.

* You are ready to download the newt tool repository. You will use Go to copy the directory (currently the asf incubator directory). Be patient as it may take a minute or two. Check the directories installed.
```no-highlight
        $ go get git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ ls
         bin	pkg	   src
        $ ls src
        git-wip-us.apache.org	github.com		gopkg.in
```

* Check that newt is in place.
```no-highlight
        $ ls $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt 
        Godeps			README.md		coding_style.txt    newt.go
        LICENSE			cli			    design.txt
```
#### Building the newt tool


* You will use Go to run the newt.go program to build the newt tool. The command used is  `go install` which compiles and writes the resulting executable to an output file named `newt`. It installs the results along with its dependencies in $GOPATH/bin.
```no-highlight
        $ cd $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt
        $ go install
        $ ls "$GOPATH"/bin/
        godep		incubator-mynewt-newt.git	  newt
```
* Try running newt using the compiled binary. For example, check for the version number by typing 'newt version'. See all the possible commands available to a user of newt by typing 'newt -h'.

   Note: If you are going to be be modifying the newt tool itself often and wish to compile the program every time you call it, you may want to store the command in a variable in your .bash_profile. So type in `export newt="go run $GOPATH/src/git-wip-us.apache.org/repos/asf/incubator-mynewt-newt.git/newt/newt/go"` in your ~/.bashrc (or equivalent) and execute it by calling `$newt` at the prompt instead of `newt`. Here, you use `go run` which runs the compiled binary directly without producing an executable.   
  
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
* Without creating a project repository you can't do a whole lot with the Newt tool. So you'll have to wait till you have downloaded a nest to try out the tool. 

