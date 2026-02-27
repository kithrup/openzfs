#ifndef _VALUE_H
#define _VALUE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>


/*
 * This is a simple wrapper to take the place of nvpair,
 * which is used all over the place in ZFS. I'm sure there
 * is a better way to do this.
 */

enum class ZFSValueType;
class ZFSValue {
public:
	class ZFSValueException: std::exception {
	public:
		ZFSValueException(void) {}
		const char *what(void) { return "ZFS Value exception"; }
	};
	class InvalidTypeZFSValueException: ZFSValueException {
	private:
		char *descr = NULL;
	public:
		InvalidTypeZFSValueException(ZFSValueType expected, ZFSValueType actual) : ZFSValueException() {}
		const char *what(void) { return ""; };
	};

private:
	enum class ZFSValueType {
		Integer, LongInteger, Double, String, Array, Dictionary
	};
	ZFSValueType vtype;
	int ival;
	unsigned long long i64val;
	double dval;
	std::string sval;
	std::vector<ZFSValue> aval;
	std::map<std::string, ZFSValue> dict;

public:
	ZFSValue(int);
	ZFSValue(unsigned long long);
	ZFSValue(double);
	ZFSValue(std::string);
	ZFSValue(std::vector<ZFSValue>);
	ZFSValue(std::map<std::string, ZFSValue>);
	~ZFSValue() { ; }
	std::string to_string(void);

	int int_value(void);
	unsigned long long long_int_value(void);
	double double_value(void);
	std::string string_value(void);
	std::vector<ZFSValue> array_value(void);
	std::map<std::string, ZFSValue> dictonary_value(void);
};		

namespace std {
	inline string to_string(ZFSValue& v) {
		return v.to_string();
	}
};

#endif /* _VALUE_H */
