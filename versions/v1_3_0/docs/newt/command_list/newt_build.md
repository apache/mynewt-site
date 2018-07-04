## <font color="#F2853F" style="font-size:24pt">newt build </font>

Build one or more targets. 

#### Usage: 

```no-highlight
    newt build  <target-name> [target_name ...] [flags] 
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
Compiles, links, and builds an ELF binary for the target named &lt;target-name&gt;.  It builds an ELF file for the application specified by the `app` variable for the `target-name` target. The image can be loaded and run on the hardware specified by the `bsp` variable for the target. The command creates the 'bin/' directory under the project's base directory (that the `newt new` command created) and stores the executable in the 'bin/targets/&lt;target-name&gt;/app/apps/&lt;app-name&gt;' directory.  A `manifest.json` build manifest file is also generated in the same directory. This build manifest contains information such as build time, version, image name, a hash to identify the image, packages actually used to create the build, and the target for which the image is built.

You can specify a list of target names, separated by a space, to build multiple targets. 

#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
      | newt build <br> my_blinky_sim | Builds an executable for the `my_blinky_sim` target. For example, if the `my_blinky_sim` target has `app` set to `apps/blinky`, you will find the generated .elf, .a, and .lst files in the 'bin/targets/my_blinky_sim/app/apps/blinky' directory. 
      |  newt build <br> my_blinky_sim myble | Builds the images for the applications defined by the `my_blinky_sim` and `myble` targets.
