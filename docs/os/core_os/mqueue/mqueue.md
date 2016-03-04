# Mqueue

Mqueue (Mbuf event queue) is a set of API built on top of the mbuf and event queue code. A typical networking stack operation is to put a packet on a queue and post an event to the task handling that queue. Mqueue was designed to provide a common API so that individual packages would not each have to create similar code.

The mqueue data structure consists of a queue head pointer (a "stailq" queue; a singly linked list with head structure having a pointer to the start and end of the list) and an os event structure. Packets (packet header mbufs) are added to the queue using the *omp_next* pointer in the `os_mbuf_pkthdr` structure of the mbuf. The event is used to post to the task an event of type OS_EVENT_T_MQUEUE_DATA. 

<br>  

## Using Mqueue

The following code sample will demonstrate how to use an mqueue. This is a simple example where packets are put on a "receive queue" and a task processes that "receive queue" by incrementing the total number of packet received and then freeing the packet. Not shown in the code example is a call my_task_rx_data_func. Presumably, some other code will call this API. 

<br>


```no-highlight
uint32_t pkts_rxd;
struct os_mqueue rxpkt_q;
struct os_eventq my_task_evq;

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

void
my_task_handler(void *arg)
{
    struct os_event *ev;
    struct os_callout_func *cf;
    int rc;

    /* Initialize eventq */
    os_eventq_init(&my_task_evq);

	/* Initialize mqueue */
    os_mqueue_init(&rxpkt_q, NULL);

    while (1) {
        ev = os_eventq_get(&my_task_evq);
        switch (ev->ev_type) {
        
        case OS_EVENT_T_MQUEUE_DATA:
            process_rx_data_queue();
            break;

        default:
            assert(0);
            break;
        }
    }
}
    
```



## Data Structures

```no-highlight
struct os_mqueue {
    STAILQ_HEAD(, os_mbuf_pkthdr) mq_head;
    struct os_event mq_ev;
};
```

<br>

## List of Functions

The functions available in Mqueue are:

* [os_mqueue_init](os_mqueue_init.md)
* [os_mqueue_get](os_mqueue_get.md)
* [os_mqueue_put](os_mqueue_put.md)

