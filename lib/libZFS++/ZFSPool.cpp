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
