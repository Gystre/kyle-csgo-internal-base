#pragma once

class Vector2
{
public:
	float x, y;

	Vector2();
	Vector2(float, float);
	~Vector2();

	Vector2& operator+=(const Vector2& v) {
		x += v.x; y += v.y;  return *this;
	}
	Vector2& operator-=(const Vector2& v) {
		x -= v.x; y -= v.y; return *this;
	}
	Vector2& operator*=(float v) {
		x *= v; y *= v; return *this;
	}
	Vector2 operator-(const Vector2& v) {
		return Vector2{ x - v.x, y - v.y };
	}

	float distance(Vector2 vec);
};