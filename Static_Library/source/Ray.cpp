#include <Ray.h>


//Default Constructor - (initialiser list)
Ray::Ray(): m_v3Origin(0.f, 0.f, 0.f),
			m_v3Direction(0.f, 0.f, 1.f),
			m_MaxLength(std::numeric_limits<float>::max())
{
}


//Constructor with Origin and Direction Values
Ray::Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_maxLength): 
	m_v3Origin(a_v3Origin), m_v3Direction(a_v3Direction), m_MaxLength(a_maxLength)
{
	if (m_v3Direction.Length() > 1.f)
	{
		m_v3Direction.Normalize();
	}
}

//Copy Constructor
Ray::Ray(const Ray& a_Ray):
	m_v3Origin(a_Ray.m_v3Origin), m_v3Direction(a_Ray.m_v3Direction), m_MaxLength(a_Ray.m_MaxLength)
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
	return m_v3Origin + (m_v3Direction * a_distance);
}


bool Ray::IntersectSphere(const Vector3& a_center, const float a_radius)
{
	Vector3 OC = m_v3Origin - a_center;
	float a = m_v3Direction.Dot(m_v3Direction);
	float b = 2.f * Dot(OC, m_v3Direction);
	float c = Dot(OC, OC) - a_radius * a_radius;
	float discriminant = b * b - 4.f * a * c;
	return (discriminant > 0.f); //ask about
}
