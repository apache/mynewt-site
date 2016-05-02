# testutil


The testutil package is a test framework that provides facilities for specifying test cases and recording test results.

You would use it to build regression tests for your library.

###Description

A package may optionally contain a set of test cases.  Test cases are not normally compiled and linked when a package is built; they are only included
when the "test" identity is specified.  All of a package's test code goes in its `src/test` directory.  For example, the nffs package's test code is located in the following directory:
```no-highlight
    * fs/nffs/src/test/
```
This directory contains the source and header files that implement the nffs test code.

The test code has access to all the header files in the following directories:
```no-highlight
    * src
    * src/arch/<target-arch>
    * include
    * src/test
    * src/test/arch/<target-arch>
    * include directories of all package dependencies
```
Package test code typically depends on the testutil package, described later in this document.

Some test cases or test initialization code may be platform-specific.  In such cases, the platform-specific function definitions are placed in arch subdirectories within the package test directory.

While building the test code (i.e., when the `test` identity is specified), the newt tool defines the `TEST` macro.  This macro is defined during compilation of all C source files in all projects and packages.

Tests are structured according to the following hierarchy:
```no-highlight
                [test]
               /      \
        [suite]        [suite]
       /       \      /       \
     [case] [case]  [case] [case]
```

I.e., a test consists of test suites, and a test suite consists of test cases.

The test code uses testutil to define test suites and test cases.

Regression test can then be executed using 'newt target test' command, or by including a call to your test suite from `project/test/src/test.c`.

### Example

[This Tutorial](../../tutorials/unit_test.md) shows how to create a test suite
for a Mynewt package.

###Data structures

```no-highlight
struct tu_config {
    int tc_print_results;
    int tc_system_assert;

    tu_case_init_fn_t *tc_case_init_cb;
    void *tc_case_init_arg;

    tu_case_report_fn_t *tc_case_fail_cb;
    void *tc_case_fail_arg;

    tu_case_report_fn_t *tc_case_pass_cb;
    void *tc_case_pass_arg;

    tu_suite_init_fn_t *tc_suite_init_cb;
    void *tc_suite_init_arg;

    tu_restart_fn_t *tc_restart_cb;
    void *tc_restart_arg;
};
extern struct tu_config tu_config;
```
The global `tu_config` struct contains all the testutil package's settings.
This should be populated before `tu_init()` is called.

###List of Functions

<Comments such as these instructions are placed within angle brackets. List all the functions here. Note how the anchors work. You put the text you want to show up as a link within [] and the relevant #heading within (). Note that the header has to have at least 2 words for the anchor to work - that's how it is. "no-highlight" disables syntax highlighting. You can enable it for a particular language by specifying what the language is instead of "no-highlight". Be warned that this highlighting or no-highlighting specification may not show up nicely on Mou.>

The functions, and macros available in `testutil` are:

* [tu_init](tu_init.md)
* [TEST_ASSERT](test_assert.md)
* [TEST_PASS](test_pass.md)
* [TEST_SUITE](test_suite.md)
* [TEST_CASE](test_case.md)
* [TEST_CASE_DECL](test_decl.md)
* [tu_restart](tu_restart.md)
