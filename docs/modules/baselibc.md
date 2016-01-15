# Baselibc

baselibc is a very simple libc for embedded systems geared primarily for 32-bit microcontrollers in the 10-100kB memory range. The library of basic system calls and facilities compiles to less than 5kB total on Cortex-M3, and much less if some functions aren't used.

The code is based on klibc and tinyprintf modules, and licensed under the BSD license.

## Description

Mynewt Os comes bundled with libc (the standard C library). However, you may choose to replace libc functions with baselibc ones for a reduced image size.

## How to switch to baselibc

In order to switch from using libc to using baselibc you have to add the baselibc egg as dependency in the project egg. Specifying this dependency ensures that the linker first looks for the functions in baselibc before falling back to libc while creating the executable. For example, project `boot` uses baselibc. Its project description file `boot.yml` looks like the following:

```no-highlight
   project.name: boot
   project.identities: bootloader
   project.eggs:
       - libs/os
       - libs/bootutil
       - libs/nffs
       - libs/console/stub
       - libs/util
       - libs/baselibc
 ```

## List of Functions

The functions available in this OS feature are listed below. Documentation is available in the form of  on-line manual pages or at [https://www.freebsd.org/cgi/man.cgi](#https://www.freebsd.org/cgi/man.cgi).  `mynewt.c` adds two new functions listed in the Function reference section.

* asprintf.c	
* atoi.c	
* atol.c
* atoll.c	
* bsearch.c	
* bzero.c	
* calloc.c	
* fgets.c	 
* inline.c	
* jrand48.c	
* lrand48.c	
* malloc.c	
* malloc.h	
* memccpy.c	
* memchr.c	
* memcmp.c	
* memcpy.c	
* memfile.c	
* memmem.c	
* memmove.c	
* memrchr.c	
* memset.c	
* memswap.c	
* mrand48.c	
* mynewt.c	
* nrand48.c	
* qsort.c	
* realloc.c	
* sprintf.c	
* srand48.c	
* sscanf.c	
* strcasecmp.c	
* strcat.c	
* strchr.c	
* strcmp.c	
* strcpy.c	
* strcspn.c	
* strdup.c	
* strlcat.c	
* strlcpy.c	
* strlen.c	
* strncasecmp.c	
* strncat.c	
* strncmp.c	
* strncpy.c	
* strndup.c	
* strnlen.c	
* strntoimax.c	
* strntoumax.c	
* strpbrk.c	
* strrchr.c	
* strsep.c	
* strspn.c	
* strstr.c	
* strtoimax.c	
* strtok.c	
* strtok_r.c	
* strtol.c	
* strtoll.c	
* strtoul.c	
* strtoull.c	
* strtoumax.c	
* templates	
* test	
* tinyprintf.c	
* vasprintf.c	
* vprintf.c	
* vsprintf.c	
* vsscanf.c	

## Function Reference

------------------

## <font color="F2853F" style="font-size:24pt"> stdin_read </font>

```no-highlight
    static size_t
    stdin_read(FILE *fp, char *bp, size_t n)
```

Read from a file.

#### Arguments

| Arguments | Description |
|-----------|-------------|
| fp |  pointer to the input file |
| bp |  pointer to the string to be read  |
| n  | size of buffer (number of characters) to be read |

#### Returned values

N/A

#### Notes 

N/A

#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------
   
## <font color="#F2853F" style="font-size:24pt"> stdout_write </font>

```no-highlight
   static size_t
   stdout_write(FILE *fp, const char *bp, size_t n)
```

Write to a file or console. 


#### Arguments

| Arguments | Description |
|-----------|-------------|
| fp |  pointer to the output file |
| bp |  pointer to the string to be written  |
| n  | size of buffer (number of characters) to be output |

#### Returned values

N/A

#### Notes 

N/A

#### Example

<Add text to set up the context for the example here>

```no-highlight
<Insert the code snippet here>
```

---------------------
