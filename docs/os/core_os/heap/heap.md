# Heap


API for doing dynamic memory allocation.


### Description

This provides malloc()/free() functionality with locking.  The shared resource heap needs to be protected from concurrent access when OS has been started. *os_malloc()* function grabs a mutex before calling *malloc()*.

### Data structures

N/A

### List of Functions


The functions available in heap are:

| **Function** | **Description** |
|-----------|-------------|
| [os_free](os_free) | Frees previously allocated memory back to the heap. |
| [os_malloc](os_malloc) | Allocates the given number of bytes from heap and returns a pointer to it. |
| [os_realloc](os_realloc) | Tries to resize previously allocated memory block, and returns pointer to resized memory. |



