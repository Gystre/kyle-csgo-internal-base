#include "pch.h"
#include "Vector3.h"
#include "Math.h"

Vector3::Vector3(void)
{
	x = y = z = 0.0f;
}

Vector3::Vector3(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

Vector3::Vector3(float* arr) {
	x = arr[0];
	y = arr[1];
	z = arr[2];
}

Vector3::~Vector3(void) { }

void Vector3::clamp() {
	//x = clip_number(x, -89.0f, 89.0f);
	//y = clip_number(std::remainder(y, 360.0f), -180.0f, 180.0f);
	////z = clip_number(z, -50.0f, 50.0f);
	//z = 0;

	if (x > 89.f)
		x = 89.f;

	if (x < -89.f)
		x = -89.f;

	while (y < -180.f)
		y += 360.f;

	while (y > 180.f)
		y -= 360.f;

	z = 0.0f;
}

Vector3& Vector3::normalize() {
	x = std::isfinite(x) ? std::remainder(x, 360.0f) : 0.0f;
	y = std::isfinite(y) ? std::remainder(y, 360.0f) : 0.0f;
	z = 0.0f;
	return *this;
}

float Vector3::normalizeInPlace() {
	float radius = sqrt(x * x + y * y + z * z);

	// FLT_EPSILON is added to the radius to eliminate the possibility of divide by zero.
	float iradius = 1.f / (radius + FLT_EPSILON);

	x *= iradius;
	y *= iradius;
	z *= iradius;

	return radius;
}

float Vector3::length(void) {
	float root = 0.0f, sqsr = this->lengthSqr();

	__asm        sqrtss xmm0, sqsr
	__asm        movss root, xmm0

	return root;
}

float Vector3::lengthSqr(void) {
	auto sqr = [](float n) {
		return static_cast<float>(n * n);
	};

	return (sqr(x) + sqr(y) + sqr(z));
}

float Vector3::dot(const Vector3 other) {
	return (x * other.x + y * other.y + z * other.z);
}

Vector3 Vector3::toAngle()
{
	return Vector3(radiansToDegrees(std::atan2(-z, std::hypot(x, y))),
		radiansToDegrees(std::atan2(y, x)),
		0.0f);
}

std::string Vector3::toString()
{
	return "[ " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " ]";
}