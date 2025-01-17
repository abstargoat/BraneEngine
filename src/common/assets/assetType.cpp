#include "assetType.h"

AssetType::Type AssetType::fromString(const std::string& type)
{
	static const std::unordered_map<std::string, AssetType::Type> _toEnumMap = {
			{"",          AssetType::none     },
			{"none",      AssetType::none     },
			{"component", AssetType::component},
			{"system",    AssetType::system   },
			{"mesh",      AssetType::mesh     },
			{"texture",   AssetType::texture  },
			{"player",    AssetType::player   },
			{"shader",    AssetType::shader   },
			{"assembly",  AssetType::assembly }
	};
	assert(_toEnumMap.count(type));
	return _toEnumMap.at(type);
}

const std::string& AssetType::toString(Type type)
{
	static const std::unordered_map<AssetType::Type, const std::string> _toStringMap = {
			{AssetType::none,      "none"     },
			{AssetType::component, "component"},
			{AssetType::system,    "system"   },
			{AssetType::mesh,      "mesh"     },
			{AssetType::texture,   "texture"  },
			{AssetType::player,    "player"   },
			{AssetType::shader,    "shader"   },
			{AssetType::assembly, "assembly"  }
	};
	assert(_toStringMap.count(type));
	return _toStringMap.at(type);
}

AssetType::AssetType()
{
	_type = none;
}

void AssetType::set(const std::string& type)
{
	
	_type = fromString(type);
}
void AssetType::set(AssetType::Type type)
{
	_type = type;
}

AssetType::Type AssetType::type() const
{
	return _type;
}

const std::string& AssetType::string() const
{
	return toString(_type);
}

bool AssetType::operator==(AssetType::Type t) const
{
	return t == _type;
}

bool AssetType::operator==(AssetType t) const
{
	return _type == t._type;
}
bool AssetType::operator!=(AssetType t) const
{
	return _type != t._type;
}

bool AssetType::operator!=(AssetType::Type t) const
{
	return t != _type;
}
