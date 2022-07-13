#include <Ellipsoid.h>

Ellipsoid::Ellipsoid() :m_radius(1.f)
{
}

Ellipsoid::Ellipsoid(const Vector3& a_position, const float& a_radius) : m_radius(a_radius)
{
	SetPosition(a_position);
	SetScale(Vector3(m_radius, m_radius, m_radius));
}

Ellipsoid::~Ellipsoid()
{
}

bool Ellipsoid::IntersectTest(const Ray& a_ray, IntersectionResponse& a_ir) const
{
	Matrix4 normalMatrix = m_Transform.GetTranspose().Inverse();

	Matrix4 invTx = m_Transform.Inverse();
	Vector4 rayOrigin = invTx * Vector4(a_ray.Origin(), 1.f);
	Vector4 rayDir = Normalize(invTx * Vector4(a_ray.Direction()));

	Vector3 OC = rayOrigin.xyz();
	float b = Dot(OC, rayDir.xyz());
	float c = Dot(OC, OC) - 1.f;
	float discriminant = b * b - c;
	if (discriminant < 0.f)
	{
		return false;
	}
	else
	{
		float dist = -1.f;
		float i0 = -b - sqrt(discriminant);
		float i1 = -b + sqrt(discriminant);
		if (i0 > 0.f) { dist = i0; }
		else if (i1 > 0.f) { dist = i1; }
		else { return false; }
		Vector4 hp = rayOrigin + rayDir * dist;
		Vector3 sn = Normalize(hp.xyz());
		hp = m_Transform * hp;
		a_ir.HitPos = Vector3(hp.x, hp.y, hp.z);
		a_ir.SurfaceNormal = Normalize(normalMatrix * sn);
		a_ir.distance = (a_ray.Origin() - hp.xyz()).Length();
		a_ir.material = m_material;

		return true;
	}
	return false;
}