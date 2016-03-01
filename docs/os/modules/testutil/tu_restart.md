## <font color="F2853F" style="font-size:24pt"> tu_restart </font>

```no-highlight
void tu_restart(void)
```

This function is used when a system reset is necessary to proceed with testing.  For example, the OS is designed to run forever once started, so a test which creates several OS tasks and then starts the OS has no means of completing. This function, when called from such a test, gracefully ends the current test case and proceeds to the next test case.

The particulars of this function depend on whether it is called from a simulated environment.  In a simulated environment, this function uses a `longjmp()` call to break out of the current test case.


#### Arguments

N/A

#### Returned values

Returns 0 on success; nonzero on failure.

#### Example

```no-highlight
void
os_test_restart(void)
{
    ....

    tu_restart();
}
#endif
```
