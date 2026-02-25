#ifndef _ZFSEXCEPTION_H
# define _ZFSEXCEPTION_H

#include <string>
#include <exception>

class ZFSException: public std::exception {
public:
	ZFSException() {}
	const char *what() const noexcept override {
		return "ZFS Exception";
	}
};

class ZFSImportException: public ZFSException {
private:
	std::string message;
public:
	ZFSImportException(std::string& name, int code = 0) {
		message = "Cannot import pool" + name;
		if (code)
			message += " (code " + std::to_string(code) + ")";
	}
	ZFSImportException(const char *name, int code = 0) {
		message = std::string("Cannot import pool") + name;
		if (code)
			message += " (code " + std::to_string(code) + ")";
	}
	const char *what() const noexcept override { return message.c_str(); }
};

#endif /* _ZFSEXCEPTION_H */
