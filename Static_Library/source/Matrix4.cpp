#include <Matrix4.h>

//A constat static varialbe to use to quickly set/get identity matrix
const Matrix4 Matrix4::IDENTITY = Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

//Default Constructor - init to identity
Matrix4::Matrix4() :
	m_11(1.f), m_21(0.f), m_31(0.f), m_41(0.f),
	m_12(0.f), m_22(1.f), m_32(0.f), m_42(0.f),
	m_13(0.f), m_23(0.f), m_33(1.f), m_43(0.f),
	m_14(0.f), m_24(0.f), m_34(0.f), m_44(1.f)
{
}

//Constructor using pointer to float data
Matrix4::Matrix4(const float* a_mat) :
	m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]), m_41(a_mat[3]),
	m_12(a_mat[4]), m_22(a_mat[5]), m_32(a_mat[6]), m_42(a_mat[7]),
	m_13(a_mat[8]), m_23(a_mat[9]), m_33(a_mat[10]), m_43(a_mat[11]),
	m_14(a_mat[12]), m_24(a_mat[13]), m_34(a_mat[14]), m_44(a_mat[15])
{
}

//Constructor using all components of matrix data structure
Matrix4::Matrix4(
	float a_m11, float a_m12, float a_m13, float a_m14,
	float a_m21, float a_m22, float a_m23, float a_m24,
	float a_m31, float a_m32, float a_m33, float a_m34,
	float a_m41, float a_m42, float a_m43, float a_m44) :
	m_11(a_m11), m_21(a_m21), m_31(a_m41), m_41(a_m41),
	m_12(a_m12), m_22(a_m22), m_32(a_m42), m_42(a_m41),
	m_13(a_m13), m_23(a_m23), m_33(a_m43), m_43(a_m41),
	m_14(a_m13), m_24(a_m23), m_34(a_m43), m_44(a_m41)
{
}

//Construct form Axis angle vectors
Matrix4::Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_tAxis) :
	m_xAxis(a_xAxis), m_yAxis(a_yAxis), m_zAxis(a_zAxis), m_tAxis(a_tAxis)
{
}

//Copy Constructor
Matrix4::Matrix4(const Matrix4& a_m4) :
	m_11(a_m4.m_11), m_21(a_m4.m_21), m_31(a_m4.m_31), m_41(a_m4.m_41),
	m_12(a_m4.m_12), m_22(a_m4.m_22), m_32(a_m4.m_32), m_42(a_m4.m_42),
	m_13(a_m4.m_13), m_23(a_m4.m_23), m_33(a_m4.m_33), m_43(a_m4.m_43),
	m_14(a_m4.m_14), m_24(a_m4.m_24), m_34(a_m4.m_34), m_44(a_m4.m_44)
{
}

//Destructor
Matrix4::~Matrix4()
{

}


//Member variable access operator
#include <cassert> 

float& Matrix4::operator()(int a_row, int a_col)
{
	assert(a_col >= 0 && a_col < 4);
	assert(a_row >= 0 && a_row < 4);
	return(m[a_col - 1][a_row - 1]);
}


float Matrix4::operator()(int a_iRow, int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return(m[a_iCol - 1][a_iRow - 1]);
}

//Column and Row access

void Matrix4::SetColumn(int a_iCol, const Vector4& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x, m[a_iCol][1] = a_vCol.y, m[a_iCol][2] = a_vCol.z, m[a_iCol][3] = a_vCol.t;
}



Vector4 Matrix4::GetColumn(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	return Vector4(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2], m[a_iCol][3]);
}

//Equivalance Operators
bool Matrix4::operator == (const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return false; }
	if (m_21 != a_m4.m_21) { return false; }
	if (m_31 != a_m4.m_31) { return false; }
	if (m_41 != a_m4.m_41) { return false; }
	if (m_12 != a_m4.m_12) { return false; }
	if (m_22 != a_m4.m_22) { return false; }
	if (m_32 != a_m4.m_32) { return false; }
	if (m_42 != a_m4.m_42) { return false; }
	if (m_13 != a_m4.m_13) { return false; }
	if (m_23 != a_m4.m_23) { return false; }
	if (m_33 != a_m4.m_33) { return false; }
	if (m_43 != a_m4.m_43) { return false; }
	if (m_14 != a_m4.m_14) { return false; }
	if (m_24 != a_m4.m_24) { return false; }
	if (m_34 != a_m4.m_34) { return false; }
	if (m_44 != a_m4.m_44) { return false; }

	return true;
}

bool Matrix4::operator != (const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return true; }
	if (m_21 != a_m4.m_21) { return true; }
	if (m_31 != a_m4.m_31) { return true; }
	if (m_41 != a_m4.m_41) { return true; }
	if (m_12 != a_m4.m_12) { return true; }
	if (m_22 != a_m4.m_22) { return true; }
	if (m_32 != a_m4.m_32) { return true; }
	if (m_42 != a_m4.m_42) { return true; }
	if (m_13 != a_m4.m_13) { return true; }
	if (m_23 != a_m4.m_23) { return true; }
	if (m_33 != a_m4.m_33) { return true; }
	if (m_43 != a_m4.m_43) { return true; }
	if (m_14 != a_m4.m_14) { return true; }
	if (m_24 != a_m4.m_24) { return true; }
	if (m_34 != a_m4.m_34) { return true; }
	if (m_44 != a_m4.m_44) { return true; }

	return false;
}

//Operator Overloads for Addition
Matrix4 Matrix4:: operator + (const Matrix4& a_m4) const
{
	return Matrix4(
		m_11 + a_m4.m_11, m_21 + a_m4.m_21, m_31 + a_m4.m_31, m_41 + a_m4.m_41,
		m_12 + a_m4.m_12, m_22 + a_m4.m_22, m_32 + a_m4.m_32, m_42 + a_m4.m_42,
		m_13 + a_m4.m_13, m_23 + a_m4.m_23, m_33 + a_m4.m_33, m_43 + a_m4.m_43,
		m_14 + a_m4.m_14, m_24 + a_m4.m_24, m_34 + a_m4.m_34, m_44 + a_m4.m_44
	);
}

const Matrix4& Matrix4:: operator += (const Matrix4& a_m4)
{
	m_11 += a_m4.m_11; m_21 += a_m4.m_21; m_31 += a_m4.m_31; m_31 += a_m4.m_41;
	m_12 += a_m4.m_12; m_22 += a_m4.m_22; m_32 += a_m4.m_32; m_31 += a_m4.m_42;
	m_13 += a_m4.m_13; m_23 += a_m4.m_23; m_33 += a_m4.m_33; m_31 += a_m4.m_43;
	m_14 += a_m4.m_14; m_24 += a_m4.m_24; m_34 += a_m4.m_34; m_31 += a_m4.m_44;
	return *this;
}

//Operator Overloads for Substraction
Matrix4  Matrix4::operator - (const Matrix4& a_m4) const
{
	return Matrix4(
		m_11 - a_m4.m_11, m_21 - a_m4.m_21, m_31 - a_m4.m_31, m_41 - a_m4.m_41,
		m_12 - a_m4.m_12, m_22 - a_m4.m_22, m_32 - a_m4.m_32, m_42 - a_m4.m_42,
		m_13 - a_m4.m_13, m_23 - a_m4.m_23, m_33 - a_m4.m_33, m_43 - a_m4.m_43,
		m_14 - a_m4.m_14, m_24 - a_m4.m_24, m_34 - a_m4.m_34, m_44 - a_m4.m_44
	);
}

const Matrix4& Matrix4:: operator -= (const Matrix4& a_m4)
{
	m_11 -= a_m4.m_11; m_21 -= a_m4.m_21; m_31 -= a_m4.m_31; m_31 -= a_m4.m_41;
	m_12 -= a_m4.m_12; m_22 -= a_m4.m_22; m_32 -= a_m4.m_32; m_31 -= a_m4.m_42;
	m_13 -= a_m4.m_13; m_23 -= a_m4.m_23; m_33 -= a_m4.m_33; m_31 -= a_m4.m_43;
	m_14 -= a_m4.m_14; m_24 -= a_m4.m_24; m_34 -= a_m4.m_34; m_31 -= a_m4.m_44;
	return *this;
}

//Operator Overloads for Multiplication by scalar values
Matrix4  Matrix4::operator *(const float a_fScalar) const
{
	return Matrix4(
		m_11 * a_fScalar, m_21 * a_fScalar, m_31 * a_fScalar, m_41 * a_fScalar,
		m_12 * a_fScalar, m_22 * a_fScalar, m_32 * a_fScalar, m_42 * a_fScalar,
		m_13 * a_fScalar, m_23 * a_fScalar, m_33 * a_fScalar, m_43 * a_fScalar,
		m_14 * a_fScalar, m_24 * a_fScalar, m_34 * a_fScalar, m_44 * a_fScalar
	);
}

const Matrix4& Matrix4:: operator *= (const float a_fScalar)
{
	m_11 *= a_fScalar; m_21 *= a_fScalar; m_31 *= a_fScalar; m_31 *= a_fScalar;
	m_12 *= a_fScalar; m_22 *= a_fScalar; m_32 *= a_fScalar; m_31 *= a_fScalar;
	m_13 *= a_fScalar; m_23 *= a_fScalar; m_33 *= a_fScalar; m_31 *= a_fScalar;
	m_14 *= a_fScalar; m_24 *= a_fScalar; m_34 *= a_fScalar; m_31 *= a_fScalar;
	return *this;
}

//Operator overloads for Multiplication by Vector4 value
Vector4  Matrix4:: operator * (const Vector4& a_v4) const
{
	return Vector4
	(
		m_11 * a_v4.x + m_12 * a_v4.y + m_13 * a_v4.z + m_14 * a_v4.t,
		m_21 * a_v4.x + m_22 * a_v4.y + m_23 * a_v4.z + m_24 * a_v4.t,
		m_31 * a_v4.x + m_32 * a_v4.y + m_33 * a_v4.z + m_34 * a_v4.t,
		m_41 * a_v4.x + m_42 * a_v4.y + m_43 * a_v4.z + m_44 * a_v4.t
	);
}

//Operator Overloads for Multiplication by Matrix4
Matrix4  Matrix4::operator *(const Matrix4& a_m4) const
{
	return Matrix4(
		m_11 * a_m4.m_11 + m_12 * a_m4.m_21 + m_13 * a_m4.m_31 + m_14 * a_m4.m_41,
		m_21 * a_m4.m_11 + m_22 * a_m4.m_21 + m_23 * a_m4.m_31 + m_24 * a_m4.m_41,
		m_31 * a_m4.m_11 + m_32 * a_m4.m_21 + m_33 * a_m4.m_31 + m_34 * a_m4.m_41,
		m_41 * a_m4.m_11 + m_42 * a_m4.m_21 + m_43 * a_m4.m_31 + m_44 * a_m4.m_41,

		m_11* a_m4.m_12 + m_12 * a_m4.m_22 + m_13 * a_m4.m_32 + m_14 * a_m4.m_42,
		m_21* a_m4.m_12 + m_22 * a_m4.m_22 + m_23 * a_m4.m_32 + m_24 * a_m4.m_42,
		m_31* a_m4.m_12 + m_32 * a_m4.m_22 + m_33 * a_m4.m_32 + m_34 * a_m4.m_42,
		m_41* a_m4.m_12 + m_42 * a_m4.m_22 + m_43 * a_m4.m_32 + m_44 * a_m4.m_42,

		m_11* a_m4.m_13 + m_12 * a_m4.m_23 + m_13 * a_m4.m_33 + m_14 * a_m4.m_43,
		m_21* a_m4.m_13 + m_22 * a_m4.m_23 + m_23 * a_m4.m_33 + m_24 * a_m4.m_43,
		m_31* a_m4.m_13 + m_32 * a_m4.m_23 + m_33 * a_m4.m_33 + m_34 * a_m4.m_43,
		m_41* a_m4.m_13 + m_42 * a_m4.m_23 + m_43 * a_m4.m_33 + m_44 * a_m4.m_43,

		m_11* a_m4.m_14 + m_12 * a_m4.m_24 + m_13 * a_m4.m_34 + m_14 * a_m4.m_44,
		m_21* a_m4.m_14 + m_22 * a_m4.m_24 + m_23 * a_m4.m_34 + m_24 * a_m4.m_44,
		m_31* a_m4.m_14 + m_32 * a_m4.m_24 + m_33 * a_m4.m_34 + m_34 * a_m4.m_44,
		m_41* a_m4.m_14 + m_42 * a_m4.m_24 + m_43 * a_m4.m_34 + m_44 * a_m4.m_44
	);
}

const Matrix4& Matrix4:: operator*=(const Matrix4& a_m4)
{
	*this = (*this) * a_m4;
	return *this;
}

//Transpose Matrix - Transform Row to Column
//ASK ABOUT!!!!
void Matrix4::Transpose()
{
	float k;
	k = m_12; m_12 = m_21; m_21 = k;
	k = m_13; m_13 = m_31; m_31 = k;
	k = m_23; m_23 = m_32; m_32 = k;
}

Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(
		m_11, m_12, m_13, m_14,
		m_21, m_22, m_23, m_24,
		m_31, m_32, m_33, m_34,
		m_41, m_42, m_43, m_44
	);
}

//Scale Function
void Matrix4::Scale(const Vector4& a_v4)
{
	m_11 = a_v4.x;		m_12 = 0.0f;		m_13 = 0.0f;		m_14 = 0.0f;
	m_21 = 0.0f;		m_22 = a_v4.y;		m_23 = 0.0f;		m_24 = 0.0f;
	m_31 = 0.0f;		m_32 = 0.0f;		m_33 = a_v4.z;		m_34 = 0.0f;
	m_41 = 0.0f;		m_42 = 0.0f;		m_43 = 0.0f;		m_44 = a_v4.t;
}

void Matrix4::Scale(float a_fScalar)
{
	Scale(Vector4(a_fScalar, a_fScalar, a_fScalar, a_fScalar));
}

//General Matrix Function
void Matrix4::Identity()
{
	m_11 = 1.0f;		m_12 = 0.0f;		m_13 = 0.0f;	m_14 = 0.0f;
	m_21 = 0.0f;		m_22 = 1.0f;		m_23 = 0.0f;	m_24 = 0.0f;
	m_31 = 0.0f;		m_32 = 0.0f;		m_33 = 1.0f;	m_34 = 0.0f;
	m_41 = 0.0f;		m_42 = 0.0f;		m_43 = 0.0f;	m_44 = 1.0f;
}