#ifndef _VALUE_H
#define _VALUE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

#include "ZFSException.h"

/*
 * This is a simple wrapper to take the place of nvpair,
 * which is used all over the place in ZFS. I'm sure there
 * is a better way to do this.
 */

struct nvlist;

class ZFSValueTypeException: public ZFSException {
private:
	std::string message;
public:
	ZFSValueTypeException(const char *name, int expected, int actual);
	const char *what() const noexcept override { return message.c_str(); }
};

enum class ZFSValueType;
class ZFSValue {
public:


private:
	enum class ZFSValueType {
		Unknown, Boolean, Byte, UnsignedByte, Word, UnsignedWord,
		Integer, UnsignedInteger,
		LongInteger, UnsignedLongInteger,
		Time, Double, String, Array, Dictionary
	};
	ZFSValueType vtype;
	bool bval;
	int8_t byte_val;
	int16_t word_val;
	int ival;
	long long i64val;
	double dval;
	std::string sval;
	std::vector<ZFSValue> array_val;
	std::map<std::string, ZFSValue> dict;

public:
	static std::map<std::string, ZFSValue> list(struct nvlist*);
	ZFSValueType type(void) { return vtype; }
	ZFSValue(void);
	ZFSValue(bool);
	ZFSValue(int8_t);
	ZFSValue(uint8_t);
	ZFSValue(int16_t);
	ZFSValue(uint16_t);
	ZFSValue(int);
	ZFSValue(unsigned int);
	ZFSValue(int64_t);
	ZFSValue(uint64_t);
	ZFSValue(double);
	ZFSValue(std::string);
	ZFSValue(std::vector<ZFSValue>);
	ZFSValue(std::map<std::string, ZFSValue>);
	~ZFSValue() { ; }
	std::string to_string(void);

	bool bool_value(void);
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
