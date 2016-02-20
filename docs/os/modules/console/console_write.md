## <font color="#F2853F" style="font-size:24pt"> console_write </font>

```no-highlight
   void
   console_write(char *str, int cnt)
```
Transmit characters to console display over serial port.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *str |  pointer to the character or packet to be transmitted  |
| cnt  |  size of the character or packet |

#### Returned values

List any values returned.
Error codes?

#### Notes

Any special feature/special benefit that we want to tout.
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Here is an example of the function being used in an echo command with a newline at the end.

```no-highlight
static int
shell_echo_cmd(int argc, char **argv)
{
    int i;

    for (i = 1; i < argc; i++) {
        console_write(argv[i], strlen(argv[i]));
        console_write(" ", sizeof(" ")-1);
    }
    console_write("\n", sizeof("\n")-1);

    return (0);
}
```

