#ifndef _ZFSDATASET_H
# define _ZFSDATASET_H

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

class ZFSDataset: public ZFSProperties {
public:
	enum class ZFSDatasetType { filesystem, volume };

private:
	std::string name_;
	std::shared_ptr<ZFSPool> pool_;
	std::string uuid_;
public:
	ZFSDataset(std::shared_ptr<ZFSPool> pool, const std::string& name) {
		name_ = name;
		pool_ = pool;
	}
	std::string name() { return name_; }

	std::shared_ptr<ZFSPool> pool() { return pool_; }

	virtual ZFSDatasetType type() { return ZFSDatasetType::filesystem; }

//	std::map<std::string, std::string> properties(const std::string& name = {}) { return {}; }
	bool remove_property(std::string& name) { return false; }
	bool set_property(const std::string& name, const std::string& value) { return false; }
	std::string get_property(const std::string& name) { return {}; }
	// convience wrappers
	bool canmount(void) { return false; }
	std::string mountpoint(void) { return get_property("mountpoint"); }

};

#endif /* _ZFSDATASET_H */
