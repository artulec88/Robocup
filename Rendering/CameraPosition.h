#pragma once

#include "Maths\Vector.h"

namespace Rendering
{
class CameraPosition
{
public: // constructors and destructors
	CameraPosition();
	~CameraPosition();

public: // public member functions
	void Update();
	void UpdateView();
	Maths::Point3Df WorldToView(const Maths::Point3Df& point) const;
	void AssignPosition(const CameraPosition& position);

protected: // protected member variables
	Maths::Point3Df position;
	Maths::Vector3Df direction;
};
} /* end namespace Rendering */