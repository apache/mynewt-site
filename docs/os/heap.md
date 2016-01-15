# Heap


API for doing dynamic memory allocation.


## Description

This provides malloc()/free() functionality with locking.  The shared resource heap needs to be protected from concurrent access when OS has been started. *os_malloc()* function grabs a mutex before calling *malloc()*.

## Data structures

N/A

## List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions available in this OS feature are:

* [os_malloc](#os_malloc)
* [os_free](#os_free)
* [os_realloc](#os_realloc)


## Function Reference

------------------

## <font color="F2853F" style="font-size:24pt"> os_malloc</font>

```no-highlight
void *os_malloc(size_t size)
```

Allocates *size* number of bytes from heap and returns a pointer to it.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| size |  Number of bytes to allocate  |

#### Returned values

<ptr>: pointer to memory allocated from heap.
NULL: not enough memory available.

#### Notes 

*os_malloc()* calls *malloc()*, which is provided by C-library. The heap must be set up during platform initialization.
Depending on which C-library you use, you might have to do the heap setup differently. Most often *malloc()* implementation will maintain a list of allocated and then freed memory blocks. If user asks for memory which cannot be satisfied from free list, they'll call platform's *sbrk()*, which then tries to grow the heap.

#### Example

<Add text to set up the context for the example here>

```no-highlight
    info = (struct os_task_info *) os_malloc(
            sizeof(struct os_task_info) * tcount);
    if (!info) {
        rc = -1;
        goto err;
    }
```

---------------------
   
## <font color="F2853F" style="font-size:24pt">os_free</font>

```no-highlight
void os_free(void *mem)
```

Frees previously allocated memory back to the heap.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| mem |  Pointer to memory being released  |

#### Returned values

N/A

#### Notes 

Calls C-library *free()* behind the covers.

#### Example

<Add text to set up the context for the example here>

```no-highlight
   os_free(info);
```

---------------------
   
## <font color="F2853F" style="font-size:24pt">os_realloc</font>

```no-highlight
void *os_realloc(void *ptr, size_t size)
```

Tries to resize previously allocated memory block, and returns pointer to resized memory.
ptr can be NULL, in which case the call is similar to calling *os_malloc()*.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| ptr |  Pointer to previously allocated memory  |
| size |  New size to adjust the memory block to  |

#### Returned values

NULL: size adjustment was not successful. <br>
ptr: pointer to new start of memory block

#### Notes 


#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------

