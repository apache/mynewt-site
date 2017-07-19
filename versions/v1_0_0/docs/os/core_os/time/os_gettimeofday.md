## <font color="F2853F" style="font-size:24pt">os_gettimeofday</font>

```c
int os_gettimeofday(struct os_timeval *utctime, struct os_timezone *timezone); 
```

#### Arguments

| Arguments | Description |
|-----------|-------------|
| `utctime` | UTC time corresponding to wallclock time  |
| `timezone` | Timezone to convert UTC time to wallclock time |

#### Returned values

Returns 0 on success and non-zero on failure.

#### Notes
`utctime` or `timezone` may be NULL.

The function is a no-op if both `utctime` and `timezone` are NULL.

#### Example

<Add text to set up the context for the example here>

```c
    /*
     * Display wallclock time on the console.
     */
    int rc;
    struct os_timeval utc;
    struct os_timezone tz;
    char buf[DATETIME_BUFSIZE];
    
    rc = os_gettimeofday(&utc, &tz);
    if (rc == 0) {
        format_datetime(&utc, &tz, buf, sizeof(buf));
        console_printf("%s\n", buf);
    }
    
```

