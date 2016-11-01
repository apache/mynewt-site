##<font color="#F2853F" style="font-size:24pt">os_started</font>

```c
int os_started(void)
```

Returns 'true' (1) if the os has been started; 0 otherwise.

<br>

#### Arguments

None

<br>

#### Returned values
Integer value with 0 meaning the OS has not been started and 1 indicating the OS has been started (i.e. `os_start()` has been called).

