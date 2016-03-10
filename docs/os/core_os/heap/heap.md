# Heap


API for doing dynamic memory allocation.


### Description

This provides malloc()/free() functionality with locking.  The shared resource heap needs to be protected from concurrent access when OS has been started. *os_malloc()* function grabs a mutex before calling *malloc()*.

### Data structures

N/A

### List of Functions


The functions available in heap are:

* [os_free](os_free)
* [os_malloc](os_malloc)
* [os_realloc](os_realloc)



