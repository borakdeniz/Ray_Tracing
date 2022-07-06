#pragma once

class Vector2 {
public:
	//Member variables
	float x; float y;
#pragma region Constructors/Destructors
	//Constructors
	Vector2();
	Vector2(const Vector2& a_v2);
	Vector2(const float& a_x, const float& a_y);

	//Destructor

	~Vector2();
#pragma endregion
#pragma region Operator Overloads
	//Equivalance Operators
	bool operator == (const Vector2& a_v2) const;

	bool operator != (const Vector2& a_v2) const;

	//Negate Operator

	const Vector2 operator - () const;

	//Addition Operator

	Vector2 operator + (const Vector2& a_v2) const;

	//Dot Product Funtionality

	float Dot(const Vector2& a_v2) const;

	friend float Dot(const Vector2& a_v2A, const Vector2& a_v2B);
#pragma endregion

};