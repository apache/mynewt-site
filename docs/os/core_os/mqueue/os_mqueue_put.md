## <font color="#F2853F" style="font-size:24pt">os_mqueue_put</font>

```c
int os_mqueue_put(struct os_mqueue *mq, struct os_eventq *evq, struct os_mbuf *m)
```

Adds a packet (i.e. packet header mbuf) to an mqueue. The event associated with the mqueue gets posted to the specified eventq.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `mq`      | The mbuf queue to append the mbuf to. |
| `evq`     | The event queue to post an event to. |
| `m`       | The mbuf to append to the mbuf queue. |

<br>

#### Returned values

0: success

OS_EINVAL: the mbuf is not a packet header mbuf.

<br>

#### Example

```c
int
my_task_rx_data_func(struct os_mbuf *om)
{
    int rc;

    rc = os_mqueue_put(&rxpkt_q, &my_task_evq, om);
    if (rc != 0) {
        return -1;
    }

    return 0;
}
```
