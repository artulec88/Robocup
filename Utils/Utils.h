#pragma once

#ifdef UTILS_EXPORTS
#define UTILS_API __declspec(dllexport)
//#define EXPIMP_TEMPLATE
#else
#define UTILS_API __declspec(dllimport)
//#define EXPIMP_TEMPLATE extern
#endif

//#include "Log.h"
#include <string>
#include <vector>
#include <dirent.h>
#include <iostream>

namespace Utils
{
	// TODO: consider creating new enum for function returning integer
	//enum RVAL
	//{
	//	RVAL_ERR = -2,
	//	RVAL_WARN = -1,
	//	RVAL_OK = 0
	//};

	enum LogLevel
	{
		Critical = 0,
		Emergency = 1,
		Error = 2,
		Warning = 3,
		Notice = 4,
		Info = 5,
		Debug = 6,
		Delocust = 7,

		DevNull = 100
	};

	class Utility
	{
	public:
		static UTILS_API std::string ToString(int value);
		static UTILS_API std::string ToString(float value);
		static UTILS_API std::string ToString(double value);
		static UTILS_API std::string ToString(std::string value);
		static UTILS_API std::string Ltrim(std::string& s);
		static UTILS_API std::string Rtrim(std::string& s);
		static UTILS_API std::string Trim(std::string& s);
		static UTILS_API void ListAllFilesInDir(const std::string& dirPath, std::vector<std::string>& filenames);
		static UTILS_API bool StrEndsWith(const std::string& sString, const std::string& sEnding);

		/**
		 * @brief Cut the string into tokens.
		 *
		 * Tokens in str are separated by some number of spaces. 
		 * Tokens are added to the end of tokens vector -- it is not cleared at the beginning.
		 * Notably, if str == "" or "  " there will be no tokens added to vector.
		 * All the spaces are removed.
		 * 
		 * @param str string containing tokens separated by spaces
		 * @param tokens vector to which the tokes are added
		 */
		static UTILS_API void CutToTokens(const std::string& str, std::vector<std::string>& tokens);

		static UTILS_API void Explode(const std::string& str, std::vector<std::string>& tokens, const std::string& delimeter = " ");
	};
} /* end namespace Utils */