#pragma once
#include "vec3.h"

class Light
{
public:
	Light() {};
	vec3 location;
	vec3 direction;
	vec3 sourceColor;

	virtual vec3 getDiffuse(vec3 cameraPosition, vec3 intersectLocation) { return vec3(); };
	virtual vec3 getSpecular(vec3 cameraPosition, bool intersect) { return vec3(); };


};

