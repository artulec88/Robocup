#include "CameraPosition.h"

using namespace Rendering;
using namespace Maths;

CameraPosition::CameraPosition() :
	position(0.0f, 0.0f, 0.0f),
	direction(0.0f, 0.0f, 0.0f)
{
}

CameraPosition::~CameraPosition()
{
}

void CameraPosition::Update()
{
}

void CameraPosition::UpdateView()
{
}

Point3Df CameraPosition::WorldToView(const Maths::Point3Df& point) const
{
	return Point3Df();
}

void CameraPosition::AssignPosition(const CameraPosition& position)
{

}