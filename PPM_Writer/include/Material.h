#pragma once

#include <libMath.h>
#include <IntersectionResponse.h>

class Material
{
public:
	Material() : m_albedo(1.f, 1.f, 1.f), m_ambient(0.f), m_diffuse(0.f), m_specular(0.f), m_roughness(0.f), m_reflective(0.f) , m_transparency(0.f), m_refractiveIndex(1.f) {};
	Material(const Vector3& a_albedo, float a_ambient, float a_diffuse, float a_specular, float a_roughness, float a_reflective = 0.f, float a_transparency = 0.f, float a_refractiveIndex = 1.f):
		m_albedo(a_albedo), m_ambient(a_ambient), m_diffuse(a_diffuse), m_specular(a_specular), m_roughness(a_roughness), m_reflective(a_reflective), m_transparency(a_transparency), m_refractiveIndex(a_refractiveIndex) {};
	~Material() = default;

	const Vector3& GetAlbedo() { return m_albedo; }
	void SetAlbedo(const Vector3& a_albedo) { m_albedo; }

	const float& GetAmbient() const { return m_ambient; }
	void SetAmbient(const float& a_ambient) { m_ambient = a_ambient; }

	const float& GetDiffuse() const { return m_diffuse; }
	void SetDiffuse(const float& a_diffuse) { m_diffuse = a_diffuse; }

	const float& GetSpecular() const { return m_specular; }
	void SetSpecular(const float& a_specular) { m_specular = a_specular; }

	const float& GetRougness() const { return m_roughness; }
	void SetRoughness(const float& a_roughness) { m_roughness = a_roughness; }

	const float& GetReflective() const { return m_reflective; }
	void SetReflective(const float& a_reflective) { m_reflective = a_reflective; }

	const float& GetTransparency() const { return m_transparency; }
	void SetTransparency(const float& a_transparency) { m_transparency = a_transparency; }

	const float& GetRIndex() const { return m_refractiveIndex; }
	void SetRIndex(const float& a_refractiveIndex) { m_refractiveIndex = a_refractiveIndex; }

	bool CalcReflection(const Ray& a_in, const IntersectionResponse& a_ir, Ray& a_out) const;
	bool CalcRefraction(const Ray& a_in, const IntersectionResponse& a_ir, Ray& a_out) const;

	float Schlick(const Ray& a_in, const IntersectionResponse& a_ir) const;

protected:
	Vector3 m_albedo;			//Material albeo colour - colour of light reflected from surface
	float m_ambient;			//ambient component of material 0 -> 1.0
	float m_diffuse;			//diffuse component of material 0 -> 1.0
	float m_specular;			//specular component of material 0 -> 1.0
	float m_roughness;			//roughness component of material 0 -> 1.0
	float m_reflective;			//reflectivity component of material 0 -> 1.0
	float m_transparency;		//transparency component of material 0 -> 1.0
	float m_refractiveIndex;	//refractive index of the surface
};