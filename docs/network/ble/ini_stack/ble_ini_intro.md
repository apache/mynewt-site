## Nimble stack initialization

We are now going to explain how to setup your application to initialize the nimble stack and to get the basic stack, and its required modules, initialized and up and running. Note that the code shown here is an example of what is required for nimble stack operation; it is not intended to dictate to the developer exactly how to organize/setup your code. For example, the code sample shows modification of main.c in the application /src folder. The developer has the flexibility to organize the code as they see fit so this code does not need to reside in /src/main.c nor in the main() function itself. The only possible issue is the order of some of the initializations. Where this order is important it is indicated in the tutorial.

A note about the code samples: the main() function in each code sample builds upon the previous example. However, code outside of main() shows only what we add for each step. The last code sample shows the entire main.c that we created.

Let's start with a very basic main() function (shown below). In this main all we are doing is initializing the Mynewt OS and starting it.

```c
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
The Nimble stack requires a number of packages/modules to be initialized prior to being initialized. We are going to add these one by one to the application and describe each.

<br>

