#ifndef _ZFSVOLUME_H
# define _ZFSVOLUME_H

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "ZFS.h"

class ZFSVolume: public ZFSDataset {
public:
	ZFSVolume(std::shared_ptr<ZFSPool> pool, const std::string& name) :
		ZFSDataset(pool, name) { }
	ZFSDatasetType type() override { return ZFSDatasetType::volume; }
};

#endif /* _ZFSVOLUME_H */
