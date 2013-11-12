#pragma once

#include <string>
#include <map>
#include "Log.h"
#include "Utils.h"

namespace Utils
{
	class Config
	{
	protected:
		typedef std::map<std::string, std::string> ValuesMap;
	public:
		//template <typename Type> UTILS_API
		//static Type GetValue(const std::string& name, Type defaultValue);
		
		static bool IsDefined(const std::string& name, ValuesMap::iterator& valuesItr);
		template <typename Type> static Type ParseValue(const std::string& strValue)
		{
			Type value;
			std::stringstream s;
			s << strValue;
			s >> value;
			return value;
		}

		UTILS_API static int GetValue(const std::string& name, int defaultValue);
		UTILS_API static float GetValue(const std::string& name, float defaultValue);
		UTILS_API static std::string GetValue(const std::string& name, const std::string& defaultValue);

		UTILS_API static void LoadFromFile(const std::string& filename);
		//template <typename Type> UTILS_API
		//static std::string ReportUndefined();
	protected:
		static bool IsInitialized() { return s_initialized; };
	protected:
		static ValuesMap s_values;
		static ValuesMap s_notDefined;
		static bool s_initialized;
		static std::string s_configPath;
	};
} /* end namespace Utils */