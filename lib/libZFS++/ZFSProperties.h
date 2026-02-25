#ifndef _ZFSPROPERTIES_H
# define _ZFSPROPERTIES_H

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

/*
 * In Swift/ObjC, these would be protocols; in Rust, they'd be
 * traits.
 */
class ZFSProperties {
public:
	virtual std::map<std::string, std::string> properties(const std::string& name = {}) = 0;
	virtual bool remove_property(std::string&) = 0;
	virtual bool set_property(const std::string& name, const std::string& value) = 0;
};

#endif /* _ZFSPROPERTIES_H */
