## <font color="#F2853F" style="font-size:24pt">os_mqueue_init</font>

```c
int os_mqueue_init(struct os_mqueue *mq, void *arg)
```
Initializes an queue. Sets the event argument in the os event of the mqueue to *arg*. Sets type of event to OS_EVENT_T_MQUEUE_DATA.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| mq | Pointer to a mqueue structure  |
| arg | Event argument |

<br>

#### Returned values

0: success. All other values indicate an error

<br>

#### Example

```c
/* Declare mqueue */
struct os_mqueue rxpkt_q;

/* Initialize mqueue */
os_mqueue_init(&rxpkt_q, NULL);
```

