```no-highlight
    int 
    shell_cmd_register(struct shell_cmd *sc, char *cmd, shell_cmd_func_t func)
```

Register a shell command. When shell reads a line of input which starts with `cmd`, it calls the handler `func`. Caller must allocate data structure `sc`. Shell internally links this to it's list of command handlers.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| sc |  Pointer to data structure shell egg uses to store info about the registered command |
| cmd |  Command getting registered  |
| func |  Function to call when command is received from console  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Shell splits the arguments following the command into an array of character pointers, and passes these to registered handler. The function will be called in shell task's context, so the command handler should look out for possible issues due to concurrency.

#### Example

Here is FS registering command for 'ls'.

```no-highlight
static struct shell_cmd fs_ls_struct;

void
fs_cli_init(void)
{
    int rc;

    rc = shell_cmd_register(&fs_ls_struct, "ls", fs_ls_cmd);
    if (rc != 0) {
        return;
    }
}

```

---------------------
