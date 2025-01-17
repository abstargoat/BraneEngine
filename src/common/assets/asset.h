#pragma once
#include "assets/assetID.h"
#include <utility/serializedData.h>
#include <byte.h>
#include <assets/assetType.h>

class AssetManager;

class Asset
{
public:
	enum LoadState{
		null = 0,
		partial = 1,
		complete = 2
	};
private:
	static Asset* assetFromType(AssetType type);
public:

	std::string name;
	AssetID id;
	AssetType type;
	LoadState loadState;
	static Asset* readUnknown(MarkedSerializedData& sData);
	static Asset* deserializeUnknown(ISerializedData& sData);
	virtual void serialize(OSerializedData& sData);
	virtual void deserialize(ISerializedData& sData);
	virtual void toFile(MarkedSerializedData& sData);
	virtual void fromFile(MarkedSerializedData& sData);
};

class IncrementalAsset : public Asset
{
public:
    struct SerializationContext{};
	static IncrementalAsset* deserializeUnknownHeader(ISerializedData& sData);
	virtual void serializeHeader(OSerializedData& sData);
	virtual void deserializeHeader(ISerializedData& sData);
	virtual bool serializeIncrement(OSerializedData& sData, SerializationContext* iteratorData);
	virtual void deserializeIncrement(ISerializedData& sData) = 0;
	virtual std::unique_ptr<SerializationContext> createContext() const = 0;
};


