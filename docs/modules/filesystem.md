# Filesystem

Mynewt provides a Flash File System abstraction layer (fs) to allow you to swap out the default Newtron File System (nffs) with a different file system of your choice. 

## Description

The default file system used in the Mynewt OS is the Newtron Flash File System (nffs). Hence the `nffs` egg description lists `libs/fs` as a dependency. 

```no-highlight
egg.name: libs/nffs
egg.vers: 0.1
egg.identities: NFFS
egg.deps:
    - libs/os
    - libs/fs
    - libs/testutil
    - hw/hal
```

If the user wishes to use a different flash file system (say, "ownffs"), the directory containing "ownffs" code must include the `egg.yml` file stating the dependency on `libs/fs` listed as shown above. "ownffs" uses the `libs/fs` API available in mynewt, thus minimizing changes to other parts of the project.

Note that this generic file system (`fs`) API does not expose any file system detection, initialization, and formatting functions. These function calls remain specific to the chosen file system. For example, Project Slinky uses the default Newtron File System (nffs) and therefore calls nffs_init() to initialize the nffs memory and data structures before any other file system operations are attempted. As shown below, the egg for Project Slinky includes the `libs/imgmgr` egg which in turn includes the `libs/bootutil ` egg. The egg description for `libs/bootutil` specifies `fs/nffs` as a dependency.

```no-highlight

    egg.name: project/slinky
    egg.vers: 0.1
    egg.deps:
        - libs/os
        - libs/console/full
        - libs/shell
        - libs/newtmgr
        - libs/imgmgr
        - sys/config
        - sys/log
        - sys/stats
```

```no-highlight

    egg.name: libs/imgmgr
    egg.vers: 0.1
    egg.deps:
        - libs/newtmgr
        - libs/bootutil
    egg.deps.FS:
        - fs/fs
    egg.cflags.FS: -DFS_PRESENT
```

```no-highlight
 
    egg.name: libs/bootutil
    egg.vers: 0.1 
    egg.deps: 
        - fs/nffs
        - libs/os 
        - libs/testutil
        - hw/hal
```
        
## Data Structures


## API

```no-highlight
   struct fs_file;
```

The functions available in this OS feature are:

* [fs_open](#fs_open)
* [fs_close](#fs_close)
* [fs_read](#fs_read)
* [fs_write](#fs_write)
* [fs_seek](#fs_seek)
* [fs_getpos](#fs_getpos)
* [fs_filelen](#fs_filelen)
* [fs_unlink](#fs_unlink)
* [fs_rename](#fs_rename)
* [fs_mkdir](#fs_mkdir)
* [fs_opendir](#fs_opendir)
* [fs_readdir](#fs_readdir)
* [fs_closedir](#fs_closedir)
* [fs_dirent_name](#fs_dirent_name)
* [fs_dirent_is_dir](#fs_dirent_is_dir)

Additional file system utilities that bundle some of the basic functions above are:

* [fsutil_read_file](#fsutil_read_file)
* [fsutil_write_file](#fsutil_write_file)


## API Reference

------------------

## <font color="F2853F" style="font-size:24pt"> fs_open </font>

```no-highlight
    int
    fs_open(const char *filename, uint8_t access_flags, struct fs_file **out_file);
```

Opens a file at the specified path.  The result of opening a nonexistent file depends on the access flags specified.  All intermediate directories must already exist.

By default (when nffs is the underlying filesystem used) the mode strings passed to fopen() map to nffs_open()'s access flags as follows:

```no-highlight
    "r"  -  NFFS_ACCESS_READ
    "r+" -  NFFS_ACCESS_READ | NFFS_ACCESS_WRITE
    "w"  -  NFFS_ACCESS_WRITE | NFFS_ACCESS_TRUNCATE
    "w+" -  NFFS_ACCESS_READ | NFFS_ACCESS_WRITE | NFFS_ACCESS_TRUNCATE
    "a"  -  NFFS_ACCESS_WRITE | NFFS_ACCESS_APPEND
    "a+" -  NFFS_ACCESS_READ | NFFS_ACCESS_WRITE | NFFS_ACCESS_APPEND
```

#### Arguments

| Arguments | Description |
|-----------|-------------|
| filename |  Pointer to the file created at the path of the specified filename    |
| access_flags |  Flags controlling file access; see above table   |
| out_file | On success, a pointer to the newly-created file handle gets written here|

#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

<Add text to set up the context for the example here>

```no-highlight

<Insert the code snippet here>

```

---------------------
   
## <font color="#F2853F" style="font-size:24pt"> fs_close </font>

```no-highlight
   int
   fs_close(struct fs_file *file);  
```

Closes the specified file and invalidates the file handle.  If the file has already been unlinked, and this is the last open handle to the file, this operation causes the file to be deleted from disk.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| file|  Pointer to the file to close  |

#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

<Add text to set up the context for the example here>

```no-highlight

<Insert the code snippet here>

```

---------------------
   
## <font color="#F2853F" style="font-size:24pt"> fs_read </font>

```no-highlight
   int
   fs_read(struct fs_file *file, uint32_t len, void *out_data, uint32_t *out_len);
```

Reads data from the specified file.  If more data is requested than remains in the file, all available data is retrieved.  

#### Arguments

| Arguments | Description |
|-----------|-------------|
| file |  Pointer to the the file to read from  |
| len |  The number of bytes to attempt to read |
| out_data | The destination buffer to read into
| out_len  | On success, the number of bytes actually read gets written here.  Pass null if you don't care. |

#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

This type of short read results in a success return code.


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>

```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_write </font>

```no-highlight
   int
   fs_write(struct fs_file *file, const void *data, int len);
```

Writes the supplied data to the current offset of the specified file handle.  

#### Arguments

| Arguments | Description |
|-----------|-------------|
| file |  Pointer to the file to write to |
| data |  The data to write |
| len | The number of bytes to write |


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_seek </font>

```no-highlight
   int
   fs_seek(struct fs_file *file, uint32_t offset);
```

Positions a file's read and write pointer at the specified offset.  The offset is expressed as the number of bytes from the start of the file (i.e., seeking to offset 0 places the pointer at the first byte in the file). 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| file |  Pointer to the file to reposition |
| offset |  The 0-based file offset to seek to |


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_getpos </font>

```no-highlight
   uint32_t
   fs_getpos(const struct fs_file *file);
```

Retrieves the current read and write position of the specified open file. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| file |  Pointer to the file to query |


#### Returned values

* The file offset, in bytes

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_filelen </font>

```no-highlight
   int
   fs_filelen(const struct fs_file *file, uint32_t *out_len);

```

Retrieves the current length of the specified open file.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| file |  Pointer to the file to query |
| out_len |  On success, the number of bytes in the file gets written here |


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_unlink </font>

```no-highlight
   int
   fs_unlink(const char *filename);

```

Unlinks the file or directory at the specified path.  If the path refers to a directory, all the directory's descendants are recursively unlinked.  Any open file handles refering to an unlinked file remain valid, and can be read from and written to.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| filename |  The path of the file or directory to unlink |


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_rename </font>

```no-highlight
   int
   fs_rename(const char *from, const char *to);

```

Performs a rename and / or move of the specified source path to the specified destination.  

#### Arguments

| Arguments | Description |
|-----------|-------------|
| from |  The source path |
| to   | The destination path |


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

The source path can refer to either a file or a directory.  All intermediate directories in the destination path must already exist.  If the source path refers to a file, the destination path must contain a full filename path, rather than just the new parent directory.  If an object already exists at the specified destination path, this function causes it to be unlinked prior to the rename (i.e., the destination gets clobbered).


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_mkdir </font>

```no-highlight
   int
   fs_mkdir(const char *path);

```

Creates the directory represented by the specified path.  

#### Arguments

| Arguments | Description |
|-----------|-------------|
| path |  Pointer to the directory to create |


#### Returned values

* 0 on success
* nonzero on failure.

#### Notes 

All intermediate directories must already exist.  The specified path must start with a '/' character.


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_opendir </font>

```no-highlight

   int
   fs_opendir(const char *path, struct fs_dir **out_dir);

```

Opens the directory at the specified path.  The directory's contents can be read with subsequent calls to fs_readdir().  When you are done with the directory handle, close it with fs_closedir(). 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| path |  Pointer to the directory to create |
| out_dir  | On success, points to the directory handle |


#### Returned values

* 0 on success
* FS_ENOENT if the specified directory does not exist (no such file)
* Other nonzero on error.

#### Notes 

Unlinking files from the directory while it is open may result in unpredictable behavior.  New files can be created inside the directory.


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_readdir </font>

```no-highlight
   int
   fs_readdir(struct fs_dir *dir, struct fs_dirent **out_dirent);

```

Reads the next entry in an open directory. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| dir |  The directory handle to read from |
| out_dirent  | On success, points to the next child entry in the specified directory |


#### Returned values

* 0 on success
* FS_ENOENT if there are no more entries in the parent directory
* Other nonzero on error.

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_closedir </font>

```no-highlight
   int
   fs_closedir(struct fs_dir *dir);

```

Closes the specified directory handle. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| dir |  Pointer to the directory to close |


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_dirent_name </font>

```no-highlight
   int
   fs_dirent_name(const struct fs_dirent *dirent, size_t max_len,
     char *out_name, uint8_t *out_name_len);

```

Retrieves the filename of the specified directory entry. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| dirent |  Pointer to the directory entry to query |
| max_len | Size of the "out_name" character buffer  |
| out_name | On success, the entry's filename is written here; always null-terminated   |
| out_name_len |  On success, contains the actual length of the filename, NOT including the null-terminator | 


#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

The retrieved filename is always null-terminated.  To ensure enough space to hold the full filename plus a null-termintor, a destination buffer of size  (filename max length + 1) should be used.


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fs_dirent_is_dir </font>

```no-highlight
   int
   fs_dirent_is_dir(const struct fs_dirent *dirent);

```

Tells you whether the specified directory entry is a sub-directory or a regular file. 

#### Arguments

| Arguments | Description |
|-----------|-------------|
| dirent |  Pointer to the directory entry to query |


#### Returned values

* 1: The entry is a directory
* 0: The entry is a regular file.

#### Notes 

<any notes?>

#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fsutil_read_file </font>

```no-highlight
   int
   fsutil_read_file(const char *path, uint32_t offset, uint32_t len, void *dst,
                    uint32_t *out_len);
```

Calls fs_open(), fs_read(), and fs_close() to open a file at the specified path, retrieve data from the file starting from the specified offset, and close the file and invalidate the file handle.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| path |  Pointer to the directory entry to query |
| offset |  Position of the file's read pointer |
| len |  Number of bytes to attempt to read |
| dst |  Destination buffer to read into |
| out_len |  On success, the number of bytes actually read gets written here.  Pass null if you don't care. |

#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>

#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

## <font color="#F2853F" style="font-size:24pt"> fsutil_write_file </font>

```no-highlight
   int
   fsutil_write_file(const char *path, const void *data, uint32_t len);
```

Calls fs_open(), fs_write(), and fs_close() to open a file at the specified path, write the supplied data to the current offset of the specified file handle, and close the file and invalidate the file handle.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| path |  Pointer to the file to write to |
| data |  The data to write |
| len |  The number of bytes to write |

#### Returned values

* 0 on success
* nonzero on failure

#### Notes 

<any notes?>

#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------
