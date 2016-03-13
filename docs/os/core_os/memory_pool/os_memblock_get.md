## <font color="#F2853F" style="font-size:24pt"> os_memblock_get</font>

```c
void *os_memblock_get(struct os_mempool *mp)
```

Allocate an element from the memory pool. If succesful, you'll get a pointer to allocated element. If there are no elements available, you'll get NULL as response.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| mp |  Pool where element is getting allocated from  |

#### Returned values

NULL: no elements available.
<pointer>: pointer to allocated element.

#### Notes


#### Example

<Add text to set up the context for the example here>

```c
	struct nffs_file *file;

    file = os_memblock_get(&nffs_file_pool);
    if (file != NULL) {
        memset(file, 0, sizeof *file);
    }

```


