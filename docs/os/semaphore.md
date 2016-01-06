# Semaphore

A semaphore is a structure used for gaining exclusive access (much like a mutex), synchronizing task operations and/or use in a "producer/consumer" roles. Semaphores like the ones used by the myNewt OS are called "counting" semaphores as they are allowed to have more than one token (explained below).


## Description

A semaphore is a fairly simple construct consisting of a queue for waiting tasks and the number of tokens currently owned by the semaphore. A semaphore can be obtained as long as there are tokens in the semaphore. Any task can add tokens to the semaphore and any task can request the semaphore, thereby removing tokens. When creating the semaphore, the initial number of tokens can be set as well.

When used for exclusive access to a shared resource the semaphore only needs a single token. In this case, a single task "creates" the semaphore by calling *os_sem_init* with a value of one (1) for the token. When a task desires exclusive access to the shared resource it requests the semaphore by calling *os_sem_pend*. If there is a token the requesting task will acquire the semaphore and continue operation. If no tokens are available the task will be put to sleep until there is a token. A common "problem" with using a semaphore for exclusive access is called *priority inversion*. Consider the following scenario: a high and low priority task both share a resource which is locked using a semaphore. If the low priority task obtains the semaphore and then the high priority task requests the semaphore, the high priority task is now blocked until the low priority task releases the semaphore. Now suppose that there are tasks between the low priority task and the high priority task that want to run. These tasks will preempt the low priority task which owns the semaphore. Thus, the high priority task is blocked waiting for the low priority task to finish using the semaphore but the low priority task cannot run since other tasks are running. Thus, the high priority tasks is "inverted" in priority; in effect running at a much lower priority as normally it would preempt the other (lower priority) tasks. If this is an issue a mutex should be used instead of a semaphore.

Semaphores can also be used for task synchronization. A simple example of this would be the following. A task creates a semaphore and initializes it with no tokens. The task then waits on the semaphore, and since there are no tokens, the task is put to sleep. When other tasks want to wake up the sleeping task they simply add a token by calling *os_sem_release*. This will cause the sleeping task to wake up (instantly if no other higher priority tasks want to run).

The other common use of a counting semaphore is in what is commonly called a "producer/consumer" relationship. The producer adds tokens (by calling *os_sem_release*) and the consumer consumes them by calling *os_sem_pend*. In this relationship, the producer has work for the consumer to do. Each token added to the semaphore will cause the consumer to do whatever work is required. A simple example could be the following: every time a button is pressed there is some work to do (ring a bell). Each button press causes the producer to add a token. Each token consumed rings the bell. There will exactly the same number of bell rings as there are button presses. In other words, each call to *os_sem_pend* subtracts exactly one token and each call to *os_sem_release* adds exactly one token.

## Data structures
```

struct os_sem
{
    SLIST_HEAD(, os_task) sem_head;     /* chain of waiting tasks */
    uint16_t    _pad;
    uint16_t    sem_tokens;             /* # of tokens */
};
```

| Element | Description |
|-----------|-------------|
| sem_head |  Queue head for list of tasks waiting on semaphore |
| _pad |  Padding for alignment  |
| sem_tokens | Current number of tokens |

## List of Functions

<List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the words of the heading need to be connected with a dash for the anchor to work. Hence the word "function" and the function name is connected with a dash, not underscore! And the header has to have at least 2 words for the anchor to work - that's how it is.>

The functions available in this OS feature are:

* [os_sem_init](#function-os_sem_init)
* [os_sem_release](#function-os_sem_release)
* [os_sem_pend](#function-os_sem_pend)
* [os_sem_delete](#function-os_sem_delete)


## Function Reference

------------------

### <font color="2980b9">function os_sem_init</font>

```
    os_error_t os_sem_init(struct os_sem *sem, uint16_t tokens)    

```

Initialize a semaphore with a given number of tokens. Should be called before the semaphore is used.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |
| tokens |  Initial number of tokens allocated to semaphore  |

#### Returned values

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore initialized successfully.

#### Notes 

<Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).>

#### Example

The following example shows how to initialize a semaphore used for exclusive access.

```
struct os_mutex g_os_sem;
os_error_t err;

err = os_sem_init(&g_os_sem, 1);
assert(err == OS_OK);

```

---------------------
   
### <font color="#2980b9"> function os_sem_release </font>

```
os_error_t os_sem_release(struct os_sem *sem)
   
```

Release a semaphore that you are holding. This adds a token to the semaphore.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |

#### Returned values

OS_NOT_STARTED: Called before os has been started.

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore released successfully.

#### Notes 


#### Example

```
struct os_sem g_os_sem;
os_error_t err;

err = os_sem_pend(&g_os_sem, OS_TIMEOUT_NEVER);
assert(err == OS_OK);

/* Perform operations requiring semaphore lock */

err = os_sem_release(&g_os_sem);
assert(err == OS_OK);

```

---------------------
   
### <font color="#2980b9"> function os_sem_pend </font>

```
os_error_t os_sem_pend(struct os_sem *sem, uint32_t timeout)
   
```

Wait for a semaphore for a given amount of time.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |
| timeout |  Amount of time, in os ticks, to wait for semaphore. A value of 0 means no wait. A value of 0xFFFFFFFF means wait forever.  |

#### Returned values

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore acquired successfully.

OS_TIMEOUT: the semaphore was not available within the timeout specified.

OS_NOT_STARTED: Attempt to release a semaphore before os started.

#### Notes 

If a timeout of 0 is used and the function returns OS_TIMEOUT, the semaphore was not available and was not acquired. No release of the semaphore should occur and the calling task does not own the semaphore.

#### Example

```
struct os_sem g_os_sem;
os_error_t err;

err = os_sem_pend(&g_os_sem, OS_TIMEOUT_NEVER);
assert(err == OS_OK);

/* Perform operations requiring semaphore lock */

err = os_sem_release(&g_os_sem);
assert(err == OS_OK);

```

---------------------

### <font color="#2980b9"> function os_sem_delete </font>

```
os_error_t os_sem_delete(struct os_sem *sem)
   
```

Delete a semaphore

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *sem |  Pointer to semaphore  |

#### Returned values

OS_INVALID_PARM: returned when *sem is NULL on entry.

OS_OK: semaphore deleted successfully.

OS_NOT_STARTED: Attempt to release a semaphore before os started.

#### Notes 

Care must be taken when deleting a semaphore as deleting a semaphore used by other tasks could causes unexpected/unwanted behavior.

#### Example

```
struct os_sem g_os_sem;
os_error_t err;

err = os_sem_delete(&g_os_sem);
assert(err == OS_OK);


```

---------------------
