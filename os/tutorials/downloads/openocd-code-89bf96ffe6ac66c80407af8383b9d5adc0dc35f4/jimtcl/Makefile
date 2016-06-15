# Tools
CC =  cc
CXX =  c++
RANLIB = ranlib
AR = ar
STRIP = strip

# Configuration

SH_CFLAGS ?= -dynamic
SH_LDFLAGS ?= -dynamiclib
SH_LDFLAGS += -Wl,-install_name,libjim.0.76.dylib
SHOBJ_CFLAGS ?= -dynamic -fno-common
SHOBJ_LDFLAGS ?= -bundle -undefined dynamic_lookup
CFLAGS = -g -O2 -fno-unwind-tables -fno-asynchronous-unwind-tables 
CXXFLAGS = -g -O2 
LDFLAGS = 
LDLIBS += 
LIBS += 
exec_prefix ?= /usr/local
prefix ?= /usr/local
docdir = ${prefix}/docs/jim

CC += -D_GNU_SOURCE -Wall $(OPTIM) -I.
CXX += -D_GNU_SOURCE -Wall $(OPTIM) -I.

LIBJIM := libjim.a

JIMSH_CC := $(CC) $(CFLAGS)

OBJS := _load-static-exts.o jim-subcmd.o jim-interactive.o jim-format.o jim.o utf8.o jimregexp.o \
    linenoise.o jim-aio.o jim-array.o jim-clock.o jim-eventloop.o jim-exec.o jim-file.o jim-history.o jim-load.o jim-namespace.o jim-pack.o jim-package.o jim-posix.o jim-readdir.o jim-regexp.o jim-signal.o jim-syslog.o jim-tclprefix.o binary.o glob.o nshelper.o oo.o stdlib.o tclcompat.o tree.o

JIMSH := jimsh


all: $(JIMSH) 

# Create C extensions from pure Tcl extensions
.SUFFIXES: .tcl
.tcl.o:
	/usr/bin/tclsh ./make-c-ext.tcl $< >_$*.c
	$(CC) $(CFLAGS) -c -o $@ _$*.c

docs: Tcl.html

install-docs: docs
	$(INSTALL_DATA_DIR) $(DESTDIR)$(docdir)
	$(INSTALL_DATA) Tcl.html $(DESTDIR)$(docdir)

$(JIMSH): $(LIBJIM) jimsh.o initjimsh.o
	$(JIMSH_CC)  $(LDFLAGS) -o $@ jimsh.o initjimsh.o $(LIBJIM) $(LDLIBS) $(LIBS)

install install-exec: all
uninstall:

test check: $(JIMSH)
	cd ./tests; $(DEF_LD_PATH) $(MAKE) jimsh=/Users/marko/tools/openocd-code-89bf96ffe6ac66c80407af8383b9d5adc0dc35f4/jimtcl/jimsh TOPSRCDIR=.

$(OBJS): Makefile $(wildcard *.h)


_load-static-exts.c: ./make-load-static-exts.tcl Makefile
	/usr/bin/tclsh ./make-load-static-exts.tcl aio array clock eventloop exec file history load namespace pack package posix readdir regexp signal syslog tclprefix binary glob nshelper oo stdlib tclcompat tree >$@ || ( rm $@; exit 1)

$(LIBJIM): $(OBJS)
	$(AR) cr $@ $(OBJS)
	$(RANLIB) $@

# Note that $> $^ is for compatibility with both GNU make and BSD make
readdir.so: jim-readdir.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-readdir.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-readdir.o $(SH_LIBJIM)

array.so: jim-array.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-array.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-array.o $(SH_LIBJIM)

clock.so: jim-clock.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-clock.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-clock.o $(SH_LIBJIM)

file.so: jim-file.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-file.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-file.o $(SH_LIBJIM)

posix.so: jim-posix.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-posix.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-posix.o $(SH_LIBJIM)

regexp.so: jim-regexp.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-regexp.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-regexp.o $(SH_LIBJIM)

syslog.so: jim-syslog.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-syslog.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-syslog.o $(SH_LIBJIM)

readline.so: jim-readline.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-readline.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-readline.o $(SH_LIBJIM) 

pack.so: jim-pack.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-pack.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-pack.o $(SH_LIBJIM) 

tclprefix.so: jim-tclprefix.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-tclprefix.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-tclprefix.o $(SH_LIBJIM) 

sqlite3.so: jim-sqlite3.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-sqlite3.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-sqlite3.o $(SH_LIBJIM) 

win32.so: jim-win32.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-win32.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-win32.o $(SH_LIBJIM) 

mk.so: jim-mk.cpp
	$(CXX) $(CXXFLAGS) $(SHOBJ_CFLAGS) -c -o jim-mk.o $> $^
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-mk.o $(SH_LIBJIM) 

sdl.so: jim-sdl.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-sdl.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-sdl.o $(SH_LIBJIM) 

Tcl.html: jim_tcl.txt
	/usr/bin/tclsh ./make-index $> $^ | asciidoc -o $@ -d manpage - || cp ./Tcl_shipped.html Tcl.html

clean:
	rm -f *.o *.so *.dll *.exe lib*.a $(JIMSH) $(LIBJIM) Tcl.html _*.c

distclean: clean
	rm -f jimautoconf.h jim-config.h Makefile config.log autosetup/jimsh0 build-jim-ext

ship: Tcl.html
	cp $< Tcl_shipped.html

# automake compatibility. do nothing for all these targets
EMPTY_AUTOMAKE_TARGETS := dvi pdf ps info html tags ctags mostlyclean maintainer-clean check installcheck installdirs \
 install-pdf install-ps install-info install-html -install-dvi uninstall install-data
.PHONY: $(EMPTY_AUTOMAKE_TARGETS)
$(EMPTY_AUTOMAKE_TARGETS):

# automake compatibility - install sources from the current dir to $(distdir)
distdir_full := $(shell cd $(distdir); pwd)
distdir:
	cd "."; git ls-files | cpio -pdmu $(distdir_full)

reconfig:
	CC='cc' /Users/marko/tools/openocd-code-89bf96ffe6ac66c80407af8383b9d5adc0dc35f4/jimtcl/configure --disable-install-jim --disable-option-checking --prefix=/usr/local --enable-cmsis-dap --enable-openjtag_ftdi --enable-jlink --enable-stlink --cache-file=/dev/null --srcdir=.
