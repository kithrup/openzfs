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

static libzfs_handle_t *libzfs_handle = libzfs_init();
static int libzfs_core_init_status = libzfs_core_init();

ZFSPool::~ZFSPool() {
	fprintf(stderr, "in %s\n", __FUNCTION__);
	fflush(stderr);
	free(this->ivar);
	this->ivar = NULL;
}
