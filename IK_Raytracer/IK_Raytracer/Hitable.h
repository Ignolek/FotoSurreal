#ifndef HITABLEH
#define HITABLEH
#include "Ray.h"

class Material;

struct hitRecord
{
	float t;
	vec3 p;
	vec3 normal;
	vec3 hitColor;
	Material* materialPtr = nullptr;
};

class Hitable 
{
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};
#endif // !HITABLEH
