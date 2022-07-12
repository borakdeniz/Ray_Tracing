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

//\============================================================================
//\ Normalise the Vector
//\============================================================================
void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.f)            //if this is false vector has no length
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}
Vector3 Normalize(const Vector3& a_vec3)
{
	float mag = a_vec3.Length();
	if (mag > 0.f) {
		return Vector3(a_vec3.x / mag, a_vec3.y / mag, a_vec3.z / mag);
	}
	return Vector3(0.f, 0.f, 0.f);
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
	return(x != a_v3.x || y != a_v3.y || z != a_v3.z);
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

//\=========================================================================
//\ Cross Product
//\=========================================================================
Vector3 Vector3::Cross(const Vector3& a_v3) const
{
	return Vector3(y * a_v3.z - a_v3.y * z, z * a_v3.x - x * a_v3.z, x * a_v3.y - y * a_v3.x);
}
Vector3    Cross(const Vector3& a_v3a, const Vector3& a_v3b)
{
	return a_v3a.Cross(a_v3b);
}

Vector3		Reflect(const Vector3& a_v3A, const Vector3& a_v3B)
{
	Vector3 reflect = a_v3A - (a_v3B * 2.f * Dot(a_v3A, a_v3B));
	return reflect;
}

const Vector3& Vector3:: operator += (const Vector3& a_v3)
{
	x += a_v3.x;	y += a_v3.y;	z += a_v3.z;
	return *this;
}