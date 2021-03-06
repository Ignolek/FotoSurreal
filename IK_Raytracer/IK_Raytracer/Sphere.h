#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"

class Sphere : public Hitable
{
private:
	vec3 center;
	float radius;

public:
	Sphere() : center(0, 0, 0), radius(0.1f) {};
	Sphere(vec3 cen, float r) : center(cen), radius(r) {};

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

			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin)
		{
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			
			return true;
		}
	}

	return false;
}

