#pragma once
#include "Material.h"
class Lambertian : public Material
{
public:
	vec3 albedo;

	Lambertian(const vec3& a) : albedo(a){}
	virtual bool scatter(const Ray& r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const
	{
		vec3 target = rec.p + rec.normal; //+ randomInUnitSphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};

