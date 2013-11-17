#include "Matrix.h"
//#include "Vector.h"
#include <string>
#include <sstream>

using namespace Maths;

template <typename Type> Matrix4D<Type>::Matrix4D(void) { }
template <typename Type> Matrix4D<Type>::~Matrix4D(void) { }

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Identity()
{
	Matrix4D<Type> m;

	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	return m;
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Perspective(Type fovy, Type aspect, Type near, Type far)
{
	Matrix4D<Type> m;

	Type fovyInRad = ToRad(fovy / 2);

	Type f = static_cast<Type>(1.0 / tan(static_cast<float>(fovyInRad))); // TODO: What to do with ambiguous 'tan' overloaded functions?
	Type div = static_cast<Type>(1.0/(near - far));
	
	m[0][0] = f / aspect;	m[0][1] = 0;	m[0][2] = 0;					m[0][3] = 0;
	m[1][0] = 0;			m[1][1] = f;	m[1][2] = 0;					m[1][3] = 0;
	m[2][0] = 0;			m[2][1] = 0;	m[2][2] = (far + near) * div;	m[2][3] = 2 * far * near * div;
	m[3][0] = 0;			m[3][1] = 0;	m[3][2] = -1;					m[3][3] = 0;
				

	return m;
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Translation(Type x, Type y, Type z)
{
	Matrix4D<Type> m;

	m[0][0] = 1;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = x;
	m[1][0] = 0;	m[1][1] = 1;	m[1][2] = 0;	m[1][3] = y;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = 1;	m[2][3] = z;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	return m;
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Translation(const Vector3D<Type>& point)
{
	return Translation(point.GetX(), point.GetY(), point.GetZ());
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Scale(Type x, Type y, Type z)
{
	Matrix4D<Type> m;

	m[0][0] = x;	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = y;	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = z;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;

	return m;
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Scale(const Vector3D<Type>& point)
{
	return Scale(point.GetX(), point.GetY(), point.GetZ());
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Rotation(Type x, Type y, Type z, Type angle)
{
	Type vecLength = sqrt(static_cast<float>(x*x + y*y + z*z));
	x /= vecLength;
	y /= vecLength;
	z /= vecLength;

	angle *= DegToRadFactor;

	Type c = cos(static_cast<float>(angle));
	Type s = sin(static_cast<float>(angle));
	Type omc = 1 - c;
	Type xs = x * s;
	Type ys = y * s;
	Type zs = z * s;
	Type xy = x * y;
	Type xz = x * z;
	Type yz = y * z;

	Matrix4D<Type> m;

	m[0][0] = x*x*omc+c;	m[0][1] = xy*omc-zs;	m[0][2] = xz*omc+ys;	m[0][3] = 0;
	m[1][0] = xy*omc+zs;	m[1][1] = y*y*omc+c;	m[1][2] = yz*omc-xs;	m[1][3] = 0;
	m[2][0] = xz*omc-ys;	m[2][1] = yz*omc+xs;	m[2][2] = z*z*omc+c;	m[2][3] = 0;
	m[3][0] = 0;			m[3][1] = 0;			m[3][2] = 0;			m[3][3] = 1;

	return m;
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Rotation(const Vector3D<Type>& point, Type angle)
{
	return Rotation(point.GetX(), point.GetY(), point.GetZ(), angle);
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::Geographic(const LatLong<Type>& latLong)
{
	/**
	 * Let alpha=latlong.longitude, beta=latlong.latitude. Then
	 * First matrix is equal to:
	 * -sin(alpha)	0	-cos(alpha)	0
	 * 0			1	0			0
	 * cos(alpha)	0	-sin(alpha)	0
	 * 0			0	0			1
	 *
	 * Second matrix is equal to:
	 * 1	0			0			0
	 * 0	cos(beta)	-sin(beta)	0
	 * 0	sin(beta)	cos(beta)	0
	 * 0	0			0			1
	 *
	 * Their multiplication product is equal to:
	 * -sin(alpha)	-sin(beta)*cos(alpha)	-cos(beta)*cos(alpha)	0
	 * 0			cos(beta)				-sin(beta)				0
	 * cos(alpha)	-sin(beta)*sin(alpha)	-cos(beta)*sin(alpha)	0
	 * 0			0						0						1
	*/
	return (Rotation(0, -1, 0, latLong.GetLongitude() + 90) * Rotation(1, 0, 0, latLong.GetLatitude()));
}

template <typename Type>
/* static */ Matrix4D<Type> Matrix4D<Type>::InvertedGeographic(const LatLong<Type>& latLong)
{
	/**
	 * Let alpha=latlong.longitude, beta=latlong.latitude. Then
	 * First matrix is equal to:
	 * 1	0			0			0
	 * 0	cos(beta)	sin(beta)	0
	 * 0	-sin(beta)	cos(beta)	0
	 * 0	0			0			1
	 *
	 * Second matrix is equal to:
	 * -sin(alpha)	0	cos(alpha)	0
	 * 0			1	0			0
	 * -cos(alpha)	0	-sin(alpha)	0
	 * 0			0	0			1
	 *
	 * Their multiplication product is equal to:
	 * -sin(alpha)				0			cos(alpha)				0
	 * -cos(alpha)*sin(beta)	cos(beta)	-sin(alpha)*sin(beta)	0
	 * -cos(alpha)*cos(beta)	-sin(beta)	-sin(alpha)*cos(beta)	0
	 * 0						0			0						1
	*/
	return Rotation(-1, 0, 0, latLong.GetLatitude()) * Rotation(0, 1, 0, latLong.GetLongitude() + 90);
}

template <typename Type>
Matrix4D<Type> Matrix4D<Type>::operator*(const Matrix4D<Type>& matrix) const
{
	Matrix4D<Type> m;

	m[0][0] = 0;
	//m[0][0] = this[0][0];

	//m[0][0] = this[0][0] * matrix[0][0] + this[0][1] * matrix[1][0] + this[0][2] * matrix[2][0] + this[0][3] * matrix[3][0];
	//m[0][1] = this[0][0] * matrix[0][1] + this[0][1] * matrix[1][1] + this[0][2] * matrix[2][1] + this[0][3] * matrix[3][1];
	//m[0][2] = this[0][0] * matrix[0][2] + this[0][1] * matrix[1][2] + this[0][2] * matrix[2][2] + this[0][3] * matrix[3][2];
	//m[0][3] = this[0][0] * matrix[0][3] + this[0][1] * matrix[1][3] + this[0][2] * matrix[2][3] + this[0][3] * matrix[3][3];

	//m[1][0] = this[1][0] * matrix[0][0] + this[1][1] * matrix[1][0] + this[1][2] * matrix[2][0] + this[1][3] * matrix[3][0];
	//m[1][1] = this[1][0] * matrix[0][1] + this[1][1] * matrix[1][1] + this[1][2] * matrix[2][1] + this[1][3] * matrix[3][1];
	//m[1][2] = this[1][0] * matrix[0][2] + this[1][1] * matrix[1][2] + this[1][2] * matrix[2][2] + this[1][3] * matrix[3][2];
	//m[1][3] = this[1][0] * matrix[0][3] + this[1][1] * matrix[1][3] + this[1][2] * matrix[2][3] + this[1][3] * matrix[3][3];
	//		
	//m[2][0] = this[2][0] * matrix[0][0] + this[2][1] * matrix[1][0] + this[2][2] * matrix[2][0] + this[2][3] * matrix[3][0];
	//m[2][1] = this[2][0] * matrix[0][1] + this[2][1] * matrix[1][1] + this[2][2] * matrix[2][1] + this[2][3] * matrix[3][1];
	//m[2][2] = this[2][0] * matrix[0][2] + this[2][1] * matrix[1][2] + this[2][2] * matrix[2][2] + this[2][3] * matrix[3][2];
	//m[2][3] = this[2][0] * matrix[0][3] + this[2][1] * matrix[1][3] + this[2][2] * matrix[2][3] + this[2][3] * matrix[3][3];
	//		                                                                                                                          
	//m[3][0] = this[3][0] * matrix[0][0] + this[3][1] * matrix[1][0] + this[3][2] * matrix[2][0] + this[3][3] * matrix[3][0];
	//m[3][1] = this[3][0] * matrix[0][1] + this[3][1] * matrix[1][1] + this[3][2] * matrix[2][1] + this[3][3] * matrix[3][1];
	//m[3][2] = this[3][0] * matrix[0][2] + this[3][1] * matrix[1][2] + this[3][2] * matrix[2][2] + this[3][3] * matrix[3][2];
	//m[3][3] = this[3][0] * matrix[0][3] + this[3][1] * matrix[1][3] + this[3][2] * matrix[2][3] + this[3][3] * matrix[3][3];
				
	return m;
}

template <typename Type>
Vector3D<Type> Matrix4D<Type>::operator*(const Vector3D<Type>& p) const
{
	Vector3D<Type> result;

	Matrix4D<Type> matrix(*this);

	Type oneperw = 1 / (matrix[3][0] * p.GetX() + matrix[3][1] * p.GetY() + matrix[3][2] * p.GetZ() + matrix[3][3]);

	/*Type oneperw = 1 / (this[3][0] * p.GetX() + this[3][1] * p.GetY() + this[3][2] * p.GetZ() + this[3][3]);

	result.SetX((this[0][0]*p.GetX() + this[0][1]*p.GetY() + this[0][2]*p.GetZ() + this[0][3]) * oneperw);
	result.SetY((this[1][0]*p.GetX() + this[1][1]*p.GetY() + this[1][2]*p.GetZ() + this[1][3]) * oneperw);
	result.SetZ((this[2][0]*p.GetX() + this[2][1]*p.GetY() + this[2][2]*p.GetZ() + this[2][3]) * oneperw);*/

	return result;
}

//template <typename Type>
//Matrix4D<Type>::Row Matrix4D<Type>::operator[](int row) const
//{
//	return Row(*this, row);
//}

template <typename Type>
std::string Matrix4D<Type>::ToString() const
{
	std::stringstream s("");
	s << m_matrix[0][0] << " ";
	s << m_matrix[0][1] << " ";
	s << m_matrix[0][2] << " ";
	s << m_matrix[0][3] << " ";
	s << std::endl;

	s << m_matrix[1][0] << " ";
	s << m_matrix[1][1] << " ";
	s << m_matrix[1][2] << " ";
	s << m_matrix[1][3] << " ";
	s << std::endl;

	s << m_matrix[2][0] << " ";
	s << m_matrix[2][1] << " ";
	s << m_matrix[2][2] << " ";
	s << m_matrix[2][3] << " ";
	s << std::endl;

	s << m_matrix[3][0] << " ";
	s << m_matrix[3][1] << " ";
	s << m_matrix[3][2] << " ";
	s << m_matrix[3][3] << " ";
	s << std::endl;


	return s.str();
}