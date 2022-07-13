#include <DirectionalLight.h>
#include <cmath>
#include <Material.h>



DirectionalLight::DirectionalLight()
{
	SetDirection(Vector3(0.f, 0.f, 0.f));
}

DirectionalLight::DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing):
	Light(a_transform, a_colour)
{
	SetDirection(a_facing);
}

DirectionalLight:: ~DirectionalLight()
{
}


//Functionality to Set and Get the direction of the light
void DirectionalLight::SetDirection(const Vector3& a_direction, const Vector3& a_up)
{
	m_Transform.SetColumn(2, a_direction);
	m_Transform.SetColumn(1, a_up);
	m_Transform.Orthonormalise();
}

Vector3	DirectionalLight::GetDirection() const
{
	return m_Transform.GetColumn(2).xyz();
}



ColourRGB DirectionalLight::CalculateLighthing(const IntersectionResponse& a_ir, const Vector3& a_eyePos, float a_shadowFactor) const
{	
	Vector3 effectiveColour = a_ir.material->GetAlbedo();

	//Treat all surfaces as being the same under this light
	ColourRGB ambient = effectiveColour * a_ir.material->GetAmbient();												//Get ambient colour for surface
	
	//Light direction is forward axis of light matrix
	Vector3 lightDirection = -GetDirection();														//Get direction to light from surface
	float lightDiffuse = MathLib::Max(0.f, Dot(lightDirection, a_ir.SurfaceNormal));				//Positive value indicate vectors in same direction
	ColourRGB diffuse = effectiveColour * a_ir.material->GetDiffuse() * lightDiffuse;										//Blend light diffuse with diffuse value and colour
		
	//Calculate light specular value
	Vector3 eyeDir = Normalize(a_ir.HitPos - a_eyePos);
	Vector3 reflectionVec = Reflect(eyeDir, a_ir.SurfaceNormal);

	float specularPower = (1.0f - a_ir.material->GetRougness()) * 254.f + 1.0f;
	float specularFactor = std::powf(MathLib::Max(0.f, Dot(reflectionVec, lightDirection)), specularPower);
	ColourRGB specular = m_colourRGB * a_ir.material->GetSpecular() * specularFactor;

	return ambient + (diffuse + specular) * a_shadowFactor;
}

Vector3 DirectionalLight::GetDirectionToLight(const Vector3& a_point) const
{
	return GetDirection();
}
