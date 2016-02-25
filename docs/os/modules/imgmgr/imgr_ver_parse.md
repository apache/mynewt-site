## <font color="#F2853F" style="font-size:24pt"> imgr_ver_parse </font>

```no-highlight
   int
   imgr_ver_parse(char *src, struct image_version *ver)
```

  Parses character string containing image version number `src` and writes that to `ver`. Version number string should be in format <major>.<minor>.<revision>.<build_number>. Major and minor numbers should be within range 0-255, revision between 0-65535 and build_number 0-4294967295.
  

#### Arguments

| Arguments | Description |
|-----------|-------------|
| src | Pointer to C string that contains version number being parsed |
| ver | Image version number structure containing the returned value |

#### Returned values

0 on success and <0 if version number string could not be parsed.

#### Notes

Numbers within the string are separated by `.`. The first   number is the major number, and must be provided. Rest of the numbers (minor etc.) are optional.

#### Example

```no-highlight
int main(int argc, char **argv)
{
    struct image_version hdr_ver;
    int rc;
    ...
    
    rc = imgr_ver_parse(argv[3], &hdr_ver);
    if (rc != 0) {
        print_usage(stderr);
        return 1;
    }
    ...
}
```


