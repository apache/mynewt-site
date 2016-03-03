## <font color="#F2853F" style="font-size:24pt"> shell_cmd_register </font>

```no-highlight
int shell_cmd_register(struct shell_cmd *sc)
```

Registers a handler for incoming console commands. Within the structure there is the command string, and the handler for those commands. Caller must allocate the memory for this structure, and keep it around, as shell links this to it's own internal data structures.

Command handler is of type 'int (*shell_cmd_func_t)(int argc, char **argv)'. Command line arguments are passed to it as an array of character pointers.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| sc | Structure containing info about the command.  |

#### Returned values

Returns 0 on success.
Non-zero on failure.

#### Example

```no-highlight
static int fs_ls_cmd(int argc, char **argv);

static struct shell_cmd fs_ls_struct = {
    .sc_cmd = "ls",
    .sc_cmd_func = fs_ls_cmd
};

void
fs_cli_init(void)
{
    shell_cmd_register(&fs_ls_struct);
    ....
}
```
