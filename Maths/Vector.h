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
		Vector2D() : m_x(0), m_y(0) { };
		Vector2D(Type x, Type y) : m_x(x), m_y(y) { };
	public: // public member functions
		Type GetX() const { return m_x; };
		Type GetY() const { return m_y; };
		void SetX(Type x) { m_x = x; };
		void SetY(Type y) { m_y = y; };

		std::string ToString() const { std::stringstream s(""); s << m_x << " " << m_y << " "; return s.str(); };
		Type Length() const { return static_cast<Type>(sqrt(static_cast<float>(LengthSquared()))); };
		Type LengthSquared() const { return static_cast<Type>(m_x * m_x + m_y * m_y); };

		void Negate() { m_x = -m_x; m_y = -m_y; }; // creates negation vector

		Vector2D operator+(const Vector2D& v) const { return Vector2D<Type>(m_x + v.GetX(), m_y + v.GetY()); };
		Vector2D operator-() const { return Vector2D<Type>(-m_x, -m_y); };
		Vector2D operator-(const Vector2D& v) const { return Vector2D<Type>(m_x - v.GetX(), m_y - v.GetY()); };
		Vector2D operator*(Type s) const { return Vector2D<Type>(s * m_x, s * m_y); };
		Vector2D operator/(Type s) const { return Vector2D<Type>(m_x / s, m_y / s); };

		Vector2D Normalized() const { return (*this) / Length(); };
		void Normalize() { (*this) = (*this) / Length(); };

		Type Dot(const Vector2D& v) const { return (m_x * v.GetX() + m_y * v.GetY()); };
	protected: // member variables
		Type m_x;
		Type m_y;
	};

	template <typename Type>
	class MATHS_API Vector3D
	{
	protected: // member variables
		Type m_x;
		Type m_y;
		Type m_z;
	public: // constructors and destructors
		Vector3D() : m_x(0), m_y(0), m_z(0) { };
		Vector3D(Type x, Type y, Type z) : m_x(x), m_y(y), m_z(z) { };
	public: // public member functions
		Type GetX() const { return m_x; };
		Type GetY() const { return m_y; };
		Type GetZ() const { return m_z; };
		void SetX(Type x) { m_x = x; };
		void SetY(Type y) { m_y = y; };
		void SetZ(Type z) { m_z = z; };

		std::string ToString() const { std::stringstream s(""); s << m_x << " " << m_y << " " << m_z << " "; return s.str(); };
		Type Length() const { return static_cast<Type>(sqrt(static_cast<float>(LengthSquared()))); };
		Type LengthSquared() const { return static_cast<Type>(m_x * m_x + m_y * m_y + m_z * m_z); };

		void Negate() { m_x = -m_x; m_y = -m_y; m_z = -m_z; }; // creates negation vector

		Vector3D operator+(const Vector3D& v) const { return Vector3D<Type>(m_x + v.GetX(), m_y + v.GetY(), m_z + v.GetZ()); };
		Vector3D operator-() const { return Vector3D<Type>(-m_x, -m_y, -m_z); };
		Vector3D operator-(const Vector3D& v) const { return Vector3D<Type>(m_x - v.GetX(), m_y - v.GetY(), m_z - v.GetZ()); };
		Vector3D operator*(Type s) const { return Vector3D<Type>(s * m_x, s * m_y, s * m_z); };
		Vector3D operator/(Type s) const { return Vector3D<Type>(m_x / s, m_y / s, m_z / s); };

		Vector3D Normalized() const { return (*this) / Length(); };
		void Normalize() { (*this) = (*this) / Length(); };

		Type Dot(const Vector3D& v) const { return m_x * v.GetX() + m_y * v.GetY() + m_z * v.GetZ(); };
		Vector3D Cross(const Vector3D& v) const { return Vector3D<Type>(m_y * v.GetZ() - m_z * v.GetY(), m_z * v.GetX() - m_x * v.GetZ(), m_x * v.GetY() - m_y * v.GetX()); };
	};

	template <typename Type>
	class MATHS_API Vector4D
	{
	protected: // member variables
		Type m_x;
		Type m_y;
		Type m_z;
		Type m_w;
	public: // constructors and destructors
		Vector4D() : m_x(0), m_y(0), m_z(0), m_w(0) { };
		Vector4D(Type x, Type y, Type z, Type w) : m_x(x), m_y(y), m_z(z), m_w(w) { };
	public: // public member functions
		Type GetX() const { return m_x; };
		Type GetY() const { return m_y; };
		Type GetZ() const { return m_z; };
		Type GetW() const { return m_w; };
		void SetX(Type x) { m_x = x; };
		void SetY(Type y) { m_y = y; };
		void SetZ(Type z) { m_z = z; };
		void SetW(Type w) { m_w = w; };

		std::string ToString() const { std::stringstream s(""); s << m_x << " " << m_y << " " << m_z << " " << m_w << " "; return s.str(); };
		Type Length() const { return static_cast<Type>(sqrt(static_cast<float>(LengthSquared()))); };
		Type LengthSquared() const { return static_cast<Type>(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w); };

		void Negate() { m_x = -m_x; m_y = -m_y; m_z = -m_z; m_w = -m_w; }; // creates negation vector

		Vector4D operator+(const Vector4D& v) const { return Vector4D<Type>(m_x + v.GetX(), m_y + v.GetY(), m_z + v.GetZ(), m_w + v.GetW()); };
		Vector4D operator-() const { return Vector4D<Type>(-m_x, -m_y, -m_z, -m_w); };
		Vector4D operator-(const Vector4D& v) const { return Vector4D<Type>(m_x - v.GetX(), m_y - v.GetY(), m_z - v.GetZ(), m_w - v.GetW()); };
		Vector4D operator*(Type s) const { return Vector4D<Type>(s * m_x, s * m_y, s * m_z, s * m_w); };
		Vector4D operator/(Type s) const { return Vector4D<Type>(m_x / s, m_y / s, m_z / s, m_w / s); };

		Vector4D Normalized() const { return (*this) / Length(); };
		void Normalize() { (*this) = (*this) / Length(); };

		Type Dot(const Vector4D& v) const { return ( m_x * v.GetX() + m_y * v.GetY() + m_z * v.GetZ() + m_w * v.GetW() ); };
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

