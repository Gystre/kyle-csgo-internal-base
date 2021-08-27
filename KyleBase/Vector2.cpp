#include "pch.h"
#include "Vector2.h"

Vector2::Vector2()
{
	x = y = 0;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::distance(Vector2 vec)
{
	float dx = vec.x - x;
	float dy = vec.y - y;

	return sqrt(dx * dx + dy * dy);
}

Vector2::~Vector2() {}