## <font color="F2853F" style="font-size:24pt">os_realloc</font>

```c
void *os_realloc(void *ptr, size_t size)
```

Tries to resize previously allocated memory block, and returns pointer to resized memory.
`ptr` can be **NULL**, in which case the call is similar to calling `os_malloc()`.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `ptr` |  Pointer to previously allocated memory  |
| `size` |  New size to adjust the memory block to  |

#### Returned values

**NULL**: size adjustment was not successful. <br>
`ptr`: pointer to new start of memory block

#### Notes 


#### Example

<Add text to set up the context for the example here>

```c
<Insert the code snippet here>
```

