## <font color="#F2853F" style="font-size:24pt">ble\_hs\_sched\_reset</font>

```c
void
ble_hs_sched_reset(int reason)
```

### Description

Causes the host to reset the NimBLE stack as soon as possible.  The application is notified when the reset occurs via the host reset callback.

### Parameters

| *Parameter* | *Description* |
|-------------|---------------|
| reason | The host error code that gets passed to the reset callback. |

### Returned values

None
