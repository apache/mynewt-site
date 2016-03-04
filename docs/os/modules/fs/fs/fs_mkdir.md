## <font color="#F2853F" style="font-size:24pt">fs\_mkdir</font>

```no-highlight
int fs_mkdir(const char *path)
```

Creates the directory represented by the specified path.  

#### Arguments

| Arguments | Description |
|-----------|-------------|
| path      |  The name of the directory to create |


#### Returned values

* 0 on success
* [FS error code](fs_return_codes.md) on failure.

#### Notes 

All intermediate directories must already exist.  The specified path must start with a '/' character.

#### Header file

```no-highlight
#include "fs/fs.h"
```

#### Example

This example demonstrates creating a series of nested directories.

```no-highlight
int
create_path(void)
{
    int rc;

    rc = fs_mkdir("/data");
    if (rc != 0) goto err;

    rc = fs_mkdir("/data/logs");
    if (rc != 0) goto err;

    rc = fs_mkdir("/data/logs/temperature");
    if (rc != 0) goto err;

    rc = fs_mkdir("/data/logs/temperature/current");
    if (rc != 0) goto err;

    return 0;

err:
    /* Clean up the incomplete directory tree, if any. */
    fs_unlink("/data");
    return -1;
}
```
