#include <cmath>

#include "Base.h"
#include "Vec2.h"


Vec2::Vec2()
{	
	x = 0;
	y = 0;
}

Vec2::Vec2(float px, float py)
{	
	x = px;
	y = py;
}

Vec2 Vec2::abs() const
{	
	Vec2 ret;

	ret.x = std::abs(x);
	ret.y = std::abs(y);

	return ret;
}

float Vec2::length() const
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normalize() const
{
	float l = length();
	return (l != 0) ? *this / l : *this;
}

float Vec2::dot(const Vec2& other) const
{
	return x * other.x + y * other.y;
}

float Vec2::angle(const Vec2& other) const
{	
	float ret = atan2(-(other.y - y), other.x - x) * 180 / PI;

	if (ret < 0) {
		ret += 360;
	}

	return ret;
}

float Vec2::distance(const Vec2& other) const
{
	return (other - *this).length();
}

const Vec2 operator+(const Vec2& v1, const Vec2& v2)
{
	Vec2 ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;

	return ret;
}

const Vec2 operator+(const Vec2& v1, float fValue)
{
	Vec2 ret;

	ret.x = v1.x + fValue;
	ret.y = v1.y + fValue;

	return ret;
}

const Vec2 operator+(float fValue, const Vec2& v1)
{
	return v1 + fValue;
}


const Vec2 operator-(const Vec2& v1, const Vec2& v2)
{	
	Vec2 ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;

	return ret;
}

const Vec2 operator-(const Vec2& v1, float fValue)
{
	Vec2 ret;

	ret.x = v1.x - fValue;
	ret.y = v1.y - fValue;

	return ret;
}

const Vec2 operator-(float fValue, const Vec2& v1)
{
	Vec2 ret;

	ret.x = fValue - v1.x;
	ret.y = fValue - v1.y;

	return ret;
}

const Vec2 operator*(const Vec2& v1, const Vec2& v2)
{
	Vec2 ret;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;

	return ret;
}

const Vec2 operator*(const Vec2& v1, float fValue)
{
	Vec2 ret;

	ret.x = v1.x * fValue;
	ret.y = v1.y * fValue;

	return ret;
}

const Vec2 operator*(float fValue, const Vec2& v1)
{
	return v1 * fValue;
}

const Vec2 operator/(const Vec2& v1, const Vec2& v2)
{
	Vec2 ret;

	ret.x = v1.x / v2.x;
	ret.y = v1.y / v2.y;

	return ret;
}

const Vec2 operator/(const Vec2& v1, float fValue)
{
	Vec2 ret;

	ret.x = v1.x / fValue;
	ret.y = v1.y / fValue;

	return ret;
}

const Vec2 operator/(float fValue, const Vec2& v)
{
	Vec2 ret;

	ret.x = fValue / v.x;
	ret.y = fValue / v.y;

	return ret;
}