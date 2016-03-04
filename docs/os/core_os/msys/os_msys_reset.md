## <font color="#F2853F" style="font-size:24pt">os_msys_reset</font>

```no-highlight
void os_msys_reset(void) 
```

Resets msys module. This de-registers all pools from msys but does nothing to the pools themselves (they still exist as mbuf pools).

<br>

#### Arguments

None

<br>

#### Returned values

None

<br>

#### Example

```no-highlight
    os_msys_reset(); 
```

---------------------
