## <font color="#F2853F" style="font-size:24pt"> console_add_char</font>

```no-highlight
   static void
   console_add_char(struct console_ring *cr, char ch)
```

Adds a character to the console ring buffer. When you store an item in the buffer you store it at the head location, and the head advances to the next location.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *cr |  Pointer to a console ring data structure whose `cr_head` variable is to be set to the second argument in this function call|
| ch |  Character to be inserted to the ring |

#### Returned values

None

#### Notes

Any special feature/special benefit that we want to tout.
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Add a new line character to the output (transmit) buffer.

```no-highlight
void
task()
{
     struct console_ring *tx = &ct->ct_tx;

     console_add_char(tx, '\n');
}
```


