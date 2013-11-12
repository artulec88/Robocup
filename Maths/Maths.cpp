#include "Maths.h"

using namespace Maths;

template <typename Type>
int Signum(Type v)
{
	if (v < 0)
	{
		return -1;
	}
	if (v > 0)
	{
		return 1;
	}
	return 0;
}

template <typename Type>
Type Absolute(Type v)
{
	{
		(v < 0) ? return -v : return v;
	}
}

template<typename Type>
Type ToRad(Type angleInDegrees)
{
	return static_cast<Type>(Maths::DegToRadFactor * angleInDegrees);
}

template<typename Type>
Type ToDeg(Type angleInRad)
{
	return static_cast<Type>(Maths::RadToDegFactor * angle);
}

template<typename Type>
Type Det2x2(Type a1, Type b1, Type a2, Type b2)
{
	return (a1 * b2) - (a2 * b1);
}

template<typename Type>
Type Infinity()
{
	return std::numeric_limits<Type>::infinity();
}

template<typename Type>
bool IsNan(const Type& value)
{
	return isnan(value);
}