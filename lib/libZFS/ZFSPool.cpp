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


ZFSPool::ZFSPool(std::string& name)
{
	this->name_ = name;
	ivar = NULL;
}

ZFSPool::~ZFSPool()
{
	fflush(stderr);
	free(this->ivar);
	this->ivar = NULL;
}
