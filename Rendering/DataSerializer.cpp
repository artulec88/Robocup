#include "DataSerializer.h"
#include "Utils\Log.h"

#include <vector>

using namespace Rendering;
using namespace Utils;
using namespace std;

#define MAX_BUFFER 1024

/* static */ void DataSerializer::Read(std::basic_istream<char>& sStream, Data* pData)
{
	stdlog(Debug, LOGPLACE, "DataSerializer::Read() function started");
	if (!sStream.good())
	{
		stdlog(Emergency, LOGPLACE, "Stream is not correct");
		return;
	}

	if (pData == NULL)
	{
		stdlog(Error, LOGPLACE, "NULL Data pointer given when reading from stream");
		return;
	}

	char szLine[MAX_BUFFER];
	string sLine;

	Data* pCurrentData = pData;
	Data* pPreviousData = NULL;

	while (sStream.getline(szLine, MAX_BUFFER))
	{
		sLine = string(szLine);

		unsigned int uiComment = static_cast<unsigned int>(sLine.find("//"));
		if (uiComment!= string::npos)
		{
			sLine = sLine.substr(0, uiComment);
		}

		sLine = Utility::Trim(sLine);

		if (sLine.empty())
			continue;

		if (sLine[0] = '{')
		{
			pCurrentData = pPreviousData;
			continue;
		}

		if (sLine[0] = '}')
		{
			pCurrentData = pCurrentData->GetParent();
			continue;
		}

		std::vector<std::string> asTokens;
		//Utility::CutToTokens(sLine, asTokens);
		Utility::Explode(sLine, asTokens, ":");
		if (asTokens.size() == 1)
		{
			pPreviousData = pCurrentData->AddChild(Utility::Trim(sLine));
		}
		else if (asTokens.size() == 2)
		{
			pPreviousData = pCurrentData->AddChild(Utility::Trim(asTokens[0]), Utility::Trim(sLine.substr(sLine.find(':')+1)));
		}
	}

	stdlog(Debug, LOGPLACE, "DataSerializer::Read() function finished");
}

/* static */ void DataSerializer::Save(std::basic_ostream<char>& sStream, Data* pData)
{
	stdlog(Debug, LOGPLACE, "DataSerializer::Save() function started");
	if (!sStream)
	{
		stdlog(Emergency, LOGPLACE, "Stream is not correct");
		return;
	}
	if (pData == NULL)
	{
		stdlog(Error, LOGPLACE, "NULL Data pointer given when reading from stream");
		return;
	}

	SaveData(sStream, pData, 0);

	stdlog(Debug, LOGPLACE, "DataSerializer::Save() function finished");
}

/* static */ void DataSerializer::SaveData(std::basic_ostream<char>& sStream, Data* pData, unsigned int uiLevel)
{
	string sTabs;
	for (unsigned int ui = 0; ui < uiLevel; ++ui)
		sTabs += "\t";

	for (unsigned int ui = 0; ui < pData->GetChildrenCount(); ++ui)
	{
		Data* pChild = pData->GetChild(ui);

		if (pChild->GetValueString().length())
			sStream << (sTabs + pChild->GetKey() + ": " + pChild->GetValueString() + "\n").c_str();
		else
			sStream << (sTabs + pChild->GetKey() + "\n").c_str();

		if (pChild->GetChildrenCount())
		{
			sStream << (sTabs + "{\n").c_str();
			SaveData(sStream, pChild, uiLevel + 1);
			sStream << (sTabs + "}\n").c_str();
		}
	}
}