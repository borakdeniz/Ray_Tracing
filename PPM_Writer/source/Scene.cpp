#include <Scene.h>
#include <Primitive.h>
#include <Light.h>
#include <Camera.h>
#include <Random.h>

Scene::Scene()
{
	m_objects.clear();
	m_lights.clear();
}

Scene::~Scene()
{
	m_pCamera = nullptr;
	m_objects.clear();
	m_lights.clear();
}

void Scene::AddObject(const Primitive* a_object)
{
	m_objects.push_back(a_object);
}

void Scene::RemoveObject(const Primitive* a_object)
{
	for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		if (*iter == a_object)					//We have located the object
		{
			iter = m_objects.erase(iter);		//Delete the object from the vector
		}
	}
}

void Scene::AddLight(const Light* a_light)
{
	m_lights.push_back(a_light);
}

void Scene::RemoveLight(const Light* a_light)
{
	for (auto iter = m_lights.begin(); iter != m_lights.end(); iter++)
	{
		if (*iter == a_light)					//We have located the object
		{
			iter = m_lights.erase(iter);		//Delete the object from the vector
		}
	}
}


bool Scene::HitTest(const Ray& a_ray, IntersectionResponse& a_ir)
{
	float intersectDist = FLT_MAX;
	bool intersectionOccured = false;
	IntersectionResponse objectIntersection;
	for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Primitive* object = (*iter);
		if (object->IntersectTest(a_ray, objectIntersection))
		{
			intersectionOccured = true;
			if (objectIntersection.distance < intersectDist)
			{
				intersectDist = objectIntersection.distance;
				a_ir = objectIntersection;
			}
		}
	}
	return intersectionOccured;
}

ColourRGB Scene::IntersectTest(const Ray& a_ray, int bounces)
{
	IntersectionResponse ir;
	if (HitTest(a_ray, ir))
	{
		if (bounces <= 0)
		{
			return ColourRGB(0.f, 0.f, 0.f);
		}
		//Generate a random vector in range -1 -> 1 for all components
		Vector3 randomUnitVec = Vector3(Random::RandRange(-1.f, 1.f), Random::RandRange(-1.f, 1.f), Random::RandRange(-1.f, 1.f));
		randomUnitVec.Normalize();
		
		//Bounced ray, from hit location, with random direction reflected from surface
		Ray bounceRay = Ray(ir.HitPos + (ir.SurfaceNormal * 0.001f), (ir.HitPos + ir.SurfaceNormal + randomUnitVec) - ir.HitPos);

		//Call Intersect Test function to accumulate colour of pixel with bounce ray
		ColourRGB rayColour = IntersectTest(bounceRay, bounces - 1) * ir.colour;
		if (m_pCamera != nullptr)
		{
			//for all lights in the scene sum the effects the lights have on the object
			for (auto lightIter = m_lights.begin(); lightIter != m_lights.end(); lightIter++)
			{
				rayColour += (*lightIter)->CalculateLighthing(ir, m_pCamera->GetPosition());
			}
			return rayColour * 0.5f;
		}
	}
	Vector3 rayToColour = RaytoColour(a_ray);
	rayToColour = Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayToColour.y);
	return rayToColour;
}