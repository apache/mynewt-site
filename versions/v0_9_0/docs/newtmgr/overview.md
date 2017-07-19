## Newt Manager

Newt Manager (newtmgr) is the application tool that enables a user to communicate with and manage remote instances of Mynewt OS. 


## Description



## Command List

### Available high-level commands

```no-highlight
    help        Lists commands and flags available 
    conn        Manage newtmgr connection profiles
    echo        Send data to remote endpoint using newtmgr, and receive data back
    image       Manage images on remote instance
    stat        Read statistics from a remote endpoint
    taskstats   Read statistics from a remote endpoint
    mpstats     Read statistics from a remote endpoint
    config      Read or write config value on target
```

### Available Flags

```no-highlight
  -c, --connection string       connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
newtmgr -caditi03 taskstats

### *help*

#### Usage:
```no-highlight
    newtmgr help [input1]
```    
You can also use "newtmgr [command] --help" to display the help text for a newtmgr command.

Flags:

```no-highlight
  -c, --connection string      connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```
    
Examples

Sub-command | Available Flags | Explanation
------------| ----------------|-----------------
taskstats  | newtmgr -cprofile1 taskstats | Run the taskstats subcommand on the device connected via the 'profile1' connection
   
### *conn*

#### Usage:
```no-highlight
    newtmgr conn [flags]
    newtmgr conn [command]
```    

Available commands: 

```no-highlight
    add         Add a newtmgr connection profile
    delete      Delete a newtmgr connection profile
    show        Show newtmgr connection profiles
```

Flags:

```no-highlight
  -c, --conn string       connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```

Description

Sub-command  | Explanation
-------------| ------------------------
add       | Adds a connection profile. A properly defined profile needs a name, a connection type, and the physical or virtual port to be used for communication.
delete    | Deletes a connection profile associated with the given name
show      | List the specified or all the connection profiles with the name, connection type, and the controlling terminal or port.
    

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
add       | newtmgr conn add myserial02 type=serial connstring=/dev/ttys002 | Adds a newtmgr connection profile for the serial port /dev/ttys002 and names it 'myserial02'
delete    | newtmgr conn delete myserial02  | Deletes the connection profile named 'myserial02'
show      | newtmgr conn show myserial01 | Shows the details of the profile named 'myserial01'
show      | newtmgr conn show  | Shows all the current profiles defined
    
### *echo*

#### Usage:
```no-highlight
    newtmgr echo [flags] [text]
```    
This command sends the text to the remote device at the other end of the connection specified with the -c flag and outputs the text when it gets a response from the device. If the device is not responding or if the connection profile is invalid it displays errors. 

Flags:

```no-highlight
  -c, --conn string       connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
echo       | newtmgr echo -c profile01 hello | Sends the string 'hello' to the remote device over the connection profile 'profile01' and receives the string back and displays it.


   
### *image*

#### Usage:
```no-highlight
  newtmgr image [flags]
  newtmgr image [command]
```    

Available commands: 

```no-highlight
    list         Show target images
    upload       Upload image to target
    boot         Which image to boot
    fileupload   Upload file to target
    filedownload Download file from target
```

Flags:

```no-highlight
  -c, --conn string       connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```

Description

Sub-command  | Explanation
-------------| ------------------------
list      | Adds a connection profile. A properly defined profile needs a name, a connection type, and the physical or virtual port to be used for communication.
upload    | Deletes a connection profile associated with the given name
boot      | Specify the image to boot 
fileupload | upload file to the remote target
filedownload | download/retrieve file from remote target
    

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
list       | newtmgr list | 
upload     | newtmgr upload  | 
boot       | newtmgr boot | 
fileupload | newtmgr fileupload  | 
filedownload | newtmgr filedownload | 


### *stat*

#### Usage:
```no-highlight
  newtmgr stat [flags]
  newtmgr stat [command]
```    
Flags:

```no-highlight
  -c, --conn string       connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
stat       | newtmgr stat | 


### *taskstats*

#### Usage:
```no-highlight
  newtmgr taskstats [flags]
  newtmgr taskstats [command]
```    

Lists all the tasks running on the remote endpoint at the end of the specified connection and for each task lists statistics such as priority, task id, runtime (how long the task has been running in ms), context switch count, stack size allocated, actual stack usage, last sanity checkin, next sanity check-in. 

Flags:

```no-highlight
  -c, --conn string       connection profile to use.
  -l, --loglevel string   log level to use (default WARN.)
```

Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
stat       | newtmgr taskstats -c profile01 | Lists all the tasks running on the remote device at the end of connection named 'profile01' 

Example output

```no-highlight
$ newtmgr  -c profile01 taskstats
Return Code = 0
  idle (prio=255 tid=0 runtime=3299340 cswcnt=280342 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
  os_sanity (prio=254 tid=1 runtime=0 cswcnt=3287 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
  shell (prio=3 tid=2 runtime=0 cswcnt=165 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
  uart_poller (prio=0 tid=3 runtime=0 cswcnt=279368 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
  newtmgr (prio=4 tid=4 runtime=0 cswcnt=14 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
  task1 (prio=1 tid=5 runtime=0 cswcnt=3287 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
  task2 (prio=2 tid=6 runtime=0 cswcnt=3287 stksize=1024 stkusage=1000 last_checkin=0 next_checkin=0)
```