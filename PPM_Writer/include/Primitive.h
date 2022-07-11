#pragma once
#include <libMath.h>

class Primitive
{
public:
	Primitive();

	virtual ~Primitive();
	
	virtual bool IntersectTest(const Ray& a_ray, Vector3& a_hitPos, Vector3& a_surfNormal) const = 0;

	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);

	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);

	Vector3 GetScale() const;
	void SetScale(const Vector3& a_v3);

protected:
	Matrix4 m_Transform;
	Vector3 m_Scale;

};