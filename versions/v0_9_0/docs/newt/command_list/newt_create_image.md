## <font color="#F2853F" style="font-size:24pt">newt create-image </font>

Creates a signed image by adding image header to created binary file for specified target. Version number in the header is set to be <version> 

#### Usage: 

```no-highlight
    newt create-image <target-name> <version> [flags]
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
create-image | Signs and adds image header to the created binary file for target named `<target-name>` and given the version specified as `<version>`. The application image generated is `<app-name>.img` where the app-name is the same as the app specified in the target definition. The generated application image can be found in `/bin/<target-name>/apps/<app-name>/`. <br> <br> A build manifest file `manifest.json` is also generated in the same directory. This build manifest contains information such as build time, version, image name, a hash to identify the image, packages actually used to create the build, and the target for which the image is built.


#### Examples

 Sub-command  | Usage                  | Explanation 
-------------| -----------------------|-----------------
create-image   | newt create-image myble2 1.0.1.0 | Creates a signed image for target `myble2` and assigns it the version `1.0.1.0`. <br> <br> If the target is as follows: <br> targets/myble2 <br> app=@apache-mynewt-core/apps/bletiny <br> bsp=@apache-mynewt-core/hw/bsp/nrf52pdk <br> build_profile=optimized <br> cflags=-DSTATS_NAME_ENABLE <br> <br> then, the created image is `bin/myble2/apps/bletiny/bletiny.img` and the manifest is `bin/myble2/apps/bletiny/manifest.json`
