/*
   uio_mmap.c
   UIO helper function: ... ... ...

   Copyright (C) 2009, 2017, Stephan Linz <linz@li-pro.net>
   Copyright (C) 2009, Hans J. Koch <hjk@linutronix.de>

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

#include "uio_helper.h"

static void __uio_mmap(struct uio_info_t* info, int fd,
		uio_single_mmap_fp exec)
{
	int map_num;
	if (!fd) return;
	for (map_num= 0; map_num < MAX_UIO_MAPS; map_num++)
		exec(info, map_num, fd);
}

void uio_mmap(struct uio_info_t* info, int fd)
{
	__uio_mmap(info, fd, uio_single_mmap);
}

void uio_mmap_ro(struct uio_info_t* info, int fd)
{
	__uio_mmap(info, fd, uio_single_mmap_ro);
}
