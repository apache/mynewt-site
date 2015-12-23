# Console


The console is an operating system window where users interact with system programs of the operating system or a console application by entering text input (typically from a keyboard) and reading text output (typically on the computer terminal or monitor). The text written on the console brings some information and is a sequence of characters sent by the OS or programs running on the OS. 

Support is currently available for console access via the serial port on the hardware board.


## Description

In the Mynewt OS, the console library comes in two versions:

* full - containing the full implementation
* stub - containing stubs for the API

If an egg or project requires the full console capability it lists that dependency in its egg.yml file. For example, the shell egg is defined by the following egg.yml file:

    egg.name: libs/shell 
    egg.vers: 0.1
    egg.deps:
        - libs/console/full
        - libs/os
    egg.identities:
        - SHELL 

On the other hand, a project may not have a physical console (e.g. a UART port to connect a terminal to) but may have a dependency on an egg that has console capability. In that case you would use a console stub. Another example would be the bootloader project where we want to keep the size of the image small. It includes the `libs/os` egg that can print out messages on a console (e.g. if there is a hard fault) and the `libs/util` egg that uses full console (but only if SHELL is present to provide a CLI). However, we do not want to use any console I/O capability in this particular bootloader project to keep the size small. We simply use the console stub instead and the egg.yml file for the project boot egg looks like the following:

    project.name: boot
    project.identities: bootloader
    project.eggs:
        - libs/os
        - libs/bootutil
        - libs/nffs
        - libs/console/stub
        - libs/util 

## Data structures


Console interaction is intrinsically composed of two unidirectional systems. The console implementation uses two ring buffers containing input (receive) and output (transmit) characters, respectively. Read and write operations on the console_ring structure are managed by labeling the read location indicator the `cr_tail` and the write location indicator the `cr_head`. The console ring length is variable and is specified as the `cr_size` member of the data structure. `cr_buf` is the pointer to the actual array of data contained.


```
struct console_ring {
  32     uint8_t cr_head;
  33     uint8_t cr_tail;
  34     uint8_t cr_size;
  35     uint8_t _pad;
  36     uint8_t *cr_buf;
  37 }
```


```
struct console_tty {
  40     struct console_ring ct_tx;
  41     uint8_t ct_tx_buf[CONSOLE_TX_BUF_SZ]; /* must be after console_ring */
  42     struct console_ring ct_rx;
  43     uint8_t ct_rx_buf[CONSOLE_RX_BUF_SZ]; /* must be after console_ring */
  44     console_rx_cb ct_rx_cb;     /* callback that input is ready */
  45     console_write_char ct_write_char;
  46 } console_tty
```

## List of Functions

The functions available in console are:

* [console_printf](#function-console_printf)
* [console_add_char](#function-console_add_char)
* [console_pull_char](#function-console_pull_char)
* [console_pull_char_head](#function-console_pull_char_head)
* [console_queue_char](#function-console_queue_char)
* [console_blocking_tx](#function-console_blocking_tx)
* [console_blocking_mode](#function-console_blocking_mode)
* [console_write](#function-console_write)
* [console_read](#function-console_read)
* [console_tx_char](#function-console_tx_char)
* [console_rx_char](#function-console_rx_char)
* [console_init](#function-console_init)


## Function Reference

------------------

### <font color="2980b9">function console_printf</font>

```
    void 
    console_printf(const char *fmt, ...)
```

Writes a formatted message instead of raw output to the console. It first composes a C string containing text specified as arguments to the function or containing the elements in the variable argument list passed to it using snprintf or vsnprintf, respectively. It then uses function `console_write` to output the formatted data (messages) on the console.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| fmt |  Pointer to C string that contains a format string that follows the same specifications as format in printf. The string is printed to console.          |
| ... | Depending on the format string, the function may expect either a sequence of additional arguments to be used to replace a format specifier in the format string or a variable arguments list. va_list is a special type defined in <cstdarg> in stdarg.h. |

#### Returned values

None

#### Notes 

While `console_printf`, with its well understood formatting options in C, is more convenient and easy on the eyes than the raw output of `console_write`, the associated code size is considerably larger.

#### Example
Example #1:

```
char adv_data_buf[32];
    
void
task()
{ 
   char adv_data_buf[32];
   
   console_printf("%s", adv_data_buf);
}
```   

Example #2:

```
struct exception_frame {
    uint32_t r0;
    uint32_t r1;

struct trap_frame {
    struct exception_frame *ef;
    uint32_t r2;
    uint32_t r3;
};

void
task(struct trap_frame *tf)
{
     console_printf(" r0:%8.8x  r1:%8.8x", tf->ef->r0, tf->ef->r1);
     console_printf(" r8:%8.8x  r9:%8.8x", tf->r2, tf->r3);
}
```
  
---------------------
   
### <font color="#2980b9"> function console_add_char</font>

```
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

```
void
task()
{
     struct console_ring *tx = &ct->ct_tx;
     
     console_add_char(tx, '\n');
}
```

-------------------

### <font color="#2980b9"> function console_pull_char </font>

```
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

```
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

---------------
      
### <font color="#2980b9"> function console_pull_char_head </font>

```
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

```
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

-------------

### <font color="#2980b9"> function console_queue_char </font>

``` 
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

This function makes sure no interrupts are allowed while the transmit buffer is draining and the character is being added.

#### Example

```
Insert example
``` 
------------------
 
### <font color="#2980b9"> function console_blocking_tx </font>

```
    static void
    console_blocking_tx(char ch)
```
    
  Calls the hal function hal_uart_blocking_tx to transmit a byte to the console over UART in a blocking mode until the character has been sent. Hence it must be called with interrupts disabled. It is used when printing diagnostic output from system crash. 

#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.

-----------

### <font color="#2980b9"> function console_blocking_mode </font>

```
   void
   console_blocking_mode(void)
```
   Calls the console_blocking_tx function to flush the buffered console output (transmit) queue. The function OS_ENTER_CRITICAL() is called to disable interrupts and OS_EXIT_CRITICAL() is called to enable interrupts back again once the buffer is flushed.

#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.


### <font color="#2980b9">function console_write </font>
 
```
   void
   console_write(char *str, int cnt)
```
Transmit characters to console display over serial port. 

#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.


### <font color="#2980b9"> function console_read </font>

```   
  int
  console_read(char *str, int cnt)
```
  Calls hal function hal_uart_start_rx to start receiving input from console terminal over serial port.

#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.


### <font color="#2980b9"> function console_tx_char </font>

   ```   
   static int
   console_tx_char(void *arg)
   ```

#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.

  
### <font color="#2980b9"> function console_rx_char </font>

```
   static int
   console_rx_char(void *arg, uint8_t data)
```

#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.


### <font color="#2980b9"> function console_init </font>

```
   int
   console_init(console_rx_cb rx_cb)
```
   
  Initializes console receive buffer and calls hal funtions hal_uart_init_cbs and hal_uart_config to initialize serial port connection and configure it (e.g. baud rate, flow control etc.)
   
#### Arguments

| Arguments | Description |
|-------------------------|
| xx |  explain argument xx  |
| yy |  explain argument yy  |

#### Returned values

List any values returned.
Error codes?

#### Notes 

Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).

#### Example

Give at least one example of usage.
