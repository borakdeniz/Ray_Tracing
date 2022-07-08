#pragma once

class Vector4 {
public:
	//Member variables
	float x; float y; float z; float w;
#pragma region Constructors/Destructors
	//Constructors
	Vector4();
	Vector4(const Vector4& a_v4);
	Vector4(const float& a_x, const float& a_y, const float& a_z, const float& a_w);

	float Length() const;
	void Normalize();

	//Destructor

	~Vector4() = default;
#pragma endregion
#pragma region Operator Overloads
	//Equivalance Operators
	bool operator == (const Vector4& a_v4) const;

	bool operator != (const Vector4& a_v4) const;

	//Negate Operator

	const Vector4 operator - () const;

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

