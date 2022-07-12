#pragma once

#include <vector>
#include <libMath.h>
#include <IntersectionResponse.h>

class Primitive;

class Scene
{
public:
	//Constructor and Destructor
	Scene();
	~Scene();

	//Add and Remove object
	void AddObject(const Primitive* a_object);
	void RemoveObject(const Primitive* a_object);

	//Intersection Test
	bool IntersectTest(const Ray& a_ray, IntersectionResponse& a_ir);
private:
	std::vector<const Primitive*> m_objects;

};