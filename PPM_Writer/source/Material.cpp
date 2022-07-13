#include <Material.h>
#include <libMath.h>

bool Material::CalcReflection(const Ray& a_in, const IntersectionResponse& a_ir, Ray& a_out) const
{
	//Generate a random vector in range -1 : 1 for all components
	Vector3 randomUnitVec = Vector3(Random::RandRange(-1.f, 1.f), Random::RandRange(-1.f, 1.f), Random::RandRange(-1.f, 1.f));
	randomUnitVec.Normalize();

	//reflected ray, from hit location
	Vector3 reflected = Normalize(Reflect(a_in.Direction(), a_ir.SurfaceNormal));
	
	//add the random unit vector to the reflected ray based on roughness if smooth then no randomness
	a_out = Ray(a_ir.HitPos, reflected + (randomUnitVec * m_roughness), 0.001f);

	//return true if we have not reflected into the surface
	return(Dot(a_out.Direction(), a_ir.SurfaceNormal) > 0.f);
}