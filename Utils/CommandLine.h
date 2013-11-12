#pragma once

#include <vector>
#include "Utils.h"

namespace Utils
{
	class CommandLine : public std::vector<std::string>
	{
	public: // constructors and destructors
		UTILS_API CommandLine();
		UTILS_API CommandLine(std::istream& stream);
		UTILS_API CommandLine(const std::string& str);
		UTILS_API CommandLine(const char* str);
		UTILS_API CommandLine(int argc, char* argv[]);
		UTILS_API ~CommandLine();

	public:
		UTILS_API bool IsNumberCorrect(int number) const;
		UTILS_API bool Read(std::istream& stream);
		UTILS_API bool Read(const std::string& line);
		UTILS_API std::string Get(const std::string& opt, const std::string& defaultValue) const;
		UTILS_API int Get(const std::string& opt, int defaultValue) const;
		UTILS_API int GetNumber(const std::string& opt, int first = 0) const;
		UTILS_API bool IsPresent(const std::string& opt) const;
		UTILS_API void Fill(int argc, char* argv[]);

	protected:
		template<typename Type> Type Get(int number, const Type& defaultValue) const;
	};
} /* end namespace Utils */