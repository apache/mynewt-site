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
#include <libusb.h>

#include "libjaylink.h"
#include "libjaylink-internal.h"

/**
 * @file
 *
 * Core library functions.
 */

/**
 * Initialize libjaylink.
 *
 * This function must be called before any other libjaylink function is called.
 *
 * @param[out] ctx Newly allocated libjaylink context on success, and undefined
 *                 on failure.
 *
 * @retval JAYLINK_OK Success.
 * @retval JAYLINK_ERR_ARG Invalid arguments.
 * @retval JAYLINK_ERR_MALLOC Memory allocation error.
 * @retval JAYLINK_ERR Other error conditions.
 */
JAYLINK_API int jaylink_init(struct jaylink_context **ctx)
{
	int ret;
	struct jaylink_context *context;

	if (!ctx)
		return JAYLINK_ERR_ARG;

	context = malloc(sizeof(struct jaylink_context));

	if (!context)
		return JAYLINK_ERR_MALLOC;

	if (libusb_init(&context->usb_ctx) < 0) {
		free(context);
		return JAYLINK_ERR;
	}

	context->devs = NULL;

	/* Show error and warning messages by default. */
	context->log_level = JAYLINK_LOG_LEVEL_WARNING;

	context->log_callback = &log_vprintf;
	context->log_callback_data = NULL;

	ret = jaylink_log_set_domain(context, JAYLINK_LOG_DOMAIN_DEFAULT);

	if (ret != JAYLINK_OK) {
		free(context);
		return ret;
	}

	*ctx = context;

	return JAYLINK_OK;
}

/**
 * Shutdown libjaylink.
 *
 * @param[in,out] ctx libjaylink context.
 */
JAYLINK_API void jaylink_exit(struct jaylink_context *ctx)
{
	if (!ctx)
		return;

	list_free(ctx->devs);
	libusb_exit(ctx->usb_ctx);
	free(ctx);
}
