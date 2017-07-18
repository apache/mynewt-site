## <font color="#F2853F" style="font-size:24pt">newt run </font>

A single command to do four steps - build a target, create-image, load image on a board, and start a debug session with the image on board.

**Note**: If version number is omitted, create-image step is skipped

#### Usage: 

```no-highlight
    newt run <target-name> [<version>][flags] 
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

#### Description

Sub-command  | Explanation
-------------| ------------------------
run         | Same as running `build <target>`, `create-image <target> <version>`,  `load <target>`, and `debug <target>`.


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
run       | newt run blink_rigado | First compiles and builds executable for running the app defined in the target `blink_rigado` on the board defined in the same target, then loads image onto the board, and finally opens an active GNU gdb debugging session to run the image. 
run       | newt run ble_rigado 0.1.0.0 | First compiles and builds executable for running the app defined in the target `ble_rigado` on the board defined in the same target, then signs and creates image with version number 0.1.0.0, loads the image onto the board, and finally opens an active GNU gdb debugging session to run the image. <br> <br> Note that if there is no bootloader available for a particular board/kit, a signed image creation step is not necessary.