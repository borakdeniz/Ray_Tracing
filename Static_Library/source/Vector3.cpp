#include "Vector3.h"
#include <corecrt_math.h>

//Default Constructor

Vector3::Vector3() {
	x = 0.f; y = 0.f; z = 0.f;
}

//Constructor with X and Y values

Vector3::Vector3(const float& a_x, const float& a_y, const float& a_z)
{
	x = a_x;
	y = a_y;
	z = a_z;
}

float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z); //ask
}

void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.f)
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}
//Copy Constructor

Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}

//Destructor

Vector3::~Vector3()
{

}

//Equivalance Operators

bool Vector3::operator==(const Vector3& a_v3) const
{
	return(x == a_v3.x && y == a_v3.y && z == a_v3.z);
}

bool Vector3::operator!=(const Vector3& a_v3) const
{
	return(x != a_v3.x || y != a_v3.y);
}

const Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-(const Vector3& a_v3) const
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}

Vector3 Vector3::operator - (const float a_scalar) const
{
	return Vector3(x - a_scalar, y - a_scalar, z - a_scalar);
}

Vector3 Vector3::operator+(const Vector3& a_v3) const
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}

Vector3 Vector3::operator + (const float a_scalar) const
{
	return Vector3(x + a_scalar, y + a_scalar, z + a_scalar);
}

float Vector3::Dot(const Vector3& a_v3) const
{
	return (x * a_v3.x + y * a_v3.y + z * a_v3.z);
}

float Dot(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return a_v3A.Dot(a_v3B);
}

Vector3 Vector3::operator*(const float& a_scalar) const
{
	return Vector3(x * a_scalar, y * a_scalar, z * a_scalar);
}

Vector3 Lerp(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t)
{
	return(a_v3B - a_v3A) * a_t + a_v3A;
}