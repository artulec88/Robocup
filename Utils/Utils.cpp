#include "Utils.h"
#include "Log.h"

#include <functional>
#include <sstream>
#include <dirent.h>
#include <algorithm>

using namespace Utils;

std::string Utility::ToString(int value)
{
	std::stringstream s;
	s << value;
	return s.str();
}

std::string Utility::ToString(float value)
{
	std::stringstream s;
	s << value;
	return s.str();
}

std::string Utility::ToString(double value)
{
	std::stringstream s;
	s << value;
	return s.str();
}

std::string Utility::ToString(std::string value)
{
	return value;
}

void Utility::ListAllFilesInDir(const std::string& dirPath, std::vector<std::string>& filenames)
{
	std::string fullPath = dirPath + "\\";
	DIR* dir;
	struct dirent* ent;
	if ( (dir = opendir(dirPath.c_str())) != NULL)
	{
		// see http://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html
		while ( (ent = readdir(dir)) != NULL )
		{
			if (ent->d_type != DT_REG)
				continue;
			std::string filePath(fullPath);
			filePath.append(ent->d_name);
			stdlog(Debug, LOGPLACE, "Found file: %s", filePath.c_str());
			filenames.push_back(filePath);
			//stdlog(Debug, LOGPLACE, "%d", ent->d_namlen);
			//stdlog(Debug, LOGPLACE, "%d", ent->d_type);
		}
		closedir(dir);
	}
	else // could not open directory
	{
		stdlog(Error, LOGPLACE, "Could not open directory %s", dirPath);
	}
}

bool Utility::StrEndsWith(const std::string& sString, const std::string& sEnding)
{
	if (sString.length() < sEnding.length())
		return false;

	return (sString.substr(sString.length() - sEnding.length()) == sEnding);
}

void Utility::CutToTokens(const std::string& str, std::vector<std::string>& tokens)
{
	std::stringstream ss(str);
	std::string temp = "";
	ss >> temp;
	while ( temp != "" )
	{
		tokens.push_back(temp);
		temp = "";
		ss >> temp;
	}
}

std::string Utility::Ltrim(std::string& str)
{
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(isspace))));
	return str;
}

std::string Utility::Rtrim(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), str.end());
	return str;
}

std::string Utility::Trim(std::string& str)
{
	return Ltrim(Rtrim(str));
}

// explode is slightly different in that repeated delineators return multiple tokens.
// ie "a|b||c" returns { "a", "b", "", "c" } whereas strtok will cut out the blank result.
// Basically it works like PHP's explode.
void Utility::Explode(const std::string& str, std::vector<std::string>& tokens, const std::string& delimeter /* = " " */)
{
    std::string::size_type lastPos = str.find_first_of(delimeter, 0);
    std::string::size_type pos = 0;

    while (true)
    {
        tokens.push_back(str.substr(pos, lastPos - pos));

		if (lastPos == std::string::npos)
			break;

		pos = lastPos+1;
        lastPos = str.find_first_of(delimeter, pos);
    }
}