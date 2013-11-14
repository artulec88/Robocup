#pragma once

#include "Maths.h"
#include <istream>
#include <ostream>
#include <sstream>

namespace Maths 
{
	template <typename Type>
	class MATHS_API Vector2D
	{
	public: // constructors and destructors
		Vector2D();
		Vector2D(Type x, Type y);
	public: // public member functions
		Type GetX() const;
		Type GetY() const;
		void SetX(Type x);
		void SetY(Type y);

		std::string ToString() const;
		Type Length() const;
		Type LengthSquared() const;

		void Negate(); // creates negation vector

		Vector2D operator+(const Vector2D& v) const;
		Vector2D operator-(const Vector2D& v) const;
		Vector2D operator*(Type s) const;
		Vector2D operator/(Type s) const;

		Vector2D Normalized() const;
		void Normalize();

		Type Dot(const Vector2D& v) const;
	protected: // member variables
		Type x;
		Type y;
	};

	template <typename Type>
	class MATHS_API Vector3D
	{
	protected: // member variables
		Type x;
		Type y;
		Type z;
	public: // constructors and destructors
		Vector3D();
		Vector3D(Type x, Type y, Type z);
	public: // public member functions
		Type GetX() const;
		Type GetY() const;
		Type GetZ() const;
		void SetX(Type x);
		void SetY(Type y);
		void SetZ(Type z);

		std::string ToString() const;
		Type Length() const;
		Type LengthSquared() const;

		void Negate(); // creates negation vector

		Vector3D operator+(const Vector3D& v) const;
		Vector3D operator-(const Vector3D& v) const;
		Vector3D operator*(Type s) const;
		Vector3D operator/(Type s) const;

		Vector3D Normalized() const;
		void Normalize();

		Type Dot(const Vector3D& v) const;
		Vector3D Cross(const Vector3D& v) const;
	};

	template <typename Type>
	class MATHS_API Vector4D
	{
	protected: // member variables
		Type x;
		Type y;
		Type z;
		Type w;
	public: // constructors and destructors
		Vector4D();
		Vector4D(Type x, Type y, Type z, Type w);
	public: // public member functions
		Type GetX() const;
		Type GetY() const;
		Type GetZ() const;
		Type GetW() const;
		void SetX(Type x);
		void SetY(Type y);
		void SetZ(Type z);
		void SetW(Type w);

		std::string ToString() const;
		Type Length() const;
		Type LengthSquared() const;

		void Negate(); // creates negation vector

		Vector4D operator+(const Vector4D& v) const;
		Vector4D operator-(const Vector4D& v) const;
		Vector4D operator*(Type s) const;
		Vector4D operator/(Type s) const;

		Vector4D Normalized() const;
		void Normalize();

		Type Dot(const Vector4D& v) const;
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