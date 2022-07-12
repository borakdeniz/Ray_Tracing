#pragma once

class Vector3 {
public:
	//Member variables
	float x; float y; float z;
#pragma region Constructors/Destructors
	//Constructors
	Vector3();
	Vector3(const Vector3& a_v3);
	Vector3(const float& a_x, const float& a_y, const float& a_z);

	float Length() const;

	//\=========================================================================
	//\ Normalise the Vector - modifies member variables (non const function)
	//\=========================================================================
	void				Normalize();
	friend    Vector3	Normalize	(const Vector3& a_vec);

	//Destructor

	~Vector3();
#pragma endregion
#pragma region Operator Overloads
	//Equivalance Operators
	bool operator ==				(const Vector3& a_v3) const;

	bool operator !=				(const Vector3& a_v3) const;

	//Negate Operator

	const Vector3 operator - () const;

	//Subtraction Operator

	Vector3 operator -				(const Vector3& a_v3) const;

	Vector3 operator -				(const float a_scalar) const;

	//Addition Operator

	Vector3 operator +				(const Vector3& a_v3) const;

	Vector3 operator +				(const float a_scalar) const;

	const Vector3& operator	+=		(const Vector3& a_v3);

	//Dot Product Funtionality

	float				Dot			(const Vector3& a_v3) const;

	friend float		Dot			(const Vector3& a_v3A, const Vector3& a_v3B);

	Vector3 operator *				(const float& a_scalar) const; 

	friend Vector3		Lerp		(const Vector3& a_v3A, const Vector3& a_v3B, const float a_t);

	//\=========================================================================
	//\ Cross Product
	//\=========================================================================
	Vector3				Cross		(const Vector3& a_v3) const;
	friend Vector3      Cross		(const Vector3& a_v3a, const Vector3& a_v3b);

	//Reflect one vector around another
	friend Vector3		Reflect		(const Vector3& a_v3A, const Vector3& a_v3B);
#pragma endregion

};

