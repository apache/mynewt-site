# Mutex


Mutex is short for "mutual exclusion"; a mutex provides mutually exclusive access to a shared resource. A mutex provides *priority inheritance* in order to prevent *priority inversion*. Priority inversion occurs when a higher priority task is waiting on a resource owned by a lower priority task. Using a mutex, the lower priority task will inherit the highest priority of any task waiting on the mutex. 


## Description

The first order of business when using a mutex is to declare the mutex globally. The mutex needs to be initialized before it is used (see the examples). It is generally a good idea to initialize the mutex before tasks start running in order to avoid a task possibly using the mutex before it is initialized.

When a task wants exclusive access to a shared resource it needs to obtain the mutex by calling *os_mutex_pend*. If the mutex is currently owned by a different task (a lower priority task), the requesting task will be put to sleep and the owners priority will be elevated to the priority of the requesting task. Note that multiple tasks can request ownership and the current owner is elevated to the highest priority of any task waitin on the mutex. When the task is done using the shared resource, it needs to release the mutex by called *os_mutex_release*. There needs to be one release per call to pend. Note that nested calls to *os_mutex_pend* are allowed but there needs to be one release per pend.

The following example will illustrate how priority inheritance works. In this example, the task number is the same as its priority. Remember that the lower the number, the higher the priority (i.e. priority 0 is higher priority than priority 1). Suppose that task 5 gets ownership of a mutex but is preempted by task 4. Task 4 attempts to gain ownership of the mutex but cannot as it is owned by task 5. Task 4 is put to sleep and task 5 is temporarily raised to priority 4. Before task 5 can release the mutex, task 3 runs and attempts to acquire the mutex. At this point, both task 3 and task 4 are waiting on the mutex (sleeping). Task 5 now runs at priority 3 (the highest priority of all the tasks waiting on the mutex). When task 5 finally releases the mutex it will be preempted as two higher priority tasks are waiting for it. 

Note that when multiple tasks are waiting on a mutex owned by another task, once the mutex is released the highest priority task waiting on the mutex is run. 

## Data structures

```
struct os_mutex
{
    SLIST_HEAD(, os_task) mu_head;
    uint8_t     _pad;
    uint8_t     mu_prio;
    uint16_t    mu_level;
    struct os_task *mu_owner;
};

```
| Element | Description |
|-----------|-------------|
| mu_head |  Queue head for list of tasks waiting on mutex  |
| _pad |  Padding  |
| mu_prio |  Default priority of owner of mutex. Used to reset priority of task when mutex released  |
| mu_level | Call nesting level (for nested calls) |
| mu_owner | Pointer to task structure which owns mutex |

## List of Functions

<List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the words of the heading need to be connected with a dash for the anchor to work. Hence the word "function" and the function name is connected with a dash, not underscore! And the header has to have at least 2 words for the anchor to work - that's how it is.>

The functions available in this OS feature are:

* [os_mutex_init](#function-os_mutex_init)
* [os_mutex_release](#function-os_mutex_release)
* [os_mutex_pend](#function-os_mutex_pend)
* [os_mutex_delete](#function-os_mutex_delete)

## Function Reference

------------------

### <font color="2980b9">function os_mutex_init</font>

```
os_error_t os_mutex_init(struct os_mutex *mu)
    
```

Initialize the mutex. Must be called before the mutex can be used.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu|  Pointer to mutex  |

#### Returned values

OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex initialized successfully.

#### Notes 

<Any special feature/special benefit that we want to tout. 
Does it need to be used with some other specific functions?
Any caveats to be careful about (e.g. high memory requirements).>

#### Example


```
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_init(&g_mutex1);
assert(err == OS_OK);

```

---------------------
   
### <font color="#2980b9"> function os_mutex_release</font>

```
os_error_t os_mutex_release(struct os_mutex *mu)

   
```

Release ownership of a mutex


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu|  Pointer to mutex  |

#### Returned values
OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex initialized successfully.

OS_BAD_MUTEX: The mutex was not owned by the task attempting to release it.

OS_NOT_STARTED: Attempt to release a mutex before the os has been started.


#### Example


```
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_pend(&g_mutex1, 0);
assert(err == OS_OK);

/* Perform operations requiring exclusive access */

err = os_mutex_release(&g_mutex1);
assert(err == OS_OK);

```

---------------------
   
### <font color="#2980b9"> function os_mutex_pend </font>

```
os_error_t os_mutex_pend(struct os_mutex *mu, uint32_t timeout)
   
```

Acquire ownership of a mutex.


#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu |  Pointer to mutex  |
| timeout | Timeout, in os ticks. A value of 0 means no timeout. A value of 0xFFFFFFFF means to wait forever.   |

#### Returned values

OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex was successfully acquired.

OS_TIMEOUT: the mutex was not available within the timeout specified.

OS_NOT_STARTED: Attempt to release a mutex before the os has been started.


#### Notes 

If the mutex is owned by another task and the timeout is 0 the function returns immediately with the error code OS_TIMEOUT. The calling task *does not* own the mutex when this occurs.

#### Example



```
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_pend(&g_mutex1, 0);
assert(err == OS_OK);

/* Perform operations requiring exclusive access */

err = os_mutex_release(&g_mutex1);
assert(err == OS_OK);


```

---------------------

### <font color="#2980b9"> function os_mutex_delete </font>

```
os_error_t os_mutex_pend(struct os_mutex *mu)
   
```

Delete a mutex

#### Arguments

| Arguments | Description |
|-----------|-------------|
| *mu |  Pointer to mutex  |

#### Returned values

OS_INVALID_PARM: returned when *mu is NULL on entry.

OS_OK: mutex initialized successfully.

OS_NOT_STARTED: Attempt to release a mutex before the os has been started.

#### Example

```
struct os_mutex g_mutex1;
os_error_t err;

err = os_mutex_delete(&g_mutex1);
assert(err == OS_OK);


```

---------------------
