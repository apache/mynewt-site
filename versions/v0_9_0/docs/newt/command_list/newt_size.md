## <font color="#F2853F" style="font-size:24pt">newt size </font>

Calculate the size of target components specified by <target-name>

#### Usage: 

```no-highlight
    newt size <target-name> [flags]
```

#### Flags:
```no-highlight
    -h, --help=false: help for target
```

#### Global Flags:
```no-highlight
    -l, --loglevel="WARN": Log level, defaults to WARN.
    -o, --outfile string    Filename to tee log output to
    -q, --quiet=false: Be quiet; only display error output.
    -s, --silent=false: Be silent; don't output anything.
    -v, --verbose=false: Enable verbose output when executing commands.
```


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|----------------- 
size   | newt size blink_rigado | Inspects and lists the RAM and Flash memory use by each component (object files and libraries) of the target.

#### Example output for `newt size boot_olimex`:

```no-highlight

$ newt size blink_rigado
  FLASH     RAM 
      9     223 *fill*
   1052       0 baselibc.a
    195    1116 blinky.a
    616     452 bmd300eval.a
     64       0 cmsis-core.a
    124       0 crt0.o
      8       0 crti.o
     16       0 crtn.o
    277     196 full.a
     20       8 hal.a
     96    1068 libg.a
   1452       0 libgcc.a
    332      28 nrf52xxx.a
   3143     677 os.a

objsize
   text	   data	    bss	    dec	    hex	filename
   7404	   1172	   2212	  10788	   2a24	/Users/<username>/dev/rigado/bin/blink_rigado/apps/blinky/blinky.elf
```
