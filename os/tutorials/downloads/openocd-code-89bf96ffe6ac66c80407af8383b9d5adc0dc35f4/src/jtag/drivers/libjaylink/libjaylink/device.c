/*
 * This file is part of the libjaylink project.
 *
 * Copyright (C) 2014-2015 Marc Schink <jaylink-dev@marcschink.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <libusb.h>

#include "libjaylink.h"
#include "libjaylink-internal.h"

/**
 * @file
 *
 * Device enumeration and handling.
 */

/** @cond PRIVATE */
#define CMD_GET_VERSION		0x01
#define CMD_GET_HW_STATUS	0x07
#define CMD_REGISTER		0x09
#define CMD_GET_HW_INFO		0xc1
#define CMD_GET_FREE_MEMORY	0xd4
#define CMD_GET_CAPS		0xe8
#define CMD_GET_EXT_CAPS	0xed
#define CMD_GET_HW_VERSION	0xf0
#define CMD_READ_CONFIG		0xf2
#define CMD_WRITE_CONFIG	0xf3

#define REG_CMD_REGISTER	0x64
#define REG_CMD_UNREGISTER	0x65

/** Size of the registration header in bytes. */
#define REG_HEADER_SIZE		8
/** Minimum registration information size in bytes. */
#define REG_MIN_SIZE		0x4c
/** Maximum registration information size in bytes. */
#define REG_MAX_SIZE		0x200
/** Size of a connection entry in bytes. */
#define REG_CONN_INFO_SIZE	16
/** @endcond */

/** @private */
JAYLINK_PRIV struct jaylink_device *device_allocate(struct jaylink_context *ctx)
{
	struct jaylink_device *dev;
	struct list *list;

	dev = malloc(sizeof(struct jaylink_device));

	if (!dev)
		return NULL;

	list = list_prepend(ctx->devs, dev);

	if (!list) {
		free(dev);
		return NULL;
	}

	ctx->devs = list;

	dev->ctx = ctx;
	dev->refcnt = 1;
	dev->usb_dev = NULL;

	return dev;
}

/** @private */
static struct jaylink_device_handle *allocate_device_handle(
		struct jaylink_device *dev)
{
	struct jaylink_device_handle *devh;

	devh = malloc(sizeof(struct jaylink_device_handle));

	if (!devh)
		return NULL;

	devh->dev = jaylink_ref_device(dev);

	return devh;
}

/** @private */
static void free_device_handle(struct jaylink_device_handle *devh)
{
	jaylink_unref_device(devh->dev);
	free(devh);
}

/**
 * Get a list of available devices.
 *
 * @param[in,out] ctx libjaylink context.
 * @param[out] devices Newly allocated array which contains instances of
 *                     available devices on success, and undefined on failure.
 *                     The array is NULL-terminated and must be free'd by the
 *                     caller with jaylink_free_device_list().
 *
 * @return The length of the array excluding the trailing NULL-terminator, or a
 *         negative error code on failure.
 */
JAYLINK_API ssize_t jaylink_get_device_list(struct jaylink_context *ctx,
		struct jaylink_device ***devices)
{
	if (!ctx || !devices)
		return JAYLINK_ERR_ARG;

	return discovery_get_device_list(ctx, devices);
}

/**
 * Free a device list.
 *
 * @param[in,out] devices Array of device instances. Must be NULL-terminated.
 * @param[in] unref_devices Determines whether the device instances should be
 *                          unreferenced.
 */
JAYLINK_API void jaylink_free_device_list(struct jaylink_device **devices,
		bool unref_devices)
{
	size_t i;

	if (!devices)
		return;

	if (unref_devices) {
		i = 0;

		while (devices[i]) {
			jaylink_unref_device(devices[i]);
			i++;
		}
	}

	free(devices);
}

/**
 * Get the host interface of a device.
 *
 * @param[in] dev Device instance.
 * @param[out] interface Host interface of the device on success, and undefined
 *                       on failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 */
JAYLINK_API int jaylink_device_get_host_interface(
		const struct jaylink_device *dev,
		enum jaylink_host_interface *interface)
{
	if (!dev || !interface)
		return JAYLINK_ERR_ARG;

	*interface = dev->interface;

	return JAYLINK_OK;
}

/**
 * Get the serial number of a device.
 *
 * @note This serial number is for enumeration purpose only and might differ
 *       from the real serial number of the device.
 *
 * @param[in] dev Device instance.
 * @param[out] serial_number Serial number of the device on success, and
 *                           undefined on failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_NOT_AVAILABLE Serial number is not available.
 */
JAYLINK_API int jaylink_device_get_serial_number(
		const struct jaylink_device *dev, uint32_t *serial_number)
{
	if (!dev || !serial_number)
		return JAYLINK_ERR_ARG;

	if (!dev->valid_serial_number)
		return JAYLINK_ERR_NOT_AVAILABLE;

	*serial_number = dev->serial_number;

	return JAYLINK_OK;
}

/**
 * Get the USB address of a device.
 *
 * @note Identification of a device with the USB address is deprecated and the
 *       serial number should be used instead.
 *
 * @param[in] dev Device instance.
 * @param[out] address USB address of the device on success, and undefined on
 *                     failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_NOT_SUPPORTED Operation not supported.
 *
 * @see jaylink_device_get_serial_number() to get the serial number of a device.
 */
JAYLINK_API int jaylink_device_get_usb_address(const struct jaylink_device *dev,
		enum jaylink_usb_address *address)
{
	if (!dev || !address)
		return JAYLINK_ERR_ARG;

	if (dev->interface != JAYLINK_HIF_USB)
		return JAYLINK_ERR_NOT_SUPPORTED;

	*address = dev->usb_address;

	return JAYLINK_OK;
}

/**
 * Increment the reference count of a device.
 *
 * @param[in,out] dev Device instance.
 *
 * @return The given device instance on success, or NULL for invalid device
 *         instance.
 */
JAYLINK_API struct jaylink_device *jaylink_ref_device(
		struct jaylink_device *dev)
{
	if (!dev)
		return NULL;

	dev->refcnt++;

	return dev;
}

/**
 * Decrement the reference count of a device.
 *
 * @param[in,out] dev Device instance.
 */
JAYLINK_API void jaylink_unref_device(struct jaylink_device *dev)
{
	if (!dev)
		return;

	dev->refcnt--;

	if (dev->refcnt == 0) {
		dev->ctx->devs = list_remove(dev->ctx->devs, dev);

		if (dev->usb_dev)
			libusb_unref_device(dev->usb_dev);

		free(dev);
	}
}

/**
 * Open a device.
 *
 * @param[in,out] dev Device instance.
 * @param[out] devh Newly allocated handle for the opened device on success,
 *                  and undefined on failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR_MALLOC Memory allocation error.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_open(struct jaylink_device *dev,
		struct jaylink_device_handle **devh)
{
	int ret;
	struct jaylink_device_handle *handle;

	if (!dev || !devh)
		return JAYLINK_ERR_ARG;

	handle = allocate_device_handle(dev);

	if (!handle) {
		log_err(dev->ctx, "Device handle malloc failed.");
		return JAYLINK_ERR_MALLOC;
	}

	ret = transport_open(handle);

	if (ret < 0) {
		free_device_handle(handle);
		return ret;
	}

	*devh = handle;

	return JAYLINK_OK;
}

/**
 * Close a device.
 *
 * @param[in,out] devh Device instance.
 */
JAYLINK_API void jaylink_close(struct jaylink_device_handle *devh)
{
	if (!devh)
		return;

	transport_close(devh);
	free_device_handle(devh);
}

/**
 * Get the device instance from a device handle.
 *
 * @note The reference count of the device instance is not increased.
 *
 * @param[in] devh Device handle.
 *
 * @return The device instance on success, or NULL on invalid argument.
 */
JAYLINK_API struct jaylink_device *jaylink_get_device(
		struct jaylink_device_handle *devh)
{
	if (!devh)
		return NULL;

	return devh->dev;
}

/**
 * Retrieve the firmware version of a device.
 *
 * @param[in,out] devh Device handle.
 * @param[out] version Newly allocated string which contains the firmware
 *                     version  on success, and undefined if @p length is zero
 *                     or on failure. The string is null-terminated and must be
 *                     free'd by the caller.
 * @param[out] length Length of the firmware version string including trailing
 *                    null-terminator on success, and undefined on failure.
 *                    Zero if no firmware version string is available.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR_MALLOC Memory allocation error.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_get_firmware_version(struct jaylink_device_handle *devh,
		char **version, size_t *length)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[2];
	uint16_t dummy;
	char *tmp;

	if (!devh || !version || !length)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, 2, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_VERSION;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, buf, 2);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	dummy = buffer_get_u16(buf, 0);
	*length = dummy;

	if (!dummy)
		return JAYLINK_OK;

	ret = transport_start_read(devh, dummy);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_read() failed: %i.", ret);
		return ret;
	}

	tmp = malloc(dummy);

	if (!tmp) {
		log_err(ctx, "Firmware version string malloc failed.");
		return JAYLINK_ERR_MALLOC;
	}

	ret = transport_read(devh, (uint8_t *)tmp, dummy);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		free(tmp);
		return ret;
	}

	/* Last byte is reserved for null-terminator. */
	tmp[dummy - 1] = 0;
	*version = tmp;

	return JAYLINK_OK;
}

/**
 * Retrieve the hardware information of a device.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_GET_HW_INFO capability.
 *
 * @param[in,out] devh Device handle.
 * @param[in] mask A bit field where each set bit represents hardware
 *                 information to request. See #jaylink_hardware_info for a
 *                 description of the hardware information and their bit
 *                 positions.
 * @param[out] info Array to store the hardware information on success. Its
 *                  content is undefined on failure. The array must be large
 *                  enough to contain at least as many elements as bits set in
 *                  @a mask.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_get_hardware_info(struct jaylink_device_handle *devh,
		uint32_t mask, uint32_t *info)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[5];
	unsigned int i;
	unsigned int num;
	unsigned int length;

	if (!devh || !mask || !info)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	num = 0;

	for (i = 0; i < 32; i++) {
		if (mask & (1 << i))
			num++;
	}

	length = num * sizeof(uint32_t);

	ret = transport_start_write_read(devh, 5, length, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_HW_INFO;
	buffer_set_u32(buf, mask, 1);

	ret = transport_write(devh, buf, 5);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, (uint8_t *)info, length);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	for (i = 0; i < num; i++)
		info[i] = buffer_get_u32((uint8_t *)info, i * sizeof(uint32_t));

	return JAYLINK_OK;
}

/**
 * Retrieve the hardware version of a device.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_GET_HW_VERSION capability.
 *
 * @param[in,out] devh Device handle.
 * @param[out] version Hardware version on success, and undefined on failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 *
 * @see jaylink_get_caps() to retrieve device capabilities.
 */
JAYLINK_API int jaylink_get_hardware_version(struct jaylink_device_handle *devh,
		struct jaylink_hardware_version *version)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[4];
	uint32_t tmp;

	if (!devh || !version)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, 4, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_HW_VERSION;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, buf, 4);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	tmp = buffer_get_u32(buf, 0);

	version->type = (tmp / 1000000) % 100;
	version->major = (tmp / 10000) % 100;
	version->minor = (tmp / 100) % 100;
	version->revision = tmp % 100;

	return JAYLINK_OK;
}

/**
 * Retrieve the hardware status of a device.
 *
 * @param[in,out] devh Device handle.
 * @param[out] status Hardware status on success, and undefined on failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_get_hardware_status(struct jaylink_device_handle *devh,
		struct jaylink_hardware_status *status)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[8];

	if (!devh || !status)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, 8, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_HW_STATUS;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, buf, 8);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	status->target_voltage = buffer_get_u16(buf, 0);
	status->tck = buf[2];
	status->tdi = buf[3];
	status->tdo = buf[4];
	status->tms = buf[5];
	status->tres = buf[6];
	status->trst = buf[7];

	return JAYLINK_OK;
}

/**
 * Retrieve the capabilities of a device.
 *
 * The capabilities are stored in a 32-bit bit array consisting of
 * #JAYLINK_DEV_CAPS_SIZE bytes where each individual bit represents a
 * capability. The first bit of this array is the least significant bit of the
 * first byte and the following bits are sequentially numbered in order of
 * increasing bit significance and byte index. A set bit indicates a supported
 * capability. See #jaylink_device_capability for a description of the
 * capabilities and their bit positions.
 *
 * @param[in,out] devh Device handle.
 * @param[out] caps Buffer to store capabilities on success. Its content is
 *                  undefined on failure. The size of the buffer must be large
 *                  enough to contain at least #JAYLINK_DEV_CAPS_SIZE bytes.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 *
 * @see jaylink_get_extended_caps() to retrieve extended device capabilities.
 */
JAYLINK_API int jaylink_get_caps(struct jaylink_device_handle *devh,
		uint8_t *caps)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[1];

	if (!devh || !caps)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, JAYLINK_DEV_CAPS_SIZE, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_CAPS;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, caps, JAYLINK_DEV_CAPS_SIZE);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	return JAYLINK_OK;
}

/**
 * Retrieve the extended capabilities of a device.
 *
 * The extended capabilities are stored in a 256-bit bit array consisting of
 * #JAYLINK_DEV_EXT_CAPS_SIZE bytes. See jaylink_get_caps() for a further
 * description of how the capabilities are represented in this bit array. For a
 * description of the capabilities and their bit positions, see
 * #jaylink_device_capability.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_GET_EXT_CAPS capability.
 *
 * @param[in,out] devh Device handle.
 * @param[out] caps Buffer to store capabilities on success. Its content is
 *                  undefined on failure. The size of the buffer must be large
 *                  enough to contain at least #JAYLINK_DEV_EXT_CAPS_SIZE bytes.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 *
 * @see jaylink_get_caps() to retrieve device capabilities.
 */
JAYLINK_API int jaylink_get_extended_caps(struct jaylink_device_handle *devh,
		uint8_t *caps)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[1];

	if (!devh || !caps)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, JAYLINK_DEV_EXT_CAPS_SIZE,
		true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_EXT_CAPS;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, caps, JAYLINK_DEV_EXT_CAPS_SIZE);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	return JAYLINK_OK;
}

/**
 * Retrieve the size of free memory of a device.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_GET_FREE_MEMORY capability.
 *
 * @param[in,out] devh Device handle.
 * @param[out] size Size of free memory in bytes on success, and undefined on
 *                  failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 *
 * @see jaylink_get_caps() to retrieve device capabilities.
 */
JAYLINK_API int jaylink_get_free_memory(struct jaylink_device_handle *devh,
		uint32_t *size)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[4];

	if (!devh || !size)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, 4, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_GET_FREE_MEMORY;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, buf, 4);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	*size = buffer_get_u32(buf, 0);

	return JAYLINK_OK;
}

/**
 * Read the raw configuration data of a device.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_READ_CONFIG capability.
 *
 * @param[in,out] devh Device handle.
 * @param[out] config Buffer to store configuration data on success. Its
 *                    content is undefined on failure. The size of the buffer
 *                    must be large enough to contain at least
 *                    #JAYLINK_DEV_CONFIG_SIZE bytes.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_read_raw_config(struct jaylink_device_handle *devh,
		uint8_t *config)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[1];

	if (!devh || !config)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 1, JAYLINK_DEV_CONFIG_SIZE,
		true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_READ_CONFIG;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, config, JAYLINK_DEV_CONFIG_SIZE);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	return JAYLINK_OK;
}

/**
 * Write the raw configuration data of a device.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_WRITE_CONFIG capability.
 *
 * @param[in,out] devh Device handle.
 * @param[in] config Buffer to write configuration data from. The size of the
 *                   configuration data is expected to be
 *                   #JAYLINK_DEV_CONFIG_SIZE bytes.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_TIMEOUT A timeout occurred.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_write_raw_config(struct jaylink_device_handle *devh,
		const uint8_t *config)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[1];

	if (!devh || !config)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write(devh, 1 + JAYLINK_DEV_CONFIG_SIZE, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_WRITE_CONFIG;

	ret = transport_write(devh, buf, 1);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_write(devh, config, JAYLINK_DEV_CONFIG_SIZE);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	return JAYLINK_OK;
}

static void parse_conntable(struct jaylink_connection *conns,
		const uint8_t *buffer, uint16_t num, uint16_t entry_size)
{
	unsigned int i;
	size_t offset;

	offset = 0;

	for (i = 0; i < num; i++) {
		conns[i].pid = buffer_get_u32(buffer, offset);
		conns[i].hid = buffer_get_u32(buffer, offset + 4);
		conns[i].iid = buffer[offset + 8];
		conns[i].cid = buffer[offset + 9];
		conns[i].handle = buffer_get_u16(buffer, offset + 10);
		conns[i].timestamp = buffer_get_u32(buffer, offset + 12);
		offset = offset + entry_size;
	}
}

/**
 * Register a connection on a device.
 *
 * A connection can be registered by using 0 as handle. Additional information
 * about the connection can be attached whereby the timestamp is a read-only
 * value and therefore ignored for registration. On success, a new handle
 * greater than 0 is obtained from the device.
 *
 * However, if an obtained handle does not appear in the list of device
 * connections, the connection was not registered because the maximum number of
 * connections on the device is reached.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_REGISTER capability.
 *
 * @param[in,out] devh Device handle.
 * @param[in,out] connection Connection to register on the device.
 * @param[out] connections Array to store device connections on success.
 *                         Its content is undefined on failure. The array must
 *                         be large enough to contain at least
 *                         #JAYLINK_MAX_CONNECTIONS elements.
 * @param[out] info Buffer to store additional information on success, or NULL.
 *                  The content of the buffer is undefined on failure.
 * @param[out] info_size Size of the additional information in bytes on success,
 *                       and undefined on failure. Can be NULL.
 *
 * @return The number of device connections on success, a negative error code on
 *         failure.
 *
 * @see jaylink_unregister() to unregister a connection from a device.
 */
JAYLINK_API int jaylink_register(struct jaylink_device_handle *devh,
		struct jaylink_connection *connection,
		struct jaylink_connection *connections, uint8_t *info,
		uint16_t *info_size)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[REG_MAX_SIZE];
	uint16_t handle;
	uint16_t num;
	uint16_t entry_size;
	uint32_t size;
	uint32_t table_size;
	uint16_t addinfo_size;

	if (!devh || !connection || !connections)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 14, REG_MIN_SIZE, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_REGISTER;
	buf[1] = REG_CMD_REGISTER;
	buffer_set_u32(buf, connection->pid, 2);
	buffer_set_u32(buf, connection->hid, 6);
	buf[10] = connection->iid;
	buf[11] = connection->cid;
	buffer_set_u16(buf, connection->handle, 12);

	ret = transport_write(devh, buf, 14);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, buf, REG_MIN_SIZE);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	handle = buffer_get_u16(buf, 0);
	num = buffer_get_u16(buf, 2);
	entry_size = buffer_get_u16(buf, 4);
	addinfo_size = buffer_get_u16(buf, 6);

	if (num > JAYLINK_MAX_CONNECTIONS) {
		log_err(ctx, "Maximum number of device connections exceeded: "
			"%u.", num);
		return JAYLINK_ERR_PROTO;
	}

	if (entry_size != REG_CONN_INFO_SIZE) {
		log_err(ctx, "Invalid connection entry size: %u bytes.",
			entry_size);
		return JAYLINK_ERR_PROTO;
	}

	table_size = num * entry_size;
	size = REG_HEADER_SIZE + table_size + addinfo_size;

	if (size > REG_MAX_SIZE) {
		log_err(ctx, "Maximum registration information size exceeded: "
			"%u bytes.", size);
		return JAYLINK_ERR_PROTO;
	}

	if (size > REG_MIN_SIZE) {
		ret = transport_start_read(devh, size - REG_MIN_SIZE);

		if (ret != JAYLINK_OK) {
			log_err(ctx, "transport_start_read() failed: %i.", ret);
			return JAYLINK_ERR;
		}

		ret = transport_read(devh, buf + REG_MIN_SIZE,
			size - REG_MIN_SIZE);

		if (ret != JAYLINK_OK) {
			log_err(ctx, "transport_read() failed: %i.", ret);
			return JAYLINK_ERR;
		}
	}

	if (!handle) {
		log_err(ctx, "Obtained invalid connection handle.");
		return JAYLINK_ERR_PROTO;
	}

	connection->handle = handle;
	parse_conntable(connections, buf + REG_HEADER_SIZE, num, entry_size);

	if (info)
		memcpy(info, buf + REG_HEADER_SIZE + table_size, addinfo_size);

	if (info_size)
		*info_size = addinfo_size;

	return num;
}

/**
 * Unregister a connection from a device.
 *
 * @note This function must only be used if the device has the
 *       #JAYLINK_DEV_CAP_REGISTER capability.
 *
 * @param[in,out] devh Device handle.
 * @param[in,out] connection Connection to unregister from the device.
 * @param[out] connections Array to store device connections on success.
 *                         Its content is undefined on failure. The array must
 *                         be large enough to contain at least
 *                         #JAYLINK_MAX_CONNECTIONS elements.
 * @param[out] info Buffer to store additional information on success, or NULL.
 *                  The content of the buffer is undefined on failure.
 * @param[out] info_size Size of the additional information in bytes on success,
 *                       and undefined on failure. Can be NULL.
 *
 * @return The number of device connections on success, a negative error code on
 *         failure.
 */
JAYLINK_API int jaylink_unregister(struct jaylink_device_handle *devh,
		const struct jaylink_connection *connection,
		struct jaylink_connection *connections, uint8_t *info,
		uint16_t *info_size)
{
	int ret;
	struct jaylink_context *ctx;
	uint8_t buf[REG_MAX_SIZE];
	uint16_t num;
	uint16_t entry_size;
	uint32_t size;
	uint32_t table_size;
	uint16_t addinfo_size;

	if (!devh || !connection || !connections)
		return JAYLINK_ERR_ARG;

	ctx = devh->dev->ctx;
	ret = transport_start_write_read(devh, 14, REG_MIN_SIZE, true);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_start_write_read() failed: %i.", ret);
		return ret;
	}

	buf[0] = CMD_REGISTER;
	buf[1] = REG_CMD_UNREGISTER;
	buffer_set_u32(buf, connection->pid, 2);
	buffer_set_u32(buf, connection->hid, 6);
	buf[10] = connection->iid;
	buf[11] = connection->cid;
	buffer_set_u16(buf, connection->handle, 12);

	ret = transport_write(devh, buf, 14);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_write() failed: %i.", ret);
		return ret;
	}

	ret = transport_read(devh, buf, REG_MIN_SIZE);

	if (ret != JAYLINK_OK) {
		log_err(ctx, "transport_read() failed: %i.", ret);
		return ret;
	}

	num = buffer_get_u16(buf, 2);
	entry_size = buffer_get_u16(buf, 4);
	addinfo_size = buffer_get_u16(buf, 6);

	if (num > JAYLINK_MAX_CONNECTIONS) {
		log_err(ctx, "Maximum number of device connections exceeded: "
			"%u.", num);
		return JAYLINK_ERR_PROTO;
	}

	if (entry_size != REG_CONN_INFO_SIZE) {
		log_err(ctx, "Invalid connection entry size: %u bytes.",
			entry_size);
		return JAYLINK_ERR_PROTO;
	}

	table_size = num * entry_size;
	size = REG_HEADER_SIZE + table_size + addinfo_size;

	if (size > REG_MAX_SIZE) {
		log_err(ctx, "Maximum registration information size exceeded: "
			"%u bytes.", size);
		return JAYLINK_ERR_PROTO;
	}

	if (size > REG_MIN_SIZE) {
		ret = transport_start_read(devh, size - REG_MIN_SIZE);

		if (ret != JAYLINK_OK) {
			log_err(ctx, "transport_start_read() failed: %i.", ret);
			return JAYLINK_ERR;
		}

		ret = transport_read(devh, buf + REG_MIN_SIZE,
			size - REG_MIN_SIZE);

		if (ret != JAYLINK_OK) {
			log_err(ctx, "transport_read() failed: %i.", ret);
			return JAYLINK_ERR;
		}
	}

	parse_conntable(connections, buf + REG_HEADER_SIZE, num, entry_size);

	if (info)
		memcpy(info, buf + REG_HEADER_SIZE + table_size, addinfo_size);

	if (info_size)
		*info_size = addinfo_size;

	return num;
}
