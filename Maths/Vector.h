#pragma once

#include "Maths.h"
#include <istream>
#include <ostream>
#include <sstream>

namespace Maths 
{
	template <typename Type>
	class Vector2D
	{
	public: // constructors and destructors
		MATHS_API Vector2D();
		MATHS_API Vector2D(Type x, Type y);
	public: // public member functions
		MATHS_API Type GetX() const;
		MATHS_API Type GetY() const;
		MATHS_API void SetX(Type x);
		MATHS_API void SetY(Type y);

		MATHS_API std::string ToString() const;
		MATHS_API Type Length() const;
		MATHS_API Type LengthSquared() const;

		MATHS_API void Negate(); // creates negation vector

		MATHS_API Vector2D operator+(const Vector2D& v) const;
		MATHS_API Vector2D operator-(const Vector2D& v) const;
		MATHS_API Vector2D operator*(Type s) const;
		MATHS_API Vector2D operator/(Type s) const;

		MATHS_API Vector2D Normalized() const;
		MATHS_API void Normalize();

		MATHS_API Type Dot(const Vector2D& v) const;
	protected: // member variables
		Type x;
		Type y;
	};

	template <typename Type>
	class Vector3D
	{
	protected: // member variables
		Type x;
		Type y;
		Type z;
	public: // constructors and destructors
		MATHS_API Vector3D();
		MATHS_API Vector3D(Type x, Type y, Type z);
	public: // public member functions
		MATHS_API Type GetX() const;
		MATHS_API Type GetY() const;
		MATHS_API Type GetZ() const;
		MATHS_API void SetX(Type x);
		MATHS_API void SetY(Type y);
		MATHS_API void SetZ(Type z);

		MATHS_API std::string ToString() const;
		MATHS_API Type Length() const;
		MATHS_API Type LengthSquared() const;

		MATHS_API void Negate(); // creates negation vector

		MATHS_API Vector3D operator+(const Vector3D& v) const;
		MATHS_API Vector3D operator-(const Vector3D& v) const;
		MATHS_API Vector3D operator*(Type s) const;
		MATHS_API Vector3D operator/(Type s) const;

		MATHS_API Vector3D Normalized() const;
		MATHS_API void Normalize();

		MATHS_API Type Dot(const Vector3D& v) const;
		MATHS_API Vector3D Cross(const Vector3D& v) const;
	};

	template <typename Type>
	class Vector4D
	{
	protected: // member variables
		Type x;
		Type y;
		Type z;
		Type w;
	public: // constructors and destructors
		MATHS_API Vector4D();
		MATHS_API Vector4D(Type x, Type y, Type z, Type w);
	public: // public member functions
		MATHS_API Type GetX() const;
		MATHS_API Type GetY() const;
		MATHS_API Type GetZ() const;
		MATHS_API Type GetW() const;
		MATHS_API void SetX(Type x);
		MATHS_API void SetY(Type y);
		MATHS_API void SetZ(Type z);
		MATHS_API void SetW(Type w);

		MATHS_API std::string ToString() const;
		MATHS_API Type Length() const;
		MATHS_API Type LengthSquared() const;

		MATHS_API void Negate(); // creates negation vector

		MATHS_API Vector4D operator+(const Vector4D& v) const;
		MATHS_API Vector4D operator-(const Vector4D& v) const;
		MATHS_API Vector4D operator*(Type s) const;
		MATHS_API Vector4D operator/(Type s) const;

		MATHS_API Vector4D Normalized() const;
		MATHS_API void Normalize();

		MATHS_API Type Dot(const Vector4D& v) const;
	};
	template class Vector2D<int>;
	template class Vector2D<float>;
	template class Vector2D<double>;
	template class Vector3D<int>;
	template class Vector3D<float>;
	template class Vector3D<double>;
	template class Vector4D<int>;
	template class Vector4D<float>;
	template class Vector4D<double>;

	typedef Vector2D<int> Vector2Di;
	typedef Vector2D<float> Vector2Df;
	typedef Vector2D<double> Vector2Dd;
	typedef Vector3D<int> Vector3Di;
	typedef Vector3D<float> Vector3Df;
	typedef Vector3D<double> Vector3Dd;
	typedef Vector4D<int> Vector4Di;
	typedef Vector4D<float> Vector4Df;
	typedef Vector4D<double> Vector4Dd;

	typedef Vector2D<int> Point2Di;
	typedef Vector2D<float> Point2Df;
	typedef Vector2D<double> Point2Dd;
	typedef Vector3D<int> Point3Di;
	typedef Vector3D<float> Point3Df;
	typedef Vector3D<double> Point3Dd;
	typedef Vector4D<int> Point4Di;
	typedef Vector4D<float> Point4Df;
	typedef Vector4D<double> Point4Dd;
} /* end namespace Maths */