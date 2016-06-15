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

#include "libjaylink-internal.h"

/**
 * @file
 *
 * Singly-linked list functions.
 */

JAYLINK_PRIV struct list *list_prepend(struct list *list, void *data)
{
	struct list *item;

	item = malloc(sizeof(struct list));

	if (!item)
		return NULL;

	item->data = data;
	item->next = list;

	return item;
}

JAYLINK_PRIV struct list *list_remove(struct list *list, const void *data)
{
	struct list *item;
	struct list *tmp;

	if (!list)
		return NULL;

	item = list;

	if (item->data == data) {
		tmp = item->next;
		free(item);
		return tmp;
	}

	while (item->next) {
		if (item->next->data == data) {
			tmp = item->next;
			item->next = item->next->next;
			free(tmp);
			break;
		}

		item = item->next;
	}

	return list;
}

JAYLINK_PRIV struct list *list_find_custom(struct list *list,
		list_compare_callback cb, const void *cb_data)
{
	if (!cb)
		return NULL;

	while (list) {
		if (!cb(list->data, cb_data))
			return list;

		list = list->next;
	}

	return NULL;
}

JAYLINK_PRIV void list_free(struct list *list)
{
	struct list *tmp;

	while (list) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
