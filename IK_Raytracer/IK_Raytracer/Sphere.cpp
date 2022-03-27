#include "Sphere.h"

Sphere::Sphere() : coords(0,0,0), radius(0) {}

Sphere::Sphere(vec3 coordinates, float r)
{
	this->coords = coordinates;
	this->radius = r;
}

//vec3* Sphere::intersect(Ray& ray)
//{
//	//obliczamy równanie kwadratowe
//	vec3 v = ray.origin() - this->coords;
//	float a = dot(ray.direction(), ray.direction());
//	float b = dot(2.0 * (ray.direction());
//	float c = v.dotProduct(v) - (this->radius * this->radius);
//	float u[2];
//
//	Vector* crossCoord = nullptr;
//	//obliczamy wyró¿nik kwadratowy
//	float discriminant = b * b - 4 * a * c;
//	//zwracamy lokacje przeciêcia
//	if (discriminant > 0.0)
//	{
//		const float root = sqrt(discriminant);
//		const float denom = 2.0 * a;
//
//		crossCoord = new Vector(((-b + root) / denom), ((-b - root) / denom), 0);
//		/*u[0] = (-b + root) / denom;
//		u[1] = (-b - root) / denom;*/
//	}
//	else if (discriminant == 0.0)
//	{
//		const float denom = 2.0 * a;
//
//		crossCoord = new Vector(((-b) / denom), 0.0, 0.0);
//		/*u[0] = (-b) / denom;
//		u[1] = 0.0;*/
//	}
//	else if (discriminant < 0.0)
//	{
//		//zwracamy wartoœæ null kiedy nie wystêpuje przeciêcie ze sfer¹
//		return nullptr;
//	}
//
//	return crossCoord;
//}

bool Sphere::hitRay(Ray& ray)
{
	vec3 oc = ray.origin() - this->coords;
	float a = dot(ray.direction(), ray.direction());
	float b = 2.0 * dot(oc, ray.direction());
	float c = dot(oc, oc) - this->radius * this->radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
