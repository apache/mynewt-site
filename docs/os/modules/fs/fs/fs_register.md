## <font color="F2853F" style="font-size:24pt">fs\_register</font>

```no-highlight
int fs_register(const struct fs_ops *fops)
```

Registers a file system with the abstraction layer.  On success, all calls into `fs/fs` will use the registered file system.

#### Arguments

| Argument | Description |
|----------|-------------|
| fops     | A pointer to const [struct fs\_ops](fs_ops.md). Specifies which file system routines get mapped to the `fs/fs` API.  All function pointers must be filled in. |

#### Returned values

* 0 on success
* *FS\_EEXIST* if a file system has already been registered

#### Notes 

Only one file system can be registered.  The registered file system is mounted in the root directory (*/*).

#### Header file

```no-highlight
#include "fs/fs.h"
```
