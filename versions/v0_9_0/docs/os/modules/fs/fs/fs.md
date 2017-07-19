#File System Abstraction

Mynewt provides a file system abstraction layer (`fs/fs`) to allow client code to be file system agnostic.  By accessing the file system via the `fs/fs` API, client code can perform file system operations without being tied to a particular implementation.  When possible, library code should use the `fs/fs` API rather than accessing the underlying file system directly.

###Description

Applications should aim to minimize the amount of code which depends on a particular file system implementation.  When possible, only depend on the `fs/fs` package.  In the simplest case, the only code which needs to know which file system is in use is the code which initializes the file system.  In terms of the Mynewt hierarchy, the **app** package must depend on a specific file system package, while **library** packages should only depend on `fs/fs`.

The following example illustrates how file system dependencies should be managed.  In the slinky application, the app is responsible for initializing the file system, so it depends on a concrete file system package called `fs/nffs` (Newtron Flash File System). The app explicitly initializes nffs via calls to `nffs_init()`, `nffs_detect()` and `nffs_format()`.

```no-highlight
# repos/apache-mynewt-core/apps/slinky/pkg.yml

pkg.name: repos/apache-mynewt-core/apps/slinky
pkg.deps:
    - fs/nffs

# [...]
```

```c
/* repos/apache-mynewt-core/apps/slinky/src/main.c */

#include "nffs/nffs.h"

int
main(int argc, char **argv)
{
    int rc;
    int cnt;
    struct nffs_area_desc descs[NFFS_AREA_MAX];

    rc = nffs_init();
    assert(rc == 0);

    cnt = NFFS_AREA_MAX;
    rc = flash_area_to_nffs_desc(FLASH_AREA_NFFS, &cnt, descs);
    assert(rc == 0);
    if (nffs_detect(descs) == FS_ECORRUPT) {
        rc = nffs_format(descs);
        assert(rc == 0);
    }
    // [...]
}
```

On the other hand, code which uses the file system after it has been initialized need only depend on `fs/fs`.  For example, the `libs/imgmgr` package is a library which provides firmware upload and download functionality via the use of a file system.  This library is only used after the main app has initialized the file system, and therefore only depends on the `fs/fs` package.

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
