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

macOS with Xcode ships with a C compiler called Clang. To build applications for the
Mynewt simulator, a different compiler is used as default: ``gcc``.

.. code-block:: console

    $ brew install gcc
    ...
    ...
    ==> Summary
    🍺  /usr/local/Cellar/gcc/8.2.0 (1,495 files, 335.9MB)

Check the GCC version you have installed (either using ``brew`` or
previously installed). The brew-installed version can be checked using
``brew list gcc``. The default compiler.yml configuration file in Mynewt
expects version 5.x for Mac users, so if the installed version is newer
and you wish to continue with this newer version, modify the
``<mynewt-src-directory>/repos/apache-mynewt-core/compiler/sim/compiler.yml``
file to change the default ``gcc-5`` defined there to that displayed by
``brew list gcc``, e.g. ``gcc-8``.
In other words, replace the lines shown highlighted below:

.. code-block:: yaml
    :emphasize-lines: 2,3

    # OS X.
    compiler.path.cc.DARWIN.OVERWRITE: "gcc-5"
    compiler.path.as.DARWIN.OVERWRITE: "gcc-5"
    compiler.path.objdump.DARWIN.OVERWRITE: "gobjdump"
    compiler.path.objsize.DARWIN.OVERWRITE: "objsize"
    compiler.path.objcopy.DARWIN.OVERWRITE: "gobjcopy"

...with the following:

.. code-block:: yaml

    compiler.path.cc.DARWIN.OVERWRITE: "gcc-8"
    compiler.path.as.DARWIN.OVERWRITE: "gcc-8”

In case you wish to use Clang, you can change your
``<mynewt-src-directory>/repos/apache-mynewt-core/compiler/sim/compiler.yml``
to use Clang. Delete the gcc-5 ``DARWIN.OVERWRITE`` lines highlighted below.

.. code-block:: yaml
    :emphasize-lines: 2,3

    # OS X.
    compiler.path.cc.DARWIN.OVERWRITE: "gcc-5"
    compiler.path.as.DARWIN.OVERWRITE: "gcc-5"
    compiler.path.objdump.DARWIN.OVERWRITE: "gobjdump"
    compiler.path.objsize.DARWIN.OVERWRITE: "objsize"
    compiler.path.objcopy.DARWIN.OVERWRITE: "gobjcopy"

**NOTE:** Both the newer GCC versions and Clang report a few warnings but
they can be ignored.

**FURTHER NOTE:** Mynewt developers mostly use GCC 5.x for sim builds;
so it may take a little while to fix issues reported by the newer
compiler. One option is to **disable warnings**. To do that, remove the
``-Werror`` flag as an option for the compiler in the
``<mynewt-src-directory>/repos/apache-mynewt-core/compiler/sim/compiler.yml``
file as shown below.

.. code-block:: yaml
    :emphasize-lines: 2

    compiler.flags.base: >
        -m32 -Wall -ggdb

You may alternatively choose to **specify the precise warnings to
ignore** depending on the error thrown by the compiler. For example, if
you see a ``[-Werror=misleading-indentation]`` error while building the
sim image, add ``-Wno-misleading-indentation]`` as a compiler flag in
the same line from the
``<mynewt-src-directory>/repos/apache-mynewt-core/compiler/sim/compiler.yml``
file.

.. code-block:: yaml
    :emphasize-lines: 2

    compiler.flags.base: >
        -m32 -Wall -Werror -ggdb -Wno-misleading-indentation

A third option is to simply **downgrade to GCC 5.x**:

.. code-block:: console

    $ brew install gcc@5

Note that Homebrew will no longer install GCC 5.x on macOS 10.13 and newer:

.. code-block:: console

    $ brew install gcc@5
    gcc@5: This formula either does not compile or function as expected on macOS
    versions newer than High Sierra due to an upstream incompatibility.
    Error: An unsatisfied requirement failed this build.

In this case, you might try downgrading to GCC 6.x, which is still available:

.. code-block:: console

    $ brew install gcc@6

Installing GDB
~~~~~~~~~~~~~~

.. code-block:: console

    $ brew install gdb
    ...
    ...
    ==> Summary
    🍺  /usr/local/Cellar/gdb/7.10.1: XXX files,YYM

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
