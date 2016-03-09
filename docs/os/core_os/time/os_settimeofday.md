## <font color="F2853F" style="font-size:24pt">os_settimeofday</font>

```no-highlight
int os_settimeofday(struct os_timeval *utctime, struct os_timezone *timezone);
```

#### Arguments

| Arguments | Description |
|-----------|-------------|
| utctime | UTC time corresponding to the wallclock time  |
| timezone | Timezone associated with the wallclock time |

#### Returned values

Returns 0 on success and non-zero on failure.

#### Notes
`utctime` may be NULL if only the timezone needs to be changed. This is useful when adjusting the `timezone` to account for daylight savings.

`timezone` may be NULL if only the UTC time needs to be changed. This is useful when synchronizing Mynewt's time with an external time source like NTP.

The function is a no-op if both `utctime` and `timezone` are NULL.

#### Example

<Add text to set up the context for the example here>

```no-highlight
    int rc;
    parse_datetime(datestr, &utctime, &tz);
    rc = os_settimeofday(&utctime, &tz);
    if (rc == 0) {
        /* success */
    }
```
---------------------
