## <font color="#F2853F" style="font-size:24pt">fs\_getpos</font>

```no-highlight
uint32_t fs_getpos(const struct fs_file *file)
```

Retrieves the current read and write position of the specified open file. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| file |  Pointer to the file to query |

#### Returned values

* The file offset, in bytes

#### Notes 

If a file is opened in append mode, its write pointer is always positioned at the end of the file.  Calling this function on such a file only indicates the read position.

#### Header file

```no-highlight
#include "fs/fs.h"
```
