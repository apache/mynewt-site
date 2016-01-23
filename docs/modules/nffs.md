# Newtron Flash Filesystem (nffs)

Mynewt comes with the flash file system called the Newtron Flash File System (nffs) which is designed with two priorities that makes it suitable for embedded use: 

* Minimal RAM usage
* Reliability

Mynewt also provides an abstraction layer API (fs) to allow you to swap out nffs with a different file system of your choice.

## Description

Describe module here, special features, how pieces fit together etc.

## Disk and data structures

At the top level, an nffs disk is partitioned into areas.  An area is a region
of disk with the following properties:

1. An area can be fully erased without affecting any other areas.
2. A write to one area does not restrict writes to other areas.

   **Note**: Some flash hardware divides its memory space into "blocks."  Writes within a block must be sequential, but writes to one block have no effect on what parts of other blocks can be written.  Thus, for flash hardware with such a restriction, each area must comprise a discrete number of blocks.

While not strictly necessary, it is recommended that all areas have the same
size.

On disk, each area is prefixed with the following header:

```no-highlight
/** On-disk representation of an area header. */
struct nffs_disk_area {
    uint32_t nda_magic[4];  /* NFFS_AREA_MAGIC{0,1,2,3} */
    uint32_t nda_length;    /* Total size of area, in bytes. */
    uint8_t nda_ver;        /* Current nffs version: 0 */
    uint8_t nda_gc_seq;     /* Garbage collection count. */
    uint8_t reserved8;
    uint8_t nda_id;         /* 0xff if scratch area. */
};
```

Beyond its header, an area contains a sequence of disk objects, representing
the contents of the file system.  There are two types of objects: **inodes** and
**data blocks**.  An inode represents a file or directory; a data block represents
part of a file's contents.

```no-highlight
/** On-disk representation of an inode (file or directory). */
struct nffs_disk_inode {
    uint32_t ndi_magic;         /* NFFS_INODE_MAGIC */
    uint32_t ndi_id;            /* Unique object ID. */
    uint32_t ndi_seq;           /* Sequence number; greater supersedes
                                   lesser. */
    uint32_t ndi_parent_id;     /* Object ID of parent directory inode. */
    uint8_t reserved8;
    uint8_t ndi_filename_len;   /* Length of filename, in bytes. */
    uint16_t ndi_crc16;         /* Covers rest of header and filename. */
    /* Followed by filename. */
};
```

An inode filename's length cannot exceed 256 bytes.  The filename is not
null-terminated.  The following ASCII characters are not allowed in a
filename:
    * /  (slash character)
    * \0 (NUL character)

```no-highlight
/** On-disk representation of a data block. */
struct nffs_disk_block {
    uint32_t ndb_magic;     /* NFFS_BLOCK_MAGIC */
    uint32_t ndb_id;        /* Unique object ID. */
    uint32_t ndb_seq;       /* Sequence number; greater supersedes lesser. */
    uint32_t ndb_inode_id;  /* Object ID of owning inode. */
    uint32_t ndb_prev_id;   /* Object ID of previous block in file;
                               NFFS_ID_NONE if this is the first block. */
    uint16_t ndb_data_len;  /* Length of data contents, in bytes. */
    uint16_t ndb_crc16;     /* Covers rest of header and data. */
    /* Followed by 'ndb_data_len' bytes of data. */
};
```

Each data block contains the ID of the previous data block in the file.
Together, the set of blocks in a file form a reverse singly-linked list.

The maximum number of data bytes that a block can contain is determined at
initialization-time.  The result is the greatest number which satisfies all of
the following restrictions:
    o No more than 2048.
    o At least two maximum-sized blocks can fit in the smallest area.

The 2048 number was chosen somewhat arbitrarily, and may change in the future.

### ID space

All disk objects have a unique 32-bit ID.  The ID space is partitioned as
follows:
      * 0x00000000 - 0x0fffffff: Directory inodes.
      * 0x10000000 - 0x7fffffff: File inodes.
      * 0x80000000 - 0xfffffffe: Data blocks.
      * 0xffffffff             : Reserved (NFFS_ID_NONE)

### Scratch area

A valid nffs file system must contain a single "scratch area."  The scratch
area does not contain any objects of its own, and is only used during garbage
collection.  The scratch area must have a size greater than or equal to each
of the other areas in flash.


### RAM representation 

Every object in the file system is stored in a 256-entry hash table.  An
object's hash key is derived from its 32-bit ID.  Each list in the hash table
is sorted by time of use; most-recently-used is at the front of the list. All
objects are represented by the following structure:

```no-highlight
/**
 * What gets stored in the hash table.  Each entry represents a data block or
 * an inode.
 */
struct nffs_hash_entry {
    SLIST_ENTRY(nffs_hash_entry) nhe_next;
    uint32_t nhe_id;        /* 0 - 0x7fffffff if inode; else if block. */
    uint32_t nhe_flash_loc; /* Upper-byte = area idx; rest = area offset. */
};
```

For each data block, the above structure is all that is stored in RAM.  To
acquire more information about a data block, the block header must be read
from flash.

Inodes require a fuller RAM representation to capture the structure of the
file system.  There are two types of inodes: **files** and **directories**.  Each
inode hash entry is actually an instance of the following structure:

```no-highlight
/** Each inode hash entry is actually one of these. */
struct nffs_inode_entry {
    struct nffs_hash_entry nie_hash_entry;
    SLIST_ENTRY(nffs_inode_entry) nie_sibling_next;
    union {
        struct nffs_inode_list nie_child_list;           /* If directory */
        struct nffs_hash_entry *nie_last_block_entry;    /* If file */
    };
    uint8_t nie_refcnt;
};
```

A directory inode contains a list of its child files and directories
(fie_child_list).  These entries are sorted alphabetically using the ASCII
character set.

A file inode contains a pointer to the last data block in the file
(nie_last_block_entry).  For most file operations, the reversed block list must
be walked backwards.  This introduces a number of speed inefficiencies:
    * All data blocks must be read to determine the length of the file.
    * Data blocks often need to be processed sequentially.  The reversed
      nature of the block list transforms this from linear time to an O(n^2)
      operation.

Furthermore, obtaining information about any constituent data block requires a
separate flash read.

### Inode cache and Data Block cache

The speed issues are addressed by a pair of caches.  Cached inodes entries
contain the file length and a much more convenient doubly-linked list of
cached data blocks.  The benefit of using caches is that the size of the
caches need not be proportional to the size of the file system.  In other
words, caches can address speed efficiency concerns without negatively
impacting the file system's scalability.

nffs requires both caches during normal operation, so it is not possible to
disable them.  However, the cache sizes are configurable, and both caches can
be configured with a size of one if RAM usage must be minimized.

The following data structures are used in the inode and data block caches.

```no-highlight
/** Full data block representation; not stored permanently in RAM. */
struct nffs_block {
    struct nffs_hash_entry *nb_hash_entry;   /* Points to real block entry. */
    uint32_t nb_seq;                         /* Sequence number; greater
                                                supersedes lesser. */
    struct nffs_inode_entry *nb_inode_entry; /* Owning inode. */
    struct nffs_hash_entry *nb_prev;         /* Previous block in file. */
    uint16_t nb_data_len;                    /* # of data bytes in block. */
    uint16_t reserved16;
};

/** Represents a single cached data block. */
struct nffs_cache_block {
    TAILQ_ENTRY(nffs_cache_block) ncb_link; /* Next / prev cached block. */
    struct nffs_block ncb_block;            /* Full data block. */
    uint32_t ncb_file_offset;               /* File offset of this block. */
};

/** Full inode representation; not stored permanently in RAM. */
struct nffs_inode {
    struct nffs_inode_entry *ni_inode_entry; /* Points to real inode entry. */
    uint32_t ni_seq;                         /* Sequence number; greater
                                                supersedes lesser. */
    struct nffs_inode_entry *ni_parent;      /* Points to parent directory. */
    uint8_t ni_filename_len;                 /* # chars in filename. */
    uint8_t ni_filename[NFFS_SHORT_FILENAME_LEN]; /* First 3 bytes. */
};

/** Doubly-linked tail queue of cached blocks; contained in cached inodes. */
TAILQ_HEAD(nffs_block_cache_list, nffs_block_cache_entry);

/** Represents a single cached file inode. */
struct nffs_cache_inode {
    TAILQ_ENTRY(nffs_cache_inode) nci_link;        /* Sorted; LRU at tail. */
    struct nffs_inode nci_inode;                   /* Full inode. */
    struct nffs_cache_block_list nci_block_list;   /* List of cached blocks. */
    uint32_t nci_file_size;                        /* Total file size. */
};
```

Only file inodes are cached; directory inodes are never cached.

Within a cached inode, all cached data blocks are contiguous.  E.g., if the
start and end of a file are cached, then the middle must also be cached.  A
data block is only cached if its owning file is also cached.

Internally, cached inodes are stored in a singly-linked list, ordered by time
of use.  The most-recently-used entry is the first element in the list.  If a
new inode needs to be cached, but the inode cache is full, the
least-recently-used entry is freed to make room for the new one.  The
following operations cause an inode to be cached:

* Querying a file's length.
* Seeking within a file.
* Reading from a file.
* Writing to a file.

The following operations cause a data block to be cached:

* Reading from the block.
* Writing to the block.

If one of the above operations is applied to a data block that is not currently
cached, nffs uses the following procedure to cache the necessary block:

1. If none of the owning inode's blocks are currently cached, allocate a
       cached block entry corresponding to the requested block and insert it
       into the inode's list.
2. Else if the requested file offset is less than that of the first cached
       block, bridge the gap between the inode's sequence of cached blocks and
       the block that now needs to be cached.  This is accomplished by caching
       each block in the gap, finishing with the requested block.
3. Else (the requested offset is beyond the end of the cache),
   a. If the requested offset belongs to the block that immediately follows the end of the cache, cache the block and append it to the list.
   b. Else, clear the cache, and populate it with the single entry corresponding to the requested block.

If the system is unable to allocate a cached block entry at any point during
the above procedure, the system frees up other blocks currently in the cache. This is accomplished as follows:

* Iterate the inode cache in reverse (i.e., start with the least-recently-used entry).  For each entry:
   a. If the entry's cached block list is empty, advance to the next entry.
   b. Else, free all the cached blocks in the entry's list.

Because the system imposes a minimum block cache size of one, the above
procedure will always reclaim at least one cache block entry.  The above
procedure may result in the freeing of the block list that belongs to the very
inode being operated on.  This is OK, as the final block to get cached is
always the block being requested.


## Configuration

The file system is configured by populating fields in a global structure.
Each field in the structure corresponds to a setting.  All configuration must
be done prior to calling nffs_init().  The configuration structure is defined
as follows:

```no-highlight

struct nffs_config {
    /** Maximum number of inodes; default=1024. */
    uint32_t nc_num_inodes;

    /** Maximum number of data blocks; default=4096. */
    uint32_t nc_num_blocks;

    /** Maximum number of open files; default=4. */
    uint32_t nc_num_files;

    /** Inode cache size; default=4. */
    uint32_t nc_num_cache_inodes;

    /** Data block cache size; default=64. */
    uint32_t nc_num_cache_blocks;
    };

extern struct nffs_config nffs_config;
```

Any fields that are set to 0 (or not set at all) inherit the corresponding
default value.  This means that it is impossible to configure any setting with
a value of zero.


## Initialization

There are two means of initializing an nffs file system:

1. Restore an existing file system via detection.
2. Create a new file system via formatting.

Both methods require the user to describe how the flash memory is divided into
areas.  This is accomplished with an array of struct nffs_area_desc, defined as
follows:

```no-highlight
struct nffs_area_desc {
    uint32_t nad_offset;    /* Flash offset of start of area. */
    uint32_t nad_length;    /* Size of area, in bytes. */
};
```

An array of area descriptors is terminated by an entry with a fad_length field
of 0.

One common initialization sequence is the following:

1. Detect an nffs file system anywhere in flash.
2. If no file system detected, format a new file system in a specific
        region of flash.


## Detection

The file system detection process consists of scanning a specified set of
flash regions for valid nffs areas, and then populating the RAM representation
of the file system with the detected objects.  Detection is initiated with the
following function:

```no-highlight
/**
 * Searches for a valid nffs file system among the specified areas.  This
 * function succeeds if a file system is detected among any subset of the
 * supplied areas.  If the area set does not contain a valid file system,
 * a new one can be created via a separate call to nffs_format().
 *
 * @param area_descs        The area set to search.  This array must be
 *                              terminated with a 0-length area.
 *
 * @return                  0 on success;
 *                          NFFS_ECORRUPT if no valid file system was detected;
 *                          other nonzero on error.
 */
int nffs_detect(const struct nffs_area_desc *area_descs);
```
As indicated, not every area descriptor needs to reference a valid nffs area.
Detection is successful as long as a complete file system is detected
somewhere in the specified regions of flash.  If an application is unsure
where a file system might be located, it can initiate detection across the
entire flash region.

A detected file system is valid if:

1. At least one non-scratch area is present.
2. At least one scratch area is present (only the first gets used if there is more than one).
3. The root directory inode is present.

During detection, each indicated region of flash is checked for a valid area
header.  The contents of each valid non-scratch area are then restored into
the nffs RAM representation.  The following procedure is applied to each object
in the area:

1. Verify the object's integrity via a crc16 check.  If invalid, the object is discarded and the procedure restarts on the next object in the area.

2. Convert the disk object into its corresponding RAM representation and insert it into the hash table.  If the object is an inode, its reference count is initialized to 1, indicating ownership by its parent directory.

3. If an object with the same ID is already present, then one supersedes the other.  Accept the object with the greater sequence number and discard the other.

4. If the object references a nonexistant inode (parent directory in the case of an inode; owning file in the case of a data block), insert a temporary "dummy" inode into the hash table so that inter-object links can be maintained until the absent inode is eventually restored.  Dummy inodes are identified by a reference count of 0.

5. If a delete record for an inode is encountered, the inode's parent pointer is set to null to indicate that it should be removed from RAM.

If nffs encounters an object that cannot be identified (i.e., its magic number
is not valid), it scans the remainder of the flash area for the next valid
magic number.  Upon encountering a valid object, nffs resumes the procedure
described above.

After all areas have been restored, a sweep is performed across the entire RAM
representation so that invalid inodes can be deleted from memory.

For each directory inode:

* If its reference count is 0 (i.e., it is a dummy), migrate its children to the /lost+found directory, and delete it from the RAM representation. This should only happen in the case of file system corruption.
 * If its parent reference is null (i.e., it was deleted), delete it and all its children from the RAM representation.

For each file inode:

* If its reference count is 0 (i.e., it is a dummy), delete it from the RAM representation.  This should only happen in the case of file system corruption.  (We should try to migrate the file to the lost+found directory in this case, as mentioned in the todo section).

When an object is deleted during this sweep, it is only deleted from the RAM
representation; nothing is written to disk.

When objects are migrated to the lost+found directory, their parent inode
reference is permanently updated on the disk.

In addition, a single scratch area is identified during the detection process.
The first area whose 'fda_id' value is set to 0xff is designated as the file
system scratch area.  If no valid scratch area is found, the cause could be
that the system was restarted while a garbage collection cycle was in progress.
Such a condition is identified by the presence of two areas with the same ID.
In such a case, the shorter of the two areas is erased and designated as the
scratch area.


## Formatting

A new file system is created via formatting.  Formatting is achieved via the
following function:

```no-highlight
/**
 * Erases all the specified areas and initializes them with a clean nffs
 * file system.
 *
 * @param area_descs        The set of areas to format.
 *
 * @return                  0 on success;
 *                          nonzero on failure.
 */
int nffs_format(const struct nffs_area_desc *area_descs);
```

On success, an area header is written to each of the specified locations.  The
largest area in the set is designated as the initial scratch area.


## Flash writes

The nffs implementation always writes in a strictly sequential fashion within an
area.  For each area, the system keeps track of the current offset.  Whenever
an object gets written to an area, it gets written to that area's current
offset, and the offset is increased by the object's disk size.

When a write needs to be performed, the nffs implementation selects the
appropriate destination area by iterating though each area until one with
sufficient free space is encountered.

There is no write buffering.  Each call to a write function results in a write
operation being sent to the flash hardware.


### New objects

Whenever a new object is written to disk, it is assigned the following
properties:
    * ID: A unique value is selected from the 32-bit ID space, as appropriate
      for the object's type.
    * Sequence number: 0

When a new file or directory is created, a corresponding inode is written to
flash.  Likewise, a new data block also results in the writing of a
corresponding disk object.


### Moving/Renaming files and directories 

When a file or directory is moved or renamed, its corresponding inode is
rewritten to flash with the following properties:

* ID: Unchanged
* Sequence number: Previous value plus one.
* Parent inode: As specified by the move / rename operation.
* Filename: As specified by the move / rename operation.

Because the inode's ID is unchanged, all dependent objects remain valid.


### Unlinking files and directories

When a file or directory is unlinked from its parent directory, a deletion
record for the unlinked inode gets written to flash.  The deletion record is an
inode with the following properties:

* ID: Unchanged
* Sequence number: Previous value plus one.
* Parent inode ID: NFFS_ID_NONE

When an inode is unlinked, no deletion records need to be written for the
inode's dependent objects (constituent data blocks or child inodes).  During
the next file system detection, it is recognized that the objects belong to
a deleted inode, so they are not restored into the RAM representation.

If a file has an open handle at the time it gets unlinked, application code
can continued to use the file handle to read and write data.  All files retain
a reference count, and a file isn't deleted from the RAM representation until
its reference code drops to 0.  Any attempt to open an unlinked file fails,
even if the file is referenced by other file handles.


### Writing to a file

The following procedure is used whenever the application code writes to a file.
First, if the write operation specifies too much data to fit into a single
block, the operation is split into several separate write operations.  Then,
for each write operation:

1\. Determine which existing blocks the write operation overlaps (n = number of overwritten blocks).

2\. If n = 0, this is an append operation.  Write a data block with the following properties:

   * ID: New unique value.
   * Sequence number: 0.

3\. Else (n > 1), this write overlaps existing data.

  (a) For each block in [1, 2, ... n-1], write a new block containing the updated contents.  Each new block supersedes the block it overwrites.  That is, each block has the following properties:
   
   * ID: Unchanged
   * Sequence number: Previous value plus one.

   (b) Write the nth block.  The nth block includes all appended data, if any.  As with the other blocks, its ID is unchanged and its sequence number is incremented.

Appended data can only be written to the end of the file.  That is, "holes" are
not supported.


## Garbage collection

When the file system is too full to accomodate a write operation, the system
must perform garbage collection to make room.  The garbage collection
procedure is described below:

* The non-scratch area with the lowest garbage collection sequence number is selected as the "source area."  If there are other areas with the same sequence number, the one with the smallest flash offset is selected. 

* The source area's ID is written to the scratch area's header, transforming it into a non-scratch ID.  This former scratch area is now known as the "destination area."

* The RAM representation is exhaustively searched for collectible objects.  The following procedure is applied to each inode in the system:
    * If the inode is resident in the source area, copy the inode record to the destination area.
    * If the inode is a file inode, walk the inode's list of data blocks, starting with the last block in the file.  Each block that is resident in the source area is copied to the destination area.  If there is a run of two or more blocks that are resident in the source area, they are consolidated and copied to the destination area as a single new block (subject to the maximum block size restriction).

* The source area is reformatted as a scratch sector (i.e., is is fully erased, and its header is rewritten with an ID of 0xff).  The area's garbage collection sequence number is incremented prior to rewriting the header.  This area is now the new scratch sector.


## Miscellaneous measures

* RAM usage:
    * 24 bytes per inode
    * 12 bytes per data block
    * 36 bytes per inode cache entry
    * 32 bytes per data block cache entry
    
* Maximum filename size: 256 characters (no null terminator required)
* Disallowed filename characters: '/' and '\0'


## Future enhancements

* API function to traverse a directory.
* Migrate corrupt files to the /lost+found directory during restore, rather than discarding them from RAM.
* Error correction.
* Encryption.
* Compression.


