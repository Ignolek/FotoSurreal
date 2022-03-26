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

	Vector* intersect(Ray& a_Ray);
};

