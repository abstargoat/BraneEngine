#include "virtualType.h"
#include <unordered_map>

namespace VirtualType
{
	std::string typeToString(Type type)
	{
		static const std::unordered_map<Type, const std::string> _toStringMap = {
				{virtualUnknown,    "unknown"},
				{virtualBool,       "bool"},
				{virtualInt,        "int"},
				{virtualInt64,      "int64"},
				{virtualUInt,       "uint"},
				{virtualUInt64,     "uint64"},
				{virtualFloat,      "float"},
				{virtualString,     "string"},
				{virtualAssetID,    "assetID"},
				{virtualVec3,       "vec3"},
				{virtualQuat,       "quaternion"},
				{virtualMat4,       "mat4"},
				{virtualFloatArray, "floatVector"},
				{virtualIntArray,   "intVector"},
				{virtualUIntArray,  "uintVector"},
		};
		assert(_toStringMap.count(type));
		return _toStringMap.at(type);
	}

	Type stringToType(const std::string& type)
	{
		static const std::unordered_map<std::string, Type> _toStringMap = {
				{"unknown",     virtualUnknown},
				{"bool",        virtualBool},
				{"int",         virtualInt},
				{"int64",       virtualInt64},
				{"uint",        virtualUInt},
				{"uint64",      virtualUInt64},
				{"float",       virtualFloat},
				{"string",      virtualString},
				{"assetID",     virtualAssetID},
				{"vec3",        virtualVec3},
				{"quaternion",  virtualQuat},
				{"mat4",        virtualMat4},
				{"floatVector", virtualFloatArray},
				{"intVector",   virtualIntArray},
				{"uintVector",  virtualUIntArray},

		};
		assert(_toStringMap.count(type));
		return _toStringMap.at(type);
	}

	size_t size(Type type)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualUnknown:
				return 0;
			case virtualBool:
				return sizeof(bool);
			case virtualInt:
				return sizeof(int32_t);
			case virtualInt64:
				return sizeof(int64_t);
			case virtualUInt:
				return sizeof(uint32_t);
			case virtualUInt64:
				return sizeof(uint64_t);
			case virtualFloat:
				return sizeof(float);
			case virtualString:
				return sizeof(std::string);
			case virtualAssetID:
				return sizeof(AssetID);
			case virtualVec3:
				return sizeof(glm::vec3);
			case virtualVec4:
				return sizeof(glm::vec4);
			case virtualQuat:
				return sizeof(glm::quat);
			case virtualMat4:
				return sizeof(glm::mat4);
			case virtualFloatArray:
				return sizeof(inlineFloatArray);
			case virtualIntArray:
				return sizeof(inlineIntArray);
			case virtualUIntArray:
				return sizeof(inlineUIntArray);
		}
		assert(false && "unknown virtual type");
		return 0;
	}

	void construct(Type type, byte* var)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualBool:
				construct<bool>(var);
				return;
			case virtualInt:
				construct<int32_t>(var);
				return;
			case virtualInt64:
				construct<int64_t>(var);
				return;
			case virtualUInt:
				construct<uint32_t>(var);
				return;
			case virtualUInt64:
				construct<uint64_t>(var);
				return;
			case virtualFloat:
				construct<float>(var);
				return;
			case virtualString:
				construct<std::string>(var);
				return;
			case virtualAssetID:
				construct<AssetID>(var);
				return;
			case virtualVec3:
				construct<glm::vec3>(var);
				return;
			case virtualVec4:
				construct<glm::vec4>(var);
				return;
			case virtualQuat:
				construct<glm::quat>(var);
				return;
			case virtualMat4:
				construct<glm::mat4>(var);
				return;
			case virtualFloatArray:
				construct<inlineFloatArray>(var);
				return;
			case virtualIntArray:
				construct<inlineIntArray>(var);
				return;
			case virtualUIntArray:
				construct<inlineUIntArray>(var);
				return;
		}
	}

	void deconstruct(Type type, byte* var)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualBool:
				deconstruct<bool>(var);
				return;
			case virtualInt:
				deconstruct<int32_t>(var);
				return;
			case virtualInt64:
				deconstruct<int64_t>(var);
				return;
			case virtualUInt:
				deconstruct<uint32_t>(var);
				return;
			case virtualUInt64:
				deconstruct<uint64_t>(var);
				return;
			case virtualFloat:
				deconstruct<float>(var);
				return;
			case virtualString:
				deconstruct<std::string>(var);
				return;
			case virtualAssetID:
				deconstruct<AssetID>(var);
				return;
			case virtualVec3:
				deconstruct<glm::vec3>(var);
				return;
			case virtualVec4:
				deconstruct<glm::vec4>(var);
				return;
			case virtualQuat:
				deconstruct<glm::quat>(var);
				return;
			case virtualMat4:
				deconstruct<glm::mat4>(var);
				return;
			case virtualFloatArray:
				deconstruct<std::vector<float>>(var);
				return;
			case virtualIntArray:
				deconstruct<std::vector<int32_t>>(var);
				return;
			case virtualUIntArray:
				deconstruct<std::vector<uint32_t>>(var);
				return;
		}
	}

	void copy(Type type, byte* dest, const byte* source)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualBool:
				copy<bool>(dest, source);
				return;
			case virtualInt:
				copy<int32_t>(dest, source);
				return;
			case virtualInt64:
				copy<int64_t>(dest, source);
				return;
			case virtualUInt:
				copy<uint32_t>(dest, source);
				return;
			case virtualUInt64:
				copy<uint64_t>(dest, source);
				return;
			case virtualFloat:
				copy<float>(dest, source);
				return;
			case virtualString:
				copy<std::string>(dest, source);
				return;
			case virtualAssetID:
				copy<AssetID>(dest, source);
				return;
			case virtualVec3:
				copy<glm::vec3>(dest, source);
				return;
			case virtualVec4:
				copy<glm::vec4>(dest, source);
				return;
			case virtualQuat:
				copy<glm::quat>(dest, source);
				return;
			case virtualMat4:
				copy<glm::mat4>(dest, source);
				return;
			case virtualFloatArray:
				copy<std::vector<float>>(dest, source);
				return;
			case virtualIntArray:
				copy<std::vector<int32_t>>(dest, source);
				return;
			case virtualUIntArray:
				copy<std::vector<uint32_t>>(dest, source);
				return;
		}
	}

	void move(Type type, byte* dest, const byte* source)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualBool:
				move<bool>(dest, source);
				return;
			case virtualInt:
				move<int32_t>(dest, source);
				return;
			case virtualInt64:
				move<int64_t>(dest, source);
				return;
			case virtualUInt:
				move<uint32_t>(dest, source);
				return;
			case virtualUInt64:
				move<uint64_t>(dest, source);
				return;
			case virtualFloat:
				move<float>(dest, source);
				return;
			case virtualString:
				move<std::string>(dest, source);
				return;
			case virtualAssetID:
				move<AssetID>(dest, source);
				return;
			case virtualVec3:
				move<glm::vec3>(dest, source);
				return;
			case virtualVec4:
				move<glm::vec4>(dest, source);
				return;
			case virtualQuat:
				move<glm::quat>(dest, source);
				return;
			case virtualMat4:
				move<glm::mat4>(dest, source);
				return;
			case virtualFloatArray:
				move<inlineFloatArray>(dest, source);
				return;
			case virtualIntArray:
				move<inlineIntArray>(dest, source);
				return;
			case virtualUIntArray:
				move<inlineUIntArray>(dest, source);
				return;
		}
	}

	void serialize(Type type, OSerializedData& data, const byte* source)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualBool:
				serialize<bool>(data, source);
				return;
			case virtualInt:
				serialize<int32_t>(data, source);
				return;
			case virtualInt64:
				serialize<int64_t>(data, source);
				return;
			case virtualUInt:
				serialize<uint32_t>(data, source);
				return;
			case virtualUInt64:
				serialize<uint64_t>(data, source);
				return;
			case virtualFloat:
				serialize<float>(data, source);
				return;
			case virtualString:
				serialize<std::string>(data, source);
				return;
			case virtualAssetID:
				serialize<AssetID>(data, source);
				return;
			case virtualVec3:
				serialize<glm::vec3>(data, source);
				return;
			case virtualVec4:
				serialize<glm::vec4>(data, source);
				return;
			case virtualQuat:
				serialize<glm::quat>(data, source);
				return;
			case virtualMat4:
				serialize<glm::mat4>(data, source);
				return;
			case virtualFloatArray:
				serialize<inlineIntArray>(data, source);
				return;
			case virtualIntArray:
				serialize<inlineIntArray>(data, source);
				return;
			case virtualUIntArray:
				serialize<inlineUIntArray>(data, source);
				return;
		}
	}

	void deserialize(Type type, ISerializedData& data, byte* source)
	{
		assert(type != virtualUnknown);
		switch (type)
		{
			case virtualBool:
				deserialize<bool>(data, source);
				return;
			case virtualInt:
				deserialize<int32_t>(data, source);
				return;
			case virtualInt64:
				deserialize<int64_t>(data, source);
				return;
			case virtualUInt:
				deserialize<uint32_t>(data, source);
				return;
			case virtualUInt64:
				deserialize<uint64_t>(data, source);
				return;
			case virtualFloat:
				deserialize<float>(data, source);
				return;
			case virtualString:
				deserialize<std::string>(data, source);
				return;
			case virtualAssetID:
				deserialize<AssetID>(data, source);
				return;
			case virtualVec3:
				deserialize<glm::vec3>(data, source);
				return;
			case virtualVec4:
				deserialize<glm::vec4>(data, source);
				return;
			case virtualQuat:
				deserialize<glm::quat>(data, source);
				return;
			case virtualMat4:
				deserialize<glm::mat4>(data, source);
				return;
			case virtualFloatArray:
				deserialize<inlineFloatArray>(data, source);
				return;
			case virtualIntArray:
				deserialize<inlineIntArray>(data, source);
				return;
			case virtualUIntArray:
				deserialize<inlineUIntArray>(data, source);
				return;
		}
	}
}