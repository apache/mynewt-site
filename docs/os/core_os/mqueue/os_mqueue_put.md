## <font color="#F2853F" style="font-size:24pt">os_mqueue_put</font>

```no-highlight
int os_mqueue_put(struct os_mqueue *mq, struct os_eventq *evq, struct os_mbuf *m)
```

Adds a packet (i.e. packet header mbuf) to an mqueue. Post event to *evq*. 

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| mq |  Pointer to mqueue  |
| evq | Pointer to event queue where mqueue event should get posted |
| m | Pointer to packet header mbuf |

<br>

#### Returned values

0: success
OS_EINVAL: the mbuf is not a packet header mbuf.

<br>

#### Example

```no-highlight
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

---------------------
