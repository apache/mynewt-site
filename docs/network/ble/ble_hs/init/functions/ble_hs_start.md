## <font color="#F2853F" style="font-size:24pt">ble\_hs\_start</font>

```c
int
ble_hs_start(void)
```

### Description

Synchronizes the host with the controller by sending a sequence of HCI commands.  This function must be called before any other host functionality is used, but it must be called after both the host and controller are initialized.  Typically, the host-parent-task calls this function at the top of its task routine. 

### Parameters

None

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 0 | Success. |
| [Core return code](../../ble_hs_return_codes/#return-codes-core) | Unexpected error. |
