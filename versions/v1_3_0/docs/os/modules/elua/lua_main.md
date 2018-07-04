## <font color="#F2853F" style="font-size:24pt"> lua_main </font>

```no-highlight
   int
   lua_main(int argc, char **argv)
```

  Executes lua script in current task's context. Arguments given are passed to lua interpreter.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| argc | Number of elements in argv array |
| argv | Array of character strings |

#### Returned values

Returns the return code from the lua interpreter.

#### Notes


#### Example

```no-highlight
static int
lua_cmd(int argc, char **argv)
{
    lua_main(argc, argv);
    return 0;
}
```


