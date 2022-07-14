#include <Scene.h>
#include <Primitive.h>
#include <Light.h>
#include <Camera.h>
#include <Random.h>
#include <Material.h>

Scene::Scene(): m_pCamera(nullptr)
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


bool Scene::IntersectTest(const Ray& a_ray, IntersectionResponse &a_ir) const
{
	float intersectDist = a_ray.MaxDistance();
	bool intersectionOccured = false;
	IntersectionResponse objectIntersection;
	for (auto iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Primitive* object = (*iter);
		if (object->IntersectTest(a_ray, objectIntersection))
		{
			if (objectIntersection.distance > a_ray.MinLength()) {

				intersectionOccured = true;
				if (objectIntersection.distance < intersectDist)
				{
					intersectDist = objectIntersection.distance;
					a_ir = objectIntersection;
				}
			}
		}
	}
	return intersectionOccured;
}

Ray Scene::GetScreenRay(const Vector2& a_screenSpacePos) const
{
	//Create a Ray with origin at the camera direction into the near plane offset
	return m_pCamera->CastRay(a_screenSpacePos);
}

ColourRGB Scene::CastRay(const Ray& a_ray, int a_bounces) const
{
	if (a_bounces <= 0)
	{
		return ColourRGB(0.f, 0.f, 0.f);
	}

	IntersectionResponse ir;
	if (IntersectTest(a_ray, ir))
	{
		//calculate lighting
		Vector3 rayColour = Vector3(0.f, 0.f, 0.f);
		
		//For all lights in the scene sum the effects the lights have one the object
		for (auto lightIter = m_lights.begin(); lightIter!= m_lights.end(); lightIter++)
		{
			Ray shadowRay = Ray(ir.HitPos, -(*lightIter)->GetDirectionToLight(ir.HitPos), 0.001f);
			IntersectionResponse sr;
			float shadowValue = (!IntersectTest(shadowRay, sr));
			rayColour += (*lightIter) -> CalculateLighthing(ir, m_pCamera->GetPosition(), shadowValue);
			
			//if the material that we have hit is reflective we need to calculate the reflection vector
			//and create a new ray to project into the scene
			Ray refractRay;
			ColourRGB refractionColour = ColourRGB(0.f, 0.f, 0.f);
			if (ir.material->CalcRefraction(a_ray, ir, refractRay))
			{
				refractionColour = CastRay(refractRay, a_bounces - 1) * ir.material->GetTransparency();
			}

			ColourRGB reflectionColour = ColourRGB(0.f, 0.f, 0.f);
			Ray bounceRay;

			if (ir.material->CalcReflection(a_ray, ir, bounceRay))
			{
				refractionColour = CastRay(bounceRay, a_bounces - 1) * ir.material->GetReflective();
			}

			if (ir.material->GetReflective() > 0.f && ir.material->GetTransparency() > 0.f)
			{
				float reflectance = ir.material->Schlick(a_ray, ir);
				rayColour += reflectionColour * reflectance + refractionColour * (1.f - reflectance);
			}

			else
			{
				rayColour += reflectionColour + refractionColour;
			}
			
		}
		return rayColour;
	}
	else
	{
		Vector3 rayToColour = RaytoColour(a_ray);
		//Use Lerp to get a colour between white and blue based on the vertical value of the rayColour
		rayToColour = Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayToColour.y);
		return rayToColour;
	}
}

