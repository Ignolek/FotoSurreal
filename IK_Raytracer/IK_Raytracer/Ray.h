#pragma once
#include "vec3.h"
class Ray
{
public:
	Ray(){}
	Ray(const vec3& a, const vec3& b);
	vec3 origin() const;
	vec3 direction() const;
	vec3 pointAtParameter(float t) const;

	vec3 A;
	vec3 B;
};

