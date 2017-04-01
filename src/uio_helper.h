/*
   uio_helper
   UIO helper functions - header file.

   Copyright (C) 2009, 2017, Stephan Linz <linz@li-pro.net>
   Copyright (C) 2013, Jean-Francois Dagenais <jeff.dagenais@gmail.com>
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
#ifndef __UIO_HELPER_H__
#define __UIO_HELPER_H__

/* convensions */

#define UIO_MAX_NAME_SIZE       64
#define UIO_MAX_NUM             255

#define UIO_INVALID_SIZE        -1
#define UIO_INVALID_ADDR        (~0)

#define UIO_MMAP_NOT_DONE       0
#define UIO_MMAP_OK             1
#define UIO_MMAP_FAILED         2

/* This should be identical to the define in include/linux/uio_driver.h !!! */
#define MAX_UIO_MAPS    5

struct uio_map_t {
	unsigned long addr;
	int size;
	int mmap_result;
	void* internal_addr;
};

struct uio_dev_attr_t {
	char name[ UIO_MAX_NAME_SIZE ];
	char value[ UIO_MAX_NAME_SIZE ];
	struct uio_dev_attr_t *next;
};

struct uio_info_t {
	int uio_num;
	struct uio_map_t maps[ MAX_UIO_MAPS ];
	unsigned long event_count;
	char name[ UIO_MAX_NAME_SIZE ];
	char version[ UIO_MAX_NAME_SIZE ];
	struct uio_dev_attr_t *dev_attrs;
	struct uio_info_t* next;  /* for linked list */
};

/* function prototypes */

char* uio_lib_name(void);
char* uio_lib_version(void);
int uio_lib_ifcurrent(void);
int uio_lib_ifrevision(void);
int uio_lib_ifage(void);

int uio_get_mem_size(struct uio_info_t* info, int map_num);
int uio_get_mem_addr(struct uio_info_t* info, int map_num);
int uio_get_event_count(struct uio_info_t* info);
int uio_get_name(struct uio_info_t* info);
int uio_get_version(struct uio_info_t* info);
int uio_get_all_info(struct uio_info_t* info);
int uio_get_device_attributes(struct uio_info_t* info);

typedef void* (*uio_single_mmap_fp) (struct uio_info_t*, int, int);
void* uio_single_mmap(struct uio_info_t* info, int map_num, int fd);
void* uio_single_mmap_ro(struct uio_info_t* info, int map_num, int fd);

typedef void (*uio_mmap_fp) (struct uio_info_t*, int);
void uio_mmap(struct uio_info_t* info, int fd);
void uio_mmap_ro(struct uio_info_t* info, int fd);

void uio_single_munmap(struct uio_info_t* info, int map_num);
void uio_munmap(struct uio_info_t* info);

void uio_free_dev_attrs(struct uio_info_t* info);
void uio_free_info(struct uio_info_t* info);

struct uio_info_t* uio_find_devices(int filter_num);
struct uio_info_t* uio_find_devices_byname(const char *filter_name);

#endif /* __UIO_HELPER_H__ */
