#pragma once
#include "Vector.h"
class Ray
{
	Vector origin, direction, destination;
	float distance = 0;

public:
	Ray();
	Ray(Vector o, Vector d);
	~Ray();
};

