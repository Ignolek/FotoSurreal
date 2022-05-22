#ifndef HITABLEH
#define HITABLEH

#include "Ray.h"
#include "Material.h"

struct hitRecord
{
	float t;
	vec3 p;
	vec3 normal;
	Material* materialPtr;
	float u, v;
};

class Hitable 
{
public:
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};
#endif // !HITABLEH
