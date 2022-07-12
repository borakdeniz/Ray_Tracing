#include <libMath.h>
#include <ColourRGB.h>
#include <IntersectionResponse.h>

class Light
{
public:
	Light();
	Light(const Matrix4& a_transfrom, const ColourRGB& a_colour);

	~Light() = default;

	//Each type of light will need to calculate it's own lighting outcome based off the type of light it is
	virtual ColourRGB	CalculateLighthing	(IntersectionResponse& a_ir, const Vector3& a_eyePos) const = 0;
	
	//Get and Set Lights matrix
	Matrix4				GetTransform		()	const;
	void				SetTransform		(const Matrix4& a_m4);

	//Get and Set the position of the light
	Vector3				GetPosition			() const;
	void				SetPosition			(const Vector3& a_v3);

	//Get and Set the colour of the light
	const ColourRGB&	GetColour			()	const { return m_colourRGB; }
	void				SetColour			(const ColourRGB& a_colour) { m_colourRGB = a_colour; }

protected:
	Matrix4 m_Transform;	//Transform of the light
	ColourRGB m_colourRGB;	//Colour of the light
};