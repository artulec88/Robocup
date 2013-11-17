#include "CameraPosition.h"

using namespace Rendering;
using namespace Maths;

CameraPosition::CameraPosition() :
	position(0.0f, 0.0f, 0.0f),
	direction(0.0f, 0.0f, 0.0f)
{
	Update();
}

CameraPosition::~CameraPosition()
{
}

void CameraPosition::Update()
{
	UpdateView();

	Model = Matrix4Df::Translation(position) * Matrix4Df::Geographic(direction);
}

void CameraPosition::UpdateView()
{
	direction.Normalize();

	/**
	 * Let alpha=Direction.longitude, beta=Direction.latitude; -Position=(-x,-y,-z)
	 *
	 * InvertedGeographic is equal to:
	 * -sin(alpha)				0			cos(alpha)				0
	 * -cos(alpha)*sin(beta)	cos(beta)	-sin(alpha)*sin(beta)	0
	 * -cos(alpha)*cos(beta)	-sin(beta)	-sin(alpha)*cos(beta)	0
	 * 0						0			0						1
	 *
	 * Translation matrix is equal to:
	 * 1	0	0	-x
	 * 0	1	0	-y
	 * 0	0	1	-z
	 * 0	0	0	1
	 *
	 * Their multiplication (view matrix) is equal to:
	 * -sin(alpha)				0			cos(alpha)				sin(alpha)*x - cos(alpha)*z
	 * -cos(alpha)*sin(beta)	cos(beta)	-sin(alpha)*sin(beta)	cos(alpha)*sin(beta)*x - cos(beta)*y + sin(alpha)*sin(beta)*z
	 * -cos(alpha)*cos(beta)	-sin(beta)	-sin(alpha)*cos(beta)	cos(alpha)*cos(beta)*x + sin(beta)*y + sin(alpha)*cos(beta)*z
	 * 0						0			0						1
	*/
	View = Matrix4Df::InvertedGeographic(direction) * Matrix4Df::Translation(-position);
}

Point3Df CameraPosition::WorldToView(const Maths::Point3Df& point) const
{
	return View * point;
}

void CameraPosition::AssignPosition(const CameraPosition& position)
{
	//Position = position.Position;
	//Direction = position.Direction;
	//Update();
}