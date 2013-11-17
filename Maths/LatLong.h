#pragma once

#include "Maths.h"
#include "Vector.h"

namespace Maths
{
template <typename Type>
class MATHS_API LatLong
{
public: // constructors and destructors
	LatLong(void) : m_latitude(0), m_longitude(0) { };
	LatLong(const Maths::Vector3D<Type>& point) { Type radius; ToSpherical(point, *this, radius); };
	~LatLong(void) { };

public: // public static functions
	static void ToSpherical(const Maths::Vector3D<Type>& point, Maths::LatLong<Type>& dir, Type& radius)
	{
		radius = point.Length();
		if (radius == 0) // TODO: Replace with proper floating-point number comparison
		{
			dir.SetLatitude(-90);
			dir.SetLongitude(0);
			return;
		}

		Type r = sqrt(static_cast<float>(point.GetX() * point.GetX() + point.GetZ() * point.GetZ()));
		dir.SetLatitude(ToDeg(acos(static_cast<float>(r / radius))));
		if (point.GetY() < 0)
		{
			dir.SetLatitude((-1) * dir.GetLatitude());
		}
		if (radius == 0) // TODO: Replace with proper floating-point number comparison
		{
			dir.SetLongitude(0);
			return;
		}
		dir.SetLongitude(ToDeg(acos(static_cast<float>(point.GetX() / r))));
		if (point.GetZ() < 0)
		{
			dir.SetLongitude((-1) * dir.GetLongitude());
		}
	}
public: // public member functions
	Type GetLatitude() const { return m_latitude; };
	Type GetLongitude() const { return m_longitude; };
	void SetLatitude(Type latitude) { m_latitude = latitude; };
	void SetLongitude(Type longitude) { m_longitude = longitude; };
private:
	Type m_latitude;
	Type m_longitude;
};
	template class LatLong<int>;
	template class LatLong<float>;
	template class LatLong<double>;
	typedef LatLong<int> LatLongi;
	typedef LatLong<float> LatLongf;
	typedef LatLong<double> LatLongd;
} /* end namespace Maths */