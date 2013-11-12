#include "Color.h"


Color::Color(float red, float green, float blue, float alpha /* = 0.0f */)
{
	_red	= red;
	_green	= green;
	_blue	= blue;
	_alpha	= alpha;
}


Color::~Color(void)
{
}
