#pragma once

#include "Maths.h"
#include "Vector.h"
#include "LatLong.h"
#include <assert.h>

namespace Maths
{
// row(i) first, then column(j)
template <typename Type>
class MATHS_API Matrix4D
{
private:
	class Row
	{
		friend class Matrix4D<Type>;
	public:
		Type& operator[](int col)
		{
			assert(m_row < rowsCount);
			assert(col < colsCount);
			return m_parentMatrix.m_matrix[m_row][col];
		}
	private:
		Row(Matrix4D<Type>& parentMatrix, int row) :
		   m_parentMatrix(parentMatrix),
		   m_row(row)
		   {}

		Matrix4D<Type>& m_parentMatrix;
		int m_row;
	}; /* end class Row */
public: // constructors and destructors
	Matrix4D(void);
	~Matrix4D(void);

public: // static functions
	static Matrix4D<Type> Identity();
	static Matrix4D<Type> Perspective(Type fovy, Type aspect, Type near, Type far);
	static Matrix4D<Type> Translation(Type x, Type y, Type z);
	static Matrix4D<Type> Translation(const Maths::Vector3D<Type>& point);
	static Matrix4D<Type> Scale(Type x, Type y, Type z);
	static Matrix4D<Type> Scale(const Maths::Vector3D<Type>& point);
	static Matrix4D<Type> Rotation(Type x, Type y, Type z, Type angle);
	static Matrix4D<Type> Rotation(const Maths::Vector3D<Type>& point, Type angle);

	static Matrix4D<Type> Geographic(const Maths::LatLong<Type>& latLong);
	static Matrix4D<Type> InvertedGeographic(const Maths::LatLong<Type>& latLong);
public: // public member functions
	Row operator[](int row) { assert(row < rowsCount); return Row(*this, row); };
	Matrix4D<Type> operator*(const Matrix4D<Type>& matrix) const;
	Vector3D<Type> operator*(const Vector3D<Type>& p) const;
	std::string ToString() const;

protected:

protected:
	Type m_matrix[4][4];

	static const int rowsCount = 4;
	static const int colsCount = 4;
}; /* end class Matrix4D<Type> */
	
	template class Matrix4D<int>;
	template class Matrix4D<float>;
	template class Matrix4D<double>;
	typedef Matrix4D<int> Matrix4Di;
	typedef Matrix4D<float> Matrix4Df;
	typedef Matrix4D<double> Matrix4Dd;
} /* end namespace Maths */
