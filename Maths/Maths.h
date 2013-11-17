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

	//template<typename Type> MATHS_API int Signum(Type v);
	template<typename Type> __declspec(dllexport) Type Absolute(Type v)
	{
		(v < 0) ? return -v : return v;
	}
	template<typename Type> __declspec(dllexport) Type ToRad(Type angleInDegrees)
	{
		return static_cast<Type>(Maths::DegToRadFactor * angleInDegrees);
	}
	
	template<typename Type> __declspec(dllexport) Type ToDeg(Type angleInRad)
	{
		return static_cast<Type>(Maths::RadToDegFactor * angleInRad);
	}
	//template<typename Type> MATHS_API Type Det2x2(Type a1, Type b1, Type a2, Type b2);
	template<typename Type> __declspec(dllexport) Type Infinity()
	{
		return std::numeric_limits<Type>::infinity();
	}
	template<typename Type> __declspec(dllexport) bool IsNan(const Type& v)
	{
		return isnan(value);
	}

	//__declspec(dllexport) bool AlmostEqual(double x, double y)
	//{
	//	const double epsilon = 0.00000000001;
	//	if (x == y)
	//		return true;

	//	double absX = abs(x);
	//	double absY = abs(y);
	//	double diff = absX - absY;

	//	return (diff < epsilon);
	//}

	//template<class Type>
	//typename std::enable_if<!std::numeric_limits<Type>::is_integer, bool>::type AlmostEqual(Type x, Type y, int ulp)
	//{
	//	// the machine epsilon has to be scaled to the magnitude of the larger value
	//	// and multiplied by the desired precision in ULPs (units in the last place)
	//	return std::abs(x-y) <=   std::numeric_limits<T>::epsilon()
	//							* std::max(std::abs(x), std::abs(y))
	//							* ulp;
	//}
} /* end namespace Maths */