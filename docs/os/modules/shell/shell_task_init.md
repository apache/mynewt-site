## <font color="F2853F" style="font-size:24pt"> shell_task_init</font>

```no-highlight
int shell_task_init(uint8_t prio, os_stack_t *stack, uint16_t stack_size,
                    int max_input_length);
```

Initializes the shell package. This creates a task for shell, and registers few commands on its own (*echo*, *?*, for example). It also allocates memory for buffering console input.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| prio | Priority of the shell task |
| stack | Pointer to shell tasks's stack |
| stack_size | Size of the aforementioned stack (in units of os_stack_t) |
| max_input_length | the maximum expected length of line for input |

#### Returned values

Returns 0 on success; nonzero on failure.

#### Notes

You can register commands before calling this, but only if OS has not been started.

#### Example

Here's an example of stand-alone code which allows the user to execute regression tests for sys/config package only.

```no-highlight
#define SHELL_TASK_PRIO (3)
#define SHELL_MAX_INPUT_LEN     (256)
#define SHELL_TASK_STACK_SIZE (OS_STACK_ALIGN(384))
os_stack_t shell_stack[SHELL_TASK_STACK_SIZE];

int
main(int argc, char **argv)
{
    ....
    shell_task_init(SHELL_TASK_PRIO, shell_stack, SHELL_TASK_STACK_SIZE,
                    SHELL_MAX_INPUT_LEN);
    ....
}
```
