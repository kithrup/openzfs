#ifndef _ZFSPOOL_H
#define _ZFSPOOL_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "ZFS.h"

/*
 * A pool has, at the very least, a name, and some vdevs.
 * It may also contain some datasets, snapshots, and properties.
 */

	
class ZFSPool: public ZFSProperties {
public:
	enum class FeatureState { active, enabled, disabled };
private:
	std::string name_;
	std::string uuid_;
	std::vector<std::shared_ptr<ZFSDataset>> datasets_;
	// super private hidden state
	void *ivar;
public:
	ZFSPool(std::string& name) { name_ = name; ivar = NULL; }
	~ZFSPool();
	std::string name() { return name_; }
	std::map<std::string, std::string> properties(const std::string& name) { return {}; }
	bool remove_property(std::string& name) { return false; }
	bool set_property(const std::string& name, const std::string& value) { return false; }
	bool export_pool(void) { return false; }

	FeatureState get_feature(const std::string& name) { return FeatureState::active; }
	bool set_feature(const std::string& name, FeatureState& value) { return false; }
};

#endif /* _ZFSPOOL_H */
