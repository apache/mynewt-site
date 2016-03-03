## <font color="#F2853F" style="font-size:24pt"> shell_nlip_output </font>

```no-highlight
int shell_nlip_output(struct os_mbuf *m)
```

Queue outgoing newtmgr message for transmission. Shell package will encode this, and frame it while sending it out via console.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| m | os_mbuf containing the message  |

#### Returned values

Returns 0 on success.

#### Example

```no-highlight
static int 
nmgr_shell_out(struct nmgr_transport *nt, struct os_mbuf *m)
{
    int rc;

    rc = shell_nlip_output(m);
    if (rc != 0) {
        goto err;
    }

    return (0);
err:
    return (rc);
}
```
