#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>


class ZFSValue {
public:
		class ZFSValueException: std::exception {
		};
private:
		enum class ValueType {
				Integer, Double, String, Array, Dictionary
		};
		ValueType vtype;
		int ival;
		double dval;
		std::string sval;
		std::vector<ZFSValue> aval;
		std::map<std::string, ZFSValue> dict;

public:
		ZFSValue(int);
		ZFSValue(double);
		ZFSValue(std::string);
		ZFSValue(std::vector<ZFSValue>);
		ZFSValue(std::map<std::string, ZFSValue>);
		~ZFSValue() { ; }
		std::string to_string(void);

		int int_value(void);
		double double_value(void);
		std::string string_value(void);
		std::vector<ZFSValue> array_value(void);
		std::map<std::string, ZFSValue> dictonary_value(void);
};		

namespace std {
		string to_string(ZFSValue& v) {
				return v.to_string();
		}
};

std::string
ZFSValue::to_string(void)
{
		switch (vtype) {
		case ValueType::Integer: return std::to_string(ival);
		case ValueType::Double: return std::to_string(dval);
		case ValueType::String: return sval;
		case ValueType::Array: {
				std::string retval = "{ ";
				for (auto i = aval.begin(); i != aval.end(); i++) {
						retval += std::to_string(*i) + ", ";
				}
				return retval + "}";
		}
		case ValueType::Dictionary: return "dictionary, unsupported for now";
		}
}

ZFSValue::ZFSValue(int i) : vtype(ValueType::Integer), ival(i)
{
}
ZFSValue::ZFSValue(double d) : vtype(ValueType::Double), dval(d)
{
}
ZFSValue::ZFSValue(std::string s) : vtype(ValueType::String), sval(s)
{
}
ZFSValue::ZFSValue(std::vector<ZFSValue> a) : vtype(ValueType::Array), aval(a)
{
}
ZFSValue::ZFSValue(std::map<std::string, ZFSValue> d) : vtype(ValueType::Dictionary), dict(d)
{
}

int
main(int ac, char **av)
{
		ZFSValue v(100);
		ZFSValue a(std::vector<ZFSValue>{1, 2, 3, 4, 5});
		std::map<std::string, ZFSValue> d{{ "i", v}};
		std::cout << "v is " << std::to_string(v) << std::endl;
		std::cout << "a is " << std::to_string(a) << std::endl;
		return 0;
}
