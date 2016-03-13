## <font color="F2853F" style="font-size:24pt"> os_malloc</font>

```c
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

```c
    info = (struct os_task_info *) os_malloc(
            sizeof(struct os_task_info) * tcount);
    if (!info) {
        rc = -1;
        goto err;
    }
```


