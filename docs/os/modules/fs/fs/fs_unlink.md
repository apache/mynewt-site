## <font color="#F2853F" style="font-size:24pt">fs\_unlink</font>

```c
int fs_unlink(const char *filename)
```

Unlinks the file or directory at the specified path.  This is the function to use if you want to delete a file or directory from the disk.  If the path refers to a directory, all the directory's descendants are recursively unlinked.  Any open file handles referring to an unlinked file remain valid, and can be read from and written to as long as they remain open.

#### Arguments

| *Argument* | *Description* |
|-----------|-------------|
| filename  |  The path of the file or directory to unlink |

#### Returned values

* 0 on success
* [FS error code](fs_return_codes.md) on failure

#### Header file

```c
#include "fs/fs.h"
```

#### Example

The following example creates a file and then immediately unlinks it.  By unlinking the file, this function prevents other OS tasks from accessing it.  When the function closes the file, it is deleted from the disk.

```c
int
process_data(void)
{
    struct fs_file *file;
    int rc;

    /* If the file doesn't exist, create it.  If it does exist, truncate it to
     * zero bytes.
     */
    rc = fs_open("/tmp/buffer.bin", FS_ACCESS_WRITE | FS_ACCESS_TRUNCATE, &file);
    if (rc == 0) {
        /* Unlink the file so that other tasks cannot access it. */
        fs_unlink("/tmp/buffer.bin")

        /* <use the file as a data buffer> */

        /* Close the file.  This operation causes the file to be deleted from
         * the disk because it was unlinked earlier (and it has no other open
         * file handles).
         */
        fs_close(file);
    }

    return rc == 0 ? 0 : -1;
}
```
