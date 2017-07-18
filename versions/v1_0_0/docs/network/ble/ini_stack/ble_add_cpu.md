## Add cputime

The NimBLE stack requires "cputime". This is provided by the Mynewt HAL of the
same name. The cputime HAL provides a high resolution timer that is used by the
nimble stack (as the BLE specification requires a fairly high resolution timer
and has fairly tight timing requirements). The cputime HAL allows the user to
specify the timer resolution as different applications may require a different
resolution. While the Nimble stack does not require a specific timer resolution
per se, a resolution that is too large may affect performance and power
efficiency. A suggested clock rate for HAL cputime for the nimble stack is 1
MHz, or 1 microsecond per cputime tick. This provides enough resolution for
most needs while providing the Nimble stack enough resolution to implement the
BLE specification.

Add the initialization of cputime to your application:

```c hl_lines="1 11 12 13"
#include "hal/hal_cputime.h"

int
main(void)
{
	int rc;

    /* Initialize OS */
    os_init();

    /* Set cputime to count at 1 usec increments */
    rc = cputime_init(1000000);
    assert(rc == 0);

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```

<br>

