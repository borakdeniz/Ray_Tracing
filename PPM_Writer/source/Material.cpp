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

bool Material::CalcRefraction(const Ray& a_in, const IntersectionResponse& a_ir, Ray& a_out) const
{
	//Generate a random vector in range -1 : 1 for all components
	Vector3 randomUnitVec = Vector3(Random::RandRange(-1.f, 1.f), Random::RandRange(-1.f, 1.f), Random::RandRange(-1.f, 1.f));
	randomUnitVec.Normalize();

	//refract ray, from hit location
	float refraction_ratio = a_ir.frontFace ? (1.f / m_refractiveIndex) : m_refractiveIndex;
	float cos_i = Dot(-a_in.Direction(), a_ir.SurfaceNormal);

	float sin2_t = refraction_ratio * refraction_ratio * (1.f - cos_i * cos_i);
	if (sin2_t > 1.f) { return false; }
	float cos_t = sqrtf(fabsf(1.f - sin2_t));

	Vector3 refracted = a_ir.SurfaceNormal * (refraction_ratio * cos_i - cos_t) + a_in.Direction() * refraction_ratio;

	//add the random unit vector to the reflected ray based on roughness if smooth then no randomness
	a_out = Ray(a_ir.HitPos, refracted + (randomUnitVec * m_roughness), 0.001f);

	//return true if we have not reflected into the surface
	return true;
}

float Material::Schlick(const Ray& a_in, const IntersectionResponse& a_ir)const
{
	float cos_i = Dot(-a_in.Direction(), a_ir.SurfaceNormal);
	float refraction_ratio = a_ir.frontFace ? (1.f / m_refractiveIndex) : m_refractiveIndex;

	bool internalReflection = (a_ir.frontFace) ? (1.f > m_refractiveIndex) : (m_refractiveIndex > 1.f);
	if (internalReflection)
	{
		float sin2_t = refraction_ratio * refraction_ratio * (1.f - cos_i * cos_i);
		if (sin2_t > 1.f)
		{
			return 1.f;
		}
		cos_i = sqrtf(1.f - sin2_t);
	}
	float r0 = (1.f - refraction_ratio) / (1.f + refraction_ratio);
	r0 = r0 * r0;
	return r0 + (1.f - r0) * powf(1.f - cos_i, 5);
}