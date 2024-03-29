/*
   uio_single_mmap.c
   UIO helper function: ... ... ...

   Copyright (C) 2013, Jean-Francois Dagenais <jeff.dagenais@gmail.com>
   Copyright (C) 2009, Hans J. Koch <hjk@linutronix.de>
   Copyright (C) 2009, Stephan Linz <linz@li-pro.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sys/mman.h>

#include "uio_helper.h"

static void* __uio_single_mmap(struct uio_info_t* info, int map_num, int fd,
		int flags)
{
	if (!fd) return NULL;
	info->maps[map_num].mmap_result = UIO_MMAP_NOT_DONE;
	if (info->maps[map_num].size <= 0) return NULL;
	info->maps[map_num].mmap_result = UIO_MMAP_FAILED;
	info->maps[map_num].internal_addr =
		mmap(
			NULL,
			info->maps[map_num].size,
			flags,
			MAP_SHARED,
			fd,
			(long)map_num*getpagesize()
		);

	if (info->maps[map_num].internal_addr != MAP_FAILED) {
		info->maps[map_num].mmap_result = UIO_MMAP_OK;
		return info->maps[map_num].internal_addr;
	}

	return NULL;
}

void* uio_single_mmap(struct uio_info_t* info, int map_num, int fd)
{
	return __uio_single_mmap(info, map_num, fd, PROT_READ | PROT_WRITE);
}

void* uio_single_mmap_ro(struct uio_info_t* info, int map_num, int fd)
{
	return __uio_single_mmap(info, map_num, fd, PROT_READ);
}
