## <font color="#F2853F" style="font-size:24pt"> console_pull_char_head </font>

```no-highlight
   static void
   console_pull_char_head(struct console_ring *cr)
```

Removes the last character inserted into the ring buffer by moving back the head location and shrinking the ring size by 1.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| cr |  Pointer to the console ring buffer from which the last inserted character must be deleted |


#### Returned values

None

#### Notes

Any special feature/special benefit that we want to tout.
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

In order to see a character getting deleted when a user hits backspace while typying a command, the following needs to happen in sequence:

* output a backspace (move cursor back one character)
* output space (erasing whatever character there was before)
* output backspace (move cursor back one character)
* remove the previous character from incoming RX queue

The example below shows console_pull_char_head being used for the last step.

```no-highlight
void
task(uint8_t data)
{
      struct console_tty *ct = (struct console_tty *)arg;
      struct console_ring *tx = &ct->ct_tx;
      struct console_ring *rx = &ct->ct_rx;

      switch (data) {
      case '\b':
          console_add_char(tx, '\b');
          console_add_char(tx, ' ');
          console_add_char(tx, '\b');
          console_pull_char_head(rx);
          break;
      }
}

```

