## <font color="#F2853F" style="font-size:24pt"> shell_nlip_input_register </font>

```c
int shell_nlip_input_register(shell_nlip_input_func_t nf, void *arg)
```

Registers a handler for incoming newtmgr messages. Shell receives incoming data stream from 
UART and when it detects NLIP frame, it decodes it and passes it on by calling the function `nf`.

Handler function is of type `int (*shell_nlip_input_func_t)(struct os_mbuf *m, void *arg)`. 
Shell passes the incoming newtmgr message inside `os_mbuf` `m`, and `arg` is the argument that 
was passed in during handler registration.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `nf` | Handler for incoming newtmgr datagrams.  |
| `arg` | Argument that gets passed to this handler, along with the datagram |

#### Returned values

Returns 0 on success.

#### Example

```c
static int
nmgr_shell_in(struct os_mbuf *m, void *arg)
{
    ....
}

int 
nmgr_task_init(uint8_t prio, os_stack_t *stack_ptr, uint16_t stack_len)
{
    int rc;
    ....
    rc = shell_nlip_input_register(nmgr_shell_in, 
            (void *) &g_nmgr_shell_transport);
    if (rc != 0) {
        goto err;
    }
    ....
}
```
