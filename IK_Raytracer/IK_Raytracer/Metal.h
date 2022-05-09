#pragma once
#include "Material.h"
class Metal : public Material
{
public:
	vec3 albedo;
	float fuzz;
	Metal(const vec3& a, float f) : albedo(a)
	{
		if (f < 1.0f)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1;
		}
	}
	virtual bool scatter(const Ray& r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * randomInUnitSphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 reflect(const vec3& v, const vec3& n) const
	{
		return v - 2 * dot(v, n) * n;
	}
};

