#include "Vector4.h"
#include <corecrt_math.h>

//Default Constructor

Vector4::Vector4() {
	x = 0.f; y = 0.f; z = 0.f; t = 0.f;
}

//Constructor with X, Y, Z, T values

Vector4::Vector4(const float& a_x, const float& a_y, const float& a_z, const float& a_t)
{
	x = a_x;
	y = a_y;
	z = a_z;
	t = a_t;
}

float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + t * t); 
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
		t *= invLen;
	}
}
//Copy Constructor

Vector4::Vector4(const Vector4& a_v4)
{
	x = a_v4.x;
	y = a_v4.y;
	z = a_v4.z;
	t = a_v4.t;
}

//Destructor

Vector4::~Vector4()
{

}

//Equivalance Operators

bool Vector4::operator==(const Vector4& a_v4) const
{
	return(x == a_v4.x && y == a_v4.y && z == a_v4.z && t == a_v4.t);
}

bool Vector4::operator!=(const Vector4& a_v4) const
{
	return(x != a_v4.x || y != a_v4.y || z != a_v4.z || t != a_v4.t);
}

const Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -t);
}

Vector4 Vector4::operator-(const Vector4& a_v4) const
{
	return Vector4(x - a_v4.x, y - a_v4.y, z - a_v4.z, t - a_v4.t);
}

Vector4 Vector4::operator - (const float a_scalar) const
{
	return Vector4(x - a_scalar, y - a_scalar, z - a_scalar, t - a_scalar);
}

Vector4 Vector4::operator+(const Vector4& a_v4) const
{
	return Vector4(x + a_v4.x, y + a_v4.y, z + a_v4.z, t + a_v4.t);
}

Vector4 Vector4::operator + (const float a_scalar) const
{
	return Vector4(x + a_scalar, y + a_scalar, z + a_scalar, t + a_scalar);
}

float Vector4::Dot(const Vector4& a_v4) const
{
	return (x * a_v4.x + y * a_v4.y + z * a_v4.z + t * a_v4.t);
}

float Dot(const Vector4& a_v4A, const Vector4& a_v4B)
{
	return a_v4A.Dot(a_v4B);
}

Vector4 Vector4::operator*(const float& a_scalar) const
{
	return Vector4(x * a_scalar, y * a_scalar, z * a_scalar, t * a_scalar);
}

Vector4 Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t)
{
	return(a_v4B - a_v4A) * a_t + a_v4A;
}