#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <getopt.h>

#include <sys/types.h>
#include <time.h>

#include <libgen.h>
#include <libintl.h>
#include <libnvpair.h>
#include <sys/fs/zfs.h>

#include <libzfs.h>
#include <libzfs_core.h>
#include <zfs_prop.h>
#include <zfs_deleg.h>
#include <libzutil.h>

#include <iostream>

#include "ZFS.h"
#include "ZFSPool.h"

ZFSPool::ZFSPool(void *ptr)
{
	// ptr is a zpool_handle_t
	this->ivar = ptr;
}

ZFSPool::~ZFSPool()
{
	fflush(stderr);
	this->ivar = NULL;
}

static zpool_handle_t *
handle(void *ptr)
{
	return (zpool_handle_t*)ptr;
}

std::string
ZFSPool::name(void)
{
	return std::string(zpool_get_name(handle(ivar)));
}

int
ZFSPool::state(void)
{
	return zpool_get_state(handle(ivar));
}

std::map<std::string, ZFSValue>
ZFSPool::properties(const std::string& name)
{
	// we've got a zpool handle via handle()...
	// what do we o with it?
	std::map<std::string, ZFSValue> retval = {};
	auto zhp = handle(ivar);
	zfs_handle_t *zfp = zfs_open((libzfs_handle_t*)ZFS::libzfs_handle(),
	    zpool_get_name(zhp), ZFS_TYPE_POOL | ZFS_TYPE_FILESYSTEM);
	if (zfp == NULL) {
		abort();
	}
	nvlist_t *props = zfs_get_all_props(zfp);
	if (props == NULL) {
		abort();
	}
	retval = ZFSValue::list(props);
	for (auto elem: retval) {
		std::cerr << "name: " << elem.first << ", value: " << std::to_string(elem.second) << std::endl;
	}
	zfs_close(zfp);
	return retval;
}
