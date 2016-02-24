## <font color="#F2853F" style="font-size:24pt"> imgmgr_module_init </font>

```no-highlight
   int
   imgmgr_module_init(void)
```

  Registers image manager commands with newtmgr. This function should be called while initializing the project, preferably after newtmgr itself has been initialized.

#### Arguments

N/A

#### Returned values

List any values returned.
Error codes?

#### Notes


#### Example

```no-highlight
int main(int argc, char **argv)
{
    ...
    
    nmgr_task_init(NEWTMGR_TASK_PRIO, newtmgr_stack, NEWTMGR_TASK_STACK_SIZE);
    imgmgr_module_init();

    ...
}
```


