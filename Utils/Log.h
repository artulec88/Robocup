#pragma once

#include "Utils.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <list>

#ifdef NDEBUG
#ifdef LOGMODULE
#define LOGPLACE LOGMODULE, 0 
#else
#define LOGPLACE "unknown-module", 0 
#endif
#else
#define LOGPLACE __FILE__, __LINE__
#endif

namespace Utils
{
	class Log
	{
	public:
		typedef std::list<FILE *> Outs;
		static const char *LevelNames[];

	protected:
		LogLevel m_level;
		Outs m_outs;
		bool m_modified;
	public:
		UTILS_API Log(FILE *first = stdout);
		UTILS_API ~Log();

		UTILS_API LogLevel GetLevel() const;
		UTILS_API void operator()(LogLevel level, const char *name, int line, const char *format, ...);

		UTILS_API void Fill(const std::string& strLevel, LogLevel level);
		UTILS_API void AddFile(const char *name);
	private:
		void SetLevel(LogLevel level);
	};

} /* end namespace Utils */

UTILS_API extern Utils::Log stdlog;