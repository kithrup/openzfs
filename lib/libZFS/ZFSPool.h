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
	// super private hidden state
	void *ivar;
public:
	// Create a pool from a handle
	ZFSPool(void *);
	~ZFSPool();
	std::string name(void);
	std::map<std::string, std::string> properties(const std::string& name) { return {}; }
	bool remove_property(std::string& name) { return false; }
	bool set_property(const std::string& name, const std::string& value) { return false; }
	bool export_pool(void) { return false; }

	FeatureState get_feature(const std::string& name) { return FeatureState::active; }
	bool set_feature(const std::string& name, FeatureState& value) { return false; }
};

#endif /* _ZFSPOOL_H */
