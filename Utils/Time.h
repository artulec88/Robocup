#pragma once

#include "Utils.h"
#include <time.h>
#include <string>

namespace Utils
{
	class Time
	{
	public:
		int seconds;
		int micros;
	public: // constructors destructors
		UTILS_API Time();
		UTILS_API Time(int seconds, int micros);
		UTILS_API Time(double value);
		UTILS_API ~Time();
	public: /* static methods variables */
		UTILS_API static Time Now();
		UTILS_API static Time Eternity();
		UTILS_API static Time Chaos();

		static const Time Infinite;
		static const Time Disabled;
		static const Time Short;
	public:
		UTILS_API double ToReal() const;

		UTILS_API Time operator+(const Time &arg) const;
		UTILS_API Time operator-(const Time &arg) const;
			
		UTILS_API int Signum(const Time &arg) const;

		UTILS_API bool operator<(const Time &arg) const;
		UTILS_API bool operator>(const Time &arg) const;
		UTILS_API bool operator<=(const Time &arg) const;
		UTILS_API bool operator>=(const Time &arg) const;
		UTILS_API bool operator==(const Time &arg) const;
		UTILS_API bool operator!=(const Time &arg) const;

		UTILS_API const Time &operator=(double value);
		UTILS_API const Time &operator=(const Time &t);

		UTILS_API bool IsInfinite() const;
		UTILS_API bool IsDisabled() const;
		UTILS_API void MakeInfinite();
		UTILS_API void MakeDisabled();

		UTILS_API std::string ToString() const;
		UTILS_API std::string ToDateString(const char *format = "%Y-%m-%d %H:%M:%S") const;
	};
} /* end namespace Utils */