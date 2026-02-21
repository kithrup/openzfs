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

class ZFSPoolInternal {
private:
	libzfs_handle_t *libzfs_handle_;
	friend class ZFS;
public:
	ZFSPoolInternal() {
		libzfs_handle_ = libzfs_init();
		(void)libzfs_core_init();
	}
	~ZFSPoolInternal() {
		libzfs_fini(libzfs_handle_);
		libzfs_core_fini();
	}
};
static ZFSPoolInternal internal_state = ZFSPoolInternal();

void *
ZFS::libzfs_handle(void)
{
	return (void*)internal_state.libzfs_handle_;
}

std::string
ZFS::user_version(void)
{
	static std::string version = zfs_version_userland();
	return version;
}

std::string
ZFS::kernel_version(void)
{
	static std::string version = zfs_version_kernel();
	return version;
}

static int
build_pool_list(zpool_handle_t *handle, void *ctx)
{
	std::vector<std::string> *list = (std::vector<std::string>*)ctx;
	std::string pool_name = std::string(zpool_get_name(handle));
	list->push_back(pool_name);
	return 0;
}

std::vector<std::string>
ZFS::list_pools(void)
{
	std::vector<std::string> retval;
	int rv = zpool_iter(internal_state.libzfs_handle_,
	    &build_pool_list, (void*)&retval);
	return retval;
}
