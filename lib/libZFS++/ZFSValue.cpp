#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <exception>

#include <sys/nvpair.h>

#include "ZFSValue.h"
#include "ZFSException.h"

ZFSValueTypeException::ZFSValueTypeException(const char *name, int expected, int actual)
{
	message = std::string("Invalid value type: ") + std::to_string(actual) + " expected " + std::to_string(expected);
}

std::string
ZFSValue::to_string(void)
{
	switch (vtype) {
	case ZFSValueType::Unknown: return "<unknown>";
	case ZFSValueType::Boolean: return std::to_string(bval);
	case ZFSValueType::Byte: return std::to_string(byte_val);
	case ZFSValueType::UnsignedByte: return std::to_string((unsigned)byte_val);
	case ZFSValueType::Word: return std::to_string(word_val);
	case ZFSValueType::UnsignedWord: return std::to_string((unsigned)word_val);
	case ZFSValueType::Integer: return std::to_string(ival);
	case ZFSValueType::UnsignedInteger: return std::to_string((unsigned)ival);
	case ZFSValueType::LongInteger: return std::to_string(i64val);
	case ZFSValueType::UnsignedLongInteger: return std::to_string((unsigned)i64val);
	case ZFSValueType::Double: return std::to_string(dval);
	case ZFSValueType::String: return sval;
	case ZFSValueType::Array: {
		std::string retval = "{ ";
		for (auto i = array_val.begin(); i != array_val.end(); i++) {
			retval += std::to_string(*i) + ", ";
		}
		return retval + "}";
	}
	case ZFSValueType::Dictionary:
	{
		std::string retval = "{\n\t";
		for (auto elem: dict) {
			retval += elem.first + ": " + std::to_string(elem.second) + " }\n";
		}
		return retval + "\n}";
	}
	default:
		abort();
	}
}


ZFSValue::ZFSValue(void) : vtype(ZFSValueType::Unknown)
{
}

ZFSValue::ZFSValue(bool b) : vtype(ZFSValueType::Boolean), bval(b)
{
}

ZFSValue::ZFSValue(uint8_t b): vtype(ZFSValueType::UnsignedByte), byte_val(b)
{
}

ZFSValue::ZFSValue(int8_t b): vtype(ZFSValueType::Byte), byte_val(b)
{
}

ZFSValue::ZFSValue(int16_t s): vtype(ZFSValueType::Word), word_val(s)
{
}
ZFSValue::ZFSValue(uint16_t s): vtype(ZFSValueType::UnsignedWord), word_val(s)
{
}

ZFSValue::ZFSValue(int i) : vtype(ZFSValueType::Integer), ival(i)
{
}
ZFSValue::ZFSValue(unsigned int i): vtype(ZFSValueType::UnsignedInteger), ival(i)
{
}

ZFSValue::ZFSValue(int64_t i) : vtype(ZFSValueType::LongInteger), i64val(i)
{
}
ZFSValue::ZFSValue(uint64_t i) : vtype(ZFSValueType::UnsignedLongInteger), i64val(i)
{
}

ZFSValue::ZFSValue(double d) : vtype(ZFSValueType::Double), dval(d)
{
}
ZFSValue::ZFSValue(std::string s) : vtype(ZFSValueType::String), sval(s)
{
}
ZFSValue::ZFSValue(std::vector<ZFSValue> a) : vtype(ZFSValueType::Array), array_val(a)
{
}
ZFSValue::ZFSValue(std::map<std::string, ZFSValue> d) : vtype(ZFSValueType::Dictionary), dict(d)
{
}

std::map<std::string, ZFSValue>
ZFSValue::list(struct nvlist *nvl)
{
	std::map<std::string, ZFSValue> retval;

	for (nvpair_t *nvp = nvlist_next_nvpair(nvl, NULL);
	     nvp;
	     nvp = nvlist_next_nvpair(nvl, nvp)) {
		int rv;
		std::string name = nvpair_name(nvp);
		switch (nvpair_type(nvp)) {
		case DATA_TYPE_BOOLEAN:
		{
			boolean_t b;
			rv = nvpair_value_boolean_value(nvp, &b);
			if (rv != 0) {
				// throw exception
			} else {
				retval[name] = ZFSValue((bool)b);
			}
			break;
		}
		case DATA_TYPE_BYTE:
		{
			uchar_t b;
			rv = nvpair_value_byte(nvp, &b);
			if (rv == 0) {
				retval[name] = ZFSValue(b);
			}
			break;
		}

		case DATA_TYPE_INT8:
		{
			int8_t b;
			rv = nvpair_value_int8(nvp, &b);
			if (rv == 0) {
				retval[name] = ZFSValue(b);
			}
			break;
		}
		case DATA_TYPE_UINT8:
		{
			uint8_t b;
			rv = nvpair_value_uint8(nvp, &b);
			if (rv == 0) {
				retval[name] = ZFSValue(b);
			}
			break;
		}
		case DATA_TYPE_INT16:
		{
			int16_t w;
			rv = nvpair_value_int16(nvp, &w);
			if (rv == 0)
				retval[name] = ZFSValue(w);
			break;
		}
		case DATA_TYPE_UINT16:
		{
			uint16_t w;
			rv = nvpair_value_uint16(nvp, &w);
			if (rv == 0)
				retval[name] = ZFSValue(w);
			break;
		}
		case DATA_TYPE_INT32:
		{
			int32_t i;
			rv = nvpair_value_int32(nvp, &i);
			if (rv == 0)
				retval[name] = ZFSValue(i);
			break;
		}
		case DATA_TYPE_UINT32:
		{
			uint32_t i;
			rv = nvpair_value_uint32(nvp, &i);
			if (rv == 0)
				retval[name] = ZFSValue(i);
			break;
		}
		case DATA_TYPE_INT64:
		{
			int64_t l;
			rv = nvpair_value_int64(nvp, &l);
			if (rv == 0)
				retval[name] = ZFSValue(l);
			break;
		}
		case DATA_TYPE_UINT64:
		{
			uint64_t l;
			rv = nvpair_value_uint64(nvp, &l);
			if (rv == 0)
				retval[name] = ZFSValue(l);
			break;
		}
		case DATA_TYPE_STRING:
		{
			const char *s;
			rv = nvpair_value_string(nvp, &s);
			if (rv == 0)
				retval[name] = ZFSValue(std::string(s));
			break;
		}
		case DATA_TYPE_NVLIST:
		{
			struct nvlist *value;
			rv = nvpair_value_nvlist(nvp, &value);
			if (rv == 0) {
				retval[name] = ZFSValue::list(value);
			}
			break;
		}
		case DATA_TYPE_DONTCARE:
		case DATA_TYPE_UNKNOWN:
		case DATA_TYPE_BYTE_ARRAY:
		case DATA_TYPE_INT16_ARRAY:
		case DATA_TYPE_UINT16_ARRAY:
		case DATA_TYPE_INT32_ARRAY:
		case DATA_TYPE_UINT32_ARRAY:
		case DATA_TYPE_INT64_ARRAY:
		case DATA_TYPE_UINT64_ARRAY:
		case DATA_TYPE_STRING_ARRAY:
		case DATA_TYPE_HRTIME:
		case DATA_TYPE_NVLIST_ARRAY:
		case DATA_TYPE_BOOLEAN_VALUE:
		case DATA_TYPE_BOOLEAN_ARRAY:
		case DATA_TYPE_INT8_ARRAY:
		case DATA_TYPE_UINT8_ARRAY:
		case DATA_TYPE_DOUBLE:
			fprintf(stderr, "%s:%s(%d): %s has value type %d\n", __FILE__, __FUNCTION__, __LINE__, name.c_str(), nvpair_type(nvp));
			break;
		}
	}
	fprintf(stderr, "%s:%s(%d): retval count %zd\n", __FILE__, __FUNCTION__, __LINE__, retval.size());
	return retval;
}
