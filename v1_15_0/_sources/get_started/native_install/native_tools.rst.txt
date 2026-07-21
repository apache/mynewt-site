Installing Native Toolchain
===========================

.. contents::
  :local:
  :depth: 2

This page shows you how to install the toolchain to build Mynewt OS
applications that run native on macOS and Linux. The applications run
on Mynewt's simulated hardware. It also allows you to run the test
suites for all packages that do not require HW support.

**Note:** This is not supported on Windows.

Setting Up the Toolchain for Mac
--------------------------------

Installing Brew
~~~~~~~~~~~~~~~

If you have not already installed Homebrew from the ``newt`` tutorials
pages install it (:doc:`../../newt/install/newt_mac`).

Installing GCC/libc
~~~~~~~~~~~~~~~~~~~

Since macOS with Xcode ships with a C compiler called Clang there is no need to
install the other compiler. However, one can install gcc compiler with brew:

.. code-block:: console

    $ brew install gcc
    ...
    ...
    ==> Pouring gcc-10.2.0_2.big_sur.bottle.tar.gz
        /usr/local/Cellar/gcc/10.2.0_2: 1,455 files, 338.1MB


Check the GCC version you have installed (either using ``brew`` or
previously installed). The brew-installed version can be checked using
``brew list gcc``. To use gcc instead of clang ``<mynewt-src-directory>/repos/apache-mynewt-core/compiler/sim/compiler.yml``
file must be edited:

.. code-block:: yaml
    :emphasize-lines: 2,3

    # OS X.
    compiler.path.cc.DARWIN.OVERWRITE: "gcc"
    compiler.path.as.DARWIN.OVERWRITE: "gcc"
    compiler.path.objdump.DARWIN.OVERWRITE: "gobjdump"
    compiler.path.objcopy.DARWIN.OVERWRITE: "gobjcopy"
    compiler.flags.base.DARWIN: [-DMN_OSX, -Wno-missing-braces]
    compiler.ld.resolve_circular_deps.DARWIN.OVERWRITE: false

...with the following:

.. code-block:: yaml

    compiler.path.cc.DARWIN.OVERWRITE: "gcc-<version>"
    compiler.path.as.DARWIN.OVERWRITE: "gcc-<version>”

Installing GDB
~~~~~~~~~~~~~~

.. code-block:: console

    $ brew install gdb
    ...
    ...
    ==> Summary
        /usr/local/Cellar/gdb/7.10.1: XXX files,YYM

**NOTE:** When running a program with GDB, you may need to sign your ``gdb``
executable. `This
page <https://gcc.gnu.org/onlinedocs/gnat_ugn/Codesigning-the-Debugger.html>`__
shows a recipe for gdb signing. Alternately you can skip this step and
continue without the ability to debug your mynewt application on your
PC.\*

Setting Up the Toolchain for Linux
----------------------------------

The below procedure can be used to set up a Debian-based Linux system
(e.g., Ubuntu). If you are running a different Linux distribution, you
will need to substitute invocations of *apt-get* in the below steps with
the package manager that your distro uses.

Installing GCC/libc that will produce 32-bit executables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

    $ sudo apt-get install gcc-multilib libc6-i386

Installing GDB
~~~~~~~~~~~~~~

.. code-block:: console

    $ sudo apt-get install gdb

    Reading package lists... Done
    Building dependency tree
    Reading state information... Done
    Suggested packages:
      gdb-doc gdbserver
    The following NEW packages will be installed:
      gdb
    ...
    Processing triggers for man-db (2.6.7.1-1ubuntu1) ...
    Setting up gdb (7.7.1-0ubuntu5~14.04.2) ...

Next
----

At this point you have installed all the necessary software to build and
run your first project on a simulator on your macOS or Linux computer.
You may proceed to :doc:`../project_create` or continue to the next section and install the cross tools for
ARM.
