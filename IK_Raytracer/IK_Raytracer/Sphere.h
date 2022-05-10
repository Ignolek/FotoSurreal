#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "Material.h"

class Sphere : public Hitable
{
private:
	vec3 center;
	float radius;
	vec3 color;
	Material* sphereMaterial;

public:
	Sphere() : center(0, 0, 0), radius(0.1f), color(255, 255, 0) {};
	Sphere(vec3 cen, float r, vec3 col, Material* sphereMat) : center(cen), radius(r), color(col), sphereMaterial(sphereMat) {};

	//vec3* intersect(Ray& a_Ray);
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;
};

bool Sphere::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			//rec.hitColor = color;
			rec.materialPtr = sphereMaterial;
			rec.hit = true;

			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			//rec.hitColor = color;
			rec.materialPtr = sphereMaterial;
			rec.hit = true;
			
			return true;
		}
	}

	rec.hit = false;
	return false;
}

