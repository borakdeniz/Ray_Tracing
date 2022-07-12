#include <Ray.h>


//Default Constructor - (initialiser list)
Ray::Ray(): m_v3Origin(0.f, 0.f, 0.f),
			m_v3Direction(0.f, 0.f, 1.f),
			m_MaxLength(std::numeric_limits<float>::max()),
			m_MinLength(0.f)
{
}


//Constructor with Origin and Direction Values
Ray::Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_maxLength, float a_minLength):
	m_v3Origin(a_v3Origin), m_v3Direction(a_v3Direction), m_MaxLength(a_maxLength), m_MinLength(a_minLength)
{
	if (m_v3Direction.Length() > 1.f)
	{
		m_v3Direction.Normalize();
	}
}

//Copy Constructor
Ray::Ray(const Ray& a_Ray):
	m_v3Origin(a_Ray.m_v3Origin), m_v3Direction(a_Ray.m_v3Direction), m_MaxLength(a_Ray.m_MaxLength), m_MinLength(a_Ray.m_MinLength)
{
	if (m_v3Direction.Length() > 1.f)
	{
		m_v3Direction.Normalize();
	}
}

Ray::~Ray()
{

}

Vector3 Ray::PointAt(float a_distance)
{
	if (a_distance > m_MaxLength)
	{
		a_distance = m_MaxLength;
	}
	if (a_distance < m_MinLength)
	{
		a_distance = m_MinLength;
	}
	return m_v3Origin + (m_v3Direction * a_distance);
}


float Ray::IntersectSphere(const Vector3& a_center, const float a_radius)
{
	Vector3 OC = m_v3Origin - a_center;
	float a = m_v3Direction.Dot(m_v3Direction);
	float b = 2.f * Dot(OC, m_v3Direction);
	float c = Dot(OC, OC) - a_radius * a_radius;
	float discriminant = b * b - 4.f * a * c;
	if (discriminant < 0.f)
	{
		return -1.f;			//If less then 0, we have no intersections
	}
	else
	{//????
		return(-b - sqrtf(discriminant)) / 2.f * a; //complete the equation with the formula for smallest value
	}
}
