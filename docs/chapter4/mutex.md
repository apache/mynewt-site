# Mutex


Mutex is short for "mutual exclusion"; a mutex provides mutually exclusive access to a shared resource. A mutex provides *priority inheritance* in order to prevent *priority inversion*. Priority inversion occurs when a higher priority task is waiting on a resource owned by a lower priority task. Using a mutex, the lower priority task will inherit the highest priority of any task waiting on the mutex. 


## Description

Describe OS feature here 

## Data structures

Replace this with the list of data structures used, why, any neat features

## List of Functions

<List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the words of the heading need to be connected with a dash for the anchor to work. Hence the word "function" and the function name is connected with a dash, not underscore! And the header has to have at least 2 words for the anchor to work - that's how it is.>

The functions available in this OS feature are:

* [os_mutex_init](#function-os_mutex_init)
* [os_mutex_release](#function-os_mutex_release)
* add the rest


## Function Reference

------------------

### <font color="2980b9">function os_mutex_init</font>

```
    os_error_t
    os_mutex_init(struct os_mutex *mu)
    
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
   
### <font color="#2980b9"> function os_mutex_release</font>

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

