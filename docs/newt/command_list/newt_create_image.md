## <font color="#F2853F" style="font-size:24pt">newt create-image </font>

Create and sign an image by adding an image header to the binary file created for a target. Version number in the header is set to &lt;version&gt;. To sign an image provide a .pem file for the signing-key and an optional key-id.

#### Usage: 

```no-highlight
    newt create-image <target-name> <version> [signing-key [key-id]][flags]
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

Adds an image header to the created binary file for the `target-name` target. The image version is set to `version`. It creates a `<app-name>.img` file the image, where `app-name` is the value specified in the target `app` variable, and stores the file in the '/bin/targets/&lt;target-name&gt;/app/apps/&lt;app-name&gt;/' directory. It also creates a `<app-name>.hex` file for the image in the same directory, and adds the version, build id, image file name, and image hash to the `manifest.json` file that the `newt build` command created. 

To sign an image,  provide a .pem file for the `signing-key` and an optional `key-id`. `key-id` must be a value between 0-255.

#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
             | newt create-image myble2 1.0.1.0 | Creates an image for target `myble2` and assigns it version `1.0.1.0`. <br> <br> For the following target definition: <br> targets/myble2 <br> app=@apache-mynewt-core/apps/bletiny <br> bsp=@apache-mynewt-core/hw/bsp/nrf52pdk <br> build_profile=optimized <br> syscfg=STATS_NAMES=1 <br><br> the 'bin/targets/myble2/app/apps/bletiny/bletiny.img' and 'bin/targets/myble2/app/apps/bletiny/bletiny.hex' files are created, and the manifest in 'bin/targets/myble2/app/apps/bletiny/manifest.json' is updated with the image information.
             | newt create-image myble2 1.0.1.0 private.pem | Creates an image for target `myble2` and assigns it the version `1.0.1.0`. Signs the image using  private key specified by the private.pem file. 
