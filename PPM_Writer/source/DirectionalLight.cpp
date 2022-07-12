#include <DirectionalLight.h>
#include <cmath>



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



ColourRGB DirectionalLight::CalculateLighthing(const Vector3& a_hitPoint, const Vector3& a_eyePos, const Vector3& a_normal) const
{
	//Treat all surfaces as being the same under this light
	ColourRGB ambient = m_colourRGB * 0.1f;										//Get ambient colour for surface
	
	//Light direction is forward axis of light matrix
	Vector3 lightDirection = -GetDirection();									//Get direction to light from surface
	float lightDiffuse = MathLib::Max(0.f, Dot(lightDirection, a_normal));				//Positive value indicate vectors in same direction
	ColourRGB diffuse = m_colourRGB * 0.9f * lightDiffuse;						//Blend light diffuse with diffuse value and colour
		
	//Calculate light specular value
	Vector3 eyeDir = Normalize(a_eyePos - a_hitPoint);
	Vector3 reflectionVec = Reflect(eyeDir, a_normal);
	float specularFactor = std::powf(MathLib::Max(0.f, Dot(reflectionVec, lightDirection)), 64.f);
	ColourRGB specular = m_colourRGB * 0.9f * specularFactor;

	return ambient + diffuse + specular;
}