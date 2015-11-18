# Mynewt OS 

Insert introduction here  

## Real-Time Kernel <Modify as you Wish>

 Description

## Real-Time OS <Modify as you Wish>

 Description


## Insert topic of your choice

 Description

## Features

<Insert basic feature descriptions, how the various pieces fit together etc., what's special in Mynewt OS>

* [Scheduler/context switching](context_switch.md)
* [Time](time.md)
* [Tasks](task.md)
* [Event queues/callouts](event_queue.md)
* [Semaphores](semaphore.md)
* [Mutexes](mutex.md)
* [Memory pools](memory_pool.md)
* [Heap](heap.md)
* [Mbufs](mbufs.md)
* [Sanity](sanity.md)
* [Porting OS to other platforms](port_os.md)

## OS Functions

<List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the words of the heading need to be connected with a dash for the anchor to work. Hence the word "function" and the function name is connected with a dash, not underscore! And the header has to have at least 2 words for the anchor to work - that's how it is.>

The functions available in this OS feature are:

* [os_idle_task](#function-os_idle_task)
* [os_started](#function-os_started)
* add the rest

## Function Reference

------------------

### <font color="2980b9">function os_idle_task</font>

```
    void
    os_idle_task(void *arg)
```

<Insert short description>


#### Arguments

| Arguments | Description |
|-----------|-------------|
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

<Add text to set up the context for the example here>

```

<Insert the code snippet here>

```

---------------------
   
### <font color="#2980b9"> function os_started</font>

```
   <Insert function callout here >
   
```

<Insert short description>


#### Arguments

| Arguments | Description |
|-----------|-------------|
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

<Add text to set up the context for the example here>

```

<Insert the code snippet here>

```

---------------------
   
### <font color="#2980b9"> function next_one </font>

```
   <Insert function callout here >
   
```

<Insert short description>


#### Arguments

| Arguments | Description |
|-----------|-------------|
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

<Add text to set up the context for the example here>

```

<Insert the code snippet here>

```

---------------------

