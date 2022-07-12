#include <Light.h>

Light::Light() : m_Transform(Matrix4::IDENTITY), m_colourRGB(1.f, 1.f, 1.f)
{
}

Light::Light(const Matrix4& a_transform, const ColourRGB& a_colour) :
	m_Transform(a_transform), m_colourRGB(a_colour)
{
}

//Get and set Lights Matrix
Matrix4 Light::GetTransform() const
{
	return m_Transform;
}

void Light::SetTransform(const Matrix4& a_m4)
{
	m_Transform = a_m4;
}

//Get and Set the position of the light
Vector3	Light::GetPosition() const
{
	return m_Transform.GetColumnV3(3);
}

void Light::SetPosition(const Vector3& a_v3)
{
	m_Transform.SetColumn(3, a_v3);
}

Vector3 Light::GetDirectionToLight(const Vector3& a_point) const
{
	return Normalize(GetPosition() - a_point);
}