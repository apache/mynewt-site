## <font color="#F2853F" style="font-size:24pt">newt pkg </font>

Commands for creating and manipulating packages.

#### Usage: 
```no-highlight
    newt pkg [command] [flags] 
```    
#### Flags:
```no-highlight
 -t, --type string   Type of package to create: pkg, bsp, sdk. (default "pkg")
```
#### Global Flags:
```no-highlight
    -h, --help              Help for newt commands
    -j, --jobs int          Number of concurrent build jobs (default 8)
    -l, --loglevel string   Log level (default "WARN")
    -o, --outfile string    Filename to tee output to
    -q, --quiet             Be quiet; only display error output
    -s, --silent            Be silent; don't output anything
    -v, --verbose           Enable verbose output when executing commands
```
#### Description

The pkg command provides subcommands to create and manage packages. The subcommands take one or two `package-name` arguments.

Sub-command             | Explanation
------------------------| ------------------------
copy    | The copy &lt;src-pkg&gt; &lt;dst-pkg&gt; command creates the new `dst-pkg` package by cloning the `src-pkg` package. 
move    | The move &lt;old-pkg&gt; &lt;new-pkg&gt; command moves the `old-pkg` package to the `new-pkg` package.
new     | The new &lt;new-pkg&gt; command creates a new package named `new-pkg`, from a template, in the current directory. You can create a package of type `pkg`, `bsp`, or `sdk`. The default package type is `pkg`. You use the -t flag to specify a different package type.  
remove  | The remove &lt;my-pkg&gt;  command deletes the `my-pkg` package.

#### Examples

Sub-command  | Usage                  | Explanation
-------------| -----------------------|-----------------
copy         | newt pkg copy <br>apps/bletiny apps/new_bletiny | Copies the `apps/bletiny` package to the `apps/new_bletiny`.
move         | newt pkg move <br>apps/slinky apps/new_slinky | Moves the `apps/slinky` package to the `apps/new_slinky` package.
new          | newt pkg new apps/new_slinky | Creates a package named `apps/new_slinky` of type `pkg` in the current directory.
new          | newt pkg new hw/bsp/myboard -t bsp| Creates a package named `hw/bsp/myboard` of type `bsp` in the current directory.
remove       | newt pkg remove hw/bsp/myboard | Removes the `hw/bsp/myboard` package.

