#pragma once
#include <Vector3.h>

class Vector4 {
public:
	//Member variables
	float x; float y; float z; float w;
#pragma region Constructors/Destructors
	//Constructors
	Vector4();
	Vector4(const Vector4& a_v4);
	Vector4(const Vector3& a_v3, float a_w = 0.f);
	Vector4(const float& a_x, const float& a_y, const float& a_z, const float& a_w);

	float Length() const;
	void				Normalize();
	friend    Vector4	Normalize(const Vector4& a_vec);

	//Destructor

	~Vector4() = default;
#pragma endregion
#pragma region Operator Overloads
	//Equivalance Operators
	bool operator == (const Vector4& a_v4) const;

	bool operator != (const Vector4& a_v4) const;

	//Negate Operator

	const Vector4 operator - () const;

	Vector3 xyz() const;

	//Subtraction Operator

	Vector4 operator - (const Vector4& a_v4) const;

	Vector4 operator - (const float a_scalar) const;

	//Addition Operator

	Vector4 operator + (const Vector4& a_v4) const;

	Vector4 operator + (const float a_scalar) const;

	//Dot Product Funtionality

	float Dot(const Vector4& a_v4) const;

	friend float Dot(const Vector4& a_v4A, const Vector4& a_v4B);

	Vector4 operator * (const float& a_scalar) const;

	friend Vector4 Lerp(const Vector4& a_v4A, const Vector4& a_v4B, const float a_t);

#pragma endregion

};

