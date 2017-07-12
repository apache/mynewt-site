## <font color="#F2853F" style="font-size:24pt">ble\_hs\_synced</font>

```c
int
ble_hs_synced(void)
```

### Description

Indicates whether the host has synchronized with the controller. Synchronization must occur before any host procedures can be performed.

### Parameters

None

### Returned values

| *Value* | *Condition* |
|---------|-------------|
| 1 | The host and controller are in sync. |
| 0 | The host and controller our out of sync. |
