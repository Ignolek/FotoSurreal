#pragma once
#include "Hitable.h"
class Material
{
public:
	virtual bool scatter(const Ray& r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
};

