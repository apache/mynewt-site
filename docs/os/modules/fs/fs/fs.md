#File System Abstraction

Mynewt provides a file system abstraction layer (`fs/fs`) to allow client code to be file system agnostic.  By accessing the file system via the `fs/fs` API, client code can perform file system operations without being tied to a particular implementation.  When possible, library code should use the `fs/fs` API rather than accessing the underlying file system directly.

###Description

Applications should aim to minimize the amount of code which depends on a particular file system implementation.  When possible, only depend on the
`fs/fs` package.
In terms of the Mynewt hierarchy, an **app** package must depend on a specific file system package, while **library** packages should only depend on `fs/fs`.

Applications wanting to access a filesystem are required to include the necessary packages in their applications pkg.yml file.
In the following example, the [`Newtron Flash File System`](../nffs/nffs.md)
is used.

```no-highlight
# repos/apache-mynewt-core/apps/slinky/pkg.yml

pkg.name: repos/apache-mynewt-core/apps/slinky
pkg.deps:
    - fs/fs         # include the file operations interfaces
    - fs/nffs       # include the NFFS filesystem implementation
```

```
# repos/apache-mynewt-core/apps/slinky/syscfg.yml
# [...]
 # Package: apps/<example app>
# [...]
    CONFIG_NFFS: 1  # initialize and configure NFFS into the system
#   NFFS_DETECT_FAIL: 1   # Ignore NFFS detection issues 
#   NFFS_DETECT_FAIL: 2   # Format a new NFFS file system on failure to detect

# [...]
```
Consult the documentation for [`nffs`](../nffs/nffs.md) for a more detailed explanation of NFFS_DETECT_FAIL

Code which uses the file system after the system has been initialized need only depend on `fs/fs`.  For example, the `libs/imgmgr` package is a library which provides firmware upload and download functionality via the use of a file system.  This library is only used after the system has been initialized, and therefore only depends on the `fs/fs` package.

```no-highlight
# repos/apache-mynewt-core/libs/imgmgr/pkg.yml
pkg.name: libs/imgmgr
pkg.deps:
    - fs/fs

# [...]
```

The `libs/imgmgr` package uses the `fs/fs` API for all file system operations.

###Thread Safety
All `fs/fs` functions are thread safe.

###Header Files 
All code which uses the `fs/fs` package needs to include the following header:

```c
#include "fs/fs.h"
```

###Data Structures
All `fs/fs` data structures are opaque to client code.

```c
struct fs_file;
struct fs_dir;
struct fs_dirent;
```

###API

Functions in `fs/fs` that indicate success or failure do so with the following set of return codes:

* [Return Codes](fs_return_codes.md)

The functions available in this OS feature are:

| Function | Description |
|---------|-------------|
| [fs\_close](fs_close.md) | Closes the specified file and invalidates the file handle. |
| [fs\_closedir](fs_closedir.md) | Closes the specified directory handle. |
| [fs\_dirent\_is\_dir](fs_dirent_is_dir.md) | Tells you whether the specified directory entry is a sub-directory or a regular file. |
| [fs\_dirent\_name](fs_dirent_name.md) | Retrieves the filename of the specified directory entry. |
| [fs\_filelen](fs_filelen.md) | Retrieves the current length of the specified open file. |
| [fs\_getpos](fs_getpos.md) | Retrieves the current read and write position of the specified open file. |
| [fs\_mkdir](fs_mkdir.md) | Creates the directory represented by the specified path. |
| [fs\_open](fs_open.md) | Opens a file at the specified path. |
| [fs\_opendir](fs_opendir.md) | Opens the directory at the specified path. |
| [fs\_read](fs_read.md) | Reads data from the specified file. |
| [fs\_readdir](fs_readdir.md) | Reads the next entry in an open directory. |
| [fs\_register](fs_register.md) | Registers a file system with the abstraction layer. |
| [fs\_rename](fs_rename.md) | Performs a rename and/or move of the specified source path to the specified destination. |
| [fs\_seek](fs_seek.md) | Positions a file's read and write pointer at the specified offset. |
| [fs\_unlink](fs_unlink.md) | Unlinks the file or directory at the specified path. |
| [fs\_write](fs_write.md) | Writes the supplied data to the current offset of the specified file handle. |

Additional file system utilities that bundle some of the basic functions above are:

| Function | Description |
|---------|-------------|
| [fsutil\_read\_file](fsutil_read_file.md) | Opens a file at the specified path, retrieve data from the file starting from the specified offset, and close the file and invalidate the file handle. |
| [fsutil\_write\_file](fsutil_write_file.md) | Open a file at the specified path, write the supplied data to the current offset of the specified file handle, and close the file and invalidate the file handle. |
