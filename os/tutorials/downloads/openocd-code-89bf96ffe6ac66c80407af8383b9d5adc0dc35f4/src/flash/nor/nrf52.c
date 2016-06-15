/***************************************************************************
 *   Copyright (C) 2013 Synapse Product Development                        *
 *   Andrey Smirnov <andrew.smironv@...>                             *
 *   Angus Gratton <gus@...>                                    *
 *   Erdem U. Altunyurt <spamjunkeater@...>                          *
 *                                                                         *
 *   Ported nrf51 flash driver to the nrf52 Copyright (C) 2016             *
 *   by Job Vranish <jvranish@...>                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "imp.h"
#include <target/algorithm.h>
#include <target/armv7m.h>
#include <helper/types.h>

enum {
  NRF52_FLASH_BASE = 0x00000000,
};

enum nrf52_ficr_registers {
  NRF52_FICR_BASE = 0x10000000, /* Factory Information Configuration Registers */

#define NRF52_FICR_REG(offset) (NRF52_FICR_BASE + offset)

  NRF52_FICR_CODEPAGESIZE   = NRF52_FICR_REG(0x010),
  NRF52_FICR_CODESIZE   = NRF52_FICR_REG(0x014),
  NRF52_FICR_CLENR0   = NRF52_FICR_REG(0x028),
  NRF52_FICR_PPFC     = NRF52_FICR_REG(0x02C),
  NRF52_FICR_NUMRAMBLOCK    = NRF52_FICR_REG(0x034),
  NRF52_FICR_SIZERAMBLOCK0  = NRF52_FICR_REG(0x038),
  NRF52_FICR_SIZERAMBLOCK1  = NRF52_FICR_REG(0x03C),
  NRF52_FICR_SIZERAMBLOCK2  = NRF52_FICR_REG(0x040),
  NRF52_FICR_SIZERAMBLOCK3  = NRF52_FICR_REG(0x044),
  NRF52_FICR_CONFIGID   = NRF52_FICR_REG(0x05C),
  NRF52_FICR_DEVICEID0    = NRF52_FICR_REG(0x060),
  NRF52_FICR_DEVICEID1    = NRF52_FICR_REG(0x064),
  NRF52_FICR_ER0      = NRF52_FICR_REG(0x080),
  NRF52_FICR_ER1      = NRF52_FICR_REG(0x084),
  NRF52_FICR_ER2      = NRF52_FICR_REG(0x088),
  NRF52_FICR_ER3      = NRF52_FICR_REG(0x08C),
  NRF52_FICR_IR0      = NRF52_FICR_REG(0x090),
  NRF52_FICR_IR1      = NRF52_FICR_REG(0x094),
  NRF52_FICR_IR2      = NRF52_FICR_REG(0x098),
  NRF52_FICR_IR3      = NRF52_FICR_REG(0x09C),
  NRF52_FICR_DEVICEADDRTYPE = NRF52_FICR_REG(0x0A0),
  NRF52_FICR_DEVICEADDR0    = NRF52_FICR_REG(0x0A4),
  NRF52_FICR_DEVICEADDR1    = NRF52_FICR_REG(0x0A8),
};

enum nrf52_uicr_registers {
  NRF52_UICR_BASE = 0x10001000, /* User Information
               * Configuration Regsters */

  NRF52_UICR_SIZE = 0x100,

#define NRF52_UICR_REG(offset) (NRF52_UICR_BASE + offset)

  NRF52_UICR_CLENR0 = NRF52_UICR_REG(0x000),
  NRF52_UICR_RBPCONF  = NRF52_UICR_REG(0x004),
  NRF52_UICR_XTALFREQ = NRF52_UICR_REG(0x008),
  NRF52_UICR_FWID   = NRF52_UICR_REG(0x010),
};

enum nrf52_nvmc_registers {
  NRF52_NVMC_BASE = 0x4001E000, /* Non-Volatile Memory
               * Controller Regsters */

#define NRF52_NVMC_REG(offset) (NRF52_NVMC_BASE + offset)

  NRF52_NVMC_READY  = NRF52_NVMC_REG(0x400),
  NRF52_NVMC_CONFIG = NRF52_NVMC_REG(0x504),
  NRF52_NVMC_ERASEPAGE  = NRF52_NVMC_REG(0x508),
  NRF52_NVMC_ERASEALL = NRF52_NVMC_REG(0x50C),
  NRF52_NVMC_ERASEUICR  = NRF52_NVMC_REG(0x514),
};

enum nrf52_nvmc_config_bits {
  NRF52_NVMC_CONFIG_REN = 0x00,
  NRF52_NVMC_CONFIG_WEN = 0x01,
  NRF52_NVMC_CONFIG_EEN = 0x02,

};

struct nrf52_info {
  uint32_t code_page_size;
  uint32_t code_memory_size;

  struct {
    bool probed;
    int (*write) (struct flash_bank *bank,
            struct nrf52_info *chip,
            const uint8_t *buffer, uint32_t offset, uint32_t count);
  } bank[2];
  struct target *target;
};

struct nrf52_device_spec {
  uint16_t hwid;
  // The following two fields are informational only
  const char *variant;
  const char *build_code;
  // This is used to verify flash size read from device registers matches
  //  what's expected
  unsigned int flash_size_kb;
};

static const struct nrf52_device_spec nrf52_known_devices_table[] = {
  {
    .hwid   = 0x0053,
    .variant  = "QFAA",
    .build_code = "AA",
    .flash_size_kb  = 512,
  },
};

static int nrf52_bank_is_probed(struct flash_bank *bank)
{
  struct nrf52_info *chip = bank->driver_priv;

  assert(chip != NULL);

  return chip->bank[bank->bank_number].probed;
}
static int nrf52_probe(struct flash_bank *bank);

static int nrf52_get_probed_chip_if_halted(struct flash_bank *bank, struct nrf52_info **chip)
{
  if (bank->target->state != TARGET_HALTED) {
    LOG_ERROR("Target not halted");
    return ERROR_TARGET_NOT_HALTED;
  }

  *chip = bank->driver_priv;

  int probed = nrf52_bank_is_probed(bank);
  if (probed < 0)
    return probed;
  else if (!probed)
    return nrf52_probe(bank);
  else
    return ERROR_OK;
}

static int nrf52_wait_for_nvmc(struct nrf52_info *chip)
{
  uint32_t ready;
  int res;
  int timeout = 100;

  do {
    res = target_read_u32(chip->target, NRF52_NVMC_READY, &ready);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't read NVMC_READY register");
      return res;
    }

    if (ready == 0x00000001)
      return ERROR_OK;

    alive_sleep(1);
  } while (timeout--);

  LOG_DEBUG("Timed out waiting for NVMC_READY");
  return ERROR_FLASH_BUSY;
}

static int nrf52_nvmc_erase_enable(struct nrf52_info *chip)
{
  int res;
  res = target_write_u32(chip->target,
             NRF52_NVMC_CONFIG,
             NRF52_NVMC_CONFIG_EEN);

  if (res != ERROR_OK) {
    LOG_ERROR("Failed to enable erase operation");
    return res;
  }

  /*
    According to NVMC examples in Nordic SDK busy status must be
    checked after writing to NVMC_CONFIG
   */
  res = nrf52_wait_for_nvmc(chip);
  if (res != ERROR_OK)
    LOG_ERROR("Erase enable did not complete");

  return res;
}

static int nrf52_nvmc_write_enable(struct nrf52_info *chip)
{
  int res;
  res = target_write_u32(chip->target,
             NRF52_NVMC_CONFIG,
             NRF52_NVMC_CONFIG_WEN);

  if (res != ERROR_OK) {
    LOG_ERROR("Failed to enable write operation");
    return res;
  }

  /*
    According to NVMC examples in Nordic SDK busy status must be
    checked after writing to NVMC_CONFIG
   */
  res = nrf52_wait_for_nvmc(chip);
  if (res != ERROR_OK)
    LOG_ERROR("Write enable did not complete");

  return res;
}

static int nrf52_nvmc_read_only(struct nrf52_info *chip)
{
  int res;
  res = target_write_u32(chip->target,
             NRF52_NVMC_CONFIG,
             NRF52_NVMC_CONFIG_REN);

  if (res != ERROR_OK) {
    LOG_ERROR("Failed to enable read-only operation");
    return res;
  }
  /*
    According to NVMC examples in Nordic SDK busy status must be
    checked after writing to NVMC_CONFIG
   */
  res = nrf52_wait_for_nvmc(chip);
  if (res != ERROR_OK)
    LOG_ERROR("Read only enable did not complete");

  return res;
}

static int nrf52_nvmc_generic_erase(struct nrf52_info *chip,
             uint32_t erase_register, uint32_t erase_value)
{
  int res;

  res = nrf52_nvmc_erase_enable(chip);
  if (res != ERROR_OK)
    goto error;

  res = target_write_u32(chip->target,
             erase_register,
             erase_value);
  if (res != ERROR_OK)
    goto set_read_only;

  res = nrf52_wait_for_nvmc(chip);
  if (res != ERROR_OK)
    goto set_read_only;

  return nrf52_nvmc_read_only(chip);

set_read_only:
  nrf52_nvmc_read_only(chip);
error:
  LOG_ERROR("Failed to erase reg: 0x%08"PRIx32" val: 0x%08"PRIx32,
      erase_register, erase_value);
  return ERROR_FAIL;
}

static int nrf52_protect_check(struct flash_bank *bank)
{
  int res;
  uint32_t clenr0;

  /* UICR cannot be write protected so just return early */
  if (bank->base == NRF52_UICR_BASE)
    return ERROR_OK;

  struct nrf52_info *chip = bank->driver_priv;

  assert(chip != NULL);

  res = target_read_u32(chip->target, NRF52_FICR_CLENR0,
            &clenr0);
  if (res != ERROR_OK) {
    LOG_ERROR("Couldn't read code region 0 size[FICR]");
    return res;
  }

  if (clenr0 == 0xFFFFFFFF) {
    res = target_read_u32(chip->target, NRF52_UICR_CLENR0,
              &clenr0);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't read code region 0 size[UICR]");
      return res;
    }
  }

  for (int i = 0; i < bank->num_sectors; i++)
    bank->sectors[i].is_protected =
      clenr0 != 0xFFFFFFFF && bank->sectors[i].offset < clenr0;

  return ERROR_OK;
}

static int nrf52_protect(struct flash_bank *bank, int set, int first, int last)
{
  int res;
  uint32_t clenr0, ppfc;
  struct nrf52_info *chip;

  /* UICR cannot be write protected so just bail out early */
  if (bank->base == NRF52_UICR_BASE)
    return ERROR_FAIL;

  res = nrf52_get_probed_chip_if_halted(bank, &chip);
  if (res != ERROR_OK)
    return res;

  if (first != 0) {
    LOG_ERROR("Code region 0 must start at the begining of the bank");
    return ERROR_FAIL;
  }

  res = target_read_u32(chip->target, NRF52_FICR_PPFC,
            &ppfc);
  if (res != ERROR_OK) {
    LOG_ERROR("Couldn't read PPFC register");
    return res;
  }

  if ((ppfc & 0xFF) == 0x00) {
    LOG_ERROR("Code region 0 size was pre-programmed at the factory, can't change flash protection settings");
    return ERROR_FAIL;
  };

  res = target_read_u32(chip->target, NRF52_UICR_CLENR0,
            &clenr0);
  if (res != ERROR_OK) {
    LOG_ERROR("Couldn't read code region 0 size[UICR]");
    return res;
  }

  if (clenr0 == 0xFFFFFFFF) {
    res = target_write_u32(chip->target, NRF52_UICR_CLENR0,
               clenr0);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't write code region 0 size[UICR]");
      return res;
    }

  } else {
    LOG_ERROR("You need to perform chip erase before changing the protection settings");
  }

  nrf52_protect_check(bank);

  return ERROR_OK;
}

static int nrf52_probe(struct flash_bank *bank)
{
  uint32_t hwid;
  int res;
  struct nrf52_info *chip = bank->driver_priv;

  res = target_read_u32(chip->target, NRF52_FICR_CONFIGID, &hwid);
  if (res != ERROR_OK) {
    LOG_ERROR("Couldn't read CONFIGID register");
    return res;
  }

  hwid &= 0xFFFF; /* HWID is stored in the lower two
       * bytes of the CONFIGID register */

  const struct nrf52_device_spec *spec = NULL;
  for (size_t i = 0; i < ARRAY_SIZE(nrf52_known_devices_table); i++)
    if (hwid == nrf52_known_devices_table[i].hwid) {
      spec = &nrf52_known_devices_table[i];
      break;
    }

  if (!chip->bank[0].probed && !chip->bank[1].probed) {
    if (spec)
      LOG_INFO("nRF51822-%s(build code: %s) %ukB Flash",
         spec->variant, spec->build_code, spec->flash_size_kb);
    else
      LOG_WARNING("Unknown device (HWID 0x%08" PRIx32 ")", hwid);
  }


  if (bank->base == NRF52_FLASH_BASE) {
    res = target_read_u32(chip->target, NRF52_FICR_CODEPAGESIZE,
              &chip->code_page_size);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't read code page size");
      return res;
    }

    res = target_read_u32(chip->target, NRF52_FICR_CODESIZE,
              &chip->code_memory_size);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't read code memory size");
      return res;
    }

    bank->size = chip->code_memory_size * chip->code_page_size;
    bank->num_sectors = bank->size / chip->code_page_size;
    bank->sectors = calloc(bank->num_sectors,
               sizeof((bank->sectors)[0]));
    if (!bank->sectors)
      return ERROR_FLASH_BANK_NOT_PROBED;

    unsigned int code_memory_size_kb = bank->size / 1024;

    if (spec && code_memory_size_kb != spec->flash_size_kb) {
      LOG_INFO("Chip's reported Flash capacity (%ukB) di not match expected one (%ukB)", code_memory_size_kb, spec->flash_size_kb);
      return ERROR_FAIL;
    }

    /* Fill out the sector information: all NRF51 sectors are the same size and
     * there is always a fixed number of them. */
    for (int i = 0; i < bank->num_sectors; i++) {
      bank->sectors[i].size = chip->code_page_size;
      bank->sectors[i].offset = i * chip->code_page_size;

      /* mark as unknown */
      bank->sectors[i].is_erased = -1;
      bank->sectors[i].is_protected = -1;
    }

    nrf52_protect_check(bank);

    chip->bank[0].probed = true;
  } else {
    bank->size = NRF52_UICR_SIZE;
    bank->num_sectors = 1;
    bank->sectors = calloc(bank->num_sectors,
               sizeof((bank->sectors)[0]));
    if (!bank->sectors)
      return ERROR_FLASH_BANK_NOT_PROBED;

    bank->sectors[0].size = bank->size;
    bank->sectors[0].offset = 0;

    /* mark as unknown */
    bank->sectors[0].is_erased = 0;
    bank->sectors[0].is_protected = 0;

    chip->bank[1].probed = true;
  }

  return ERROR_OK;
}

static int nrf52_auto_probe(struct flash_bank *bank)
{
  int probed = nrf52_bank_is_probed(bank);

  if (probed < 0)
    return probed;
  else if (probed)
    return ERROR_OK;
  else
    return nrf52_probe(bank);
}

static struct flash_sector *nrf52_find_sector_by_address(struct flash_bank *bank, uint32_t address)
{
  struct nrf52_info *chip = bank->driver_priv;

  for (int i = 0; i < bank->num_sectors; i++)
    if (bank->sectors[i].offset <= address &&
        address < (bank->sectors[i].offset + chip->code_page_size))
      return &bank->sectors[i];
  return NULL;
}

static int nrf52_erase_all(struct nrf52_info *chip)
{
  LOG_DEBUG("Erasing all non-volatile memory");
  return nrf52_nvmc_generic_erase(chip,
          NRF52_NVMC_ERASEALL,
          0x00000001);
}

static int nrf52_erase_page(struct flash_bank *bank,
              struct nrf52_info *chip,
              struct flash_sector *sector)
{
  int res;

  LOG_DEBUG("Erasing page at 0x%"PRIx32, sector->offset);
  if (sector->is_protected) {
    LOG_ERROR("Cannot erase protected sector at 0x%" PRIx32, sector->offset);
    return ERROR_FAIL;
  }

  if (bank->base == NRF52_UICR_BASE) {
    uint32_t ppfc;
    res = target_read_u32(chip->target, NRF52_FICR_PPFC,
              &ppfc);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't read PPFC register");
      return res;
    }

    if ((ppfc & 0xFF) == 0xFF) {
      /* We can't erase the UICR.  Double-check to
         see if it's already erased before complaining. */
      default_flash_blank_check(bank);
      if (sector->is_erased == 1)
        return ERROR_OK;

      LOG_ERROR("The chip was not pre-programmed with SoftDevice stack and UICR cannot be erased separately. Please issue mass erase before trying to write to this region");
      return ERROR_FAIL;
    };

    res = nrf52_nvmc_generic_erase(chip,
                 NRF52_NVMC_ERASEUICR,
                 0x00000001);


  } else {
    res = nrf52_nvmc_generic_erase(chip,
                 NRF52_NVMC_ERASEPAGE,
                 sector->offset);
  }

  if (res == ERROR_OK)
    sector->is_erased = 1;

  return res;
}

static const uint8_t nrf52_flash_write_code[] = {
  /* See contrib/loaders/flash/cortex-m0.S */
/* <wait_fifo>: */
  0x0d, 0x68,   /* ldr  r5, [r1,  #0] */
  0x00, 0x2d,   /* cmp  r5, #0 */
  0x0b, 0xd0,   /* beq.n  1e <exit> */
  0x4c, 0x68,   /* ldr  r4, [r1,  #4] */
  0xac, 0x42,   /* cmp  r4, r5 */
  0xf9, 0xd0,   /* beq.n  0 <wait_fifo> */
  0x20, 0xcc,   /* ldmia  r4!,  {r5} */
  0x20, 0xc3,   /* stmia  r3!,  {r5} */
  0x94, 0x42,   /* cmp  r4, r2 */
  0x01, 0xd3,   /* bcc.n  18 <no_wrap> */
  0x0c, 0x46,   /* mov  r4, r1 */
  0x08, 0x34,   /* adds r4, #8 */
/* <no_wrap>: */
  0x4c, 0x60,   /* str  r4, [r1,  #4] */
  0x04, 0x38,   /* subs r0, #4 */
  0xf0, 0xd1,   /* bne.n  0 <wait_fifo> */
/* <exit>: */
  0x00, 0xbe    /* bkpt 0x0000 */
};


/* Start a low level flash write for the specified region */
static int nrf52_ll_flash_write(struct nrf52_info *chip, uint32_t offset, const uint8_t *buffer, uint32_t bytes)
{
  struct target *target = chip->target;
  uint32_t buffer_size = 8192;
  struct working_area *write_algorithm;
  struct working_area *source;
  uint32_t address = NRF52_FLASH_BASE + offset;
  struct reg_param reg_params[4];
  struct armv7m_algorithm armv7m_info;
  int retval = ERROR_OK;


  LOG_DEBUG("Writing buffer to flash offset=0x%"PRIx32" bytes=0x%"PRIx32, offset, bytes);
  assert(bytes % 4 == 0);

  /* allocate working area with flash programming code */
  if (target_alloc_working_area(target, sizeof(nrf52_flash_write_code),
      &write_algorithm) != ERROR_OK) {
    LOG_WARNING("no working area available, falling back to slow memory writes");

    for (; bytes > 0; bytes -= 4) {
      retval = target_write_memory(chip->target, offset, 4, 1, buffer);
      if (retval != ERROR_OK)
        return retval;

      retval = nrf52_wait_for_nvmc(chip);
      if (retval != ERROR_OK)
        return retval;

      offset += 4;
      buffer += 4;
    }

    return ERROR_OK;
  }

  LOG_WARNING("using fast async flash loader. This is currently supported");
  LOG_WARNING("only with ST-Link and CMSIS-DAP. If you have issues, add");
  LOG_WARNING("\"set WORKAREASIZE 0\" before sourcing nrf52.cfg to disable it");

  retval = target_write_buffer(target, write_algorithm->address,
        sizeof(nrf52_flash_write_code),
        nrf52_flash_write_code);
  if (retval != ERROR_OK)
    return retval;

  /* memory buffer */
  while (target_alloc_working_area(target, buffer_size, &source) != ERROR_OK) {
    buffer_size /= 2;
    buffer_size &= ~3UL; /* Make sure it's 4 byte aligned */
    if (buffer_size <= 256) {
      /* free working area, write algorithm already allocated */
      target_free_working_area(target, write_algorithm);

      LOG_WARNING("No large enough working area available, can't do block memory writes");
      return ERROR_TARGET_RESOURCE_NOT_AVAILABLE;
    }
  }

  armv7m_info.common_magic = ARMV7M_COMMON_MAGIC;
  armv7m_info.core_mode = ARM_MODE_THREAD;

  init_reg_param(&reg_params[0], "r0", 32, PARAM_IN_OUT); /* byte count */
  init_reg_param(&reg_params[1], "r1", 32, PARAM_OUT);  /* buffer start */
  init_reg_param(&reg_params[2], "r2", 32, PARAM_OUT);  /* buffer end */
  init_reg_param(&reg_params[3], "r3", 32, PARAM_IN_OUT); /* target address */

  buf_set_u32(reg_params[0].value, 0, 32, bytes);
  buf_set_u32(reg_params[1].value, 0, 32, source->address);
  buf_set_u32(reg_params[2].value, 0, 32, source->address + source->size);
  buf_set_u32(reg_params[3].value, 0, 32, address);

  retval = target_run_flash_async_algorithm(target, buffer, bytes/4, 4,
      0, NULL,
      4, reg_params,
      source->address, source->size,
      write_algorithm->address, 0,
      &armv7m_info);

  target_free_working_area(target, source);
  target_free_working_area(target, write_algorithm);

  destroy_reg_param(&reg_params[0]);
  destroy_reg_param(&reg_params[1]);
  destroy_reg_param(&reg_params[2]);
  destroy_reg_param(&reg_params[3]);

  return retval;
}

/* Check and erase flash sectors in specified range then start a low level page write.
   start/end must be sector aligned.
*/
static int nrf52_write_pages(struct flash_bank *bank, uint32_t start, uint32_t end, const uint8_t *buffer)
{
  int res = ERROR_FAIL;
  struct nrf52_info *chip = bank->driver_priv;
  struct flash_sector *sector;
  uint32_t offset;

  assert(start % chip->code_page_size == 0);
  assert(end % chip->code_page_size == 0);

  /* Erase all sectors */
  for (offset = start; offset < end; offset += chip->code_page_size) {
    sector = nrf52_find_sector_by_address(bank, offset);
    if (!sector) {
      LOG_ERROR("Invalid sector @ 0x%08"PRIx32, offset);
      return ERROR_FLASH_SECTOR_INVALID;
    }

    if (sector->is_protected) {
      LOG_ERROR("Can't erase protected sector @ 0x%08"PRIx32, offset);
      goto error;
    }

    if (sector->is_erased != 1) { /* 1 = erased, 0= not erased, -1 = unknown */
      res = nrf52_erase_page(bank, chip, sector);
      if (res != ERROR_OK) {
        LOG_ERROR("Failed to erase sector @ 0x%08"PRIx32, sector->offset);
        goto error;
      }
    }
    sector->is_erased = 0;
  }

  res = nrf52_nvmc_write_enable(chip);
  if (res != ERROR_OK)
    goto error;

  res = nrf52_ll_flash_write(chip, start, buffer, (end - start));
  if (res != ERROR_OK)
    goto set_read_only;

  return nrf52_nvmc_read_only(chip);

set_read_only:
  nrf52_nvmc_read_only(chip);
error:
  LOG_ERROR("Failed to write to nrf52 flash");
  return res;
}

static int nrf52_erase(struct flash_bank *bank, int first, int last)
{
  int res;
  struct nrf52_info *chip;

  res = nrf52_get_probed_chip_if_halted(bank, &chip);
  if (res != ERROR_OK)
    return res;

  /* For each sector to be erased */
  for (int s = first; s <= last && res == ERROR_OK; s++)
    res = nrf52_erase_page(bank, chip, &bank->sectors[s]);

  return res;
}

static int nrf52_code_flash_write(struct flash_bank *bank,
          struct nrf52_info *chip,
          const uint8_t *buffer, uint32_t offset, uint32_t count)
{

  int res;
  /* Need to perform reads to fill any gaps we need to preserve in the first page,
     before the start of buffer, or in the last page, after the end of buffer */
  uint32_t first_page = offset/chip->code_page_size;
  uint32_t last_page = DIV_ROUND_UP(offset+count, chip->code_page_size);

  uint32_t first_page_offset = first_page * chip->code_page_size;
  uint32_t last_page_offset = last_page * chip->code_page_size;

  LOG_DEBUG("Padding write from 0x%08"PRIx32"-0x%08"PRIx32" as 0x%08"PRIx32"-0x%08"PRIx32,
    offset, offset+count, first_page_offset, last_page_offset);

  uint32_t page_cnt = last_page - first_page;
  uint8_t buffer_to_flash[page_cnt*chip->code_page_size];

  /* Fill in any space between start of first page and start of buffer */
  uint32_t pre = offset - first_page_offset;
  if (pre > 0) {
    res = target_read_memory(bank->target,
          first_page_offset,
          1,
          pre,
          buffer_to_flash);
    if (res != ERROR_OK)
      return res;
  }

  /* Fill in main contents of buffer */
  memcpy(buffer_to_flash+pre, buffer, count);

  /* Fill in any space between end of buffer and end of last page */
  uint32_t post = last_page_offset - (offset+count);
  if (post > 0) {
    /* Retrieve the full row contents from Flash */
    res = target_read_memory(bank->target,
          offset + count,
          1,
          post,
          buffer_to_flash+pre+count);
    if (res != ERROR_OK)
      return res;
  }

  return nrf52_write_pages(bank, first_page_offset, last_page_offset, buffer_to_flash);
}

static int nrf52_uicr_flash_write(struct flash_bank *bank,
          struct nrf52_info *chip,
          const uint8_t *buffer, uint32_t offset, uint32_t count)
{
  int res;
  uint8_t uicr[NRF52_UICR_SIZE];
  struct flash_sector *sector = &bank->sectors[0];

  if ((offset + count) > NRF52_UICR_SIZE)
    return ERROR_FAIL;

  res = target_read_memory(bank->target,
         NRF52_UICR_BASE,
         1,
         NRF52_UICR_SIZE,
         uicr);

  if (res != ERROR_OK)
    return res;

  if (sector->is_erased != 1) {
    res = nrf52_erase_page(bank, chip, sector);
    if (res != ERROR_OK)
      return res;
  }

  res = nrf52_nvmc_write_enable(chip);
  if (res != ERROR_OK)
    return res;

  memcpy(&uicr[offset], buffer, count);

  res = nrf52_ll_flash_write(chip, NRF52_UICR_BASE, uicr, NRF52_UICR_SIZE);
  if (res != ERROR_OK) {
    nrf52_nvmc_read_only(chip);
    return res;
  }

  return nrf52_nvmc_read_only(chip);
}


static int nrf52_write(struct flash_bank *bank, const uint8_t *buffer,
           uint32_t offset, uint32_t count)
{
  int res;
  struct nrf52_info *chip;

  res = nrf52_get_probed_chip_if_halted(bank, &chip);
  if (res != ERROR_OK)
    return res;

  return chip->bank[bank->bank_number].write(bank, chip, buffer, offset, count);
}


FLASH_BANK_COMMAND_HANDLER(nrf52_flash_bank_command)
{
  static struct nrf52_info *chip;

  switch (bank->base) {
  case NRF52_FLASH_BASE:
    bank->bank_number = 0;
    break;
  case NRF52_UICR_BASE:
    bank->bank_number = 1;
    break;
  default:
    LOG_ERROR("Invalid bank address 0x%08" PRIx32, bank->base);
    return ERROR_FAIL;
  }

  if (!chip) {
    /* Create a new chip */
    chip = calloc(1, sizeof(*chip));
    if (!chip)
      return ERROR_FAIL;

    chip->target = bank->target;
  }

  switch (bank->base) {
  case NRF52_FLASH_BASE:
    chip->bank[bank->bank_number].write = nrf52_code_flash_write;
    break;
  case NRF52_UICR_BASE:
    chip->bank[bank->bank_number].write = nrf52_uicr_flash_write;
    break;
  }

  chip->bank[bank->bank_number].probed = false;
  bank->driver_priv = chip;

  return ERROR_OK;
}

COMMAND_HANDLER(nrf52_handle_mass_erase_command)
{
  int res;
  struct flash_bank *bank = NULL;
  struct target *target = get_current_target(CMD_CTX);

  res = get_flash_bank_by_addr(target, NRF52_FLASH_BASE, true, &bank);
  if (res != ERROR_OK)
    return res;

  assert(bank != NULL);

  struct nrf52_info *chip;

  res = nrf52_get_probed_chip_if_halted(bank, &chip);
  if (res != ERROR_OK)
    return res;

  uint32_t ppfc;

  res = target_read_u32(target, NRF52_FICR_PPFC,
            &ppfc);
  if (res != ERROR_OK) {
    LOG_ERROR("Couldn't read PPFC register");
    return res;
  }

  if ((ppfc & 0xFF) == 0x00) {
    LOG_ERROR("Code region 0 size was pre-programmed at the factory, "
        "mass erase command won't work.");
    return ERROR_FAIL;
  };

  res = nrf52_erase_all(chip);
  if (res != ERROR_OK) {
    LOG_ERROR("Failed to erase the chip");
    nrf52_protect_check(bank);
    return res;
  }

  for (int i = 0; i < bank->num_sectors; i++)
    bank->sectors[i].is_erased = 1;

  res = nrf52_protect_check(bank);
  if (res != ERROR_OK) {
    LOG_ERROR("Failed to check chip's write protection");
    return res;
  }

  res = get_flash_bank_by_addr(target, NRF52_UICR_BASE, true, &bank);
  if (res != ERROR_OK)
    return res;

  bank->sectors[0].is_erased = 1;

  return ERROR_OK;
}

static int nrf52_info(struct flash_bank *bank, char *buf, int buf_size)
{
  int res;

  struct nrf52_info *chip;

  res = nrf52_get_probed_chip_if_halted(bank, &chip);
  if (res != ERROR_OK)
    return res;

  static struct {
    const uint32_t address;
    uint32_t value;
  } ficr[] = {
    { .address = NRF52_FICR_CODEPAGESIZE  },
    { .address = NRF52_FICR_CODESIZE  },
    { .address = NRF52_FICR_CLENR0    },
    { .address = NRF52_FICR_PPFC    },
    { .address = NRF52_FICR_NUMRAMBLOCK },
    { .address = NRF52_FICR_SIZERAMBLOCK0 },
    { .address = NRF52_FICR_SIZERAMBLOCK1 },
    { .address = NRF52_FICR_SIZERAMBLOCK2 },
    { .address = NRF52_FICR_SIZERAMBLOCK3 },
    { .address = NRF52_FICR_CONFIGID  },
    { .address = NRF52_FICR_DEVICEID0 },
    { .address = NRF52_FICR_DEVICEID1 },
    { .address = NRF52_FICR_ER0   },
    { .address = NRF52_FICR_ER1   },
    { .address = NRF52_FICR_ER2   },
    { .address = NRF52_FICR_ER3   },
    { .address = NRF52_FICR_IR0   },
    { .address = NRF52_FICR_IR1   },
    { .address = NRF52_FICR_IR2   },
    { .address = NRF52_FICR_IR3   },
    { .address = NRF52_FICR_DEVICEADDRTYPE  },
    { .address = NRF52_FICR_DEVICEADDR0 },
    { .address = NRF52_FICR_DEVICEADDR1 },
  };

  for (size_t i = 0; i < ARRAY_SIZE(ficr); i++) {
    res = target_read_u32(chip->target, ficr[i].address,
              &ficr[i].value);
    if (res != ERROR_OK) {
      LOG_ERROR("Couldn't read %" PRIx32, ficr[i].address);
      return res;
    }
  }

  snprintf(buf, buf_size,
     "\n[factory information control block]\n\n"
     "code page size: %"PRIu32"B\n"
     "code memory size: %"PRIu32"kB\n"
     "code region 0 size: %"PRIu32"kB\n"
     "pre-programmed code: %s\n"
     "number of ram blocks: %"PRIu32"\n"
     "ram block 0 size: %"PRIu32"B\n"
     "ram block 1 size: %"PRIu32"B\n"
     "ram block 2 size: %"PRIu32"B\n"
     "ram block 3 size: %"PRIu32 "B\n"
     "config id: %" PRIx32 "\n"
     "device id: 0x%"PRIx32"%08"PRIx32"\n"
     "encryption root: 0x%08"PRIx32"%08"PRIx32"%08"PRIx32"%08"PRIx32"\n"
     "identity root: 0x%08"PRIx32"%08"PRIx32"%08"PRIx32"%08"PRIx32"\n"
     "device address type: 0x%"PRIx32"\n"
     "device address: 0x%"PRIx32"%08"PRIx32"\n",
     ficr[0].value,
     ficr[1].value,
     (ficr[2].value == 0xFFFFFFFF) ? 0 : ficr[2].value / 1024,
     ((ficr[3].value & 0xFF) == 0x00) ? "present" : "not present",
     ficr[4].value,
     ficr[5].value,
     (ficr[6].value == 0xFFFFFFFF) ? 0 : ficr[6].value,
     (ficr[7].value == 0xFFFFFFFF) ? 0 : ficr[7].value,
     (ficr[8].value == 0xFFFFFFFF) ? 0 : ficr[8].value,
     ficr[9].value,
     ficr[10].value, ficr[11].value,
     ficr[12].value, ficr[13].value, ficr[14].value, ficr[15].value,
     ficr[16].value, ficr[17].value, ficr[18].value, ficr[19].value,
     ficr[20].value,
     ficr[21].value, ficr[22].value);

  return ERROR_OK;
}

static const struct command_registration nrf52_exec_command_handlers[] = {
  {
    .name   = "mass_erase",
    .handler  = nrf52_handle_mass_erase_command,
    .mode   = COMMAND_EXEC,
    .help   = "Erase all flash contents of the chip.",
  },
  COMMAND_REGISTRATION_DONE
};

static const struct command_registration nrf52_command_handlers[] = {
  {
    .name = "nrf52",
    .mode = COMMAND_ANY,
    .help = "nrf52 flash command group",
    .usage  = "",
    .chain  = nrf52_exec_command_handlers,
  },
  COMMAND_REGISTRATION_DONE
};

struct flash_driver nrf52_flash = {
  .name     = "nrf52",
  .commands   = nrf52_command_handlers,
  .flash_bank_command = nrf52_flash_bank_command,
  .info     = nrf52_info,
  .erase      = nrf52_erase,
  .protect    = nrf52_protect,
  .write      = nrf52_write,
  .read     = default_flash_read,
  .probe      = nrf52_probe,
  .auto_probe   = nrf52_auto_probe,
  .erase_check    = default_flash_blank_check,
  .protect_check    = nrf52_protect_check,
};
