#ifndef _ZFSPLUSPLUS_H
# define _ZFSPLUSPLUS_H

#include <vector>
#include <string>
#include <memory>
#include <map>

class ZFSException;
class ZFSProperties;
class ZFSPool;
class ZFSDataset;
class ZFSVolume;

class ZFS {
public:
	// throw an exception on error
	static std::shared_ptr<ZFSPool> import_pool(const std::string& name) { return {}; }
	static std::vector<std::map<std::string, std::string>> 	unimported_pools(void) { return {}; }
	static std::vector<std::string> list_pools(void) { return {}; }
	static std::string version();
};

#include "ZFSProperties.h"
#include "ZFSPool.h"
#include "ZFSDataset.h"
#include "ZFSVolume.h"
#include "ZFSException.h"

#endif /* _ZFSPLUSPLUS_H */
