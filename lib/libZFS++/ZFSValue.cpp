#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

#include "ZFSValue.h"

std::string
ZFSValue::to_string(void)
{
	switch (vtype) {
	case ZFSValueType::Integer: return std::to_string(ival);
	case ZFSValueType::LongInteger: return std::to_string(i64val);
	case ZFSValueType::Double: return std::to_string(dval);
	case ZFSValueType::String: return sval;
	case ZFSValueType::Array: {
		std::string retval = "{ ";
		for (auto i = aval.begin(); i != aval.end(); i++) {
			retval += std::to_string(*i) + ", ";
		}
		return retval + "}";
	}
	case ZFSValueType::Dictionary: return "dictionary, unsupported for now";
	}
}

ZFSValue::ZFSValue(int i) : vtype(ZFSValueType::Integer), ival(i)
{
}
ZFSValue::ZFSValue(unsigned long long i) : vtype(ZFSValueType::LongInteger), i64val(i)
{
}

ZFSValue::ZFSValue(double d) : vtype(ZFSValueType::Double), dval(d)
{
}
ZFSValue::ZFSValue(std::string s) : vtype(ZFSValueType::String), sval(s)
{
}
ZFSValue::ZFSValue(std::vector<ZFSValue> a) : vtype(ZFSValueType::Array), aval(a)
{
}
ZFSValue::ZFSValue(std::map<std::string, ZFSValue> d) : vtype(ZFSValueType::Dictionary), dict(d)
{
}
