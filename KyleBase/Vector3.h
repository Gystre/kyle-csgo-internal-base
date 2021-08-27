#pragma once

class Vector3 {
public:
	Vector3();
	Vector3(float, float, float);
	Vector3(float*);
	~Vector3();

	float x, y, z;

	Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	Vector3& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}
	Vector3 operator+(const Vector3& v) {
		return Vector3{ x + v.x, y + v.y, z + v.z };
	}
	Vector3 operator-(const Vector3& v) {
		return Vector3{ x - v.x, y - v.y, z - v.z };
	}
	Vector3 operator*(const Vector3& v) {
		return Vector3{ x * v.x, y * v.y, z * v.z };
	}
	Vector3 operator*(float v) const {
		return Vector3{ x * v, y * v, z * v };
	}
	Vector3& operator/(float v) {
		x /= v; y /= v; z /= v; return *this;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}
	float operator[](int i) const {
		return ((float*)this)[i];
	}

	void clamp();
	Vector3& normalize();
	float normalizeInPlace();
	float length();
	float lengthSqr();
	float dot(const Vector3 other);
	Vector3 toAngle();
	std::string toString();
};