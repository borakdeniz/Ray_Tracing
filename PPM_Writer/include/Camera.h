#pragma once
#include <libMath.h>

class Camera
{
public:
	//Constructor and Destructor
	Camera();

	~Camera() = default;

	//Set and get position in the world
	void setPosition(Vector3 a_v3Pos);
	Vector3 GetPosition();

	//Set Perspective Projection
	void SetPerspective(float a_fieldOfView, float a_aspectRatio, float a_near,float a_far);

	//Ortographic Projection
	void SetOrtographic(float a_left, float a_right, float a_top, float a_bottom, float a_near, float a_far);

	//Look at a certain point in the world
	void LookAt(const Vector3& a_v3Target, const Vector3& a_v3Up);

	//Cast a ray
	Ray CastRay(Vector2 a_screenspaceCoord);

	//Get Camera Position Matrix
	Matrix4 GetTransform() { return m_Transform; }

	//Get Projection Matrix
	Matrix4 GetProjectionMatrix() { return m_projectionMatrix; }
private:
	Matrix4 m_projectionMatrix;
	Matrix4 m_Transform;
	float m_aspectRatio;
	float m_fov;
	float m_zNear;
	float m_zFar;

};
