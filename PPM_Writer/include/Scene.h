#pragma once

#include <vector>
#include <libMath.h>
#include <IntersectionResponse.h>
#include <ColourRGB.h>

class Primitive;
class Light;
class Camera;

class Scene
{
public:
	//Constructor and Destructor
	Scene();
	~Scene();

	//Add and Remove object
	void		AddObject		(const Primitive* a_object);
	void		RemoveObject	(const Primitive* a_object);

	//Add and Remove Light
	void		AddLight		(const Light* a_light);
	void		RemoveLight		(const Light* a_light);

	Ray			GetScreenRay	(const Vector2& a_screenSpacePos)	const;

	ColourRGB	CastRay			(const const Ray& a_ray, int a_bounces)	const;

	//Intersection Test
	bool		IntersectTest	(const Ray& a_ray, IntersectionResponse& ir) const;


	void		SetCamera		(Camera* a_pCamera) { m_pCamera = a_pCamera; }

private:
	std::vector<const Primitive*> m_objects;
	std::vector<const Light*> m_lights;
	Camera* m_pCamera;


};