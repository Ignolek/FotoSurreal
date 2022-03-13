#pragma once
#include "Vector.h"
#include "Ray.h"

class Sphere
{
private:
	Vector coords;
	float radius;
public:
	Sphere();
	Sphere(Vector coordinates, float r);

	float* intersect(Ray& a_Ray, float& a_Dist);
};

