## <font color="#F2853F" style="font-size:24pt"> console_pull_char </font>

```no-highlight
   static uint8_t
   console_pull_char(struct console_ring *cr)
```

Reads (remove) a byte from the console ring buffer. When you read (pull) an item, you read it at the current tail location, and the tail advances to the next position.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *cr | Pointer to the console ring buffer from where a character is to be removed  |


#### Returned values

Returns the character pulled from the ring buffer.

#### Notes

Any special feature/special benefit that we want to tout.
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Read the characters in the ring buffer into a string.

```no-highlight
void
task(struct console_ring *cr, char *str, int cnt)
{
     for (i = 0; i < cnt; i++) {
          if (cr->cr_head == cr->cr_tail) {
              i = -1;
              break;
          }
     ch = console_pull_char(cr);
     *str++ = ch;
     }
}
```


