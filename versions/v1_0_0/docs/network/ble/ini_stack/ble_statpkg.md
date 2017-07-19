##  Initialize the statistics package

The NimBLE stack uses the statistics package. Initializing the statistics package is quite simple; all you need to do is enable it in your target's `syscfg.yml` configuration file and re-build your app.

```c hl_lines="4"
syscfg.vals:
    # Enable the shell task.
    SHELL_TASK: 1
    STATS_CLI: 1
```

<br>

