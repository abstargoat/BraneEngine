#include "config.h"

Json::Value Config::root;
const char* Config::configFileName = "config.json";

Json::Value& Config::json()
{
	return root;
}

void Config::loadConfig()
{
	std::ifstream configFile(configFileName, std::ios::binary);
	if (!configFile.is_open())
	{
		std::cerr << "Could not open config.json, make sure it's in the same directory as the BraneAssetServer.exe\n";
		throw std::runtime_error("Could not open config file");
	}
	try
	{
		configFile >> root;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error reading configuration file: " << e.what() << std::endl;
	}
	configFile.close();
	std::cout << "loaded config.json\n";
}

void Config::save()
{
	std::ofstream configFile(configFileName, std::ios::binary);
	if (!configFile.is_open())
	{
		std::cerr << "Could not open config.json, make sure it's in the same directory as the BraneAssetServer.exe\n";
		throw std::runtime_error("Could not open config file");
	}
	try
	{
		configFile << root;
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error saving configuration file: " << e.what() << std::endl;
	}
	configFile.close();
	std::cout << "saved config.json\n";
}
