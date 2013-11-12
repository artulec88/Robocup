#include "Config.h"
#include <fstream>
#include <assert.h>

using namespace Utils;

Config::ValuesMap Config::s_values;
Config::ValuesMap Config::s_notDefined;
bool Config::s_initialized = false;
std::string Config::s_configPath = "";

bool Config::IsDefined(const std::string& name, Config::ValuesMap::iterator& valuesItr)
{
	if (!IsInitialized())
	{
		assert(!s_configPath.empty());
		LoadFromFile(s_configPath);
	}
	assert(IsInitialized());
	
	valuesItr = s_values.find(name);
	return (valuesItr != s_values.end());
}

int Config::GetValue(const std::string& name, int defaultValue)
{
	ValuesMap::iterator valueItr;
	if (! IsDefined(name, valueItr))
	{
		//std::stringstream s;
		//s << defaultValue;
		//stdlog(Warning, LOGPLACE, "Using default value for setting '%s' (%s)", name.c_str(), s.str().c_str());
		//s_notDefined[name] = s.str();

		s_notDefined[name] = Utility::ToString(defaultValue);
		return defaultValue;
	}

	return ParseValue<int>(valueItr->second);
}

float Config::GetValue(const std::string& name, float defaultValue)
{
	ValuesMap::iterator valueItr;
	if (! IsDefined(name, valueItr))
	{
		//std::stringstream s;
		//s << defaultValue;
		//stdlog(Warning, LOGPLACE, "Using default value for setting '%s' (%s)", name.c_str(), s.str().c_str());*/
		//s_notDefined[name] = s.str();

		s_notDefined[name] = Utility::ToString(defaultValue);
		return defaultValue;
	}
	return ParseValue<float>(valueItr->second);
}

std::string Config::GetValue(const std::string& name, const std::string& defaultValue)
{
	ValuesMap::iterator valueItr;
	if (! IsDefined(name, valueItr))
	{
		/*std::stringstream s;
		s << defValue;

		stdlog(Warning, LOGPLACE, "Using default value for setting '%s' (%s)", name.c_str(), s.str().c_str());*/
		s_notDefined[name] = defaultValue;
		return defaultValue;
	}
	return valueItr->second;
}

void Config::LoadFromFile(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if(!file.is_open())
	{
		stdlog(Error, LOGPLACE, "Could not open config file %s.", filename.c_str());
		return;
	}
	s_values.clear();
	s_notDefined.clear();

	std::string name, value;
	std::string separator;
	std::string line;
	std::stringstream stream;
	while(!file.eof())
	{
		file >> name;
		if(file.fail())
		{
			break;
		}

		std::getline(file, line);

		if(name[0] != '#')
		{
			stream.clear();
			stream.str(line);
			stream >> separator >> value;

			if(stream.fail() || separator != "=")
			{
				value = "0";
			}

			s_values[name] = value;
		}
	}

	s_initialized = true;
}

//template <typename Type>
//std::string Config::ReportUndefined()
//{
//	std::stringstream stream;
//
//	for(ValuesMap::iterator it = notDefined.begin(); it != notDefined.end(); ++it)
//	{
//		stream << it->first << " = " << it->second << '\n';
//	}
//
//	return stream.str();
//}

//template UTILS_API int Config::GetValue<int>(const std::string&, int);
//template UTILS_API float Config::GetValue<float>(const std::string&, float);
//template UTILS_API double Config::GetValue<double>(const std::string&, double);

//EXPIMP_TEMPLATE template class UTILS_API std::vector<MyClass>;
//template void Config::GetValue(int);