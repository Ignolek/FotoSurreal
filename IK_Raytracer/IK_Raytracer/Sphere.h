#pragma once
#include "Vector.h"
#include "Ray.h"

class Sphere
{
private:
	Vector coords;
	float r;
public:
	Sphere();
	Sphere(Vector coordinates, float r);

	int intersect(Ray& a_Ray, float& a_Dist);
};

