#pragma once
#pragma once
#include <Vector4.h>

class Matrix4
{
private:

	union
	{
		struct 
		{
			float m[4][4];
		};
		
		struct
		{
			float m_11, m_12, m_13, m_14; // Column 1 -> x axis
			float m_21, m_22, m_23, m_24; // Column 2 -> y axis
			float m_31, m_32, m_33, m_34; // Column 3 -> z axis
			float m_41, m_42, m_43, m_44; // Column 4 -> w axis

		};

		struct
		{
			Vector4 m_xAxis;
			Vector4 m_yAxis;
			Vector4 m_zAxis;
			Vector4 m_wAxis;

		};
	};

public:
	//Constants
	static const Matrix4 IDENTITY;

	//Constructors
	Matrix4();
	Matrix4(const float* a_mat);
	Matrix4(
			float m_11, float m_12, float m_13, float m_14,
			float m_21, float m_22, float m_23, float m_24,
			float m_31, float m_32, float m_33, float m_34,
			float m_41, float m_42, float m_43, float m_44
	);
	Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_wAxis);
	Matrix4(const Matrix4& a_m4);

	//Destructor
	~Matrix4();

	//Component Access Operators
	float&		operator()		(int a_iColumn, int a_iRow);
	float		operator()		(int a_iColumn, int a_iRow) const;

	//Column and Row Access 
	void		SetColumn(int a_iCol, const Vector4& a_vCol);
	Vector4		GetColumn(int a_iCol) const;

	//Equivalance Operator
	bool		operator ==		(const Matrix4& a_m4) const;
	bool		operator !=		(const Matrix4& a_m4) const;

	//Overload operators for Substraction
	Matrix4		operator -		(const Matrix4& a_m4) const;
	const Matrix4& operator -=		(const Matrix4& a_m4);

	//Overload operators for Addition
	Matrix4		operator +		(const Matrix4& a_m4) const;
	const Matrix4& operator +=		(const Matrix4& a_m4);

	//Overload operators for Multiplication
	Matrix4		operator *		(const float a_scalar) const;
	const Matrix4& operator *=		(const float a_scalar);

	Vector4		operator *		(const Vector4& a_v4) const;

	Matrix4		operator *		(const Matrix4& a_m4) const;
	const Matrix4& operator *=		(const Matrix4& a_m4);

	//Transpose
	void		Transpose();
	Matrix4		GetTranspose() const;

	//Scale
	void		Scale(const float a_scalar);
	void		Scale(const Vector4& a_v4);

	//Identity
	void		Identity();

	//Determinant
	float		Determinant() const;

	//Inverse
	Matrix4		Inverse()	const;

};