#pragma once

#ifdef MATHS_EXPORTS
#define MATHS_API __declspec(dllexport)
#else
#define MATHS_API __declspec(dllimport)
#endif

#include <math.h>
#include <cmath>
#include <iostream>
#include <limits>

namespace Maths
{
	const double M_PI = 3.1415926536;
	const double DegToRadFactor = static_cast<double>(M_PI) / 180.0;
	const double RadToDegFactor = static_cast<double>(180) / M_PI;

	template<typename Type> MATHS_API int Signum(Type v);
	template<typename Type> MATHS_API Type Absolute(Type v);
	template<typename Type> MATHS_API Type ToRad(Type angleInDegrees);
	template<typename Type> MATHS_API Type ToDeg(Type angleInRad);
	template<typename Type> MATHS_API Type Det2x2(Type a1, Type b1, Type a2, Type b2);
	template<typename Type> MATHS_API Type Infinity();
	template<typename Type> MATHS_API bool IsNan(const Type& v);
} /* end namespace Maths */