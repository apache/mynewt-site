## Nimble stack initialization

We are now going to explain how to set up your application to initialize the nimble stack and to get the basic stack, and its required modules, initialized and up and running. Note that the code shown here is an example of what is required for nimble stack operation; it is not intended to dictate to the developer exactly how to organize and set up your code. For example, the code sample shows modification of main.c in the application _/src_ folder. The developer has the flexibility to organize the code as they see fit so this code does not need to reside in _/src/main.c_ or in the _main()_ function itself. The only possible issue is the order of some of the initializations. Where this order is important it is indicated in the sections covering stack initialization.

A note about the code samples: the _main()_ function in each code sample builds upon the previous example. However, code outside of _main()_ shows only what we add for each step. The last code sample shows the entire _main.c_ that we created.

Let's start with a very basic _main()_ function (shown below). This _main()_ function is identical to the minimal version used in the [Set up application](../nimble_setup/) introductory page.  In this _main()_ all we are doing is initializing the Mynewt OS and starting it.

```c
#include <assert.h>
#include "os/os.h"

int
main(void)
{
    /* Initialize OS */
    os_init();

    /* Start the OS */
    os_start();

    /* os start should never return. If it does, this should be an error */
    assert(0);
}
```
The Nimble stack requires a number of packages to be initialized prior to being started. We are going to add these one by one to the application and describe each.
