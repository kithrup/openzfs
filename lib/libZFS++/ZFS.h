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
class ZFSValue;

class ZFS {
private:
	static void *libzfs_handle(void);
public:
	// throw an exception on error
	static std::shared_ptr<ZFSPool> import_pool(const std::string& name,
	    const std::map<std::string, ZFSValue>&conf, const std::string& alt_roote = nullptr);
	static std::vector<std::map<std::string, std::string>> 	unimported_pools(void) { return {}; }
	static std::vector<ZFSPool> pools(void);
	static std::string user_version(void);
	static std::string kernel_version(void);
};

#include "ZFSProperties.h"
#include "ZFSPool.h"
#include "ZFSDataset.h"
#include "ZFSVolume.h"
#include "ZFSException.h"

#endif /* _ZFSPLUSPLUS_H */
