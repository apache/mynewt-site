Mynewt FAQ - File System
========================

.. contents::
  :local:
  :depth: 1

``nffs`` Setup
--------------

**Q**: I'm struggling to find any examples for ``nffs``, especially how do I setup the ``nffs_area_desc`` correctly. 
Where do I set it up in the BSP especially?

**A**: It’s all taken care of in ``nffs_pkg_init``. As long as the ``nffs`` package is included in the project, it 
should initialize itself.  A few things you might find helpful:

1. The ``NFFS_FLASH_AREA`` syscfg setting specifies the flash area that contains the file system.
2. The BSP's ``bsp.yml`` file defines all the flash areas in the system, including the one specified in "1." above.