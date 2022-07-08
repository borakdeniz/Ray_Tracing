#include "Vector4.h"
#include <corecrt_math.h>

//Default Constructor

Vector4::Vector4() {
	x = 0.f; y = 0.f; z = 0.f; w = 0.f;
}

//Constructor with X, Y, Z, T values

Vector4::Vector4(const float& a_x, const float& a_y, const float& a_z, const float& a_w)
{
	x = a_x;
	y = a_y;
	z = a_z;
	w = a_w;
}

float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w); 
}

void Vector4::Normalize()
{
	float length = Length();
	if (length > 0.f)
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
		w *= invLen;
	}
}
//Copy Constructor

Vector4::Vector4(const Vector4& a_v4)
{
	x = a_v4.x;
	y = a_v4.y;
	z = a_v4.z;
	w = a_v4.w;
}

//Equivalance Operators

bool Vector4::operator==(const Vector4& a_v4) const
{
	return(x == a_v4.x && y == a_v4.y && z == a_v4.z && w == a_v4.w);
}

bool Vector4::operator!=(const Vector4& a_v4) const
{
	return(x != a_v4.x || y != a_v4.y || z != a_v4.z || w != a_v4.w);
}

const Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator-(const Vector4& a_v4) const
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, w - a_v4.w);
}

Vector4 Vector4::operator - (const float a_scalar) const
{
	return Vector4(x - a_scalar, y - a_scalar, z - a_scalar, w - a_scalar);
}

Vector4 Vector4::operator+(const Vector4& a_v4) const
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, w + a_v4.w);
}

Vector4 Vector4::operator + (const float a_scalar) const
{
	return Vector4(x + a_scalar, y + a_scalar, z + a_scalar, w + a_scalar);
}

float Vector4::Dot(const Vector4& a_v4) const
{
	return (x * a_v4.x + y * a_v4.y + z * a_v4.z + w * a_v4.w);
}

float Dot(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.Dot(a_v4B);
}

Vector4 Vector4::operator*(const float& a_scalar) const
{
	return Vector4(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);
}

Vector4 Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t)
{
	return(a_v4B - a_v4A) * a_t + a_v4A;
}