## <font color="F2853F" style="font-size:24pt"> os_task_count</font>

```no-highlight
uint8_t os_task_count(void);
```
Returns the number of tasks that have been created. 

<br>
#### Arguments

None

<br>
#### Returned values

unsigned 8-bit integer representing number of tasks created

<br>
#### Example

```no-highlight

    uint8_t num_tasks;

    num_tasks = os_task_count();
```


