#include "Vector.h"

using namespace Maths;

/**
 * Vector2D function definitions begin
 */
template <typename Type> Vector2D<Type>::Vector2D() : x(0), y(0) { };
template <typename Type> Vector2D<Type>::Vector2D(Type x, Type y) : x(x), y(y) { };

template <typename Type> Type Vector2D<Type>::GetX() const { return x; }
template <typename Type> Type Vector2D<Type>::GetY() const { return y; }
template <typename Type> void Vector2D<Type>::SetX(Type x) { this->x = x; }
template <typename Type> void Vector2D<Type>::SetY(Type y) { this->y = y; }

template <typename Type> void Vector2D<Type>::Negate()
{
	x = -x;
	y = -y;
}

template <typename Type> std::string Vector2D<Type>::ToString() const
{
	std::stringstream s("");
	s << x << " " << y << " ";
	return s.str();
}

template <typename Type> Type Vector2D<Type>::Length() const
{
	return static_cast<Type>(sqrt(static_cast<float>(LengthSquared())));
}

template <typename Type> Type Vector2D<Type>::LengthSquared() const
{
	return static_cast<Type>(x * x + y * y);
}

template <typename Type> Vector2D<Type> Vector2D<Type>::operator+(const Vector2D& v) const
{
	return Vector2D<Type>(x + v.GetX(), y + v.GetY());
}

template <typename Type> Vector2D<Type> Vector2D<Type>::operator-(const Vector2D& v) const
{
	return Vector2D<Type>(x - v.GetX(), y - v.GetY());
}

template <typename Type> Vector2D<Type> Vector2D<Type>::operator*(Type s) const
{
	return Vector2D<Type>(s * x, s * y);
}

template <typename Type> Vector2D<Type> Vector2D<Type>::operator/(Type s) const
{
	return Vector2D<Type>(x / s, y / s);
}

template <typename Type> Vector2D<Type> Vector2D<Type>::Normalized() const
{
	return (*this) / Length();
}

template <typename Type> void Vector2D<Type>::Normalize()
{
	(*this) = (*this) / Length();
}

template <typename Type> Type Vector2D<Type>::Dot(const Vector2D& v) const
{
	return (x * v.GetX() + y * v.GetY());
}
/**
 * Vector2D function definitions end
 */

/**
 * Vector3D function definitions begin
 */
template <typename Type> Vector3D<Type>::Vector3D() : x(0), y(0), z(0) { };
template <typename Type> Vector3D<Type>::Vector3D(Type x, Type y, Type z) : x(x), y(y), z(z) { };

template <typename Type> Type Vector3D<Type>::GetX() const { return x; }
template <typename Type> Type Vector3D<Type>::GetY() const { return y; }
template <typename Type> Type Vector3D<Type>::GetZ() const { return z; }
template <typename Type> void Vector3D<Type>::SetX(Type x) { this->x = x; }
template <typename Type> void Vector3D<Type>::SetY(Type y) { this->y = y; }
template <typename Type> void Vector3D<Type>::SetZ(Type z) { this->z = z; }

template <typename Type> void Vector3D<Type>::Negate()
{
	x = -x;
	y = -y;
	z = -z;
}

template <typename Type> std::string Vector3D<Type>::ToString() const
{
	std::stringstream s("");
	s << x << " " << y << " " << z << " ";
	return s.str();
}

template <typename Type> Type Vector3D<Type>::Length() const
{
	return static_cast<Type>(sqrt(static_cast<float>(LengthSquared())));
}

template <typename Type> Type Vector3D<Type>::LengthSquared() const
{
	return static_cast<Type>(x * x + y * y + z * z);
}

template <typename Type> Vector3D<Type> Vector3D<Type>::operator+(const Vector3D& v) const
{
	return Vector3D<Type>(x + v.GetX(), y + v.GetY(), z + v.GetZ());
}

template <typename Type> Vector3D<Type> Vector3D<Type>::operator-(const Vector3D& v) const
{
	return Vector3D<Type>(x - v.GetX(), y - v.GetY(), z - v.GetZ());
}

template <typename Type> Vector3D<Type> Vector3D<Type>::operator*(Type s) const
{
	return Vector3D<Type>(s * x, s * y, s * z);
}

template <typename Type> Vector3D<Type> Vector3D<Type>::operator/(Type s) const
{
	return Vector3D<Type>(x / s, y / s, z / s);
}

template <typename Type> Vector3D<Type> Vector3D<Type>::Normalized() const
{
	return (*this) / Length();
}

template <typename Type> void Vector3D<Type>::Normalize()
{
	(*this) = (*this) / Length();
}

template <typename Type> Type Vector3D<Type>::Dot(const Vector3D& v) const
{
	return x * v.GetX() + y * v.GetY() + z * v.GetZ();
}

template <typename Type> Vector3D<Type> Vector3D<Type>::Cross(const Vector3D& v) const
{
	return Vector3D<Type>(y * v.GetZ() - z * v.GetY(),
						z * v.GetX() - x * v.GetZ(),
						x * v.GetY() - y * v.GetX());
}
/**
 * Vector3D function definitions end
 */

/**
 * Vector4D function definitions begin
 */
template <typename Type> Vector4D<Type>::Vector4D() : x(0), y(0), z(0), w(0) { };
template <typename Type> Vector4D<Type>::Vector4D(Type x, Type y, Type z, Type w) : x(x), y(y), z(z), w(w) { };

template <typename Type> Type Vector4D<Type>::GetX() const { return x; }
template <typename Type> Type Vector4D<Type>::GetY() const { return y; }
template <typename Type> Type Vector4D<Type>::GetZ() const { return z; }
template <typename Type> Type Vector4D<Type>::GetW() const { return w; }
template <typename Type> void Vector4D<Type>::SetX(Type x) { this->x = x; }
template <typename Type> void Vector4D<Type>::SetY(Type y) { this->y = y; }
template <typename Type> void Vector4D<Type>::SetZ(Type z) { this->z = z; }
template <typename Type> void Vector4D<Type>::SetW(Type w) { this->w = w; }

template <typename Type> void Vector4D<Type>::Negate()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}

template <typename Type> std::string Vector4D<Type>::ToString() const
{
	std::stringstream s("");
	s << x << " " << y << " " << z << " " << w << " ";
	return s.str();
}

template <typename Type> Type Vector4D<Type>::Length() const
{
	return static_cast<Type>(sqrt(static_cast<float>(LengthSquared())));
}

template <typename Type> Type Vector4D<Type>::LengthSquared() const
{
	return static_cast<Type>(x * x + y * y + z * z + w * w);
}

template <typename Type> Vector4D<Type> Vector4D<Type>::operator+(const Vector4D& v) const
{
	return Vector4D<Type>(x + v.GetX(), y + v.GetY(), z + v.GetZ(), w + v.GetW());
}

template <typename Type> Vector4D<Type> Vector4D<Type>::operator-(const Vector4D& v) const
{
	return Vector4D<Type>(x - v.GetX(), y - v.GetY(), z - v.GetZ(), w - v.GetW());
}

template <typename Type> Vector4D<Type> Vector4D<Type>::operator*(Type s) const
{
	return Vector4D<Type>(s * x, s * y, s * z, s * w);
}

template <typename Type> Vector4D<Type> Vector4D<Type>::operator/(Type s) const
{
	return Vector4D<Type>(x / s, y / s, z / s, w / s);
}

template <typename Type> Vector4D<Type> Vector4D<Type>::Normalized() const
{
	return (*this) / Length();
}

template <typename Type> void Vector4D<Type>::Normalize()
{
	(*this) = (*this) / Length();
}

template <typename Type> Type Vector4D<Type>::Dot(const Vector4D& v) const
{
	return ( x * v.GetX() + y * v.GetY() + z * v.GetZ() + w * v.GetW() );
}
/**
 * Vector4D function definitions end
 */