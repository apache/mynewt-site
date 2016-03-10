## <font color="#F2853F" style="font-size:24pt">os_mqueue_get</font>

```no-highlight
struct os_mbuf *os_mqueue_get(struct os_mqueue *mq)
```

Retrieves a packet off an Mqueue. Returns a pointer to the mbuf at the head of the mbuf chain. NULL if no packets are on the queue.

<br>

#### Arguments

| Arguments | Description |
|-----------|-------------|
| mq | Pointer to Mqueue structure  |

<br>

#### Returned values

The packet at the head of the queue or NULL if no packets are on the queue.

<br>

#### Example

```no-highlight
uint32_t pkts_rxd;
struct os_mqueue rxpkt_q;

void
process_rx_data_queue(void)
{
    struct os_mbuf *om;

    /* Drain all packets off queue and process them */
    while ((om = os_mqueue_get(&rxpkt_q)) != NULL) {
        ++pkts_rxd;
        os_mbuf_free_chain(om);
    }
}
```


