## <font color="#F2853F" style="font-size:24pt"> console_queue_char </font>

```no-highlight
   static void
   console_queue_char(char ch)
```

Manage the buffer queue before inserting a character into it. If the head of the output (transmit) console ring is right up to its tail, the queue needs to be drained first before any data can be added. Then it uses console_add_char function to add the character.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| ch |  Character to be inserted to the queue  |


#### Returned values

List any values returned.
Error codes?

#### Notes

Function blocks interrupts as a way of protecting against concurrent access to TX buffer.

If TX buffer is full, the function waits for TX buffer to drain. And the way it does it currently is by calling os_time_delay(). Therefore this function should only be called from within a task context, not from an interrupt handler. We might want to change this...

#### Example

```no-highlight
Insert example
```

