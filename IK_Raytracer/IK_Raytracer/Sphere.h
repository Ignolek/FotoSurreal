#pragma once
#include "vec3.h"
#include "Ray.h"

class Sphere
{
private:
	vec3 coords;
	float radius;
public:
	Sphere();
	Sphere(vec3 coordinates, float r);

	//vec3* intersect(Ray& a_Ray);
	bool hitRay(Ray& ray);
};

