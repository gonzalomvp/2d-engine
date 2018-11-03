#pragma once

class Vec2 {
public:
	float x;
	float y;

	Vec2();
	Vec2(float px, float py);

	Vec2  abs()                       const;
	float length()                    const;
	Vec2  normalize()                 const;
	float dot     (const Vec2& other) const;
	float angle   (const Vec2& other) const;
	float distance(const Vec2& other) const;
};

const Vec2 operator+(const Vec2& v1, const Vec2& v2);
const Vec2 operator+(const Vec2& v1, float fValue);
const Vec2 operator+(float fValue,   const Vec2& v1);

const Vec2 operator-(const Vec2& v1, const Vec2& v2);
const Vec2 operator-(const Vec2& v1, float fValue);
const Vec2 operator-(float fValue,   const Vec2& v1);

const Vec2 operator*(const Vec2& v1, const Vec2& v2);
const Vec2 operator*(const Vec2& v1, float fValue);
const Vec2 operator*(float fValue,   const Vec2& v1);

const Vec2 operator/(const Vec2& v1, const Vec2& v2);
const Vec2 operator/(const Vec2& v1, float fValue);
const Vec2 operator/(float fValue,   const Vec2& v1);