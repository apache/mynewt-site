# How To Write A Test Suite for Your Package

This document presents a tutorial which guides the reader through writing
a test suite for a Mynewt package (new or existing).

## Introduction

Writing a test suite involves using the [`libs/testutil`](../modules/testutil/testutil.md)
 package within Mynewt core os. The `testutil` library provides the interface to 
the `newt` command tool and also provides the compile time hooks to include
test suites into your code.  Review the 
[`testutil` introduction page ] (../modules/testutil/testutil.md)
to learn about how the library works.

### Identify Your Package

Identify the package for which you are writing a test suite.  For this example
we will use `libs/json`.  To create a new package, see [this Tutorial]().

### Modify Pkg.yml

Edit the package (`pkg.yml`) file for your package and add the test dependency
for the Mynewt core OS `libs/testutil`.

```no-highlight
pkg.deps.TEST:
   - libs/testutil
```

### Create Your Test Suite Template

Create a subdirectory `test` under your package main directory. 
Create a file pair for your test code and header files within the `test`
directory created above.  Below shows the `libs/json` directory within the 
Mynewt core, including the test directory. In this example, we used the 
convention `test_xxx.c/h` (in this case `test_json`).

```no-highlight
├── MSJSON_COPYING
├── include
│   └── json
│       └── json.h
├── pkg.yml
└── src
    ├── json_decode.c
    ├── json_encode.c
    └── test
        ├── test_json.c
        └── test_json.h
```

### Create Your Test Suite Code 

Edit the `test_json.c` file and add your test suite definition.  NOTE that 
the test suite code requires `#include <testutil/testutil.h>` to get the 
Mynewt testutil definitions.

Your test suite `test_json.c` file contains at a minimum two functions

1. A test Suite which is empty for now, but will contain calls to your test
cases.  
2. A main function which must be `#ifdef`'d using `MYNEWT_SELFTEST` to ensure
that is does not get compiled in when this test suite is run with 
test suites from other packages 

Below shows the contents of the `test_json.c` file.

```no-highlight
#include <testutil/testutil.h>

TEST_SUITE(test_json_suite) {
    /* empty for now, add test cases later */
}

#ifdef MYNEWT_SELFTEST
int
main(int argc, char **argv)
{
    tu_config.tc_print_results = 1;
    tu_init();
    test_json_suite();
    return tu_any_failed;
}
#endif
```
### Try It Out

At this point, you have a working test suite with __no__ tests.  
This will by default pass the test.  Your output will look
something like this.

You can use the `newt test` command to run the unit tests for any package.  
Just include the package name.  These unit tests run via the project 
`unittest` which is a native project automatically included in the core
os package.  Below shows some of the test output of this command.

```no-highlight
$ newt test libs/json
Archiving util.a
Linking test_json
Testing package libs/json
Test .../bin/unittest/libs/json/test_json ok!
```
### Create a Test 

To create a test within your test suite, there are two things to do.

1. Add the functions to your test suite
2. Implement the function using the `testutil` macros

For this tutorial we will create two functions: one to test a simple json
encode and one to test the decode of this simple message to ensure its 
coherent.

Follow These steps;

1\. Create function prototypes in `test_json.h` for your test functions. 
A macro in `testutil.h` hides the actual prototype, but as of this writing
the prototype is `int test_func(void);`.     
```no-highlight
#ifndef TEST_JSON_H
#define TEST_JSON_H

TEST_CASE_DECL(test_json_simple_encode);
TEST_CASE_DECL(test_json_simple_decode);

#endif /* TEST_JSON_H 
```
2\. create a new file `test_json_simple.c` to define these two functions.  For
now you can stub these functions. Below shows the contents of this file. 
The functions are defined using macros which reference back to the 
`testutil` library so the test can be enumerated and recorded automatically.
```no-highlight
#include "testutil/testutil.h"
#include "test_json.h"

TEST_CASE(test_json_simple_encode) {
}

TEST_CASE(test_json_simple_decode) {
}
#endif /* TEST_JSON_H 
```
3\. Add the tests to your test suite in `test_json.c` as shown below.
```no-highlight
TEST_SUITE(test_json_suite) {
    test_json_simple_encode();
    test_json_simple_decode();
}
```

Your test suite should still pass as shown below

```no-highlight
$newt test libs/json
Testing package libs/json
Test .../bin/unittest/libs/json/test_json ok!
```

## Add Contents to your Tests

At this point, you can add contents to your test and verify that 
the test suites pass.  For now, lets just add a simple failures to show
what it would look like when running from Newt.

1. Edit `test_json_simple.c` and add a `TEST_ASSERT` to a test funtion. The
test assert will fail if its argument is `false`.


```no-highlight
TEST_CASE(test_json_simple_encode) {
    TEST_ASSERT(0);
}
```
When running newt, you will see the test suite failures something like
the message shown below.

```no-highlight
Testing package libs/json
[FAIL] test_json_suite/(null) |test_json_simple.c:24| failed assertion: 0
Error: Test crashed: ../bin/unittest/libs/json/test_json
exit status 1
```

## Congratulations

Now you can begin the work of adding your test cases and test 


## Testing on your target

