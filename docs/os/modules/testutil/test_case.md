## <font color="F2853F" style="font-size:24pt"> TEST_CASE </font>

```no-highlight
TEST_CASE(test_case_name)
```

Declares a test case function with the following type *int test_case_name(void)*. This can then be called from regression test's *TEST_SUITE()* function.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| test_case_name | Used as the function name for this test case. |

#### Returned values

Return value is 0 if the test case passed; nonzero if it failed. Generally, the return code is not used. It is expected that the case will pass/fail with tests done using *TEST_ASSERT()*.

#### Notes


#### Example

```no-highlight
TEST_CASE(config_test_insert)
{
     ....
}
```
