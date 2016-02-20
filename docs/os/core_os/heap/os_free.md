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
