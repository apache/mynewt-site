## <font color="F2853F" style="font-size:24pt">nffs\_init</font>

```c
int nffs_init(void)
```

Initializes internal nffs memory and data structures.  This must be called before any nffs operations are attempted.

#### Returned values

* 0 on success
* [FS error code](../fs/fs_return_codes.md) on failure

#### Header file

```c
#include "nffs/nffs.h"
```
