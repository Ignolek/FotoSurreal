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
	Material* sphereMaterial;
	bool isTexRect = false;

public:
	Sphere() : center(0, 0, 0), radius(0.1f){};
	Sphere(vec3 cen, float r, Material* sphereMat) : center(cen), radius(r), sphereMaterial(sphereMat) {};
	Sphere(vec3 cen, float r, Material* sphereMat, bool texRect) : center(cen), radius(r), sphereMaterial(sphereMat), isTexRect(texRect) {};

	//vec3* intersect(Ray& a_Ray);
	bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;
	void getSphereUV(const vec3& p, float& u, float& v) const;
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

			getSphereUV((rec.p - center) / radius, rec.u, rec.v);
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
			
			getSphereUV((rec.p - center) / radius, rec.u, rec.v);
			return true;
		}
	}

	return false;
}

void Sphere::getSphereUV(const vec3& p, float& u, float& v) const
{
	if (isTexRect)
	{
		u = (p.z() + 1) / 2;
		v = (p.y() + 1) / 2;
	}
	else
	{
		float phi = atan2(p.z(), p.x());
		float theta = asin(p.y());
		u = 1 - (phi + 3.1415) / (2 * 3.1415);
		v = (theta + 3.1415 / 2) / 3.1415;
	}
}

