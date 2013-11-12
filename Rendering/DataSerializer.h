#pragma once

#include "Data.h"
#include <iostream>
#include <string>

namespace Rendering
{
class DataSerializer
{
public:
	static void Read(std::basic_istream<char>& sStream, Rendering::Data* pData);
	static void Save(std::basic_ostream<char>& sStream, Rendering::Data* pData);
	static void SaveData(std::basic_ostream<char>& sStream, Rendering::Data* pData, unsigned int uiLevel);
};
} /* end namespace Rendering */