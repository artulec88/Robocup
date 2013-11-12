#pragma once
class Color
{
public:
	Color(float red, float green, float blue, float alpha = 0.0f);
	~Color(void);

public:
	virtual float GetRed() const { return _red; };
	virtual float GetGreen() const { return _green; };
	virtual float GetBlue() const { return _blue; };
	virtual float GetAlpha() const { return _alpha; };
protected:
	float _red;
	float _green;
	float _blue;
	float _alpha;
};

