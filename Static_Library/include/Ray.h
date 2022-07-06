#pragma once
#include <Vector3.h>
#include <limits>

class Ray
{
private:
	Vector3 m_v3Origin;
	Vector3 m_v3Direction;
	float m_MaxLength;

public:
#pragma region Constructors/Destructors
	//Constructors
	Ray();
	Ray(const Vector3& a_v3Origin, const Vector3& a_v3Direction, float a_MaxLength = std::numeric_limits<float>::max());
	
	//Copy Constructor
	Ray(const Ray& a_Ray);

	//Destructor
	~Ray();
#pragma endregion
#pragma region Getters
	 //Getters
	Vector3 Origin() const { return m_v3Origin; }
	Vector3 Direction() const { return m_v3Direction; }
#pragma endregion
	//Get Point along ray at distance
	Vector3 PointAt(float a_distance);

	//Sphere Intersection Test
	bool IntersectSphere(const Vector3& a_center, const float a_radius);


};